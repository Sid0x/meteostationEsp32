#include "Controller.h"

#include "ModuleUtils.h"
#include "WiFi.h"
#include "ESPAsyncWebServer.h"
#include "FlashUtils.h"
#include "DataUtils.h"
#include "SD.h"

AsyncWebServer server(80);
DataUtils dataUtils;
FlashUtils flashUtils;
ModuleUtils moduleUtils;

const char* ssid = "Sidox";
const char* password = "0636489803";

const char* espSsid = "ESP32";
const char* espPassword = "12345678";

void Controller::initialization (int timeOffset) {
  initializationSoftAP();
  initializationWifi();
  mapping();

  server.begin();

  moduleUtils.initialization(timeOffset);
}

void Controller::initializationSoftAP() {
  WiFi.softAP(espSsid, espPassword);

  Serial.print("SoftAP ip address: ");
  Serial.println(WiFi.softAPIP());
}

void Controller::initializationWifi() {
  WiFi.begin(ssid, password);

  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("WiFi Failed");
  } else {
    Serial.print("Local ip address: ");
    Serial.println(WiFi.localIP());
  }
}

void Controller::mapping() {
  server.onNotFound([](AsyncWebServerRequest * request) {
    request->send(404);
  });

  server.on("/getSdListDir", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(200, "application/json", flashUtils.listDir(SD, "/", 0));
  });

  server.on("/getNetworks", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(dataUtils.getNetworks());
  });

  server.on("/disconnect", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(WiFi.disconnect());
  });

  server.on("/getInfo", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(dataUtils.getInfo());
  });

  server.on("/restart", HTTP_GET, [](AsyncWebServerRequest * request) {
    ESP.restart();
    request->send(false);
  });
}
