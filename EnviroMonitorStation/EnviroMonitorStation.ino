#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>

#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>
#include "Config.h"
#include "PMS3003.h"
#include "SmoglyHTU.h"

//set debug mode, use only in testing
#define DEBUG_MODE true
#define TIME_BETWEEN_METERINGS 2000

char apiEndpoint[130] = "";
char token[130] = "";

PMS3003 pms;
SmoglyHTU htu;

void setup() {
  Serial.begin(115200);
  Serial.println();

  Config config;
  config.mount();

  if (DEBUG_MODE) {
    config.reset();
  }

  config.read("/config.json");
  strcpy(apiEndpoint, config.apiEndpoint);
  strcpy(token, config.token);

  WiFiManagerParameter custom_apiEndpoint("apiEndpoint", "Smogly URL", apiEndpoint, 130);
  WiFiManagerParameter custom_token("token", "Token", token, 130);

  WiFiManager wifiManager;
  wifiManager.addParameter(&custom_apiEndpoint);
  wifiManager.addParameter(&custom_token);

  if (!wifiManager.autoConnect("Smogly Air Quality Monitor")) {
    Serial.println("Failed to connect and hit timeout");
    delay(3000);
    ESP.reset();
    delay(5000);
  }

  strcpy(apiEndpoint, custom_apiEndpoint.getValue());
  strcpy(token, custom_token.getValue());

  Serial.println("Successfully connected to WiFi network");

  config.save("/config.json");

  Serial.print("Local IP set to: ");
  Serial.println(WiFi.localIP());

  Serial.print("Initializing PMS...");
  pms.setup();
  Serial.println("Done");

  Serial.print("Initializing HTU...");
  htu.setup();
  Serial.println("Done");
  delay(TIME_BETWEEN_METERINGS);
}

void loop() {
  Serial.print("Performing measurement...");
  pms.read();
  const long pm25 = pms.getPM25();
  const long pm10 = pms.getPM10();
  Serial.print("PMS Done...");
  const float humidity = htu.readHumidity();
  const float temperature = htu.readTemperature();
  Serial.println("HTU Done");

  String output = createPayload(humidity, temperature, pm25, pm10);
  HTTPClient http;
  http.begin(apiEndpoint);
  http.addHeader("Content-Type", "application/json");
  http.POST(output);
  http.end();

  delay(TIME_BETWEEN_METERINGS);
}

String createPayload(float h, float t, long pm25, long pm10)
{
  StaticJsonBuffer<300> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  root["pm25"] = pm25;
  root["pm10"] = pm10;
  root["temperature"] = t;
  root["humidity"] = h;
  root["hw_id"] = "0";
  root["token"] = token;
  String output;
  root.printTo(output);
  Serial.println(output);
  return output;
}
