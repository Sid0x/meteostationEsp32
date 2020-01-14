#include "FlashUtils.h"
#include "Controller.h"
#include "Model.h"
#include "DbUtils.h"
#include "Service.h"

#include "SD.h"
//#include "SPIFFS.h"
#include "sqlite3.h"

const char* espSsid = "ESP32";
const char* espPassword = "12345678";

const int flashCardsPin = 17;
//const bool formatSPIFFSifFailed = false;
const int timeOffset = 3600 * 2;
unsigned long previousMillis;
unsigned long dataTimer = 0;

void setup() {
  Serial.begin(115200);
  Controller::initialization(espSsid, espPassword);
  initialization();
}

void loop() {
  unsigned long currentMillis = millis();

  if ((unsigned long)(currentMillis - previousMillis) >= dataTimer) {

    previousMillis = currentMillis;
  }
}

void initialization() {
  FlashUtils::initializationSD(flashCardsPin);
  //  FlashUtils::initializationESP(formatSPIFFSifFailed); 
  Controller::initialization(espSsid, espPassword);
  Service::initialization(timeOffset);

  //  FlashUtils::deleteDb();
  FlashUtils::prepareDb();
  DbUtils::checkDb();
}
