#include <LiquidCrystal.h>
#include <Keypad.h>

const byte ROWS = 4; // Four rows
const byte COLS = 4; // Three columns

long int set1;
long int set2;
long int set3;
long int set4;

String hours;
String minutes;
String seconds;

char keys[ROWS][COLS] = {

  {'1','2','3','A'},

  {'4','5','6','B'},

  {'7','8','9','C'},

  {'*','0','#','D'}

};

byte rowPins[ROWS] = { 6, 7, 8, 9 };// Connect keypad ROW0, ROW1, ROW2 and ROW3 to these Arduino pins
byte colPins[COLS] = { 10, 11, 12, 13 };// Connect keypad COL0, COL1 and COL2 to t

Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

LiquidCrystal lcd(A0, A1, 5, 4, 3, 2); // Creates an LC object. Parameters: (rs, enable, d4, d5, d6, d7)

 int t1, t2, t3, t4, t5, t6;
 int r1, r2, r3;
 
boolean alarm = true; // condition for alarm

 char key;
 String r[8];

 void setCounterTime()
{
  alarm = true;
  int i=0;
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Set Alarm Time");
  lcd.clear();
  lcd.print("HH:MM:SS");
  lcd.setCursor(0,1);  
  while(1){
    key = kpd.getKey();
    char j;    
    if(key!=NO_KEY){
      lcd.setCursor(j,1);
      lcd.print(key);
      Serial.print("Key Press: ");
      Serial.println(key);
      r[i] = key-48;
      Serial.print("Key Press Value: ");
      Serial.println(r[i]);
      i++;
      j++;
      
      if (j == 2 || j == 5){
        lcd.print(":"); j++;
      }
      delay(500);
    }
    if (key == 'D'){
      key=0; break; 
    }
  }
  lcd.clear();
}
 
 void setup() 
 { 
  lcd.begin(16,2);
  Serial.begin(9600);
  pinMode(A3, INPUT);
  pinMode(A4, OUTPUT);
 } 
 
 void loop() 
{ 
  lcd.setCursor(0,0);
  lcd.print("Arduino Timer");
  if (digitalRead(A3)==1) //
  {
    lcd.clear();
    setCounterTime(); 
    for(int i = 0; i < 6; i++)// this for loop is used to get the value of the counter time and print it serially
    {
      Serial.print(r[i]);
      Serial.println();
    }      
    hours = String (r[0]) + String (r[1]) ; //combining two separate int values of r[0] and r[1] into one string and save it to "hours" 
    minutes = String (r[2]) + String (r[3]) ;  //combining two separate int values of r[2] and r[3] into one string and save it to "minutes" 
    seconds = String (r[4]) + String (r[5]) ;  //combining two separate int values of r[4] and r[5] into one string and save it to "seconds" 
  
    set1 = (hours.toInt() * 3600); //converting hours into seconds
    set2 = (minutes.toInt() * 60);  //converting minutes into seconds
    set3 = seconds.toInt();
    set4 = (hours.toInt() * 3600)+ (minutes.toInt() * 60) + seconds.toInt(); //adding set1, set2 and set3 together in set4
    
    Serial.print("set4");
    Serial.print(set4);
    Serial.println();

    lcd.setCursor(0,0);
    lcd.print("Countdown begins");
    delay(1000);
    lcd.clear();
  
    for(long int j = set4; j >= 0; j--) // this for loopis used to decrease the total time in seconds
    {
      Serial.println(j);  
      lcd.setCursor(0,0);
      lcd.print("HH:MM:SS");  
      long int HH = j / 3600; // converting the remaining time into remaining hours
      lcd.setCursor(0,1);
      Serial.println(HH);
      if (HH < 10) {
        lcd.print('0');  
      }
      lcd.print(HH);
      lcd.print(":");
  
      long int MM = (j - (HH*3600))/60 ; //converting the remaining time into remaining minutes
      lcd.setCursor(3,1);
      Serial.println(MM);
      if (MM < 10) { lcd.print('0');  }
      lcd.print(MM);
      lcd.print(":");
      
      long int SS = j - ((HH*3600)+(MM*60)); //converting the remaining time into remaining seconds
      lcd.setCursor(6,1);
      Serial.println(SS);
      if (SS < 10) { 
        lcd.print('0');  
      } 
      lcd.print(SS);
      delay(1000);
    
      if (digitalRead(A3)==1){
        break;
      } 

      if (j == 0)    
      {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Timer Stop");
        lcd.setCursor(2,1);
        lcd.print("Ring alarm");
      
        for(int k =0; k<= 100; k++){ //this for loop is used for the buzzer to beep 100 time as the timer reaches zero        
          digitalWrite(A4,HIGH);
          delay(300);
          digitalWrite(A4,LOW);  
          delay(300); 
          if (digitalRead(A3)==1){
            break;
           }  
        }
      }
    }
  }
}  
