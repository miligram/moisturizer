#include "MoistureSensor.h"

MoistureSensor::MoistureSensor(uint16_t min, uint16_t max, uint8_t sensorPowerPin, uint8_t sensorReadPin, uint16_t threshold) : 
min(min), max(max), sensorPowerPin(sensorPowerPin), sensorReadPin(sensorReadPin), threshold(threshold) {
    pinMode(sensorPowerPin, OUTPUT);
    digitalWrite(sensorPowerPin, LOW);    
};

int MoistureSensor::read() {
    int readValue = 0;
    digitalWrite(this->sensorPowerPin, HIGH);
    delay(10);
    readValue = analogRead(this->sensorReadPin);
    digitalWrite(this->sensorPowerPin, LOW);        
    return this-> threshold - readValue;        
}