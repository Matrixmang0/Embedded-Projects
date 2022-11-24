#include <LiquidCrystal.h>

const int rs = 5, en = 4, d4 = 3, d5 = 2, d6 = 1, d7 = 0;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int adc = 0;

void setup() {
  pinMode(A5, INPUT);
  lcd.begin(16, 2);
  lcd.setCursor(3,1);
  lcd.print("ADC : ");
}

void loop() {
  adc = analogRead(A5);
  
  lcd.setCursor(9, 1);
  
  lcd.print(adc);
}
