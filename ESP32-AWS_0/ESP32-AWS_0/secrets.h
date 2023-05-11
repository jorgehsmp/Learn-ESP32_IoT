#include <pgmspace.h>
 
#define SECRET
#define THINGNAME "ESP32-IoT"                             //Cambiar                    

const char DEVICE_ID[] = "e10480ef0a9d402f";
const char AWS_IOT_ENDPOINT[] = "a2upmo4jsumq2m-ats.iot.eu-central-1.amazonaws.com";        //Cambiar  

const char WIFI_SSID[] = "JorgeWiFi";               //Cambiar 
const char WIFI_PASSWORD[] = "123456789";           //Cambiar 
 
// Amazon Root CA 1
static const char AWS_CERT_CA[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
MIIDQTCCAimgAwIBAgITBmyfz5m/jAo54vB4ikPmljZbyjANBgkqhkiG9w0BAQsF
ADA5MQswCQYDVQQGEwJVUzEPMA0GA1UEChMGQW1hem9uMRkwFwYDVQQDExBBbWF6
b24gUm9vdCBDQSAxMB4XDTE1MDUyNjAwMDAwMFoXDTM4MDExNzAwMDAwMFowOTEL
MAkGA1UEBhMCVVMxDzANBgNVBAoTBkFtYXpvbjEZMBcGA1UEAxMQQW1hem9uIFJv
b3QgQ0EgMTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALJ4gHHKeNXj
ca9HgFB0fW7Y14h29Jlo91ghYPl0hAEvrAIthtOgQ3pOsqTQNroBvo3bSMgHFzZM
9O6II8c+6zf1tRn4SWiw3te5djgdYZ6k/oI2peVKVuRF4fn9tBb6dNqcmzU5L/qw
IFAGbHrQgLKm+a/sRxmPUDgH3KKHOVj4utWp+UhnMJbulHheb4mjUcAwhmahRWa6
VOujw5H5SNz/0egwLX0tdHA114gk957EWW67c4cX8jJGKLhD+rcdqsq08p8kDi1L
93FcXmn/6pUCyziKrlA4b9v7LWIbxcceVOF34GfID5yHI9Y/QCB/IIDEgEw+OyQm
jgSubJrIqg0CAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMC
AYYwHQYDVR0OBBYEFIQYzIU07LwMlJQuCFmcx7IQTgoIMA0GCSqGSIb3DQEBCwUA
A4IBAQCY8jdaQZChGsV2USggNiMOruYou6r4lK5IpDB/G/wkjUu0yKGX9rbxenDI
U5PMCCjjmCXPI6T53iHTfIUJrU6adTrCC2qJeHZERxhlbI1Bjjt/msv0tadQ1wUs
N+gDS63pYaACbvXy8MWy7Vu33PqUXHeeE6V/Uq2V8viTO96LXFvKWlJbYK8U90vv
o/ufQJVtMVT8QtPHRh8jrdkPSHCa2XV4cdFyQzR1bldZwgJcJmApzyMZFo6IQ6XU
5MsI+yMRQ+hDKXJioaldXgjUkK642M4UwtBV8ob2xJNDd2ZhwLnoQdeXeGADbkpy
rqXRfboQnoZsG4q5WTP468SQvvG5
-----END CERTIFICATE-----
)EOF";
 
// Device Certificate                                               //Cambiar  
static const char AWS_CERT_CRT[] PROGMEM = R"KEY(
-----BEGIN CERTIFICATE-----
MIIDWjCCAkKgAwIBAgIVANgf9foOEbtlNhuwUB4N4e4nqURgMA0GCSqGSIb3DQEB
CwUAME0xSzBJBgNVBAsMQkFtYXpvbiBXZWIgU2VydmljZXMgTz1BbWF6b24uY29t
IEluYy4gTD1TZWF0dGxlIFNUPVdhc2hpbmd0b24gQz1VUzAeFw0yMzA1MTExMjAx
MTFaFw00OTEyMzEyMzU5NTlaMB4xHDAaBgNVBAMME0FXUyBJb1QgQ2VydGlmaWNh
dGUwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQCitTelG0Ef4NDahLWf
QxXUN52kUKQK4w96jbQfcFde8hgHTRikNl/txDNm6TX8cPplmUsrgOWxBI89ecOt
aqvPwHq9Zo3kflBV3LBmc4YZn3veqh1qX4i6ffyydPzC8UxwlNIlgd08AL63WNym
ij7ePZmZUUzgegHXWBiM7G6mMxQNnJWag6Yd6WIjg1ZtChRQ0E2Amr62rHmg/zK6
M0r4zscj18xEZtVnb5tFx1OPe4z6scU5rYCwEttETY3ShBMgy/svRaodV2Z6RcQx
D1ggStnKf0AwQ8dn/AAXBpN4bVn2NEPGcvTWlcmL2xdHAK8pwOIs2XV8yIljjDQL
ag4fAgMBAAGjYDBeMB8GA1UdIwQYMBaAFLJ2y6r/j/MQidkGV/jdfRyGjfkPMB0G
A1UdDgQWBBRCD9fyjDMp3SmRLNC8cMIs9BTqnTAMBgNVHRMBAf8EAjAAMA4GA1Ud
DwEB/wQEAwIHgDANBgkqhkiG9w0BAQsFAAOCAQEAl1NaZRq7jMIiW5QwVK9EGiLM
bYCcrmfTTiXJsseVXO3ELpfPAXZowZ3JYLe3s+qwa4ybjfoHC1JZxvdyGr+9YOPU
wTzqSnREkSu5SB3aZGDFIPVZjYzIfzfFeLsBU1oWnzkTBqtRlMRe06+k0qMnLl+O
rHZ93gO4An1TqsOsPou/2FpnNbODRQ3kflYbStyva25h7B/RS9gXcwJ2XqBD7fWO
hivjAisP6oY+dqucuI1abjIX1gE+9pMUQ00o3TJAKKLkUYSa6ie8840YLBTKtzkS
Eyy8skrIp4p8kMIkHuha2oD+/4lJ6QsRcX9smKuP8LhZ8QSjULLmwybdk00FZw==
-----END CERTIFICATE-----
)KEY";
 
