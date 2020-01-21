#include "MeteoController.h"
#include "MeteoDataUtils.h"

#include "WiFi.h"
#include "ESPAsyncWebServer.h"
#include "MeteoFlashUtils.h"
#include "MeteoDataUtils.h"
#include "SD.h"

AsyncWebServer server(80);
MeteoDataUtils meteoDataUtils;

const char* ssid = "Sidox";
const char* password = "0636489803";

const char* espSsid = "ESP32";
const char* espPassword = "12345678";

void MeteoController::initialization () {
  initializationSoftAP();
  initializationWifi();

  mapping();

  server.begin();
}

void MeteoController::initializationSoftAP() {
  WiFi.softAP(espSsid, espPassword);

  Serial.print("SoftAP ip address: ");
  Serial.println(WiFi.softAPIP());
}

void MeteoController::initializationWifi() {
  WiFi.begin(ssid, password);

  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("WiFi Failed");
  } else {
    Serial.print("Local ip address: ");
    Serial.println(WiFi.localIP());
  }
}

void MeteoController::mapping() {
  server.onNotFound([](AsyncWebServerRequest * request) {
    request->send(404);
  });

  server.on("/getSdListDir", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(200, "application/json", MeteoFlashUtils::listDir(SD, "/", 0));
  });

  server.on("/getNetworks", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(meteoDataUtils.getNetworks());
  });

  server.on("/disconnectWiFi", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(200, "application/json", MeteoDataUtils::disconnectWiFi());
  });

  server.on("/getInfo", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(meteoDataUtils.getInfo());
  });

}
