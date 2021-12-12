#include <LiquidCrystal.h>
#include <Wire.h>

// lcd
const int rs = 10, en = 9, d4 = 6, d5 = 5, d6 = 4, d7 = 3;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// other pins
const int btn_pin = 2, led_pin = 7, bzr_pin = 13;

// warning variables
bool dispayWarning = false;
unsigned long nextWarningFlash = 0;
int warningFlashDelay = 500; // milliseconds
bool warningFlashState = true;
bool canBeWarning[3] = {true, true, true};

int warningCode = 0;

// 0 - No Warning
// 1 - Too Dry
// 2 - Too Hot
// 3 - Too Cold

int temperature = 20;
int lightLevel = 0;
int moisture = 50;

// custom degree character
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

  // initialise LCD
  lcd.begin(16, 2);

  // load custom character
  lcd.createChar(0, degree);

  // assign pins and button interupt
  pinMode(led_pin, OUTPUT);
  pinMode(btn_pin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(btn_pin), buttonPress, FALLING);

  // connect to master arduino
  Wire.begin(A5);
  Wire.onReceive(receiveEvent);
}

// used to turn off warning when values return to normal
void turnOffWarning() {
  dispayWarning = false;
  warningCode = 0;
  digitalWrite(led_pin, LOW);
}

// recieve data from master arduino
void receiveEvent(int howMany) {

  // read transmitted sensor data
  temperature = Wire.read();
  lightLevel = Wire.read();
  moisture = Wire.read();

  // clear extra bytes
  while (Wire.available() > 0) {
    Wire.read();
  }

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

// display given sensor data on LCD
void updateLCD(int temp, int soil_hum, int light) {
  lcd.setCursor(0, 0);
  lcd.print("TEMP:"); lcd.print(temp); lcd.write(byte(0));
  lcd.print("SOIL:"); lcd.print(soil_hum); lcd.print("%");
  lcd.setCursor(0, 1);
  lcd.print("   LIGHT:"); lcd.print(light); lcd.print("%");
  lcd.print("       ");
}

// displays a flashing warning
void warningMsg() {
  unsigned long currentTime = millis();

  // if it's time to flip warning flash state
  if (currentTime > nextWarningFlash) {

    // flip warning flash state
    warningFlashState = !warningFlashState;

    digitalWrite(led_pin, warningFlashState);

    // write common top line of display
    lcd.setCursor(0, 0);
    if (warningFlashState) {
      tone(bzr_pin, 440, 100);
      lcd.print("### WARNING! ###");
    } else {
      lcd.print("    WARNING!    ");
    }

    // write specific bottom line of display
    lcd.setCursor(0, 1);
    switch(warningCode) {
      case 1:
        lcd.print("Soil is too dry"); break;
      case 2:
        lcd.print("Too hot"); break;
      case 3:
        lcd.print("Too cold"); break;
    }

    // set next flash time
    nextWarningFlash = currentTime + warningFlashDelay;
  }
}

// turn off warning if button is pressed
void buttonPress() {
  dispayWarning = false;
  canBeWarning[warningCode-1] = false;
  warningCode = 0;
  digitalWrite(led_pin, LOW);
}

void loop() {}
