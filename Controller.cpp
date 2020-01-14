#include "Controller.h"
#include "Service.h"

#include "WiFi.h"
#include "ESPAsyncWebServer.h"
#include "FlashUtils.h"
#include "SD.h"

AsyncWebServer server(80);

const char* ssid = "Sidox";
const char* password = "0636489803";

const char* espS;
const char* espP;

void Controller::initialization (const char* espSsid, const char* espPassword) {
  espS = espSsid;
  espP = espPassword;

  Controller::initializationSoftAP();
  Controller::initializationWifi();

  Controller::mapping();

  server.begin();
}

void Controller::initializationSoftAP() {
  WiFi.softAP(espS, espP);

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
    request->send(200, "application/json", FlashUtils::listDir(SD, "/", 0));
  });

  server.on("/getNetworks", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(200, "application/json", Service::networks());
  });

  server.on("/disconnectWiFi", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(200, "application/json", Service::disconnectWiFi());
  });

  server.on("/getInfoWiFi", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(200, "application/json", Service::infoWiFi());
  });

}
