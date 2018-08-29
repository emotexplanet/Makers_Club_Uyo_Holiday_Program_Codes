/* SPACE RACE Game using Arduino and Nokia 5110 LCD
 * Joystick -> (A0,A1)
*/

#include <SPI.h> //SPI librarey for Communication
#include <Adafruit_GFX.h> //Graphics lib for LCD
#include <Adafruit_PCD8544.h> //Nokia 5110 LCD librarey

//Bitmap Data for SpaceShip
static const unsigned char PROGMEM ship[] =
{
B00000000,B00000000,
B00000001,B00000000,
B00000011,B10000000,
B00000010,B10000000,
B00000010,B11000000,
B00000111,B11000000,
B00001101,B11100000,
B00011111,B11110000,
B00111111,B11111000,
B01111111,B11111100,
B01111111,B11111100,
B01111111,B11111100,
B00011111,B11110000,
B00000111,B11100000,
B00000000,B00000000,
};

//Bitmap Data for enemyship
static const unsigned char PROGMEM enemy[] =
{
B00000101,B11000000,
B00001011,B11100000,
B00000011,B11100000,
B00110011,B11111000,
B01111111,B11111100,
B10111111,B11111010,
B01110111,B11011100,
B01111110,B11111100,
B00111111,B11111100,
B11101111,B11101110,
B11000001,B00000110,
B10000001,B00000010,
B10000000,B00000010,
B00000000,B00000000,
};

Adafruit_PCD8544 display = Adafruit_PCD8544(7, 6, 5, 4, 3); //Specifiy the pins to which the LCD is connected

int enemy_0_pos, enemy_1_pos, enemy_phase;
int Joy_X;
int game_speed = 0;
int score = 0;
char POS=2;
boolean enemy_dead = true;
boolean control = true;

void setup()   {
  Serial.begin(9600); //Serial Monitor for Debugging

  display.begin(); //Begin the LCD communication
  display.setContrast(75); //Set the contrast of the display
  display.clearDisplay();   // clears the screen and start new
}

void loop() {
  display.clearDisplay();   // clears the screen and start new

  gamescreen(); //Displays the box, score and speed values

  //Get input from user  
  Joy_X = analogRead(A1); //Read the X vaue from Joystick
  if (Joy_X < 312 && POS!=1 && control==true) //If joy stick moves right
  { POS--; control = false;} //Decrement position of spaceship
  else if (Joy_X > 712 && POS!=3 && control==true) //If joy stick moves right
  { POS++; control = false;} //Increment position of spaceship
  else if (Joy_X >502 && Joy_X<522) //If joystick back to initial position
  control = true; //Preare it for next move
  //Input from user received
  

  player_car(POS); //Place the Space ship based on the input from user

  if (enemy_dead) //Check of enemy ships are dead
  { //If they are dead 
  enemy_0_pos = POS; //create first enemy above the space ship
  enemy_1_pos = random(0,4); //create secound enemy at some other random place
  enemy_phase = 0; //Bring the enemy form the top
  enemy_dead = false; //Enemy is created so they are not dead anymore
  }

  enemy_ship (enemy_0_pos,enemy_phase); enemy_phase++; //Place the first enemy on screen and drive him down 
  enemy_ship (enemy_1_pos,enemy_phase); enemy_phase++; //Place the secound enemy on screen and drive him down 

  if (enemy_phase>22 && ((enemy_0_pos == POS) || (enemy_1_pos == POS)) ) //If the Spaceship touches any one of the enemy 
  game_over(); //Display game over
  
  if (enemy_phase>40) //If thespace ship escapes the enemys 
  {enemy_dead = true; score++;} //Increase the score and kill the enemys 

  Level_Controller(); //BAsed on score increase the speed of game

  
  display.display();  //Update the display with all the changes made so far
}

void   Level_Controller() //Increase the speed of game based on the score. 
{ 
  if (score>=0 && score<=10) //If score 0-10 
  {
    game_speed = 0; delay(120); //slow the game by 80ms
  }
    if (score>10 && score<=20) //If score 10-40 
  {
    game_speed = 1; delay(100); //slow the game by 70ms
  }
    if (score>20 && score<=30) //If score 20-40 
  {
    game_speed = 2; delay(80); //slow the game by 60ms
  }
    if (score>30 && score<=40) //If score 30-40 
  {
    game_speed = 3; delay(60); //slow the game by 50ms
  }
}

void enemy_ship(int place, int phase) //Place the enemy_ship in the new place and phase
{
  if (place==1)
  display.drawBitmap(2, phase, enemy, 15, 15, BLACK);

  if (place==2)
  display.drawBitmap(18, phase, enemy, 15, 15, BLACK);

  if (place==3)
  display.drawBitmap(34, phase, enemy, 15, 15, BLACK);
}

void game_over() //Display game over screen
{
  while(1) //The program will be stuck here for ever 
  {
    delay(100);
    display.clearDisplay();  
    display.setCursor(20,2);
    display.println("GAME OVER");
  
    display.display(); 
    break; 
  }
}

void gamescreen()
{
//Draw the Border for Screen
  display.drawLine(0, 0, 0, 47, BLACK);
  display.drawLine(50, 0, 50, 47, BLACK);
  display.drawLine(0, 47, 50, 47, BLACK);

//Enter Default Texts
  display.setTextSize(1);
  display.setTextColor(BLACK);
  display.setCursor(52,2);
  display.println("Speed");
  display.setCursor(54,12);
  display.println(game_speed);
  display.setCursor(52,25);
  display.println("Score");
  display.setCursor(54,35);
  display.println(score);
}

void player_car(char pos) //Place the spaceship based on the user selected position
{
  if (pos==1)
  display.drawBitmap(2, 32, ship, 15, 15, BLACK);

  if (pos==2)
  display.drawBitmap(18, 32, ship, 15, 15, BLACK);

  if (pos==3)
  display.drawBitmap(34, 32, ship, 15, 15, BLACK);
}
