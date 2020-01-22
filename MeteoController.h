#include "Arduino.h"
#include "MeteoDataUtils.h"
#include "MeteoFlashUtils.h"

#ifndef MeteoController_h
#define MeteoController_h

class MeteoController {
  public:
    void initialization(int timeOffset);
  private:
    void initializationSoftAP();
    void initializationWifi();
    void mapping();
    char * espSsid;
    char * espPassword;
};

#endif
