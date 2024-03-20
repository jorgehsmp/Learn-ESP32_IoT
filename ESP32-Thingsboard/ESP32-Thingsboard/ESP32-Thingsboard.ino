#define LED 15

float t;
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
  delay(250);
  p = random(9000,10000);
  delay(250);
  h = random(50,80);

  WIFI_Manager();
  delay(10000);
}