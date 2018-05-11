#ifndef ConfigurationService_h
#define ConfigurationService_h

#include <stdint.h>
#include <Arduino.h>
#include <ArduinoJson.h>
#include "configuration.h"

class ConfigurationService {
    private:
        String configFilename;
        Configuration configuration;

    public:        
        ConfigurationService(String);
        void load();
        void save();
        bool exists();
        void printConfiguration();
        Configuration* getConfiguration();
};

#endif