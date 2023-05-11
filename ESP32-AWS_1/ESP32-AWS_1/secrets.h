#include <pgmspace.h>
 
#define SECRET
#define THINGNAME "ESP32-IoT"                       //Debe coincidir con el nombre del objeto de AWS                    

const char DEVICE_ID[] = "e10480ef0a9d402f";
const char AWS_IOT_ENDPOINT[] = "****************";        //Se obtiene de AWS IoT Core - Configuracion  

const char WIFI_SSID[] = "JorgeWiFi";               //Cambiar 
const char WIFI_PASSWORD[] = "123456789";           //Cambiar 
 
// Amazon Root CA 1
static const char AWS_CERT_CA[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
****************
-----END CERTIFICATE-----
)EOF";
 
// Device Certificate                                               //Cambiar  
static const char AWS_CERT_CRT[] PROGMEM = R"KEY(
-----BEGIN CERTIFICATE-----
****************
-----END CERTIFICATE-----
)KEY";
 
// Device Private Key                                               //Cambiar  
static const char AWS_CERT_PRIVATE[] PROGMEM = R"KEY(
-----BEGIN RSA PRIVATE KEY-----
****************
-----END RSA PRIVATE KEY-----
)KEY";
