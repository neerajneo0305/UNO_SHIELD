#include <SoftwareSerial.h>
#include "declaration.h"
SoftwareSerial shield (7, 8); // RX, TX

/*-----------------------------------------------Arduino_Setup---------------------------------------------------------------*/
void setup()
{
  Serial.begin(9600);
  shield.begin(9600);
  pinMode(13, OUTPUT);
}

/*-----------------------------------------------Arduino_Setup---------------------------------------------------------------*/


/*-----------------------------------------------Arduino_Loop---------------------------------------------------------------*/
void loop()
{
  digitalWrite(13, HIGH);
  delay(1000);
  int j = gps_data();
  Serial.print("gps_out");
  lat_long_speed(&time_now, &date_now, &speed_now, &latitude, &longitude);
  //format_data();
  clear_data();
  digitalWrite(13, LOW);
  gprs_setup();
  while (1);
}

/*-----------------------------------------------Arduino_Loop---------------------------------------------------------------*/


/*---------------------------------------------------gprs_setup-------------------------------------------------------------*/

void gprs_setup()
{


  shield.print("AT+SAPBR=1,1\r\n");
  shield.flush();
  serial_output_read();
  
  shield.print("AT+HTTPINIT\r\n");
  shield.flush();
  serial_output_read();

  shield.print("AT+HTTPPARA=\"CID\",1\r\n");
  shield.flush();
  serial_output_read();

  shield.print("AT+HTTPPARA=\"URL\",\"https://stae-1320.firebaseio.com/College_Project.json?print=pretty\"\r\n");
  shield.flush();
  serial_output_read();

  shield.print("AT+HTTPPARA=\"CONTENT\",\"application/json\"\r\n");
  shield.flush();
  serial_output_read();

  shield.print("AT+HTTPSSL=1\r\n");
  shield.flush();
  serial_output_read();

  shield.print("AT+GSN\r\n");
  shield.flush();
  serial_output_read();
  read_serial.toCharArray(result_str, 50);

  shield.print("AT+HTTPDATA=109,10000\r\n");
  shield.flush();
  serial_output_read();

  format_data();
  for (int i = 9; i < 25; i++)
  {
    shield.print(result_str[i]);
  }
  shield.print(" }\r\n");

  for (int i = 9; i < 25; i++)
  {
    Serial.print(result_str[i]);
  }
  Serial.print(" }\r\n");
  serial_output_read();


  shield.print("AT+HTTPACTION=1\r\n");
  shield.flush();
  serial_output_read();
  delay(50);
  serial_output_read();
  Serial.println("done");

}

/*---------------------------------------------------gprs_setup-------------------------------------------------------------*/


/*-----------------------------------------------format_data---------------------------------------------------------------*/

void format_data(void)
{
  shield.print("{ \"latitude\": ");
  shield.print(latitude, 5);

  shield.print(", \"longitude\":  ");
  shield.print(longitude, 5);

  shield.print(", \"speed\": ");
  shield.print(speed_now);

  shield.print(", \"time\": ");
  shield.print(time_now);

  shield.print(", \"IMEI\": ");
  //Serial.print(" }\r\n");

  Serial.print("{ \"laltitude\": ");
  Serial.print(latitude, 5);

  Serial.print(", \"longitude\":  ");
  Serial.print(longitude, 5);

  Serial.print(", \"speed\": ");
  Serial.print(speed_now);

  Serial.print(", \"time\": ");
  Serial.print(time_now);

  Serial.print(", \"IMEI\": ");
  //Serial.print(" }\r\n");
  //while (1);
}

/*-----------------------------------------------format_data---------------------------------------------------------------*/



/*----------------------------------------------serial_output_read----------------------------------------------------------*/
void serial_output_read(void)
{
  while (shield.available() != 1);
  while (shield.available() > 0)
  {
    read_serial = shield.readString();
    Serial.print(read_serial);
  }
}
/*-----------------------------------------------serial_output_read---------------------------------------------------------*/


//--------------------------------------------------------------GPS_DATA--------------------------------------------------------------------

int gps_data(void)
{
  Serial.print("gps data");
  while (1)
  {

    byteGPS = shield.read();       // Read a byte of the serial port
    //Serial.write(byteGPS);
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

//--------------------------------------------------------------GPS_DATA-------------------------------------------------------------------


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

//--------------------------------------------------------timestamp_lat_long_speed------------------------------------------------------------

//----------------------------------------------------------------clear_data------------------------------------------------------------------

void clear_data()
{
  while (shield.available() > 0)
  {
    char t = shield.read();
  }
  char t = shield.read();

  while (Serial.available() > 0)
  {
    char t = Serial.read();
  }
  t = Serial.read();
}

//----------------------------------------------------------------clear_data------------------------------------------------------------------

