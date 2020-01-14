#ifndef Controller_h
#define Controller_h
#endif

#include "Arduino.h"

class Controller {
  public:
    static void initialization(const char* espSsid, const char* espPassword);
  private:
    static void initializationSoftAP();
    static void initializationWifi();
    static void mapping();
    char* espSsid;
    char* espPassword;
};
