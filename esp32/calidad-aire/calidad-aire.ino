#include <WiFi.h>
#include <WebServer.h>
#include "webpage.h"

const char* ssid = "ESP32-Calidad-Aire";
const char* password = "12345678";

WebServer server(80);

void handleRoot() {
  server.send_P(200, "text/html", index_html);
}

void setup() {

  Serial.begin(115200);

  WiFi.softAP(ssid, password);

  Serial.println();
  Serial.println("Red Wi-Fi creada");

  Serial.print("Nombre: ");
  Serial.println(ssid);

  Serial.print("IP del ESP32: ");
  Serial.println(WiFi.softAPIP());

  server.on("/", handleRoot);

  server.begin();

  Serial.println("Servidor web iniciado");
}

void loop() {
  server.handleClient();
}
