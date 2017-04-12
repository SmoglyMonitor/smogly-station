#include "SmoglyHTU.h"
#include <Wire.h>
#include <Arduino.h>

#define HTU_ADDR         0x40
#define HTU_TRIGGER_TEMP 0xE3
#define HTU_TRIGGER_HUM  0xE5
#define HTU_READ_USER    0xE7
#define HTU_SOFT_RESET   0xFE

#define TIME_RESET 15
#define TIME_MEASURE 50

void SmoglyHTU::setup() {
  Wire.begin();
  Wire.beginTransmission(HTU_ADDR);
  Wire.write(HTU_SOFT_RESET);
  Wire.endTransmission();
  delay(TIME_RESET);
  Wire.beginTransmission(HTU_ADDR);
  Wire.write(HTU_READ_USER);
  Wire.endTransmission();
  Wire.requestFrom(HTU_ADDR, 1);
  Wire.read();
}

float SmoglyHTU::readHumidity() {
  Wire.beginTransmission(HTU_ADDR);
  Wire.write(HTU_TRIGGER_HUM);
  Wire.endTransmission();
  delay(TIME_MEASURE);
  Wire.requestFrom(HTU_ADDR, 3);
  while (!Wire.available()) {}

  const uint16_t h = Wire.read() << 8 | Wire.read();
  const uint8_t crc = Wire.read();
  return -6 + 125.0 * h / (1<<16);
}

float SmoglyHTU::readTemperature() {
  Wire.beginTransmission(HTU_ADDR);
  Wire.write(HTU_TRIGGER_TEMP);
  Wire.endTransmission();
  delay(TIME_MEASURE);
  Wire.requestFrom(HTU_ADDR, 3);
  while (!Wire.available()) {}

  const uint16_t t = Wire.read() << 8 | Wire.read();
  const uint8_t crc = Wire.read();
  return -46.85 + 175.72 * t / (1<<16);
}
