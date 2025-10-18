#pragma once
#include <Arduino.h>

// PÁGINAS HTML CON CSS MEJORADO

// ========== PÁGINA PRINCIPAL (MENÚ) ==========
const char PAGE_INDEX[] = R"====(HTTP/1.1 200 OK
Content-Type: text/html

<!DOCTYPE HTML>
<html>
<head>
<meta charset="utf-8">
<meta name="viewport" content="width=device-width, initial-scale=1">
<title>ESP32 Control Panel</title>
<style>
  * { margin: 0; padding: 0; box-sizing: border-box; }
  
  body { 
    font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif; 
    background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
    min-height: 100vh;
    display: flex;
    align-items: center;
    justify-content: center;
    color: #333;
  }
  
  .container { 
    background: rgba(255,255,255,0.95);
    backdrop-filter: blur(10px);
    border-radius: 20px;
    padding: 40px;
    box-shadow: 0 15px 35px rgba(0,0,0,0.1);
    text-align: center;
    min-width: 320px;
    max-width: 400px;
    border: 1px solid rgba(255,255,255,0.2);
  }
  
  h1 { 
    color: #2c3e50;
    margin-bottom: 30px;
    font-size: 2em;
    font-weight: 300;
    text-shadow: 0 2px 4px rgba(0,0,0,0.1);
  }
  
  .menu-item { 
    display: block; 
    margin: 20px 0; 
    padding: 18px 30px; 
    background: linear-gradient(45deg, #3498db, #2980b9);
    color: white; 
    text-decoration: none; 
    border-radius: 15px; 
    transition: all 0.3s ease;
    font-size: 1.1em;
    font-weight: 500;
    box-shadow: 0 5px 15px rgba(52,152,219,0.3);
    border: none;
    position: relative;
    overflow: hidden;
  }
  
  .menu-item:hover { 
    transform: translateY(-3px);
    box-shadow: 0 8px 25px rgba(52,152,219,0.4);
    background: linear-gradient(45deg, #2980b9, #3498db);
  }
  
  .menu-item:active {
    transform: translateY(0);
    box-shadow: 0 3px 10px rgba(52,152,219,0.3);
  }
  
  .info { 
    color: #7f8c8d; 
    font-size: 0.9em; 
    margin-top: 30px;
    font-style: italic;
  }
  
  .icon { 
    font-size: 1.5em; 
    margin-right: 10px;
    vertical-align: middle;
  }
</style>
</head>
<body>
<div class="container">
  <h1><span class="icon">🏠</span>ESP32 Control Panel</h1>
  <a href="/led" class="menu-item">
    <span class="icon">💡</span>Control de LED
  </a>
  <div class="info">
    <p>Sistema ESP32 - Servidor Web v2.0</p>
  </div>
</div>
</body>
</html>
)====";

// ========== PÁGINA DE CONTROL LED - INICIO ==========
const char PAGE_LED_START[] = R"====(HTTP/1.1 200 OK
Content-Type: text/html

<!DOCTYPE HTML>
<html>
<head>
<meta charset="utf-8">
<meta name="viewport" content="width=device-width, initial-scale=1">
<title>ESP32 - Control LED</title>
<style>
  * { margin: 0; padding: 0; box-sizing: border-box; }
  
  body { 
    font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif; 
    background: linear-gradient(135deg, #ff9a9e 0%, #fecfef 50%, #fecfef 100%);
    min-height: 100vh;
    display: flex;
    align-items: center;
    justify-content: center;
    color: #333;
  }
  
  .container { 
    background: rgba(255,255,255,0.95);
    backdrop-filter: blur(10px);
    border-radius: 20px;
    padding: 40px;
    box-shadow: 0 15px 35px rgba(0,0,0,0.1);
    text-align: center;
    min-width: 320px;
    max-width: 400px;
    border: 1px solid rgba(255,255,255,0.2);
  }
  
  h1 { 
    color: #2c3e50;
    margin-bottom: 30px;
    font-size: 2em;
    font-weight: 300;
    text-shadow: 0 2px 4px rgba(0,0,0,0.1);
  }
  
  .status { 
    font-size: 1.4em; 
    margin: 25px 0; 
    padding: 20px; 
    border-radius: 15px; 
    font-weight: 600;
    box-shadow: 0 5px 15px rgba(0,0,0,0.1);
    border: 2px solid;
    transition: all 0.3s ease;
  }
  
  .status-on { 
    background: linear-gradient(45deg, #2ecc71, #27ae60);
    color: white;
    border-color: #27ae60;
    animation: pulse-green 2s infinite;
  }
  
  .status-off { 
    background: linear-gradient(45deg, #e74c3c, #c0392b);
    color: white;
    border-color: #c0392b;
    animation: pulse-red 2s infinite;
  }
  
  @keyframes pulse-green {
    0%, 100% { box-shadow: 0 5px 15px rgba(46,204,113,0.3); }
    50% { box-shadow: 0 8px 25px rgba(46,204,113,0.5); }
  }
  
  @keyframes pulse-red {
    0%, 100% { box-shadow: 0 5px 15px rgba(231,76,60,0.3); }
    50% { box-shadow: 0 8px 25px rgba(231,76,60,0.5); }
  }
  
  .btn { 
    padding: 15px 30px; 
    margin: 10px; 
    border-radius: 15px; 
    text-decoration: none; 
    color: white; 
    display: inline-block; 
    transition: all 0.3s ease;
    font-size: 1.1em;
    font-weight: 500;
    border: none;
    min-width: 140px;
    position: relative;
    overflow: hidden;
  }
  
  .btn-on { 
    background: linear-gradient(45deg, #2ecc71, #27ae60);
    box-shadow: 0 5px 15px rgba(46,204,113,0.3);
  }
  
  .btn-on:hover { 
    transform: translateY(-3px);
    box-shadow: 0 8px 25px rgba(46,204,113,0.4);
  }
  
  .btn-off { 
    background: linear-gradient(45deg, #e74c3c, #c0392b);
    box-shadow: 0 5px 15px rgba(231,76,60,0.3);
  }
  
  .btn-off:hover { 
    transform: translateY(-3px);
    box-shadow: 0 8px 25px rgba(231,76,60,0.4);
  }
  
  .btn-home { 
    background: linear-gradient(45deg, #95a5a6, #7f8c8d);
    margin-top: 25px;
    box-shadow: 0 5px 15px rgba(149,165,166,0.3);
  }
  
  .btn-home:hover { 
    transform: translateY(-3px);
    box-shadow: 0 8px 25px rgba(149,165,166,0.4);
  }
  
  .btn:active {
    transform: translateY(0);
  }
  
  .controls {
    margin: 30px 0;
  }
  
  .icon { 
    font-size: 1.2em; 
    margin-right: 8px;
    vertical-align: middle;
  }
</style>
</head>
<body>
<div class="container">
  <h1><span class="icon">💡</span>Control de LED</h1>
)====";

// ========== PÁGINA DE CONTROL LED - FINAL ==========
const char PAGE_LED_END[] = R"====(
  <div class="controls">
    <a href="/" class="btn btn-home">
      <span class="icon">🏠</span>Volver al Menú
    </a>
  </div>
</div>
</body>
</html>
)====";

// NOTA: Entre PAGE_LED_START y PAGE_LED_END se inserta el estado y botones dinámicamente