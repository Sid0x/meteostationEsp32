#include "MeteoController.h"

#include "WiFi.h"
#include "ESPAsyncWebServer.h"
#include "MeteoFlashUtils.h"
#include "MeteoDataUtils.h"
#include "SD.h"
#include "NTPClient.h"
#include "WiFiUdp.h"

AsyncWebServer server(80);
MeteoDataUtils dataUtils;
MeteoFlashUtils flashUtils;
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

const char* ssid = "Sidox";
const char* password = "0636489803";

const char* espSsid = "ESP32";
const char* espPassword = "12345678";

void MeteoController::initialization (int timeOffset) {
  initializationSoftAP();
  initializationWifi();
  mapping();

  server.begin();

  timeClient.begin();
  timeClient.setTimeOffset(timeOffset);

  dataUtils.initialization(timeClient);
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
    request->send(200, "application/json", flashUtils.listDir(SD, "/", 0));
  });

  server.on("/getNetworks", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(dataUtils.getNetworks());
  });

  server.on("/disconnectWiFi", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(dataUtils.disconnectWiFi());
  });

  server.on("/getInfo", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(dataUtils.getInfo());
  });

}
