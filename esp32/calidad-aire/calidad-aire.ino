#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "ESP32-Calidad-Aire";
const char* password = "12345678";

WebServer server(80);

void handleRoot() {

  String html = R"rawliteral(

<!DOCTYPE html>
<html>
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Calidad del aire</title>
  <style>
    body {
      font-family: Arial, sans-serif;
      background: #f2f2f2;
      text-align: center;
      margin: 0;
      padding: 30px;
    }
    .contenedor {
      max-width: 500px;
      margin: auto;
      background: white;
      padding: 25px;
      border-radius: 15px;
      box-shadow: 0 4px 15px rgba(0,0,0,0.15);
    }
    h1 {
      margin-bottom: 25px;
    }
    .dato {
      background: #eeeeee;
      margin: 12px 0;
      padding: 15px;
      border-radius: 10px;
    }
    .valor {
      font-size: 28px;
      font-weight: bold;
    }
  </style>
</head>
<body>
  <div class="contenedor">
    <h1>Calidad del aire</h1>
    <div class="dato">
      <div>PM2.5</div>
      <div class="valor">-- &microg;/m&sup3;</div>
    </div>
    <div class="dato">
      <div>PM10</div>
      <div class="valor">-- &microg;/m&sup3;</div>
    </div>
    <div class="dato">
      <div>Estado del filtro</div>
      <div class="valor">APAGADO</div>
    </div>
  </div>
</body>
</html>
)rawliteral";

  server.send(200, "text/html", html);
}

void setup() {

  Serial.begin(115200);

  // Crear nuestra propia red Wi-Fi
  WiFi.softAP(ssid, password);

  Serial.println();
  Serial.println("Red Wi-Fi creada");

  Serial.print("Nombre: ");
  Serial.println(ssid);

  Serial.print("IP del ESP32: ");
  Serial.println(WiFi.softAPIP());

  // Configurar página principal
  server.on("/", handleRoot);

  // Iniciar servidor web
  server.begin();

  Serial.println("Servidor web iniciado");
}

void loop() {

  server.handleClient();

}