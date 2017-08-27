char result_str[50];               //It is used to store the output char array whenever some string is converted to char array.
String read_serial;                 //We are reading string output from Serial1

float time_now = 0;
float date_now = 0;
float speed_now = 0;
float latitude = 0;
float longitude = 0;

char gps_string[300] = "";
char comandGPR[7] = "$GPRMC";
int byteGPS ;
word comma_count = 0;
word gps_data_count = 0;
word cmd_num = 0;
word comma_place[13];

void serial_output_read(void);   // Read the buffer output
void gprs_setup(void);           // Setup the parameter for GPRS like:- HTTP parameter, User-Id e.t.c
void format_data(void);
void clear_data(void);
float data(word i, word j);
int gps_data(void);
void lat_long_speed(float *time_now, float *date_now, float *speed_now, float *latitude, float *longitude);
