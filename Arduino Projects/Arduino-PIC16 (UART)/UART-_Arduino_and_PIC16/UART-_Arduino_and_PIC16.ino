#include <LiquidCrystal.h>

char data;

const int rs = 7, en = 6, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.setCursor(2,1);
  lcd.print("Rcd. Data : ");
}

void loop() {

  lcd.setCursor(14, 1);
  if(Serial.available()) {
     data = Serial.read();
     lcd.print(data);
  }
}