// Device Private Key                                               //Cambiar  
static const char AWS_CERT_PRIVATE[] PROGMEM = R"KEY(
-----BEGIN RSA PRIVATE KEY-----
MIIEpAIBAAKCAQEAorU3pRtBH+DQ2oS1n0MV1DedpFCkCuMPeo20H3BXXvIYB00Y
pDZf7cQzZuk1/HD6ZZlLK4DlsQSPPXnDrWqrz8B6vWaN5H5QVdywZnOGGZ973qod
al+Iun38snT8wvFMcJTSJYHdPAC+t1jcpoo+3j2ZmVFM4HoB11gYjOxupjMUDZyV
moOmHeliI4NWbQoUUNBNgJq+tqx5oP8yujNK+M7HI9fMRGbVZ2+bRcdTj3uM+rHF
Oa2AsBLbRE2N0oQTIMv7L0WqHVdmekXEMQ9YIErZyn9AMEPHZ/wAFwaTeG1Z9jRD
xnL01pXJi9sXRwCvKcDiLNl1fMiJY4w0C2oOHwIDAQABAoIBAQCX+5BTwGaPwW81
ftssPfzI835kOxNQPBJ8VpsW9tgWDyuUvlYzJbtrnGarTVIpUNsERjGqHEfxlyG5
ueCnP0nn0JKWEpKeCcM+wNthh62Oh6OsNNkvQLe2A/MkOxTTf5P4YXr+oBSodMWw
++d4BRB+hanRRdj6odzQazDbigo9YWGWT8FvRLVR6x7h2GkgpszUVu5ZPK65rbFt
+efkYD7cnS02jGx1hijkZXYTLn1KW8rZwG4KRSbq15LZX3v3CQLw60myc76/HrWB
um/mW20KGwr9ba1FvAJYuYYoiun2ivzwth3gEXPJH74RirK/17/+n/NzVKM1/h8L
PGYHvHlZAoGBAM+gOnsyBqOMb0o69D+gcrS8gNtsiyW3IoL/LDH7sYRIpntZwo6p
NO2LV1ztUc9ei51pck1Qj+zmHzNa42iRM9ChyVsx4LKg4b+LTPh75n6znHGS6ExP
gS6e0kmZZfPn7kSjjhhG5P/JTQRZ5X9YxhgL/mCh1q6nUlxc5ZK1n1CLAoGBAMid
3spEZf2eV7YKdb418d/1C7e/SEHzmzrTrLKgSdFfkaRB6TwtHzx3++nrdgmBPJej
O50Vk3vPaUWGln8rxd67/SxmiWPIsmc/EBLMxNa941+67zdGaUfX1mta8WKZfvbU
gOYbrq01pj8LaGvqFjV8Pp90XrZYq3ga9uZNMjc9AoGAJKUkDUBcGZucvN5A48X+
2NV4bMHwoTx8c+BzvXKt9yoXcCf8hc9pjw+L4NPmH5KRU7wbt3ejn21STm8ZOgh+
u7ECZ/0aqoxoq7T7ZdQAb5Zl40nJhEZ4B3FyrhjL/MuPqz+uwawpmNe/pyfysJJL
jEz5nbaSvIq9p52hy04RC1cCgYEAl1OWSWactFlrehKbzDXu1GuIQjtUawMxtYcT
/s2vwPJg7tEU+OJkbH1pFYMaT4MfzJZBknVDAaJrmxkxjo3bPO76wzI5Mn6iLAVC
v5ucYwtrZrugVEaVha7Gu8YmzKRSRCf5bxm0gk00sNuPEc/Knt+wcSEbjFqIRRm5
4fCbD1UCgYBdGg4/r9Epl09soQfczbSWHSbl3NxcEb87x0+pcY36b+GSRzutY6FT
KactKxA9cTTPZFDenAgscfcfL0JmIH98HkQ3cZEmYt23vtvykF5DDBI5yqEgrg40
B60hJFnBW5EgS4ONguqgm05sGTkdnBYDzK+0NMpQgvaUmHxPHPewmw==
-----END RSA PRIVATE KEY-----
)KEY";
