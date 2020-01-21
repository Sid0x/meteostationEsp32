#include "MeteoFlashUtils.h"
#include "MeteoController.h"
#include "DbUtils.h"
#include "MeteoDataUtils.h"

#include "SD.h"
//#include "SPIFFS.h"
#include "sqlite3.h"

const int flashCardsPin = 17;
//const bool formatSPIFFSifFailed = false;
const int timeOffset = 3600 * 2;
unsigned long previousMillis;
unsigned long dataTimer = 0;

MeteoController meteoController;

void setup() {
  Serial.begin(115200);

  //  MeteoFlashUtils::initializationSD(flashCardsPin);/
  //  MeteoFlashUtils::initializationESP(formatSPIFFSifFailed);
  meteoController.initialization();
  MeteoDataUtils::initialization(timeOffset);

  //  MeteoFlashUtils::deleteDb();
  //  MeteoFlashUtils::prepareDb();
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
