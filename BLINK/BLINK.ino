/*-------------------------------------------------------------------------------
This is just a blink program to blink the 
LED of ARDUINO UNO attached with pin 13.
Do not place SHIELD for this program.
-------------------------------------------------------------------------------*/
void setup() 
{
  pinMode(13, OUTPUT);
}


void loop() 
{
  digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(5000);              // wait for a second
  digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
  delay(5000);              // wait for a second
}
