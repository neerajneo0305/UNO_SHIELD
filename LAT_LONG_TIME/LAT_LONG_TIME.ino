#include "declaration.h"
#include <SoftwareSerial.h>
SoftwareSerial shield (7, 8); // RX, TX

void setup()
{
  Serial.begin(9600);
  shield.begin(9600);
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  delay(1000);
}

void loop()
{
  float time_now = 0;
  float date_now = 0;
  float speed_now = 0;
  float latitude = 0;
  float longitude = 0;

  int j = gps_data();
  lat_long_speed(&time_now, &date_now, &speed_now, &latitude, &longitude);

  Serial.print("time = ");
  Serial.println(time_now);
  Serial.print("date = ");
  Serial.println(date_now);
  Serial.print("speed = ");
  Serial.println(speed_now);
  Serial.print("latitude = ");
  Serial.println(latitude, 6);
  Serial.print("longitude = ");
  Serial.println(longitude, 6);
  Serial.println("-------------------------");
}


//--------------------------------------------------------------GPS_DATA-----------------------------------------------------------------------

int gps_data(void)
{
  while (1)
  {
    byteGPS = shield.read();       // Read a byte of the serial port
    if (byteGPS != -1)              
    {
      gps_string[cmd_num] = byteGPS;        
      cmd_num++;
      if (byteGPS == 13)                  // If the received byte is = to 13, end of transmission
      {
        comma_count = 0;
        gps_data_count = 0;                  
        for (int i = 1; i < 7; i++)
        {
          if (gps_string[i] == comandGPR[i - 1])
          {
            gps_data_count++;
          }
        }
        if (gps_data_count == 6)      
        {
          for (int i = 0; i < 300; i++)
          {
            if (gps_string[i] == ',')
            {
              comma_place[comma_count] = i;
              comma_count++;
            }
            if (gps_string[i] == '*')
            {
              comma_place[comma_count] = i;
              comma_count++;
              cmd_num = 0;
              return 0;
            }
          }
        }
        cmd_num = 0;
      }
    }
  }
}

//--------------------------------------------------------------GPS_DATA-----------------------------------------------------------------------



//--------------------------------------------------------------DATA-----------------------------------------------------------------------

float data(word lower_limit, word upper_limit)
{
  float cordinate = 0.00;

  for (byte k = lower_limit; k <= upper_limit; k++)
  {
    if ((gps_string[k] >= '0') && (gps_string[k] <= '9'))
    {
      cordinate = cordinate * 10 + (gps_string[k] - 48);
    }
  }
  return cordinate;
}


//---------------------------------------------------------------DATA--------------------------------------------------------------------------


//------------------------------------------------------------lat_long_speed-------------------------------------------------------------------

void lat_long_speed(float *time_now, float *date_now, float *speed_now, float *latitude, float *longitude)
{
  *time_now = data((comma_place[0] + 1), (comma_place[0] + 6));
  *date_now = data((comma_place[8]), (comma_place[9]));
  *speed_now = data((comma_place[6] ), (comma_place[6] + 4));

  float latitude1 = data((comma_place[2] + 1), (comma_place[2] + 2));
  int cordinate_int  = (int)latitude1;
  float latitude2 = data((comma_place[2] + 3), (comma_place[3] - 1));
  latitude2 = latitude2 / 600000;
  *latitude = latitude1 + latitude2;

  float longitude1 = data((comma_place[4] + 1) , comma_place[4] + 3);
  cordinate_int = (int)longitude1;
  float longitude2 = data((comma_place[4] + 4) , comma_place[5] - 1);
  longitude2 = longitude2 / 600000;
  *longitude = longitude1 + longitude2 ;
}

//--------------------------------------------------------timestamp_lat_long_speed-------------------------------------------------------------


