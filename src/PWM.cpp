#include "PWM.h"

PWM::PWM(uint8_t pwmPin): pwmPin(pwmPin) {
    pinMode(pwmPin, OUTPUT);
    analogWrite(pwmPin, 0);
};

void PWM::setValue(uint8_t value) {    
    analogWrite(this->pwmPin, value);
}

void PWM::setDuty(uint8_t value) {    
    analogWrite(this->pwmPin, map(value, 0, 100, 0, 255));
}