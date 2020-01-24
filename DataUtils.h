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
  private:
    String getLocalIP();
};

#endif
