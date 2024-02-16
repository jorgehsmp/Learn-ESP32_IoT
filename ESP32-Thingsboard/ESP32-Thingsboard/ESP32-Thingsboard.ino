#include "Seeed_BME280.h"
#include <Wire.h>

#define LED 0

float t;
int h;
int p;

BME280 bme280;

void setup()
{
  Serial.begin(115200);
  connectWIFI();
  setupMQTT();

  if(!bme280.init()){
    Serial.println("Device error!");
  }

  pinMode(LED, OUTPUT);
}
 
void loop()
{
  t = bme280.getTemperature();
  Serial.println("Temperatura obtenida!");
  delay(250);
  p = bme280.getPressure();
  Serial.println("Presión obtenida!");
  delay(250);
  h = bme280.getHumidity();
  Serial.println("Humedad obtenida!");

  WIFI_Manager();
  delay(10000);
}