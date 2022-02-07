#include <SoftwareSerial.h>
int IRSensor = 2; // connect ir sensor to arduino pin 2
int LED = 13; // conect Led to arduino pin 13
int statusSensor = 0;
//int gas = 7;
int flame= 8;
//int gas_sensor=0;
int flame_sensor=0;
int LED1 = 10;

SoftwareSerial mySerial(4,5);




void setup()
{
  mySerial.begin(9600);   // Setting the baud rate of GSM Module  
  Serial.begin(9600);    // Setting the baud rate of Serial Monitor (Arduino)
  delay(100);
  
 

  pinMode (IRSensor, INPUT); // sensor pin INPUT
  pinMode (LED, OUTPUT); // Led pin OUTPUT
  pinMode(flame,INPUT);
  //pinMode(gas, INPUT);
  pinMode(LED1,OUTPUT);
}

void loop()
{
   statusSensor = digitalRead (IRSensor);
   flame_sensor=digitalRead(flame);
   //gas_sensor = digitalRead(gas);
   
  
  if (statusSensor == 1 ){ //flame_sensor==0 || gas_sensor==0){
    digitalWrite(LED1, LOW);// LED LOW
    digitalWrite(LED,HIGH);
    
    //delay(5000);
    
      SendMessage();
      makecall();
  }
  else if (flame_sensor==0) {
    digitalWrite(LED1, LOW);// LED LOW
    digitalWrite(LED,HIGH);
    
    //delay(5000);
    
      Flame();
      makecall();    
  }
  
  
  else
  {
    digitalWrite(LED1, HIGH); // LED High
     digitalWrite(LED,LOW);
  }
  Serial.println(statusSensor); 
  Serial.println(flame_sensor); 
  //Serial.println(gas_sensor); 
  
}


void SendMessage()
{
  
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  mySerial.println("ATD+91XXXXXXXXXX");
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"+91XXXXXXXXXX\"\r"); // Replace x with mobile number
  //delay(1000);
  mySerial.println("DANGER! SOMEONE IS TRYING TO ENTER!!");   // The SMS text you want to send
  //delay(100);
   mySerial.println((char)26);// ASCII code of CTRL+Z
  //delay(1000);
}
void Flame()
{
  
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  mySerial.println("ATD+91XXXXXXXXXX");
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"+ATD+91XXXXXXXXX\"\r"); // Replace x with mobile number
  //delay(1000);
  mySerial.println("DANGER! FIRE IN THE OFFFICE!!");   // The SMS text you want to send
  //delay(100);
   mySerial.println((char)26);// ASCII code of CTRL+Z
  //delay(1000);
}

void makecall()
{
  Serial.println("ATD+91XXXXXXXXXX");
}
