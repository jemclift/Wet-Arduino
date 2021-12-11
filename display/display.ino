#include <LiquidCrystal.h>
#include <Wire.h>

// lcd
const int rs = 10, en = 9, d4 = 6, d5 = 5, d6 = 4, d7 = 3;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// other pins
const int btn_pin = 2, led_pin = 7, bzr_pin = 13;

bool dispayWarning = false;
unsigned long nextWarningFlash = 0;
int warningFlashDelay = 500; // milliseconds
bool warningFlashState = true;
int warningCode = 0;
bool canBeWarning[3] = {true, true, true};

// 0 - No Warning
// 1 - Too Dry
// 2 - Too Hot
// 3 - Too Cold

int temperature = 20;
int lightLevel = 0;
int moisture = 50;

byte degree[8] = {
  0b11100,
  0b10100,
  0b11100,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000
};

void setup() {
  lcd.begin(16, 2);
  lcd.createChar(0, degree);
  pinMode(led_pin, OUTPUT);
  pinMode(btn_pin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(btn_pin), buttonPress, FALLING);

  Wire.begin(A5);
  Wire.onReceive(receiveEvent);
}

void turnOffWarning() {
  dispayWarning = false;
  warningCode = 0;
  digitalWrite(led_pin, LOW);
}

void receiveEvent(int howMany) {
  temperature = Wire.read();
  lightLevel = Wire.read();
  moisture = Wire.read();
  while(Wire.available() > 0){
    Wire.read();
  }

  // 1 - Too Dry
  // 2 - Too Hot
  // 3 - Too Cold

  // warning checks
  if (moisture < 20) {
    dispayWarning = true;
    warningCode = 1;
  } else {
    if (warningCode == 1) {
      turnOffWarning();
    }
    canBeWarning[0] = true;
  }
  if (temperature > 25) {
    dispayWarning = true;
    warningCode = 2;
  } else {
    if (warningCode == 2) {
      turnOffWarning();
    }
    canBeWarning[1] = true;
  }
  if (temperature < 15) {
    dispayWarning = true;
    warningCode = 3;
  } else {
    if (warningCode == 3) {
      turnOffWarning();
    }
    canBeWarning[2] = true;
  }

  // update lcd
  if (dispayWarning && canBeWarning[warningCode-1]) {
    warningMsg();
  } else {
    updateLCD(temperature, moisture, lightLevel);
  }
}

void updateLCD(int temp, int soil_hum, int light) {
  lcd.setCursor(0, 0);
  lcd.print("TEMP:"); lcd.print(temp); lcd.write(byte(0));
  lcd.print("SOIL:"); lcd.print(soil_hum); lcd.print("%");
  lcd.setCursor(0, 1);
  lcd.print("   LIGHT:"); lcd.print(light); lcd.print("%");
  lcd.print("       ");
}

void warningMsg() {
  unsigned long currentTime = millis();

  if (currentTime > nextWarningFlash) {
    warningFlashState = !warningFlashState;

    digitalWrite(led_pin, warningFlashState);
    lcd.setCursor(0, 0);
    if (warningFlashState) {
      tone(bzr_pin, 440, 100);
      lcd.print("### WARNING! ###");
    } else {
      lcd.print("    WARNING!    ");
    }

    lcd.setCursor(0, 1);
    switch(warningCode) {
      case 1:
        lcd.print("Soil is too dry"); break;
      case 2:
        lcd.print("Too hot"); break;
      case 3:
        lcd.print("Too cold"); break;
    }
    nextWarningFlash = currentTime + warningFlashDelay;
  }
}

void buttonPress() {
  dispayWarning = false;
  canBeWarning[warningCode-1] = false;
  warningCode = 0;
  digitalWrite(led_pin, LOW);
}

void loop() {}
