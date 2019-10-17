#ifndef Config_h
#define Config_h

#include "Datastructure.h"

#include <Arduino.h>
#include <FS.h>
#include <ArduinoJson.h>

#define CONFIG_FILE "/config.json"

class Config {
  public:
    // Constructor(s)
    Config();

    bool load();
    bool save();

    servConfig config;
};

#endif
