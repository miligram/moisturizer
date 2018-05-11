#ifndef PWM_h
#define PWM_h

#include <stdint.h>
#include <Arduino.h>

class PWM {
    private:        
        uint8_t pwmPin;        

    public:
        PWM(uint8_t);                
        void setValue(uint8_t);
        void setDuty(uint8_t);
};

#endif