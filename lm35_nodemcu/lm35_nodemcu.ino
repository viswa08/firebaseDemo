//--------------------nodemcu with lm35---------------------
////////////////////////////////////////////////////////////

#define lm35Pin A0

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  float lm35Val = getLm35Val();
  Serial.println(lm35Val);   
  delay(2000);
}

float getLm35Val()
{
  int analogValue = analogRead(lm35Pin);
  float milliVolts = (analogValue/1024.0) * 3300; //3300 is the voltage provided by nodemcu
  float celsius = milliVolts/10;
  return celsius;
}

