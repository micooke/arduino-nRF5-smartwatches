#include "ID107_OLED.h"

bool button_wasPressed = false;

ID107_OLED id107_oled;
uint8_t page_num = 0;
uint32_t tPage;

void setup()
{
   id107_oled.begin();

   Serial.begin(9600);
   Serial.println(__FILE__);

   pinMode(PIN_BUTTON1, INPUT_PULLUP);

   tPage = millis();
}

void loop()
{
  if (Button_isPressed(PIN_BUTTON1))
  {
    page_num = (page_num + 1 < id107_oled.getPageCount())?page_num+1:0;
  }
  
  if (millis() - tPage > 20) // 20ms = 50Hz
  {
    tPage = millis();
    id107_oled.drawPage(page_num);
  }
  yield();
}

// debounce the button
bool Button_isPressed(uint8_t ButtonPin)
{
  bool button_isPressed = (digitalRead(ButtonPin) == 0);

  bool result = (button_wasPressed == false) & (button_isPressed == true);
  button_wasPressed = button_isPressed;
  return result;
}
