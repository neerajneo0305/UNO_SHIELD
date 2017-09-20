/*----------------------------------------------------------------------------
This will print the burst data coming out from GPS module
----------------------------------------------------------------------------*/

#include <SoftwareSerial.h>
SoftwareSerial shield (7, 8); // RX, TX


void setup()
{
  Serial.begin(9600);
  shield.begin(9600);
  pinMode(9, OUTPUT);
  digitalWrite(9, HIGH);
  delay(1000);
}

void loop()
{
  int byteGPS = -1;

  while (shield.available())
  {
    byteGPS = shield.read();
    if (byteGPS != -1)
      Serial.write(byteGPS);
  }
}
