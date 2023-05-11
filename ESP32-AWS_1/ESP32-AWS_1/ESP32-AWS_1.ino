#include "Seeed_BME280.h"
#include <Wire.h>
 
int t;
int h;
int p;

BME280 bme280;

void setup()
{
  Serial.begin(115200);
  connectWIFI();

  Serial.println("Iniciando BME280");
  if(!bme280.init()){
    Serial.println("BME280 error!");
  }
  else{
    Serial.println("BME280 iniciado!");
  }
}
 
void loop()
{
  t = bme280.getTemperature();      //Obtiene e imprime la temperatura
  Serial.println("Temperatura obtenida!");
  delay(250);
  p = bme280.getPressure();         //Obtiene e imprime la presión atmosférica
  Serial.println("Presión obtenida!");
  delay(250);
  h = bme280.getHumidity();         //Obtiene e imprime la humedad
  Serial.println("Humedad obtenida!");

  WIFI_Manager();
  delay(10000);
}