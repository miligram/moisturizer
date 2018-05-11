#ifndef MoistureSensor_h
#define MoistureSensor_h

#include <stdint.h>
#include <Arduino.h>

class MoistureSensor {
    private:
        uint16_t max;
        uint16_t min;
        uint8_t sensorPowerPin;
        uint8_t sensorReadPin;
        uint16_t threshold;

    public:        
        MoistureSensor(uint16_t, uint16_t, uint8_t, uint8_t, uint16_t);
        int read();
};

#endif