#include <SoftwareSerial.h>
SoftwareSerial shield (7, 8); // RX, TX

void setup()
{
  Serial.begin(9600);
  shield.begin(9600);
  pinMode(13, OUTPUT);
}

void loop()
{
  digitalWrite(13, LOW);
  delay(1000);
  Serial.println("Sending Message through SIM900");
  delay(100);
  shield.println("AT+CMGF=1\r\n");
  delay(100);
  while (!(shield.available()));
  while (shield.available() > 0)
  {
    Serial.write(shield.read());
  }

  shield.println("AT+CMGS=\"0XXXXXXXXXX\"\r\n");
  delay(1000);
  while (!(shield.available()));
  while (shield.available() > 0)
  {
    Serial.write(shield.read());
  }
  shield.print("Welcome to Tashiqa training ");
  shield.write(0x1A);
  shield.print("\r\n");
  delay(1000);
  while (!(shield.available()));
  while (shield.available() > 0)
  {
    Serial.write(shield.read());
  }
  Serial.println("Message sent");
  while (1);


}


