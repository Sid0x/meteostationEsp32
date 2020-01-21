#include "Arduino.h"
#include "AsyncJson.h"
#include "ArduinoJson.h"

#ifndef MeteoDataUtils_h
#define MeteoDataUtils_h

class MeteoDataUtils {
  public:
    AsyncJsonResponse * getInfo();
    static void initialization(int timeOffset);
    static long currentTime();
    AsyncJsonResponse * getNetworks();
    static String convertToIsoTime(long timeStamp);
    static String disconnectWiFi();
    static void initializationBme();
    static void recordingData();
  private:
    String getwiFiLocalIP();
};

#endif
