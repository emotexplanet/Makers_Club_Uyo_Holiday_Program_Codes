#define LED1 9
#define LED2 10

char data = '\0';//Variable for storing received data

void setup() 
{
  Serial.begin(9600);         //Sets the data rate in bits per second (baud) for serial data transmission
  pinMode(LED1, OUTPUT);        //Sets digital pin A0 as output pin
  pinMode(LED2, OUTPUT);        //Sets digital pin A1 as output pin
}
void loop()
{
  if(Serial.available() > 0)  // Send data only when you receive data:
  {
    data = Serial.read();      //Read the incoming data and store it into variable data
    Serial.print(data);        //Print Value inside data in Serial monitor
    Serial.print("\n");        //New line 
    if(data == 'a'){            //Checks whether value of data is equal to 1 
      digitalWrite(LED1, HIGH);  //If value is 1 then LED turns ON
    }
    else if(data == 'b'){       //Checks whether value of data is equal to 0
      digitalWrite(LED1, LOW); //If value is 0 then LED turns OFF
    }

    if(data == 'c'){            //Checks whether value of data is equal to 1 
      digitalWrite(LED2, HIGH);  //If value is 1 then LED turns ON
    }
    else if(data == 'd'){       //Checks whether value of data is equal to 0
      digitalWrite(LED2, LOW); //If value is 0 then LED turns OFF
    }
  }                            
 
}
