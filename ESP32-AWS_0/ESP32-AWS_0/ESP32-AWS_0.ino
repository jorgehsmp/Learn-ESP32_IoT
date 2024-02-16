#include "Seeed_BME280.h"
#include <Wire.h>

BME280 bme280;

int t = 0;
int h = 0;
int p = 0;

void setup()
{
  Serial.begin(115200);

  if(!bme280.init()){
    Serial.println("Device error!");
  }
  pinMode(0, OUTPUT);

  connectWIFI();
}
 
void loop()
{

  t = bme280.getTemperature();
  h = bme280.getHumidity();
  p = bme280.getPressure();

  WIFI_Manager();
  delay(30000);
}