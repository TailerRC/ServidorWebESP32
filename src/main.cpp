#include <Arduino.h>
#include <WiFi.h>
#include <WiFiMulti.h>
#include "data.h"

int pinLed = 27;         // Pin del LED integrado en la placa ESP32
boolean Estado = false; // Estado actual del LED

unsigned long TiempoActual = 0;
unsigned long TiempoAnterior = 0;
const long TiempoCancelacion = 500; // Tiempo para cancelar la conexión (ms)

WiFiMulti wifiMulti;                    // Permite conectar a múltiples redes WiFi
const uint32_t TiempoEsperaWifi = 5000; // Tiempo de espera entre intentos (ms)
WiFiServer servidor(80);                // Crear un servidor WiFi en el puerto 80

// SECTION Funciones
void VerificarMensaje(String Mensaje)
{
  if (Mensaje.indexOf("GET /encender") >= 0)
  {
    Estado = true;
  }
  else if (Mensaje.indexOf("GET /apagar") >= 0)
  {
    Estado = false;
  }
}

void ResponderCliente(WiFiClient &cliente)
{
  cliente.print(Pagina);
  cliente.print("Hola");
  cliente.print(cliente.remoteIP());
  cliente.print("<br>Estado del led: ");
  cliente.print(Estado ? "Encendido" : "Apagado");
  cliente.print("<br>Cambia el led: ");
  cliente.print("<a href= '/");
  cliente.print(Estado ? "apagar" : "encender");
  cliente.print("'>Cambiar </a><br>");
  cliente.print("</html>");
}
//! SECTION

void setup()
{
  Serial.begin(115200);
  Serial.println("\n🚀 Iniciando conexión WiFi múltiple...");
  pinMode(pinLed, OUTPUT);
  // 🔧 Agrega las redes WiFi disponibles
  wifiMulti.addAP(ssid_1, password_1);
  wifiMulti.addAP(ssid_2, password_2);
  // wifiMulti.addAP("ssid_3", "contrasenna_3");

  WiFi.mode(WIFI_STA);
  Serial.print("Conectando a WiFi ");
  while (wifiMulti.run(TiempoEsperaWifi) != WL_CONNECTED)
  {
    Serial.print(".");
  }

  Serial.println("\n✅ Conectado correctamente");
  Serial.print("📶 SSID: ");
  Serial.println(WiFi.SSID());
  Serial.print("🌍 IP local: ");
  Serial.println(WiFi.localIP());

  servidor.begin();
}

void loop()
{
  WiFiClient cliente = servidor.available();
  if (cliente)
  {
    Serial.println("Nuevo cliente conectado");
    TiempoActual = millis();
    TiempoAnterior = TiempoActual;
    String LineaActual = "";

    while (cliente.connected() && TiempoActual - TiempoAnterior <= TiempoCancelacion)
    {
      if (cliente.available())
      {
        TiempoActual = millis();
        char Letra = cliente.read();
        if (Letra == '\n')
        {
          if (LineaActual.length() == 0)
          {
            digitalWrite(pinLed, Estado);
            ResponderCliente(cliente);
            break;
          }
          else
          {
            Serial.println(LineaActual);
            VerificarMensaje(LineaActual);
            LineaActual = "";
          }
        }
        else if (Letra != '\r')
        {
          LineaActual += Letra;
        }
      }
    }

    cliente.stop();
    Serial.println("Cliente desconectado");
    Serial.println();
  }
}
