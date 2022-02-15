// C++ code
//
int Light = 0;

int Motion = 0;

void setup()
{
  pinMode(7, INPUT);
  pinMode(8, INPUT);
  pinMode(10, OUTPUT);
}

void loop()
{
  Light = digitalRead(7);
  Motion = digitalRead(8);
  if (Light == 0 && Motion == 1) {
    digitalWrite(10, HIGH);
  } else {
    digitalWrite(10, LOW);
  }
  delay(10); // Delay a little bit to improve simulation performance
}
