
#include <LiquidCrystal.h>

const int rs = 10, en = 8, d4 = 3, d5 = 2, d6 = 1, d7 = 0;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

char name[] = {"SANTHOSH"};

void setup() {
  
  lcd.begin(16, 2);
  
}

void loop() {
 
  for (int i=0; i<=7; i++){
     lcd.setCursor(i+4, 0);
     lcd.print(name[i]);
     lcd.setCursor(11-i, 1);
     lcd.print(name[i]);
     delay(200);
  }
  
  
}
