#include <WiFi.h>
#include <WebServer.h>
#include "webpage.h"

HardwareSerial PMS(2);
WebServer server(80);

const char* ap_ssid = "AireMonitor";
const char* ap_password = "12345678"; // minimo 8 caracteres

uint16_t pm1 = 0, pm25 = 0, pm10 = 0;

void handleRoot() {
  server.send_P(200, "text/html", index_html);
}

void handleData() {
  String json = "{";
  json += "\"pm1\":" + String(pm1) + ",";
  json += "\"pm25\":" + String(pm25) + ",";
  json += "\"pm10\":" + String(pm10);
  json += "}";
  server.send(200, "application/json", json);
}

void leerPMS() {
  while (PMS.available() >= 32) {
    if (PMS.peek() != 0x42) {
      PMS.read();
      continue;
    }

    PMS.read(); // 0x42
    if (PMS.read() != 0x4D) continue;

    uint8_t data[30];
    for (int i = 0; i < 30; i++) data[i] = PMS.read();

    uint16_t checksum = (data[28] << 8) | data[29];
    uint16_t sum = 0x42 + 0x4D;
    for (int i = 0; i < 28; i++) sum += data[i];

    if (sum == checksum) {
      pm1  = (data[2] << 8) | data[3];
      pm25 = (data[4] << 8) | data[5];
      pm10 = (data[6] << 8) | data[7];
    }
  }
}

void setup() {
  Serial.begin(115200);
  PMS.begin(9600, SERIAL_8N1, 16, 17);

  WiFi.softAP(ap_ssid, ap_password);
  Serial.print("Access Point creado. IP: ");
  Serial.println(WiFi.softAPIP());

  server.on("/", handleRoot);
  server.on("/data", handleData);
  server.begin();

  Serial.println("Servidor web iniciado");
}

void loop() {
  leerPMS();
  server.handleClient();
}
