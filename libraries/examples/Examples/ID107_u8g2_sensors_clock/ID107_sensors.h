#ifndef ID107_SENSORS_H
#define ID107_SENSORS_H

#include <SoftwareI2C.h>

#include <KX022.h>
#include <Si114.h>

#include <Timezone.h>   // https://github.com/JChristensen/Timezone

TimeChangeRule ACST = {"ACST", First, Sun, Apr, 3, 570}; // Australian Central Daylight Time = UTC +9:30 hours
TimeChangeRule ACDT = {"ACDT", First, Sun, Oct, 2, 630}; // Australian Central Standard Time = UTC +10:30 hours
Timezone AdelaideTimezone(ACST, ACDT);
TimeChangeRule *tcr;        // pointer to the time change rule, use to get TZ abbrev

#ifdef ACCEL_HWI2C
// Kx022 - Hardware I2C (Wire)
KX022<> acc(Wire);

// Si1143 - Software I2C
SoftwareI2C sWire(PIN_WIRE1_SDA, PIN_WIRE1_SCL);
PulsePlug<SoftwareI2C> pulse(sWire);
#else
// Kx022 - Software I2C (Wire)
SoftwareI2C sWire(PIN_WIRE1_SDA, PIN_WIRE1_SCL);
KX022<SoftwareI2C> acc(sWire);

// Si1143 - Hardware I2C
PulsePlug<> pulse(Wire);
#endif

class ID107_sensors{
private:
	uint8_t _retries;
	void float2chars(float &in, char (&out)[5]);
	time_t compileTime();
public:
	ID107_sensors(uint8_t retries = 5) : _retries(retries) {}
	~ID107_sensors() {}
	void begin();
	void get_heartrate(uint8_t ambiant_sensor = 0);
	void get_accelerometer();
	void get_clock();
	String row[3];
};

void ID107_sensors::begin()
{
   // Clock
   setTime(AdelaideTimezone.toUTC(compileTime()));

   // Si1143 - Heartrate
   uint8_t attempts = 0;
   while ((pulse.isPresent() == false) & (attempts < _retries))
   {
      delay(100);
      ++attempts;
   }
   if (pulse.isPresent())
   {
     pulse.init();
   }

   // Kx022 - Accelerometer
   acc.init();
}

void ID107_sensors::get_heartrate(uint8_t ambiant_sensor)
{
  if (pulse.isPresent())
  {
    pulse.readSensor(ambiant_sensor + 1);   // sensorIdx = 1(HeartRate),2(Ambiant),3(Both)
  	if (ambiant_sensor)
  	{
  		
      row[0] = "VIS " + String(pulse.als_vis);
      row[1] = "IR  " + String(pulse.als_ir);
      row[2] = "";
  	}
  	else
  	{
  		row[0] = "RED " + String(pulse.led_red);
  		row[1] = "IR1 " + String(pulse.led_ir1);
  		row[2] = "IR2 " + String(pulse.led_ir2);
  	}
  }
  else
  {
  	row[0] = "Si1143 (HRM)";
  	row[1] = "Not";
  	row[2] = "Present";
  }
}

void ID107_sensors::get_accelerometer()
{
	row[0] = "X ";
	row[1] = "Y ";
	row[2] = "Z ";

	char fltBuf[5];
  float xyz[3];
  acc.getAccelXYZ(xyz);
  
  float2chars(xyz[0],fltBuf); row[0] += String(fltBuf);
  float2chars(xyz[1],fltBuf); row[1] += String(fltBuf);
  float2chars(xyz[2],fltBuf); row[2] += String(fltBuf);
}

void ID107_sensors::get_clock()
{
	time_t utc = now();
	time_t local = AdelaideTimezone.toLocal(utc, &tcr);

	char timeString[10];

	sprintf(timeString, "%.2d:%.2d:%.2d", hour(local), minute(local), second(local));

	char dateString[11];

	sprintf(dateString, "%.2d/%.2d/%d", day(local), month(local), year(local));
	/*
	char dayString[7];
	char monthYearString[9];
  char m[4];    // temporary storage for month string (DateStrings.cpp uses shared buffer)
  strcpy(m, monthShortStr(month(local)));

	sprintf(dayString, "%s %.2d", dayShortStr(weekday(local)), day(local));
	sprintf(buf, "%s %d", m, year(local));
	*/
	row[0] = timeString;
	row[1] = dateString;
  row[2] = "";
}

// Function to return the compile date and time as a time_t value
time_t ID107_sensors::compileTime()
{
  const time_t FUDGE(4);     // fudge factor to allow for compile time (seconds, YMMV)
  const char *compDate = __DATE__, *compTime = __TIME__, *months = "JanFebMarAprMayJunJulAugSepOctNovDec";
  char chMon[3], *m;
  tmElements_t tm;
  
  strncpy(chMon, compDate, 3);
  chMon[3] = '\0';
  m = strstr(months, chMon);
  tm.Month = ((m - months) / 3 + 1);
  
  tm.Day = atoi(compDate + 4);
  tm.Year = atoi(compDate + 7) - 1970;
  tm.Hour = atoi(compTime);
  tm.Minute = atoi(compTime + 3);
  tm.Second = atoi(compTime + 6);
  time_t t = makeTime(tm);
  return t + FUDGE;           // add fudge factor to allow for compile time
}

void ID107_sensors::float2chars(float &in, char (&out)[5])
{
  bool sign_bit = (in < 0);
  uint16_t tmp = sign_bit?(-in * 10):(in * 10);
  out[0] = (sign_bit)?'-':' ';
  out[1] = char('0' + (tmp / 10));
  out[2] = '.';
  out[3] = char('0' + (tmp % 10));
  out[4] = '\0';
}

#endif
