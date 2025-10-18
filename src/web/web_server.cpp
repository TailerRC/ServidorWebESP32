#include "web_server.h"
#include "web_html.h"

namespace web {

// Variables estáticas del módulo
static WiFiServer *s_server = nullptr;
static int s_ledPin = -1;
static bool s_estado = false;

// Función simple para responder al cliente
void responderCliente(WiFiClient &cliente, const String &requestLine)
{
  // Determinar qué página enviar y si cambiar LED
  if (requestLine.indexOf("GET /led/encender") >= 0) {
    s_estado = true;
    if (s_ledPin >= 0) digitalWrite(s_ledPin, HIGH);
    
    // Enviar página LED con estilo CSS mejorado
    cliente.print(PAGE_LED_START);
    cliente.print("<div class='status status-on'>");
    cliente.print("<span class='icon'>🟢</span>LED ENCENDIDO");
    cliente.print("</div>");
    cliente.print("<div class='controls'>");
    cliente.print("<a href='/led/apagar' class='btn btn-off'>");
    cliente.print("<span class='icon'>⭕</span>Apagar LED</a>");
    cliente.print("<a href='/led/encender' class='btn btn-on'>");
    cliente.print("<span class='icon'>✅</span>Encender LED</a>");
    cliente.print("</div>");
    cliente.print(PAGE_LED_END);
  }
  else if (requestLine.indexOf("GET /led/apagar") >= 0) {
    s_estado = false;
    if (s_ledPin >= 0) digitalWrite(s_ledPin, LOW);
    
    // Enviar página LED con estilo CSS mejorado
    cliente.print(PAGE_LED_START);
    cliente.print("<div class='status status-off'>");
    cliente.print("<span class='icon'>🔴</span>LED APAGADO");
    cliente.print("</div>");
    cliente.print("<div class='controls'>");
    cliente.print("<a href='/led/apagar' class='btn btn-off'>");
    cliente.print("<span class='icon'>⭕</span>Apagar LED</a>");
    cliente.print("<a href='/led/encender' class='btn btn-on'>");
    cliente.print("<span class='icon'>✅</span>Encender LED</a>");
    cliente.print("</div>");
    cliente.print(PAGE_LED_END);
  }
  else if (requestLine.indexOf("GET /led") >= 0) {
    // Enviar página LED con estado actual
    cliente.print(PAGE_LED_START);
    
    if (s_estado) {
      cliente.print("<div class='status status-on'>");
      cliente.print("<span class='icon'>🟢</span>LED ENCENDIDO");
    } else {
      cliente.print("<div class='status status-off'>");
      cliente.print("<span class='icon'>🔴</span>LED APAGADO");
    }
    cliente.print("</div>");
    
    cliente.print("<div class='controls'>");
    cliente.print("<a href='/led/apagar' class='btn btn-off'>");
    cliente.print("<span class='icon'>⭕</span>Apagar LED</a>");
    cliente.print("<a href='/led/encender' class='btn btn-on'>");
    cliente.print("<span class='icon'>✅</span>Encender LED</a>");
    cliente.print("</div>");
    cliente.print(PAGE_LED_END);
  }
  else {
    // Mostrar menú principal
    cliente.print(PAGE_INDEX);
  }
}

// Inicializar el módulo web
void begin(WiFiServer &server, int ledPin)
{
  s_server = &server;
  s_ledPin = ledPin;
}

// Procesar clientes HTTP - versión simplificada
void handleClient()
{
  if (!s_server) return;

  WiFiClient cliente = s_server->available();
  if (!cliente) return;

  // Leer solo la primera línea (GET /ruta HTTP/1.1)
  String requestLine = "";
  unsigned long timeout = millis();
  
  while (cliente.connected() && (millis() - timeout < 1000)) {
    if (cliente.available()) {
      char c = cliente.read();
      if (c == '\n') {
        if (requestLine.length() > 0) {
          // Tenemos la primera línea, salir del bucle
          break;
        }
      }
      else if (c != '\r') {
        requestLine += c;
      }
    }
  }
  
  // Leer y descartar el resto de headers
  while (cliente.available()) {
    String line = cliente.readStringUntil('\n');
    if (line.length() <= 1) break; // Línea vacía = fin de headers
  }
  
  // Procesar y responder
  responderCliente(cliente, requestLine);
  
  cliente.stop();
}

} // namespace web
