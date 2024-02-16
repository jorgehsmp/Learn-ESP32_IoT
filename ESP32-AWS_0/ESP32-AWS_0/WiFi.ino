#include "secrets.h"
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include "WiFi.h"
 
#define AWS_IOT_PUBLISH_TOPIC   "esp32/pub"
#define AWS_IOT_SUBSCRIBE_TOPIC "esp32/sub"

WiFiClientSecure net = WiFiClientSecure();
PubSubClient client(net);

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

void connectAWS()
{
  if (wificonn_notpossible == false)
  {
    Serial.println("[SETUP] Conectando a AWS...");
  
    net.setCACert(AWS_CERT_CA);                                       // Configura WiFiClientSecure para usar las credenciales del "Thing" AWS IoT
    net.setCertificate(AWS_CERT_CRT);                                 //
    net.setPrivateKey(AWS_CERT_PRIVATE);                              //
  
    client.setServer(AWS_IOT_ENDPOINT, 8883);                         // Conecta con el broker MQTT del punto de enlade de AWS definido
    client.setCallback(messageHandler);                               // Crea una manejadora para gestionar mensajes recibidos
  
    Serial.println("[SETUP] Conectando a AWS IoT Core...");
  
    while (!client.connect(THINGNAME))
    {
      Serial.print(".");
      delay(100);
    }
  
    if (!client.connected())
    {
      Serial.println("Limite de tiempo sobrepasado!");
      return;
    }
  
    client.subscribe(AWS_IOT_SUBSCRIBE_TOPIC);                        // Subscribe a un tema
  
    Serial.println("AWS IoT Conectado!");
  }
}
 
void publishMessage()
{
  char jsonBuffer[512];
  StaticJsonDocument<200> doc;

  doc["ID"] = DEVICE_ID;
  doc["time"] = rtc.getEpoch();
  doc["temperature"] = t;
  doc["humidity"] = h;
  doc["pressure"] = p;
  
  serializeJson(doc, jsonBuffer); 

  client.publish(AWS_IOT_PUBLISH_TOPIC, jsonBuffer);                  // Publica el mensaje

  Serial.println("Publicando mensaje: ");
  Serial.println(jsonBuffer);
}
 
void messageHandler(char* topic, byte* payload, unsigned int length)
{
  Serial.print("Recibido mensaje del topic: ");
  Serial.println(topic);
 
  StaticJsonDocument<200> doc;
  deserializeJson(doc, payload);
  const char* message = doc["message"];
  Serial.println(message);
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
    Serial.println("Enviando datos...");

    connectAWS();
    publishMessage();
  }
  client.loop();
}