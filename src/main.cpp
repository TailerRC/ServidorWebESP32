// Librerías principales del ESP32
#include <Arduino.h>
#include <WiFi.h>
#include "data.h"           // Credenciales WiFi
#include "web/web_server.h" // Módulo web separado

// Configuración de hardware
int pinLed = 27;             // Pin del LED integrado en la placa ESP32
WiFiServer servidor(80);     // Servidor HTTP en puerto 80 (estándar web)

void setup()
{
  const uint32_t TiempoEsperaWifi = 5000; // Timeout: 10 segundos por red (20 intentos × 500ms)
  
  // Inicializar comunicación serial para debug
  Serial.begin(115200);
  Serial.println("\n🚀 Iniciando conexión WiFi secuencial...");
  
  // Configurar pin del LED como salida
  pinMode(pinLed, OUTPUT);
  
  // Configurar WiFi en modo estación (cliente, no punto de acceso)
  WiFi.mode(WIFI_STA);
  Serial.print("Conectando a WiFi ");

  // PASO 1: Intentar conectar a la primera red WiFi
  Serial.print("-> Intentando ");
  Serial.println(ssid_1);
  WiFi.begin(ssid_1, password_1);
  
  int intentos = 0;
  while (WiFi.status() != WL_CONNECTED && intentos < 20) {
    delay(500);          // Esperar medio segundo entre intentos
    Serial.print(".");   // Mostrar progreso visual
    intentos++;
  }
  
  // PASO 2: Si falló la primera, intentar la segunda red
  if (WiFi.status() != WL_CONNECTED) {
    Serial.print("\n-> Intentando ");
    Serial.println(ssid_2);
    WiFi.begin(ssid_2, password_2);
    
    intentos = 0;
    while (WiFi.status() != WL_CONNECTED && intentos < 20) {
      delay(500);        // Mismo timeout que la primera red
      Serial.print(".");
      intentos++;
    }
  }
  
  // Verificar si alguna red se conectó exitosamente
  bool conectado = (WiFi.status() == WL_CONNECTED);
  if (!conectado)
  {
    Serial.println("\n⚠️ No se pudo conectar a ninguna red configurada. Continuando sin WiFi.");
  }
  else
  {
    // Mostrar información de la conexión exitosa
    Serial.println("\n✅ Conectado correctamente");
    Serial.print("📶 SSID: ");
    Serial.println(WiFi.SSID());        // Nombre de la red conectada
    Serial.print("🌍 IP local: ");
    Serial.println(WiFi.localIP());     // Dirección IP asignada
  }

  // Inicializar servidor HTTP y módulo web
  servidor.begin();                     // Comenzar a escuchar en puerto 80
  web::begin(servidor, pinLed);         // Configurar módulo web con servidor y pin LED
}

void loop()
{
  // Bucle principal: delegar todo el manejo web al módulo separado
  web::handleClient();                  // Procesar peticiones HTTP entrantes
}
