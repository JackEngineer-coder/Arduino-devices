#include <Keypad.h>
#include <Servo.h>
//#include <EEPROM.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);
Servo food;

const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {10, 3, 4, 5}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {6, 7, 8, 9}; //connect to the column pinouts of the keypad
 
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

String password = "7060";
String mypassword;
 
String fishcount;
 
int counter = 0; 
int attempts = 0; 
int max_attempts = 3; 
 
void setup(){
delay(1000);
 Serial.begin(9600);
  lcd.init();                 //Init the LCD
  lcd.backlight();            //Activate backlight     
  lcd.home();                           
  
  Serial.println("enter password to continue");
  lcd.setCursor(2, 0);  
  lcd.print("Enter Password:");
  food.attach(11);
}
  
void loop()
{   

  
//for(i=0;i<=(fishcount.toInt());i++){
//  food.write(45);
//  delay(150);
//  food.write(0);
  
 keypadfunction();
}

void keypadfunction()
{
 char key = keypad.getKey();
  
  if (key){
    Serial.println(key);
    counter = counter + 1; 
    lcd.setCursor(counter, 1);
    lcd.print("*");
  
  if (key == '1')
  {
 
    mypassword = mypassword + 1;   
  }
  
    if (key == '2')
  {
 
    mypassword = mypassword + 2;  
  }
  
  if (key == '3')
  {
 
    mypassword = mypassword + 3; 
  }
  
   if (key == '4')
  {
  
    mypassword = mypassword + 4;  
  }
  
  if (key == '5')
  {
  
    mypassword = mypassword + 5;
  }
  
   if (key == '6')
  {
   
    mypassword = mypassword + 6; 
  }
  
   if (key == '7')
  {
 
    mypassword = mypassword + 7; 
  }
 
   if (key == '8')
  {
 
    mypassword = mypassword + 8; 
  }
  
  if (key == '9')
  {
 
    mypassword = mypassword + 9;
  }
             
  if (key == '0')
  {
 
    mypassword = mypassword + 0; 
  }
  
  }
 
if (key == '#'){
  int f=0; 
    Serial.println(mypassword); 
    
if (password.equals(mypassword))
{
  Serial.println("Setup Fish Count");
lcd.clear(); 
lcd.println("Setup Fish Count");
lcd.setCursor(0,1);
lcd.println("b/w 1 to 99");
while(f<=2){
  Serial.println("enter fish count");
 char key = keypad.waitForKey();
  if (key){
    fishcount+=key;
    lcd.setCursor(f, 1);
    lcd.print(key);
    Serial.println(key);
    //Serial.println(f); 
     if(1<f<2&&key=='*'){
//    Wire.requestFrom(8,1);                           // request 1 byte from slave arduino (8)
//    byte MasterReceive = Wire.read(); 
    Serial.println("Sending data to Slave");
    Serial.println(fishcount.toInt());
    for(int i=1;i<=fishcount.toInt();i++)
    {
      food.write(100);
      delay(150);
      food.write(163);
      delay(500); 
    }
    Wire.beginTransmission(8);                       // start transmit to slave arduino (8)
    Wire.write(fishcount.toInt());                          // sends one byte converted POT value to slave
    Wire.endTransmission(); 
    fishcount="";
      }}
      f++;
     }
     

mypassword = ""; 
counter = 0; 
lcd.clear();
lcd.setCursor(0,0); 
lcd.println("Enter password");
}
else
{
Serial.println("wrong");

attempts = attempts + 1; 
if (attempts >= max_attempts )
{
  lcd.clear();
  lcd.setCursor(0,0); 
  lcd.print("Locked Out");
  
attempts = 0; 
 
}
mypassword = ""; 
counter = 0; 
lcd.clear(); 
lcd.setCursor(0,0); 
lcd.print("Wrong Password");
delay(1000);
 
lcd.setCursor(0,1); 
lcd.print("max attempts 3");
delay(1000);
 
lcd.clear(); 
lcd.println("Enter password");
lcd.setCursor(0,1); 
}
 }    
}
