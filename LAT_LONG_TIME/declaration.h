char gps_string[300] = "";
char comandGPR[7] = "$GPRMC";
int byteGPS = -1;
word comma_count = 0;
word gps_data_count = 0;
word cmd_num = 0;
word comma_place[13];
float lat_tmp = 0;

float data(word i, word j);
int gps_data(void);
void lat_long_speed(float *time_now, float *date_now, float *speed_now, float *latitude, float *longitude);
