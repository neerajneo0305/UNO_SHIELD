/*----------------------------------------------------------------------------------
Place your SHIELD on UNO board.
Enter the mobile no. at line 23 and upload the program.
This will call to the number entered at line 223
-----------------------------------------------------------------------------------*/

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
  Serial.println("Calling through SIM900");
  delay(100);
  shield.println("ATD0XXXXXXXXXX;\r\n");       // Enter the mobile number
  delay(5000);
  while (!(shield.available()));
  while (shield.available() > 0)
  {
    Serial.write(shield.read());
  }
  while (!(shield.available()));
  while (shield.available() > 0)
  {
    Serial.write(shield.read());
  }

  Serial.println("Call Finished");
  delay(100);

  while (1);
}


