
void setup()
{
  Serial.begin(115200);

  connectWIFI();
}
 
void loop()
{
  WIFI_Manager();
  delay(30000);
}