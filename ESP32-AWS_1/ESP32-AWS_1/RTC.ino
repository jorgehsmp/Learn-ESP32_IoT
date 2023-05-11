#include <ESP32Time.h>

ESP32Time rtc;

const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 2*3600;
const int   daylightOffset_sec = 0;
unsigned long tiempo = 0;

struct tm timeinfo;

void RTCcompareHeatTimer ()
{
  unsigned long tiempo = rtc.getEpoch();
  Serial.println(tiempo);
}

void RTCsetTime()
{
  configTime (gmtOffset_sec, daylightOffset_sec, ntpServer);
  Serial.println("Configurando RTC...");
  if (getLocalTime(&timeinfo))
  {
    rtc.setTimeStruct(timeinfo);
  }
}