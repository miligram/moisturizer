#ifndef Relay_h
#define Relay_h


#include <stdint.h>
#include <Arduino.h>

class Relay {
    private:        
        uint8_t relayPin;        

    public:
        Relay(uint8_t);                
        void on();
        void off();
};

#endif