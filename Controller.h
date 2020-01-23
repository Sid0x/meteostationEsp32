#include "Arduino.h"
#include "DataUtils.h"
#include "FlashUtils.h"

#ifndef Controller_h
#define Controller_h

class Controller {
  public:
    void initialization(int timeOffset);
    static long currentTime();
  private:
    void initializationSoftAP();
    void initializationWifi();
    void mapping();
    char * espSsid;
    char * espPassword;
};

#endif
