#include <Arduino.h>
#include <WiFi.h>
#include <WiFiMulti.h>


WiFiMulti wifiMulti;  // Permite conectar a múltiples redes WiFi
const uint32_t TiempoEsperaWifi = 5000; // Tiempo de espera entre intentos (ms)

void ActualizarWifi() {
  if (wifiMulti.run(TiempoEsperaWifi) != WL_CONNECTED) {
    Serial.println("❌ No conectado a WiFi, reintentando...");
  }
}

void setup() {
  Serial.begin(115200);
  Serial.println("\n🚀 Iniciando conexión WiFi múltiple...");

  // 🔧 Agrega las redes WiFi disponibles
  wifiMulti.addAP("Rodrigo", "12345678");
  //wifiMulti.addAP("ssid_2", "contrasenna_2");
  //wifiMulti.addAP("ssid_3", "contrasenna_3");

  WiFi.mode(WIFI_STA);
  Serial.print("Conectando a WiFi ");
  while (wifiMulti.run(TiempoEsperaWifi) != WL_CONNECTED) {
    Serial.print(".");
  }

  Serial.println("\n✅ Conectado correctamente");
  Serial.print("📶 SSID: ");
  Serial.println(WiFi.SSID());
  Serial.print("🌍 IP local: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  ActualizarWifi();

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("📡 Código ejecutándose con conexión WiFi");
  } else {
    Serial.println("⚠️ Código ejecutándose sin conexión WiFi");
  }

  delay(1000);
}

