#ifndef Service_h
#define Service_h
#endif

#include "Arduino.h"

class Service {
  public:
    static void initialization(int timeOffset);
    static long currentTime();
    static String networks();
    static String convertToIsoTime(long timeStamp);
    static String infoWiFi();
    static String disconnectWiFi();
    static String freeMemory();
    static void initializationBme();
    static void recordingData();
  private:
};
