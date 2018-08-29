//Display values of Temperature and Humidity sensor (Weather Station)
#include "DHT.h"
#include <LiquidCrystal.h>
#define DHTPIN 2     // what digital pin we're connected to
#define DHTTYPE DHT11   // DHT 11
DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal lcd(12, 11, 10, 9, 8, 7); // create lcd// 
//Parameters: (rs, enable, d4, d5, d6, d7)
void setup(){
  lcd.begin(16, 2); //set lcd 
 Serial.begin(9600);
 lcd.setCursor(0,0);
 lcd.print("  UYO WEATHER");
 delay(3000);
 lcd.clear();
}
void loop()
{
//Read humidity
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
 float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
 float f = dht.readTemperature(true);  
  lcd.setCursor(0,0);  // Sets the location to display text
  lcd.print("Temp: "); // print “Temp:”
  lcd.print(t); // print temperature value
  lcd.print((char)223); // print degree
  lcd.print("C");
  lcd.setCursor(0,1); //Sets the location to display text
  lcd.print("Humidity: "); // print “Humidity”
  lcd.print(h); // print humidity value
  lcd.print("%"); // print percentage
  delay(1000); // wait for one-second
  }

