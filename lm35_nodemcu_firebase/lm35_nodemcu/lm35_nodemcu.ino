//--------------------nodemcu with lm35---------------------
////////////////////////////////////////////////////////////

#define lm35Pin A0
#define ledPin 14

#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

// Set these to run example.
#define FIREBASE_HOST "led1-bb4f2.firebaseio.com"
#define FIREBASE_AUTH "YnUD8FAZgJu0QEL6pik5agrGLwjW3EBcrVx0Nbzq"
#define WIFI_SSID "SRRD"
#define WIFI_PASSWORD "sree2930"

void setup()
{
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);

  /* initialization for firebase */
  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) 
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop()
{
  float lm35Val = getLm35Val();
  delay(500);

  Firebase.setFloat("sensor1/temperature", lm35Val);
  // handle error
  if (Firebase.failed()) {
      Serial.print("setting /number failed:");
      Serial.println(Firebase.error());  
      return;
     
      delay(2000);
  }
  int minimumVal = Firebase.getInt("minimum temperature/value");
  int maximumVal = Firebase.getInt("maximum temperature/value");

  if((minimumVal <= lm35Val)&&(lm35Val <= maximumVal))
  {
    digitalWrite(ledPin, HIGH);
    
  }
  else
  {
    digitalWrite(ledPin, LOW);
  }
  delay(1500);
  
}


//function to get temperature value fom lm35
int getLm35Val()
{
  int analogValue = analogRead(lm35Pin);
  float milliVolts = (analogValue/1024.0) * 3300; //3300 is the voltage provided by nodemcu
  int celsius = milliVolts/10;
  return celsius;
}

