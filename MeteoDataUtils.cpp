#include "MeteoDataUtils.h"

#include "AsyncJson.h"
#include "ArduinoJson.h"
#include "WiFi.h"
#include "Arduino.h"
#include "NTPClient.h"
#include "WiFiUdp.h"
#include "Wire.h"
#include "Adafruit_Sensor.h"
#include "Adafruit_BME280.h"

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);
Adafruit_BME280 bme;

int const bmeSda = 17;
int const bmeScl = 16;

void MeteoDataUtils::initializationBme() {
  Wire.begin(bmeSda, bmeScl);

  bool statusBme = bme.begin(0x76, &Wire);
  if (!statusBme) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
  }
}

AsyncJsonResponse * MeteoDataUtils::getInfo() {
  AsyncJsonResponse * response = new AsyncJsonResponse();
  JsonObject root = response->getRoot();

  root["heap"] = ESP.getFreeHeap();
  root["status"] = WiFi.status();
  root["ssid"] = WiFi.SSID();
  root["localIP"] = getwiFiLocalIP();

  response->setLength();

  return response;
}

AsyncJsonResponse * MeteoDataUtils::getNetworks() {
  AsyncJsonResponse * response = new AsyncJsonResponse();
  JsonObject root = response->getRoot();
  int count = WiFi.scanComplete();

  if (count == -2) {
    WiFi.scanNetworks(true);
  } else if (count) {
    for (int i = 0; i < count; ++i) {
      root[WiFi.SSID(i)] = WiFi.RSSI(i);
    }
    WiFi.scanDelete();
    if (WiFi.scanComplete() == -2) {
      WiFi.scanNetworks(true);
    }
  }

  response->setLength();

  return response;


  //  String json;
  //  DynamicJsonDocument doc(2048);
  //  JsonArray data = doc.createNestedArray("networks");
  //  int count = WiFi.scanComplete();
  //
  //  if (count == -2) {
  //    WiFi.scanNetworks(true);
  //  } else if (count) {
  //    for (int i = 0; i < count; ++i) {
  //      data.add(WiFi.SSID(i));
  //    }
  //    WiFi.scanDelete();
  //    if (WiFi.scanComplete() == -2) {
  //      WiFi.scanNetworks(true);
  //    }
  //  }
  //
  //  serializeJson(doc, json);
  //
  //  return json;
}

String MeteoDataUtils::getwiFiLocalIP() {
  char wiFiLocalIP[16];

  sprintf(wiFiLocalIP, "%d.%d.%d.%d", WiFi.localIP()[0], WiFi.localIP()[1], WiFi.localIP()[2], WiFi.localIP()[3]);

  return wiFiLocalIP;
}

void MeteoDataUtils::recordingData() {
  //  Serial.print("Temperature from BME2 = ");
  //  Serial.print(bme.readTemperature());
  //  Serial.println(" *C");
  //
  //  Serial.print("Humidity from BME2 = ");
  //  Serial.print(bme.readHumidity());
  //  Serial.println(" %");
  //
  //  Serial.print("Pressure from BME2 = ");
  //  Serial.print(bme.readPressure() / 100.0F);
  //  Serial.println(" hPa");
}

void MeteoDataUtils::initialization(int timeOffset) {
  timeClient.begin();
  timeClient.setTimeOffset(timeOffset);
}

long MeteoDataUtils::currentTime() {
  timeClient.update();

  return timeClient.getEpochTime();
}

String MeteoDataUtils::convertToIsoTime(long timeStamp) {
  time_t rawtime = timeStamp;
  struct tm * ti;
  ti = localtime(&rawtime);

  uint16_t year = ti->tm_year + 1900;
  String yearStr = String(year);

  uint8_t month = ti->tm_mon + 1;
  String monthStr = month < 10 ? "0" + String(month) : String(month);

  uint8_t day = ti->tm_mday;
  String dayStr = day < 10 ? "0" + String(day) : String(day);

  uint8_t hours = ti->tm_hour;
  String hoursStr = hours < 10 ? "0" + String(hours) : String(hours);

  uint8_t minutes = ti->tm_min;
  String minuteStr = minutes < 10 ? "0" + String(minutes) : String(minutes);

  uint8_t seconds = ti->tm_sec;
  String secondStr = seconds < 10 ? "0" + String(seconds) : String(seconds);

  return yearStr + "-" + monthStr + "-" + dayStr + " " +
         hoursStr + ":" + minuteStr + ":" + secondStr;
}

String MeteoDataUtils::disconnectWiFi() {
  DynamicJsonDocument doc(32);
  String json;

  if (WiFi.disconnect()) {
    doc["disconnectWiFi"] = "success";
  } else {
    doc["disconnectWiFi"] = "fail";
  };

  serializeJson(doc, json);

  return json;
}

//String Model::authorization(String ssid, String password) {
//  WiFi.begin(ssid, password);
//
//  return "connection";
//}
