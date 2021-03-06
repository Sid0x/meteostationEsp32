#include "DataUtils.h"

#include "AsyncJson.h"
#include "ArduinoJson.h"
#include "WiFi.h"
#include "Arduino.h"

void DataUtils::initialization() {
}

AsyncJsonResponse * DataUtils::getInfo() {
  AsyncJsonResponse * response = new AsyncJsonResponse();
  JsonObject root = response->getRoot();

  root["heap"] = ESP.getFreeHeap();
  root["status"] = WiFi.status();
  root["ssid"] = WiFi.SSID();
  root["localIP"] = getLocalIP();

  response->setLength();

  return response;
}

AsyncJsonResponse * DataUtils::getNetworks() {
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
}

String DataUtils::getLocalIP() {
  char wiFiLocalIP[16];

  sprintf(wiFiLocalIP, "%d.%d.%d.%d", WiFi.localIP()[0], WiFi.localIP()[1], WiFi.localIP()[2], WiFi.localIP()[3]);

  return wiFiLocalIP;
}

String DataUtils::convertToIsoTime(long timeStamp) {
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

//String Model::authorization(String ssid, String password) {
//  WiFi.begin(ssid, password);
//
//  return "connection";
//}
