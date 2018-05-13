#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiGeneric.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266WiFiScan.h>
#include <ESP8266WiFiSTA.h>
#include <ESP8266WiFiType.h>
#include <WiFiClient.h>
#include <WiFiClientSecure.h>
#include <WiFiServer.h>
#include <WiFiUdp.h>
#include "os_type.h"
#include "MoistureSensor.h"
#include "Relay.h"
#include "ConfigurationService.h"
#include <FS.h>

MoistureSensor* moistureSensor;
Relay* relay;
HTTPClient http;

void setupWifi(char* ssid, char* password) {
  WiFi.begin(ssid, password);
  Serial.setDebugOutput(true);
  Serial.print(F("Connecting: "));
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(F("."));
  }

  Serial.print(F("Connected, IP address: "));
  Serial.println(WiFi.localIP());
}

void setup() {
  SPIFFS.begin();
  Serial.begin(74880);
  
  //SPIFFS.format();

  printFsInfo();

  ConfigurationService configurationService("/config.json");
  Configuration* config = configurationService.getConfiguration();
  
  //if (fs_info.usedBytes == 0) {
    
  //}

  if (configurationService.exists()) {
    
    Serial.println(F("load configuration"));
    configurationService.load();    

    configurationService.printConfigurationFile(&Serial);
    configurationService.printConfiguration(&Serial);
  } else {
    Serial.println(F("save configuration"));

    strlcpy(config->ssid, "@cce$$_z0ne", sizeof(config->ssid));
    strlcpy(config->password, "06244248", sizeof(config->password));
    
    config->relayPin = D2;
    
    config->moistureSensorsCount = 1;
    config->moistureSensors = new MoistureSensorConfig[config->moistureSensorsCount];
    config->moistureSensors[0] = MoistureSensorConfig(0, 1024, D0, A0, 1024);
    
    configurationService.save();
    Serial.println(F("save configuration"));
    configurationService.printConfigurationFile(&Serial);
    configurationService.printConfiguration(&Serial);

    printFsInfo();
  }

  Serial.println(F("setupWifi();"));
  setupWifi(config->ssid, config->password);
  
  //Serial.println("MoistureSensor");
  //moistureSensor = new MoistureSensor(0, 1024, D0, A0, 1024);

  //Serial.println("Relay");
  //relay = new Relay(config->relayPin);

  //Serial.println("HTTP connection");
  //http.begin("http://pine.local:8086/write?db=moisture");  
}

void printFsInfo() {
  FSInfo fs_info;
  SPIFFS.info(fs_info);
  Serial.printf("usedBytes: %d\n\n", fs_info.usedBytes);  
}

void loop() {  
  // int soil = moistureSensor->read();
  // Serial.printf("MoistureSensor->read() = %d\n", soil);
  // int status;
  
  //status = http.POST("moisture value=" + String(soil)); 
  // Serial.printf("POST('moisture value = %d') : %d\n\n", soil, status);
  
  // delay(20);
  
  // if (soil < 200) {
    //status = http.POST("relay value=1");
    // Serial.printf("http.POST('relay value=1') : %d\n", status);
    //relay->on();
  // } else {
    //status = http.POST("relay value=0");
    // Serial.printf("http.POST('relay value=0') : %d\n\n", status);
    //relay->off();
  // }

  delay(5000);
}

