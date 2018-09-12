//--------------------nodemcu with lm35---------------------
////////////////////////////////////////////////////////////

#define lm35Pin A0

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
  

  Firebase.setFloat("temperature", lm35Val);
  // handle error
  if (Firebase.failed()) {
      Serial.print("setting /number failed:");
      Serial.println(Firebase.error());  
      return;

      delay(2000);
  }
}


//function to get temperature value fom lm35
float getLm35Val()
{
  int analogValue = analogRead(lm35Pin);
  float milliVolts = (analogValue/1024.0) * 3300; //3300 is the voltage provided by nodemcu
  float celsius = milliVolts/10;
  return celsius;
}

