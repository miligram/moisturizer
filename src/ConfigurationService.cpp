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

bool ConfigurationService::load() {
    StaticJsonBuffer<2048> staticJsonBuffer;
    
    File file = SPIFFS.open(this->configFilename, "r");

    if (!file) {
        Serial.print(F("Failed to open file: "));
        Serial.println(this->configFilename);
        return false;
    }

    if (file != 0) {
        JsonObject& root = staticJsonBuffer.parse(file);

        if (!root.success()) {
            Serial.println(F("Failed to parse configuration file"));
            return false;
        }
  
        strlcpy(this->configuration.ssid, root["ssid"], sizeof(this->configuration.ssid));
        strlcpy(this->configuration.password, root["password"], sizeof(this->configuration.password));
        
        this->configuration.relayPin = root["relayPin"];
        this->configuration.moistureSensorsCount = root["moistureSensorsCount"];
        this->configuration.moistureSensors = new MoistureSensorConfig[this->configuration.moistureSensorsCount];

        for (uint8_t i = 0; i < this->configuration.moistureSensorsCount; i++) {
            JsonObject &sensor = root["moistureSensors"][i].as<JsonObject>();            
            this->configuration.moistureSensors[i] = MoistureSensorConfig(sensor["min"], sensor["max"], sensor["sensorPowerPin"], sensor["sensorReadPin"], sensor["threshold"]);            
        }

        file.close();
    }

    return true;    
}

bool ConfigurationService::save() {
    SPIFFS.begin();

    File file = SPIFFS.open(this->configFilename, "w");

    if (!file) {
        Serial.print(F("Failed to create file "));
        Serial.println(this->configFilename);
        return false;
    }

    StaticJsonBuffer<2048> jsonBuffer;
    JsonObject &root = jsonBuffer.createObject();
    
    root["ssid"] = this->configuration.ssid;
    root["password"] = this->configuration.password;
    root["relayPin"] = this->configuration.relayPin;
    root["moistureSensorsCount"] = this->configuration.moistureSensorsCount;
    
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
        return false;
    } 

    file.close();
    return true;
}

void ConfigurationService::printConfiguration(Stream *stream) {
    stream->printf("ssid: %s\n", this->configuration.ssid);
    stream->printf("password: %s\n", this->configuration.password);
    stream->printf("relayPin: %d\n", this->configuration.relayPin);

    for (uint8_t i = 0; i < this->configuration.moistureSensorsCount; i++) { 
        stream->printf("moistureSensors[%d]::min: %d\n", i, this->configuration.moistureSensors[0].min);
        stream->printf("moistureSensors[%d]::max: %d\n", i, this->configuration.moistureSensors[0].max);
        stream->printf("moistureSensors[%d]::sensorPowerPin: %d\n", i, this->configuration.moistureSensors[0].sensorPowerPin);
        stream->printf("moistureSensors[%d]::sensorReadPin: %d\n", i, this->configuration.moistureSensors[0].sensorReadPin);
        stream->printf("moistureSensors[%d]::threshold: %d\n", i, this->configuration.moistureSensors[0].threshold);
    }    
}

void ConfigurationService::printConfigurationFile(Stream *stream) {
    SPIFFS.begin();

    File file = SPIFFS.open(this->configFilename, "r");
    
    if (!file) {
        stream->println(F("Failed to read file"));
        return;
    }

    while (file.available()) {
        stream->print((char)file.read());
    }

    stream->println();
    
    file.close();
}