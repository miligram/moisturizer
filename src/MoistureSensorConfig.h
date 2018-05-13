#ifndef MoistureSensorConfig_h
#define MoistureSensorConfig_h

#include <stdint.h>
#include <Arduino.h>

struct MoistureSensorConfig {
    uint16_t min;
    uint16_t max;    
    uint8_t sensorPowerPin;
    uint8_t sensorReadPin;
    uint16_t threshold;        

    MoistureSensorConfig() {};

    MoistureSensorConfig(uint16_t min, uint16_t max, uint8_t sensorPowerPin, uint8_t sensorReadPin, uint16_t threshold): 
    min(min), max(max), sensorPowerPin(sensorPowerPin),sensorReadPin(sensorReadPin), threshold(threshold) {};
};

#endif