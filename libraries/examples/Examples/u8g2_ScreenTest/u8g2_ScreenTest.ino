/*
  ScreenTest.ino using:
  Universal 8bit Graphics Library (https://github.com/olikraus/u8g2/)
*/

#include <Arduino.h>
#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

/*
  U8glib Example Overview:
    Frame Buffer Examples: clearBuffer/sendBuffer. Fast, but may not work with all Arduino boards because of RAM consumption
    Page Buffer Examples: firstPage/nextPage. Less RAM usage, should work with all Arduino boards.
    U8x8 Text Only Example: No RAM usage, direct communication with display controller. No graphics, 8x8 Text only.
    
  This is a page buffer example.    
*/

#if defined(_VARIANT_T28_)
  U8G2_SH1107_64X128_1_4W_HW_SPI u8g2(U8G2_R0, OLED_CS, OLED_DC, OLED_RST);
#elif defined (_VARIANT_IDO003_) | defined (_VARIANT_ID100HR_) | defined(_VARIANT_ID107HR_)
  U8G2_SH1106_64X32_1_4W_HW_SPI u8g2(U8G2_R0, OLED_CS, OLED_DC, OLED_RST);
#else
  // generic example for the common 128x64 SSD1306 OLED
  #define OLED_CS 10
  #define OLED_DC 9
  #define OLED_RST 8
  U8G2_SSD1306_128X64_NONAME_1_4W_HW_SPI u8g2(U8G2_R0, OLED_CS, OLED_DC, OLED_RST);
#endif

void u8g2_prepare(void) {
  u8g2.setFont(u8g2_font_6x10_tf);
  u8g2.setFontRefHeightExtendedText();
  u8g2.setDrawColor(1);
  u8g2.setFontPosTop();
  u8g2.setFontDirection(0);
}

void u8g2_box_title() {
  u8g2.drawStr( 5, 5, "U8g2");
  u8g2.drawStr( 5, 20, "ScreenTest");
  
  u8g2.drawFrame(0, 0, u8g2.getDisplayWidth(), u8g2.getDisplayHeight());
}

void displayPage()
{
  u8g2.firstPage();  
  do {
    u8g2_box_title();
  } while( u8g2.nextPage() );
}

void setup(void)
{
  #if defined (_VARIANT_T28_)
  // Turn off the vibration motor and hr sensor (both are driven by P-mosfets, so drive HIGH to turn off)
  pinMode(PIN_VIBRATE, OUTPUT);
  pinMode(PIN_HR_ON, OUTPUT);
  digitalWrite(PIN_VIBRATE, HIGH);
  digitalWrite(PIN_HR_ON, HIGH);
  #endif

  Serial.begin(9600);
  Serial.println(__FILE__);
  Serial.print(__DATE__); Serial.print(F(" @ ")); Serial.println(__TIME__);

  u8g2.begin();
  u8g2_prepare();
  displayPage();
  Serial.println("end setup");
}

void loop(void)
{
  delay(5000);
  u8g2.setFlipMode(true);
  displayPage();
  delay(5000);
  u8g2.setFlipMode(false);
  displayPage();
}