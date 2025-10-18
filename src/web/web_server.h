#pragma once                    // Evita inclusiones múltiples del mismo header
#include <Arduino.h>
#include <WiFi.h>

// MÓDULO WEB SEPARADO
// Maneja todas las peticiones HTTP y control del LED de forma independiente
// Permite mantener main.cpp limpio y organizado
//
// API de uso:
//   web::begin(WiFiServer& server, int ledPin);  // Inicializar módulo
//   web::handleClient();                         // Procesar clientes (llamar en loop)

namespace web {

// Inicializar el módulo web con el servidor y pin del LED
void begin(WiFiServer &server, int ledPin);

// Manejar peticiones HTTP entrantes (no bloquea si no hay clientes)
void handleClient();

}
