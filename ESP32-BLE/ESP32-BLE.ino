#define BLE_MAX_TIME  30000

unsigned long runTime;
bool deviceConnectedBLE = false;

void setup()
{
  Serial.begin(115200);
  runTime = millis();         //Almacena el dato de tiempo actual (millis()) 
}
 
void loop()
{
  BLE_Manager();
  if( ((millis() - runTime) > BLE_MAX_TIME) && !deviceConnectedBLE) // Si han pasado 30seg (BLE_MAX_TIME) desde que se almacenó el tiempo en el setup Y el no existe conexión BLE...
  {
    // Hacer esto...
  }
}
