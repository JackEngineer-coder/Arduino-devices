void setup()
{
  pinMode(13,OUTPUT); // LED == output device
  pinMode(4, INPUT);// sensor == input device
}
void loop()
{
  int motion = 0; // motion ==0
  motion =digitalRead(4); // whatever you are receiving from sensor
  if(motion==1)
  {
    digitalWrite(13, HIGH); 
    delay(5000);
    digitalWrite(13, LOW); 
  }
  else{
    digitalWrite(13, LOW);
  }
}
