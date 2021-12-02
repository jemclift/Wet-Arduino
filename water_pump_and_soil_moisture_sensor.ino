#define waterPumpPin 3
#define sensorPinPower 13
#define sensorPinRead A0

void setup() {
  // put your setup code here, to run once:
  pinMode(waterPumpPin, OUTPUT);
  pinMode(sensorPinPower, OUTPUT);
  digitalWrite(waterPumpPin, LOW);
  digitalWrite(sensorPinPower, LOW);

  Serial.begin(9600);
  
  


}

void loop() {
  int soilMoisturePercentage = readSoilMoisture();
  Serial.print("Water Moisture level: ");
  Serial.print(soilMoisturePercentage);
  Serial.println("%");
  if (soilMoisturePercentage < 50){
    activatePump();
  }
  delay(5000);
  
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
