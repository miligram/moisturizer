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
        bool load();
        bool save();
        bool exists();
        void printConfiguration(Stream *stream);
        void printConfigurationFile(Stream *stream);
        Configuration* getConfiguration();
};

#endif