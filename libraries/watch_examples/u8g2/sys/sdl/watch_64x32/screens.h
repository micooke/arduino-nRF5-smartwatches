#pragma once

#include "u8g2.h"
#include <string>
/*
objects:
0 - temp
1 - time
2 - heart rate
3 - bluetooth
4 - battery
5 - date
*/

int8_t x[] = {65,-5,65,0,53,14};
int8_t y[] = {8,33,17,8,7,8};
uint16_t font[] = {0,1040,0,0,0,692};
uint8_t width[] = {12,12,8,12,12,8};

const uint16_t _temperature = 0xe010+12; // thermometer
const uint16_t _heartrate[2] = {0xe100+6,0xe100+7}; // big heart, small heart
const uint16_t _bluetooth[2] = {0xe000+11,0xe1b0+5}; // big BT, medium BT
const uint16_t _battery = 0xe230+10; // battery charging

// sijiNumerals(u8g2_t *u8g2, std::string &s, uint8_t x, uint8_t y, uint8_t font_size = 2)
// writes the string at position x,y using siji numbers instead of the standard number set
// font_size = {0,1,2,3} = {small rounded, large rounded, small squared, large squared}
// 
void sijiNumerals(u8g2_t *u8g2, uint8_t x, uint8_t y, std::string s, uint8_t font_size = 1)
{
	const uint16_t c_offset = (font_size < 4)?(0xE15F + font_size*10):0xE17D;
	const uint8_t font_width = 7;

	uint8_t c_index = 0;
	u8g2_SetFont(u8g2, u8g2_font_siji_t_6x10);
	for (uint8_t c = 0; c < s.length(); c++)
	{
		c_index = s[c] - '0';
		if (c_index < 10)
		{
			u8g2_DrawGlyph(u8g2, x + c*font_width, y, c_offset + c_index);
		}
		else
		{
			// font_size determines the colon used
			// 0,2 - small fonts use 0xE192
			// 1,3 - large fonts use 0xE193
			u8g2_DrawGlyph(u8g2, x + c*font_width, y, 0xE192 + (font_size % 2));
		}
	}
}

void printObject(u8g2_t *u8g2, uint8_t object_index = 0)
{
  // set the correct font
  switch(object_index)
  {
    case 0: // temp
      setFont(u8g2, 0);
      u8g2_DrawGlyph(u8g2, x[object_index], y[object_index], _temperature); // thermometer
      setFont(u8g2, font[object_index]);
      u8g2_DrawStr(u8g2, x[object_index]+ width[object_index], y[object_index], "30");
      break;    // 12 x 12
    case 1: // time
      setFont(u8g2, font[object_index]);
      u8g2_DrawStr(u8g2, x[object_index], y[object_index], "12:34");
      break;
    case 2: // heart rate
      setFont(u8g2, 0);
      u8g2_DrawGlyph(u8g2, x[object_index], y[object_index], _heartrate[0]); // big heart
      setFont(u8g2, font[object_index]);
      //u8g2_DrawStr(u8g2, x[object_index]+ width[object_index], y[object_index], "189");
      sijiNumerals(u8g2, x[object_index]+ width[object_index], y[object_index], std::string("189"));
      break;
    case 3: // bluetooth
      setFont(u8g2, 0);
      u8g2_DrawGlyph(u8g2, x[object_index], y[object_index], _bluetooth[1]); // bluetooth
      break;
    case 4: // battery
      setFont(u8g2, 0);
      u8g2_DrawGlyph(u8g2, x[object_index], y[object_index], _battery); // battery
      break;
    case 5: // date
      setFont(u8g2, font[object_index]);
      u8g2_DrawStr(u8g2, x[object_index], y[object_index], "12 JAN");
      break;
    default:
      printObject(u8g2, 0);     
      printObject(u8g2, 1);
      printObject(u8g2, 2);
      printObject(u8g2, 3);
      printObject(u8g2, 4);
      printObject(u8g2, 5);
  }
}

void screen(u8g2_t *u8g2, uint8_t s = 0)
{
/*
objects:
0 - temp
1 - time
2 - heart rate
3 - bluetooth
4 - battery
5 - date

Default layout
[] : icon, # : index
+----------------+
|[#3]  [#5]  [#4]|
| +---- #1 ----+ |
| |    HH:MM   | |
| +------------+ |
+----------------+

+----------------+
|[#3]  [#2]  [#4]|
| +---- #1 ----+ |
| |    HH:MM   | |
| +------------+ |
+----------------+

+----------------+
|[#3]  [#1]  [#4]|
| +---- #2 ----+ |
| |    BPM     | |
| +------------+ |
+----------------+



*/

	switch(s)
	{
		case 0:
			printObject(u8g2, -1); // print all
			break;
		case 1: // BIG TIME
			setFont(u8g2, 0);
		    u8g2_DrawGlyph(u8g2, 16, 8, _heartrate[0]); // big heart
			//u8g2_DrawStr(u8g2, 16 + 12, 8, "189");
			sijiNumerals(u8g2, 16+8, 8, std::string("189"));
			u8g2_DrawGlyph(u8g2, 0, 8, _bluetooth[1]); // bluetooth
		    u8g2_DrawGlyph(u8g2, 53, 7, _battery); // battery

		    // time
		    setFont(u8g2, 1040);
		    u8g2_DrawStr(u8g2, -5, 33, "12:34");
	    	break;
		case 2: // BIG HEART RATE
			setFont(u8g2, 0);
			u8g2_DrawGlyph(u8g2, 0, 8, _bluetooth[1]); // bluetooth
		    u8g2_DrawGlyph(u8g2, 53, 7, _battery); // battery

		    // time
		    //u8g2_DrawStr(u8g2, 16, 8, "12:34");
		    sijiNumerals(u8g2, 12, 8, std::string("12:04"));

		    // heartrate
		    u8g2_DrawGlyph(u8g2, 4, 25, _heartrate[0]); // big heart
		    setFont(u8g2, 1040);
			u8g2_DrawStr(u8g2, 11, 33, "189");
	    	break;
  	}
}