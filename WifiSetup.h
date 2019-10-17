#ifndef WifiSetup_h
#define WifiSetup_h

#include "Datastructure.h"

#include <ESP8266WiFi.h>
#include <WiFiManager.h>
#include <ESP8266mDNS.h>

class WifiSetup {
  public:
    // Constructor(s)
    WifiSetup(config kobaConfig);

    void begin();
    bool hasConfigChanged();
    IPAddress getIp();
    config getConfig();

    static void saveConfigCallback();
    static bool shouldSaveConfig;
    
  private:
    config config;
};

#endif