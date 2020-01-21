#include "Arduino.h"

#ifndef MeteoController_h
#define MeteoController_h

class MeteoController {
  public:
    void initialization();
  private:
    void initializationSoftAP();
    void initializationWifi();
    void mapping();
    char* espSsid;
    char* espPassword;
};

#endif
