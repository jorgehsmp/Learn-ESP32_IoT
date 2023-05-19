
#define LED 0

int t;
int h;
int p;


void setup()
{
  Serial.begin(115200);
  connectWIFI();
  setupMQTT();

  pinMode(LED, OUTPUT);
}
 
void loop()
{
  t = random(20,30);
  Serial.println("Temperatura obtenida!");
  delay(250);
  p = random(1010,1020);
  Serial.println("Presión obtenida!");
  delay(250);
  h = random(20,80);
  Serial.println("Humedad obtenida!");

  WIFI_Manager();
  delay(10000);
}