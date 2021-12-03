#include <Wire.h>
#define waterPumpPin 3
#define sensorPinPower 13
#define sensorPinRead A0

int soilCheckDelay = 60; // minutes
unsigned long nextSoilCheck = 0;
int sensorCheckDelay = 1; // minutes
unsigned long nextSensorCheck = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(waterPumpPin, OUTPUT);
  pinMode(sensorPinPower, OUTPUT);
  digitalWrite(waterPumpPin, LOW);
  digitalWrite(sensorPinPower, LOW);

  Serial.begin(9600);
  Wire.begin();
  Wire.onRequest(requestEvent);
}

void requestEvent() {
  Wire.beginTransmission(A5);
  Wire.write("hello ");
  Wire.endTransmission();
}

void activatePump(){
  Serial.println("Water Pump Activated");
  digitalWrite(waterPumpPin, HIGH);
  delay(2000);
  digitalWrite(waterPumpPin, LOW);
}

int readSoilMoisture(){
  digitalWrite(sensorPinPower, HIGH);
  delay(10);
  int val = analogRead(sensorPinRead);
  digitalWrite(sensorPinPower,LOW);
  val = map(val,1024,0,0,100);
  return val;
}

// int x = -1;

void loop() {
  unsigned long currentTime = millis();

  // water plant if it's too dry every soilCheckDelay mins
  if (currentTime > nextSoilCheck) {
    int soilMoisturePercentage = readSoilMoisture();
    Serial.print("Water Moisture level: ");
    Serial.print(soilMoisturePercentage);
    Serial.println("%");
    if (soilMoisturePercentage < 50) {
      activatePump();
    }
    nextSoilCheck = currentTime + (soilCheckDelay*60*1000);
  }

  // send temperature and light readings to other arduino
  if (currentTime > nextSensorCheck) {
    // TODO: check light and temp values and send to other arduino
    nextSensorCheck = currentTime + (sensorCheckDelay*60*1000);
  }

  // just to prove that it works
  // ------------
  // ++x %= 12;
  // if(x == 0){
  //   requestEvent();
  // }
  // ------------
}
