#ifndef Configuration_h
#define Configuration_h

#include <stdint.h>
#include <Arduino.h>
#include <MoistureSensorConfig.h>

struct Configuration {
    char ssid[32];
    char password[16];
    uint8_t relayPin;
    uint8_t moistureSensorsCount;
    MoistureSensorConfig*  moistureSensors;
};

#endif