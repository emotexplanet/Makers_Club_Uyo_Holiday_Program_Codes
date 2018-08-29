
#include <LiquidCrystal.h>
//rs, en, D4, D5, D6, D7
LiquidCrystal lcd(12, 11, 10, 9, 8, 7);
void setup() {
  lcd.begin(16,2);
  lcd.print("Hello World!!!");
  lcd.setCursor(0,1);
  lcd.print("Starthub");
  delay(2000);
  lcd.clear();
  lcd.print("Makers' Club");
}
void loop() {
  lcd.setCursor(0, 1);
  lcd.print(millis()/1000);
}
