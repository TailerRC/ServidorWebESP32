#pragma once
#include <Arduino.h>

// CONTENIDO HTML SEPARADO
// Contiene la respuesta HTTP completa: cabeceras + HTML
// Nota: Si el HTML crece mucho, considerar usar PROGMEM para ahorrar RAM

const char PAGE_MAIN[] = R"====(HTTP/1.1 200 OK
Content-Type: text/html

<!DOCTYPE HTML>
<html>
  <head>
    <meta charset=\"utf-8\">
    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">
    <title>ESP32 Control</title>
    <style>
      /* Estilos CSS embebidos para mejor apariencia */
      body { font-family: Arial, Helvetica, sans-serif; text-align:center; margin-top:30px; }
      a { text-decoration:none; color: white; background: #007bff; padding:10px 16px; border-radius:6px; }
    </style>
  </head>
  <body>
    <h1>Control de LED</h1>
)====";

// NOTA: El resto del HTML se genera dinámicamente en responderCliente()
// Esto incluye: IP del cliente, estado del LED, y botón de cambio