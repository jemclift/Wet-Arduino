#include <Wire.h>
#define waterPumpPin 3
#define sensorPinPower 13
#define sensorPinRead A0
#define buttonPin 2
#define tempPin A1
#define lightSensorPin A2

float soilCheckDelay = 0.01; // minutes
unsigned long nextSoilCheck = 0;
float sensorCheckDelay = 1; // minutes
unsigned long nextSensorCheck = 0;
int numOfSoilReadings = 0; // This keeps track of the number of times the soil moisture has been checked.
int totalSoilMoisturePercentage = 0; //The soil percentage is added to this and then divided by the amount of checks.
int numOfSoilReadingsBeforeCheck = 10;

// readings
double temperature = 0;
int lightLevel = 0;
int soilMoisturePercentage = 0;


void setup() {
  // put your setup code here, to run once:
  pinMode(waterPumpPin, OUTPUT);
  pinMode(sensorPinPower, OUTPUT);
  pinMode(lightSensorPin, INPUT);
  digitalWrite(waterPumpPin, LOW);
  digitalWrite(sensorPinPower, LOW);

  Serial.begin(9600);
  Wire.begin();
  Wire.onRequest(sendToSlave);

}


void manualButtonPump(){
  int buttonState = HIGH;
  digitalWrite(waterPumpPin, HIGH);

  Serial.println("pump manually on");
  Serial.println(digitalRead(buttonPin));
  while (buttonState == HIGH){
    delay(10);
    buttonState = digitalRead(buttonPin);
  }
  digitalWrite(waterPumpPin, LOW);
}


void sendToSlave() {
  Wire.beginTransmission(A5);
  byte message[] = {(byte)temperature, lightLevel, soilMoisturePercentage};
  int message_length = 10;
  Wire.write(message, message_length);
  Wire.endTransmission();
}


void activatePump(){
  Serial.println("Water Pump Activated");
  digitalWrite(waterPumpPin, HIGH);
  delay(2000);
  digitalWrite(waterPumpPin, LOW);
}


int readLightSensor() {
  int lightReading = analogRead(lightSensorPin);
  return lightReading / 4;
}


// returns temp in degrees c
double readTemperatureSensor() {
  int sensorReading = analogRead(tempPin);
  // return ((double)sensorReading-102.4) * 125/256;
  double temp = (double)sensorReading / 1024;
  temp = temp * 5;
  temp = temp - 0.5;
  temp = temp * 100;
  return temp;
}


int readSoilMoisture(){
  digitalWrite(sensorPinPower, HIGH);
  delay(10);
  int val = analogRead(sensorPinRead);
  digitalWrite(sensorPinPower,LOW);
  val = map(val,1024,0,0,100);
  return val;
}


void loop() {
  unsigned long currentTime = millis();
  bool sendData = false;
  // water plant if it's too dry every soilCheckDelay mins
  if (currentTime > nextSoilCheck) {
    sendData = true;
    soilMoisturePercentage = readSoilMoisture();
    Serial.print("Water Moisture level: ");
    Serial.print(soilMoisturePercentage);
    Serial.println("%");
    totalSoilMoisturePercentage = soilMoisturePercentage + totalSoilMoisturePercentage;
    numOfSoilReadings +=1;
    if ((numOfSoilReadings % numOfSoilReadingsBeforeCheck == 0) and (numOfSoilReadings != 0)){
      int averageSoilMoisturePercentage = totalSoilMoisturePercentage / numOfSoilReadingsBeforeCheck;
      Serial.println("Check Soil Moisture Percentage");
      if (averageSoilMoisturePercentage < 50) {
        activatePump();
      }
    }
    nextSoilCheck = currentTime + (soilCheckDelay*60*1000);
  }
  // send temperature and light readings to other arduino
  if (currentTime > nextSensorCheck) {
    sendData = true;
    lightLevel = readLightSensor();
    temperature = readTemperatureSensor();

    nextSensorCheck = currentTime + (sensorCheckDelay*60*1000);
  }

  if (sendData){
    sendToSlave();
  }

  if (digitalRead(buttonPin) == HIGH){
    manualButtonPump();
  }

}
