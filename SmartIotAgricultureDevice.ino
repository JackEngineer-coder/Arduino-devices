#define BLYNK_PRINT Serial   
#include <SPI.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SimpleTimer.h>
#include <DHT.h>
#define BLYNK_PRINT Serial
#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS D2
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

char auth[] ="";               //Authentication code sent by Blynk
char ssid[] = "";                       //WiFi SSID
char pass[] = "";                       //WiFi Password

#define sensorPin D3 
#define pir_pin D1
int sensorState = 0;
int lastState = 0;
int pir =0;
#define DHTPIN 2    
#define DHTTYPE DHT11     
DHT dht(DHTPIN, DHTTYPE);
SimpleTimer timer;
void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
 
  Blynk.virtualWrite(V5, h);  //V5 is for Humidity
  Blynk.virtualWrite(V6, t);  //V6 is for Temperature
}
void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
   pinMode(sensorPin, INPUT);
   pinMode(pir_pin, INPUT);
  dht.begin();

  timer.setInterval(1000L, sendSensor);
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
   sensors.begin();
}
int sensor=0;
void sendTemps()
{
sensor=analogRead(A0);
sensors.requestTemperatures();
float temp = sensors.getTempCByIndex(0); 
Serial.println(temp);
Serial.println(sensor);
Blynk.virtualWrite(V1, temp);
Blynk.virtualWrite(V2,sensor);
Blynk.virtualWrite(V3,pir);
delay(1000);
}
void loop()
{
  Blynk.run(); 
  timer.run(); 
  sendTemps();
  sensorState = digitalRead(sensorPin);
  pir = digitalRead(pir_pin);
  Serial.println(sensorState);

if (sensorState == 1 && lastState == 0) {
  Serial.println("needs water, send notification");
  Blynk.notify("Water your plants");
  lastState = 1;
  delay(1000);
//send notification
    
  }
  else if(pir==1)
  {
    Serial.println("Motion detected");
    Blynk.notify("Protect your field someon in the field now");
    delay(1000);
  } 
  else if (sensorState == 1 && lastState == 1) {
    //do nothing, has not been watered yet
  Serial.println("has not been watered yet");
  delay(1000);
  }
 
  else {
    
    Serial.println("does not need water");
    Serial.println("Nobody is in the field");
    lastState = 0;
    delay(1000);
  }
  
  delay(100);
}
