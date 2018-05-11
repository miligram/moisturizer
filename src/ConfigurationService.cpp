#include "ConfigurationService.h"
#include "MoistureSensorConfig.h"
#include <FS.h>

ConfigurationService::ConfigurationService(String configFilename) {
    this->configFilename = configFilename;    
}

Configuration* ConfigurationService::getConfiguration() {
    return &this->configuration;
}

bool ConfigurationService::exists() {
    return SPIFFS.exists(this->configFilename);
}

void ConfigurationService::load() {
    StaticJsonBuffer<2048> staticJsonBuffer;
    
    File file = SPIFFS.open(this->configFilename, "r");

    if (file != 0) {
        JsonObject& root = staticJsonBuffer.parse(file);

        if (!root.success()) {
            Serial.println(F("Failed to read file, using default configuration"));
        }
  
        strlcpy(this->configuration.ssid, root["ssid"], sizeof(this->configuration.ssid));
        strlcpy(this->configuration.password, root["password"], sizeof(this->configuration.password));
        
        this->configuration.relayPin = root["relayPin"];

        this->configuration.moistureSensorsCount = root["moistureSensorsCount"];
        this->configuration.moistureSensors = new MoistureSensorConfig[this->configuration.moistureSensorsCount];

        for (uint8_t i = 0; i < this->configuration.moistureSensorsCount; i++) {
            JsonObject &sensor = root["moistureSensors"][i].as<JsonObject>();
            this->configuration.moistureSensors[i].min = sensor["min"];
            this->configuration.moistureSensors[i].max = sensor["max"];
            this->configuration.moistureSensors[i].sensorPowerPin = sensor["sensorPowerPin"];
            this->configuration.moistureSensors[i].sensorReadPin = sensor["sensorReadPin"];
            this->configuration.moistureSensors[i].threshold = sensor["threshold"];
        }

        file.close();
    }    
}

void ConfigurationService::save() {
    SPIFFS.begin();

    File file = SPIFFS.open(this->configFilename, "w");

    if (!file) {
        Serial.print(F("Failed to create file "));
        Serial.println(this->configFilename);
        return;
    }

    StaticJsonBuffer<2048> jsonBuffer;
    JsonObject &root = jsonBuffer.createObject();
    
    root["ssid"] = this->configuration.ssid;
    root["password"] = this->configuration.password;
    root["relayPin"] = this->configuration.relayPin;
    
     JsonArray& moistureSensors = root.createNestedArray("moistureSensors");
    
     for (uint8_t i = 0; i < this->configuration.moistureSensorsCount; i++) { 
         JsonObject &sensor = moistureSensors.createNestedObject();
        
         sensor["min"] = this->configuration.moistureSensors[i].min;
         sensor["max"] = this->configuration.moistureSensors[i].max;
         sensor["sensorPowerPin"] = this->configuration.moistureSensors[i].sensorPowerPin;
         sensor["sensorReadPin"] = this->configuration.moistureSensors[i].sensorReadPin;
         sensor["threshold"] = this->configuration.moistureSensors[i].threshold;         
    }
    
    if (root.printTo(file) == 0) {
        Serial.println(F("Failed to write to file"));
    }
    
    file.close();
}

void ConfigurationService::printConfiguration() {
    SPIFFS.begin();

    File file = SPIFFS.open(this->configFilename, "r");
    
    if (!file) {
        Serial.println(F("Failed to read file"));
        return;
    }

    while (file.available()) {
        Serial.print((char)file.read());
    }

    Serial.println();
    
    file.close();
}