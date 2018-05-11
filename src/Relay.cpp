#include "Relay.h"

Relay::Relay(uint8_t relayPin): relayPin(relayPin) {
    pinMode(relayPin, OUTPUT);
    digitalWrite(relayPin, LOW);
};

void Relay::on() {    
    digitalWrite(this->relayPin, HIGH);
}

void Relay::off() {    
    digitalWrite(this->relayPin, LOW);    
}