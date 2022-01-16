int sensor = 7; // connect output of sensor at digital pin 7 of Arduino
int LED = 5; // connect +ve leg  of LED to pin number 5 of Arduino.
int val=0; // createed variable and intialized it with 0.
void setup()
{
  // In void setup you have to write a code which you want to runs one time only.
  pinMode(sensor,INPUT);  // define sensor pin.
  pinMode(LED, OUTPUT);  // define output pin.
  Serial.begin(9600); // communication between Arduino and computer at 9600 baud rate.
}

void loop()
{
  val = digitalRead(sensor); // read digital value from sensor and updated it on val.
  if(val==1)
  {
    digitalWrite(LED,HIGH); // if val is getting one then we are going to on the LED programatically.
  }
  else
  {
    digitalWrite(LED,LOW); // else LED is going to off state.
  }
  Serial.println(val); // print the value of val on serial monitor.
}
  
