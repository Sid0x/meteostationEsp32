#include "Arduino.h"
#include "AsyncJson.h"
#include "ArduinoJson.h"
#include "NTPClient.h"
#include "WiFiUdp.h"

#ifndef DataUtils_h
#define DataUtils_h

class DataUtils {
  public:
    AsyncJsonResponse * getInfo();
    void initialization();
    AsyncJsonResponse * getNetworks();
    String convertToIsoTime(long timeStamp);
    void initializationBme();
    void recordingData();
  private:
    String getLocalIP();
//    NTPClient timeClient;
};

#endif
