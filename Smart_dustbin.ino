#include<Servo.h>
Servo servo;
void setup() {
  // put your setup code here, to run once:
pinMode(7,INPUT);

pinMode(5,INPUT);
servo.attach(3);
Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
int moisture = digitalRead(7);
int IR = digitalRead(5);
if(moisture ==1 && IR ==1)
{
  servo.write(120);
  
  
}
else if(moisture==0 && IR==0)
{
  servo.write(160);
}
else
{
  servo.write(180);
}
Serial.println(IR);
//Serial.println(moisture);

}
