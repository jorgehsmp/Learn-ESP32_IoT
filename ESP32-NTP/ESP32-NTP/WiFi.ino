#include <WiFiClientSecure.h>
#include "WiFi.h"

WiFiClientSecure net = WiFiClientSecure();

const char WIFI_SSID[] = "JorgeWiFi";               //Cambiar 
const char WIFI_PASSWORD[] = "123456789";           //Cambiar 

bool wifisetup = false;
bool wificonn_notpossible = false;
bool pubfail = true;

void connectWIFI() 
{
  uint8_t n = 0;

  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  Serial.print("    - Conectando...");
  
  while (WiFi.status() != WL_CONNECTED)                               // Espera hasta conectar con la red WiFi
  {    
    Serial.print(".");
    delay(500);
    if (++n > 15) {
      Serial.println("[SETUP] Imposibe conectar... \n\n");
      wificonn_notpossible = true;
      return;
    }
  }
  Serial.print("[SETUP] Conectado a la red WiFi: ");
  Serial.println(WIFI_SSID);
  delay(250);
  RTCsetTime();
}

void WIFI_Manager ()
{
  if (WiFi.status() != WL_CONNECTED)
  {
    Serial.println("Conectando WiFi...");
   
    connectWIFI();
  }
  if (WiFi.status() == WL_CONNECTED)
  {
    Serial.println(rtc.getEpoch());
  }
}