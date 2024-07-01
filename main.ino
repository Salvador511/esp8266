#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

#include "config.h"  // Sustituir con datos de vuestra red
#include "API.hpp"
#include "ESP8266_Utils.hpp"

void setup() {
	Serial.begin(115200);
 	ConnectWiFi_STA();

  GetEndPointConnection();
  GetAll();
  String currentId = Post("1.39");
  Serial.println("current id:" + currentId);
  Get(currentId);
  Put(currentId, "2.3");
  Patch(currentId, "3.3");
  DeleteById(currentId);
}

void loop() {
}