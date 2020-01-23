#include "FlashUtils.h"
#include "Controller.h"
#include "DataUtils.h"

#include "SD.h"
//#include "SPIFFS.h"
#include "sqlite3.h"

const int flashCardsPin = 17;
//const bool formatSPIFFSifFailed = false;
const int timeOffset = 3600 * 2;
unsigned long previousMillis;
unsigned long dataTimer = 0;

Controller controller;

void setup() {
  Serial.begin(115200);

  //  FlashUtils::initializationSD(flashCardsPin);/
  //  FlashUtils::initializationESP(formatSPIFFSifFailed);
  controller.initialization(timeOffset);

  //  FlashUtils::deleteDb();
  //  FlashUtils::prepareDb();
  //  DbUtils::checkDb();
}

void loop() {
  //  unsigned long currentMillis = millis();
  //
  //  if ((unsigned long)(currentMillis - previousMillis) >= dataTimer) {
  //
  //    previousMillis = currentMillis;
  //  }
}
