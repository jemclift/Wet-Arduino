#include <Wire.h>
#define waterPumpPin 3
#define sensorPinPower 13
#define sensorPinRead A0
#define buttonPin 2
#define tempPin A1
#define lightSensorPin A2

float soilCheckDelay = 30; // This specifies how often the soil should be checked
unsigned long nextSoilCheck = 0;
float sensorCheckDelay = 10; // This specifies how often the temperature, light and soil moisture Percentage should be updated and sent to the LCD on the slave Ardunio.
unsigned long nextSensorCheck = 0;

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
  // This function pumps water as long as the button is held down.
  int buttonState = HIGH;
  digitalWrite(waterPumpPin, HIGH);

  Serial.println("pump manually on");
  while (buttonState == HIGH){
    delay(10);
    buttonState = digitalRead(buttonPin);
  }
  digitalWrite(waterPumpPin, LOW);
}


void sendToSlave() {
  // This function sends the data recorded to the slave arudino so it can be shown on the screen.
  Wire.beginTransmission(A5);
  byte message[] = {(byte)temperature, lightLevel, soilMoisturePercentage};
  int message_length = 10;
  Wire.write(message, message_length);
  Wire.endTransmission();
}


void activatePump(){
  // This function activates the pump for 2 secs to pump a small amount of water into the plant.
  Serial.println("Water Pump Activated");
  digitalWrite(waterPumpPin, HIGH);
  unsigned long currentTime = millis();
  unsigned long pumpOnTime = currentTime + 2000;
  while (currentTime < pumpOnTime){
    currentTime = millis();
  }
  // delay(2000);
  digitalWrite(waterPumpPin, LOW);
}


int readLightSensor() {
  // This function returns a percentage value stating how much light the LDR is receiving.
  int lightReading = analogRead(lightSensorPin);
  return map(lightReading, 0, 1024, 0, 100);
}



double readTemperatureSensor() {
  // This function returns the temperature in degrees celcius.
  int sensorReading = analogRead(tempPin);
  double temp = (double)sensorReading / 1024;
  temp = temp * 5;
  temp = temp - 0.5;
  temp = temp * 100;
  return temp;
}


int readSoilMoisture(){
  // This function returns the percentage moisture of the soil.
  digitalWrite(sensorPinPower, HIGH);
  delay(10);
  int val = analogRead(sensorPinRead);
  digitalWrite(sensorPinPower,LOW);
  val = map(val,1024,0,0,100);
  return val;
}

void checkSoilMoisturePercentage(){
  // This function records the percentage moisture of the soil 10 times and then waters the plant if the value is less than 50%
  int numOfSoilReadings = 0;
  int numOfSoilReadingsBeforeCheck = 10; //This specifies the number of readings taken before the average reading is worked out.
  int totalSoilMoisturePercentage;
  int averageSoilMoisturePercentage;

  while (numOfSoilReadings < numOfSoilReadingsBeforeCheck){
    numOfSoilReadings +=1;
    // This retrieves the soil Moisture Percentage and prints it out to the serial.
    soilMoisturePercentage = readSoilMoisture();
    Serial.print("Water Moisture level: ");
    Serial.print(soilMoisturePercentage);
    Serial.println("%");

    totalSoilMoisturePercentage = soilMoisturePercentage + totalSoilMoisturePercentage;
    if (numOfSoilReadings == numOfSoilReadingsBeforeCheck){
      averageSoilMoisturePercentage = totalSoilMoisturePercentage / numOfSoilReadingsBeforeCheck;
      totalSoilMoisturePercentage = 0;

      // This part checks if the soil moisture is over 50%. If it isn't the plant will be water
      Serial.println("Check Soil Moisture Percentage");
      if (averageSoilMoisturePercentage < 50) {
        activatePump();
      }
    }
  }
}

void loop() {
  unsigned long currentTime = millis();
  bool sendData = false;

  // Checks to see if the plant should be watered and then works out at what time the plant should be checked again.
  if (currentTime > nextSoilCheck) {
    sendData = true;
    checkSoilMoisturePercentage();
    nextSoilCheck = currentTime + (soilCheckDelay*60*1000);
      }

  if (currentTime > nextSensorCheck) {
    // Gets new values from all of the sensors.
    sendData = true;
    lightLevel = readLightSensor();
    temperature = readTemperatureSensor();
    soilMoisturePercentage = readSoilMoisture();

    nextSensorCheck = currentTime + (sensorCheckDelay*60*1000);
  }

  // if the new values from the sensor have been calculated it will send these to the other arduino to be shown on the LCD.
  if (sendData){
    sendToSlave();
  }

  if (digitalRead(buttonPin) == HIGH){
    manualButtonPump();
  }

}
