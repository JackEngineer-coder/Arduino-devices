// Interfacing the Pulse sensior
#include <ESP8266WiFi.h>;
#include <WiFiClient.h>;
#include <ThingSpeak.h>;
#include<DHT.h>;

const char* ssid = "G299"; //Your Network SSID
const char* password = "12345678jc"; //Your Network Password
int val;
int PulseSensorpin = A0; //Pulse Sensor Pin Connected at A0 Pin
WiFiClient client;

unsigned long myChannelNumber = 788360; //Your Channel Number (Without Brackets)
const char * myWriteAPIKey = "NAFP5OO5L5P3C2A7"; //Your Write API Key
DHT dht(D5, DHT11);

void setup()
{
 Serial.begin(9600);
 delay(10);
  // Connect to WiFi network
  WiFi.begin(ssid, password);
  ThingSpeak.begin(client);
}

void loop()
{
  val = analogRead(PulseSensorpin); //Read Analog values and Store in val variable
  int pulse = map(val,0,1023,0,100);
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  Serial.println("Pulse Sensorvalue=  "); // Start Printing on Pulse sensor value on LCD
  Serial.println(pulse); // Start Printing on Pulse sensor value on LCD
  Serial.println("Temperature: " + (String) t);
  Serial.println("Humidity: " + (String) h);
  ThingSpeak.writeField(myChannelNumber, 3, t, myWriteAPIKey);
  ThingSpeak.writeField(myChannelNumber, 2, h, myWriteAPIKey);
  delay(10);
  ThingSpeak.writeField(myChannelNumber, 1,pulse, myWriteAPIKey); //Update in ThingSpeak
}
