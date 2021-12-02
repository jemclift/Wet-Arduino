#include <LiquidCrystal.h>

const int rs = 10, en = 9, d4 = 6, d5 = 5, d6 = 4, d7 = 3, btn_pin = 2, led_pin = 7, bzr_pin = 13;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

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
}

void updateLCD(int temp, int soil_hum, int light) {
  lcd.setCursor(0, 0);
  lcd.print("TEMP:"); lcd.print(temp); lcd.write(byte(0));
  lcd.print("SOIL:"); lcd.print(soil_hum); lcd.print("%");
  lcd.setCursor(0, 1);
  lcd.print("LIGHT:"); lcd.print(light); lcd.print("%");
}

void buttonPress() {
  digitalWrite(led_pin,HIGH);
  tone(bzr_pin, 440, 100);
  digitalWrite(led_pin,LOW);
}

void loop() {
  updateLCD(35, 12, 50);
}
