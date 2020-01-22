#include "Arduino.h"
#include "AsyncJson.h"
#include "ArduinoJson.h"
#include "NTPClient.h"
#include "WiFiUdp.h"

#ifndef MeteoDataUtils_h
#define MeteoDataUtils_h

class MeteoDataUtils {
  public:
    AsyncJsonResponse * getInfo();
    void initialization(NTPClient & timeClient);
    long currentTime();
    AsyncJsonResponse * getNetworks();
    String convertToIsoTime(long timeStamp);
    AsyncJsonResponse * disconnectWiFi();
    void initializationBme();
    void recordingData();
  private:
    String getLocalIP();
//    NTPClient timeClient;
};

#endif
