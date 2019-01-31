#ifndef ID107_OLED_H
#define ID107_OLED_H

#include "ID107_sensors.h"

#include <U8g2lib.h>
#include <SPI.h>

U8G2_SH1106_64X32_1_4W_HW_SPI u8g2(U8G2_R0, OLED_CS, OLED_DC, OLED_RST);

class ID107_OLED{
private:
  const uint8_t _numPages = 4;
  uint32_t _splashTime;
  uint8_t _pageNum;
  time_t compileTime();
  
  ID107_sensors _id107_sensors;
  
  void splash(uint32_t splash_time_ms);
  void draw();
public:
	ID107_OLED(uint32_t splash_time_ms = 2000): _splashTime(splash_time_ms), _pageNum(0) {}
	~ID107_OLED() {}
	void begin();
	void heartrate(uint8_t ambiant_sensor = 0);
	void accelerometer();
	void clock();
	void nextPage();
  uint8_t getPageCount() { return _numPages; }
	void drawPage(uint8_t pageNum = 0);
};

void ID107_OLED::begin()
{
  _id107_sensors.begin();
  
  u8g2.begin();
  u8g2.setFont(u8g2_font_6x10_tf);
  u8g2.setFontRefHeightExtendedText();
  u8g2.setDrawColor(1);
  u8g2.setFontPosTop();
  u8g2.setFontDirection(0);

  splash(_splashTime);
}

void ID107_OLED::drawPage(uint8_t pageNum)
{
	switch(pageNum) {
		case 0:
			heartrate(0); break;
		case 1:
			heartrate(1); break;
		case 2:
			accelerometer(); break;
		default:
			clock();
	}
}

void ID107_OLED::draw()
{
  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_6x10_tf);
    u8g2.drawStr( 0, 0, _id107_sensors.row[0].c_str());
    u8g2.drawStr(0, 10, _id107_sensors.row[1].c_str());
    u8g2.drawStr(0, 20, _id107_sensors.row[2].c_str());
  } while ( u8g2.nextPage() );
}

void ID107_OLED::nextPage()
{
	// increment the page number
	_pageNum = (_pageNum < _numPages - 1)?_pageNum + 1:0;

	// draw the page
	drawPage(_pageNum);	
}


void ID107_OLED::heartrate(uint8_t ambiant_sensor)
{
  _id107_sensors.get_heartrate(ambiant_sensor);

  draw();
}

void ID107_OLED::accelerometer()
{
  _id107_sensors.get_accelerometer();

  draw();
}

void ID107_OLED::clock()
{
  _id107_sensors.get_clock();

  draw();
}

void ID107_OLED::splash(uint32_t splash_time_ms)
{
  _id107_sensors.row[0] = "github.com";
  _id107_sensors.row[1] = "/micooke";
  _id107_sensors.row[2] = __TIME__;

  draw();

  delay(splash_time_ms);
}

#endif
