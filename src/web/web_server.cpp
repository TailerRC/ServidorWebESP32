#include "web_server.h"
#include "web_html.h"

namespace web {

// Variables estáticas del módulo (privadas, solo accesibles dentro del namespace)
static WiFiServer *s_server = nullptr;  // Referencia al servidor HTTP
static int s_ledPin = -1;                // Pin del LED a controlar
static bool s_estado = false;            // Estado actual del LED (false=apagado, true=encendido)

// Analizar la petición HTTP para detectar comandos de control
void verificarMensaje(const String &mensaje)
{
  // Buscar rutas específicas en la línea de petición HTTP
  if (mensaje.indexOf("GET /encender") >= 0)  // URL: http://ip/encender
  {
    s_estado = true;                           // Cambiar estado a encendido
  }
  else if (mensaje.indexOf("GET /apagar") >= 0) // URL: http://ip/apagar
  {
    s_estado = false;                          // Cambiar estado a apagado
  }
}

// Generar y enviar la respuesta HTTP completa al cliente
void responderCliente(WiFiClient &cliente)
{
  // Enviar cabeceras HTTP y inicio de la página HTML
  cliente.print(PAGE_MAIN);
  
  // Información del cliente conectado
  cliente.print("<p>IP cliente: ");
  cliente.print(cliente.remoteIP());  // Mostrar IP de quien hizo la petición
  cliente.print("</p>");
  
  // Estado actual del LED
  cliente.print("<p>Estado del led: ");
  cliente.print(s_estado ? "Encendido" : "Apagado");
  cliente.print("</p>");
  
  // Botón dinámico: si está encendido muestra "Apagar", si está apagado muestra "Encender"
  cliente.print("<p>");
  cliente.print("<a href='/");
  cliente.print(s_estado ? "apagar" : "encender");  // URL dinámica
  cliente.print("'>Cambiar</a>");
  cliente.print("</p>");
  
  // Cerrar tags HTML
  cliente.print("</body></html>");
}

// Inicializar el módulo web (llamar una vez desde setup())
void begin(WiFiServer &server, int ledPin)
{
  s_server = &server;  // Guardar referencia al servidor HTTP
  s_ledPin = ledPin;   // Guardar pin del LED a controlar
}

// Procesar clientes HTTP entrantes (llamar repetidamente desde loop())
void handleClient()
{
  // Verificaciones de seguridad
  if (!s_server)       // Si no se inicializó el servidor
    return;

  WiFiClient cliente = s_server->available();  // Verificar si hay cliente esperando
  if (!cliente)        // Si no hay nadie conectado
    return;

  // Parsear la petición HTTP línea por línea (protocolo HTTP estándar)
  unsigned long tiempoActual = millis();
  unsigned long tiempoAnterior = tiempoActual;
  const unsigned long tiempoCancelacion = 500;  // Timeout: 500ms para leer petición completa
  String lineaActual = "";                      // Buffer para la línea actual

  // Leer petición HTTP completa con timeout
  while (cliente.connected() && (millis() - tiempoAnterior <= tiempoCancelacion))
  {
    if (cliente.available())  // Si hay datos para leer
    {
      tiempoAnterior = millis();           // Resetear timeout
      char letra = cliente.read();         // Leer un carácter
      
      if (letra == '\n')                   // Fin de línea HTTP
      {
        if (lineaActual.length() == 0)     // Línea vacía = fin de cabeceras HTTP
        {
          // PROCESAR: Aplicar cambio al LED y responder
          if (s_ledPin >= 0)               // Verificar que el pin sea válido
            digitalWrite(s_ledPin, s_estado);  // Aplicar nuevo estado al LED
          responderCliente(cliente);       // Enviar página HTML de respuesta
          break;                           // Terminar procesamiento
        }
        else
        {
          // Analizar la línea para comandos (GET /encender, GET /apagar, etc.)
          verificarMensaje(lineaActual);
          lineaActual = "";                // Limpiar buffer para próxima línea
        }
      }
      else if (letra != '\r')              // Ignorar caracteres de retorno de carro
      {
        lineaActual += letra;              // Agregar carácter al buffer
      }
    }
  }

  cliente.stop();                          // Cerrar conexión con el cliente
}

} // namespace web
