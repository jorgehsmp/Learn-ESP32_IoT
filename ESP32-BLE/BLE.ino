#include <BLEDevice.h>
#include <string.h>

#define B_DEBUG   
// The remote service we wish to connect to.
#define SERVICE_UUID              "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_WRITE_UUID  "beb5483e-36e1-4688-b7f5-ea07361b26a8"
#define CHARACTERISTIC_READ_UUID    "13b26b14-8bc1-11ee-b9d1-0242ac120002"
#define CHARACTERISTIC_NOTIFY_UUID    "1e2d3c18-8bc1-11ee-b9d1-0242ac120002"

BLECharacteristic* wCharacteristic = NULL;
BLECharacteristic* rCharacteristic = NULL;
BLECharacteristic* nCharacteristic = NULL;

bool blesetup = false;
bool blestop = false;

int value = 0;

unsigned long BleInitTime = 0;

class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
      deviceConnectedBLE = true;
      BLEDevice::startAdvertising();
      
      Serial.println("Servicio BLE conectado");
    };

    void onDisconnect(BLEServer* pServer) {
      deviceConnectedBLE = false;

      Serial.println("Servicio BLE desconectado");
    }
};

class WRITECallback: public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *wCharacteristic) {
      std::string value = wCharacteristic->getValue();

      Serial.print("Dato recibido: ");
      Serial.println(value.c_str());

      //Mandamos por notificación ese mensaje que ha llegado 
      nCharacteristic->setValue(value.c_str()); //Envia valor por caracteristica de notificación
      nCharacteristic->notify();
    }
};

void setupBLE()
{
  BLEDevice::init("ESP32-BLE");
  BLEServer *pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());
  
  BLEService *pService = pServer->createService(SERVICE_UUID);

  wCharacteristic = pService->createCharacteristic(
                                         CHARACTERISTIC_WRITE_UUID,
                                         BLECharacteristic::PROPERTY_WRITE
                                       );
  
  rCharacteristic = pService->createCharacteristic(
                                         CHARACTERISTIC_READ_UUID,
                                         BLECharacteristic::PROPERTY_READ
                                       );

  nCharacteristic = pService->createCharacteristic(
                                         CHARACTERISTIC_NOTIFY_UUID,
                                         BLECharacteristic::PROPERTY_NOTIFY
                                       );

  wCharacteristic->setCallbacks(new WRITECallback());

  pService->start();

  BLEAdvertising *pAdvertising = pServer->getAdvertising();
  pAdvertising->start();
}

void BLE_Manager ()
{
  if (!blesetup)
  {
    setupBLE();
    BleInitTime = millis();
    blesetup = true;
  }
  if (!blestop && ((millis() - BleInitTime) > BLE_MAX_TIME) && !deviceConnectedBLE)
  {
    BLEDevice::deinit(true);
    blestop = true;
  }
  else{
    if (deviceConnectedBLE) {
      
        rCharacteristic->setValue(value); //Envia valor por caracteristica de lectura
        value++;
        delay(100); 
    }
  }
}