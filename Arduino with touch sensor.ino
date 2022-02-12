int lastState = LOW;      // the previous state from the input pin
int currentState;         // the current reading from the input pin

void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  // initialize the Arduino's pin as aninput
  pinMode(SENSOR_PIN, INPUT);
}

void loop() {
  // read the state of the the input pin:
  currentState = digitalRead(SENSOR_PIN);

  if(lastState == LOW && currentState == HIGH)
    Serial.println("The sensor is touched");

  // save the the last state
  lastState = currentState;
}
