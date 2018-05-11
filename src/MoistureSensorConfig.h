#ifndef MoistureSensorConfig_h
#define MoistureSensorConfig_h

#include <stdint.h>
#include <Arduino.h>

struct MoistureSensorConfig {
    uint16_t max;
    uint16_t min;
    uint8_t sensorPowerPin;
    uint8_t sensorReadPin;
    uint16_t threshold;        
};

#endif