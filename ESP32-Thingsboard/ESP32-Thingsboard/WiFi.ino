#include "secrets.h"
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include "WiFi.h"
 
#define THINGSBOARD_PUBLISH_TOPIC   "v1/devices/me/telemetry"
#define THINGSBOARD_SUBSCRIBE_TOPIC "v1/devices/me/rpc/request/+"

WiFiClient wificlient;
PubSubClient mqtt(wificlient);

bool wifisetup = false;
bool wificonn_notpossible = false;
bool pubfail = true;

bool stateButton = false;

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
}

void setupMQTT() 
{
  if (wificonn_notpossible == false)
  {
    mqtt.setServer( thingsboardServer, 1883 );  // Activa las comunicacions con ese servidor
    mqtt.setCallback(MQTT_callback);            // Define la subrutina a ejecutar cuando se recivan datos del servidor
   MQTT_Reconect();                            // Subrutina que realiza la conexión en caso de ser necesaria
  }
}
 
void MQTT_Publish()
{
  char msg[512];
  StaticJsonDocument<200> doc;

  doc["ID"] = DEVICE_ID;
  doc["temperature"] = t;
  doc["humidity"] = h;
  doc["pressure"] = p;
  
  serializeJson(doc, msg); 

  mqtt.publish(THINGSBOARD_PUBLISH_TOPIC, msg);                  // Publica el mensaje

  Serial.println("Publicando mensaje: ");
  Serial.println(msg);
}

void MQTT_Reconect() 
{
  Serial.print("[MQTT] Attempting connection... ");

  if (mqtt.connect(DEVICE_ID, TB_TOKEN, NULL)) {   // Attempt to connect: objeto.connect("Unique Name", "USER", "PASSWORD")
    Serial.print("Connected with ID: "); Serial.println(DEVICE_ID);
    mqtt.subscribe(THINGSBOARD_SUBSCRIBE_TOPIC);// Se suscribe para recibir las peticiones de ThingsBoard
  } else {
    Serial.print("Connection failed, rc=");
    Serial.print(mqtt.state());                   // Si la conexión no se ha podido realizar, muestra el error
    Serial.println(" try again in 5 seconds");
  }
}
 
// The callback for when a PUBLISH message is received from the server.
void MQTT_callback(char* topic, byte* payload, unsigned int length)
{
  Serial.print("Recibido mensaje del topic: ");
  Serial.println(topic);

  Serial.println("Mensaje recibido desde ThingsBoard:");
  
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  
  Serial.println();

  StaticJsonDocument<200> doc;
  deserializeJson(doc, payload);
  bool button = doc["params"];
  
  if (button == true)
  {
    Serial.println("LED ENCENDIDO!");
    digitalWrite(LED, HIGH);
  }
  else{
    Serial.println("LED APAGADO!");
    digitalWrite(LED, LOW);
  }

}


void WIFI_Manager()
{
  if (WiFi.status() != WL_CONNECTED)
  {
    Serial.println("Conectando WiFi...");
   
    connectWIFI();
  }
  if (mqtt.connected())
  {
    Serial.println("Enviando datos...");
    MQTT_Publish();

  } 
  else {
    connectWIFI();
    MQTT_Reconect();                              // Si está conecatado... Intenta reconectar.
  }
  mqtt.loop();
}