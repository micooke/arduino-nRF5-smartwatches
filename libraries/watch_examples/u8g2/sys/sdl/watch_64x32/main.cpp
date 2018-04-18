#include <cstdio>
#include <cstdint>
#include <string>

#include "u8g2.h"
#include "fonts.h"
#include "screens.h"
  
u8g2_t u8g2;

/*
objects:
0 - temp
1 - time
2 - heart rate
3 - bluetooth
4 - battery
*/

/*
Default layout
[] : icon, # : index
+----------------+
|[#3]  [#2]  [#4]|
| +---- #1 ----+ |
| |    HH:MM   | |
| +------------+ |
+----------------+

+----------------+
|[#3]  [#0]  [#4]|
| +- #1-++-#2--+ |
| |HH:MM|| BPM | |
| +-----++-----+ |
+----------------+

+----------------+
|[#3]  [#1]  [#4]|
| +---- #2 ----+ |
| |    BPM     | |
| +------------+ |
+----------------+
*/

/*
int8_t x[5] = {65,-5,16,0,54};
int8_t y[5] = {8,33,8,8,7};
uint16_t font[5] = {0,1040,0,0,0};
uint8_t width[5] = {12,12,12,12,12};
*/
uint8_t screen_index = 0;
std::string object_name[] = {"temp", "time", "heart rate", "bluetooth", "battery", "date"};

int main(void)
{
  uint8_t object = 0;
  char k = ' ';

  u8g2_SetupBuffer_SDL_128x64(&u8g2, &u8g2_cb_r0);
  u8g2_InitDisplay(&u8g2);
  u8g2_SetPowerSave(&u8g2, 0);  

  setFont(&u8g2, -1);
  u8g2_SetFontDirection(&u8g2, 0);
  u8g2_SetFontRefHeightAll(&u8g2);

  
  while (true)
  {
    //u8g2_InitDisplay(&u8g2);
    //u8g2_ClearDisplay(&u8g2);
    //u8g2_ClearBuffer(&u8g2);
    u8g2_FirstPage(&u8g2);
    do {
      screen(&u8g2, screen_index);
      u8g2_DrawHLine(&u8g2,0,33,66);
      u8g2_DrawVLine(&u8g2,65,0,34);
    } while( u8g2_NextPage(&u8g2) );

    do
    {
      k = u8g_sdl_get_key();
    } while( k < 0 );

    printf("k = %d(%c)\n", k, k);

    if ( k == 'q' )
    {
      break;
    }
    else if (k == ' ')
    {
      screen_index = (screen_index == 2)?0:screen_index+1;
    }
    else if (k == 's')
    {
      object = (object == 5)?0:object+1;
    }
    else if ( k == 'h')
    {
      for (uint8_t i = 0; i < 6; ++i)
      {
        printf("%s: x,y,font = %d,%d,%d\n",(object_name[i]).c_str(),x[i],y[i],font[i]);
      }
    }
    else
    {
      if ( k == 17 ) y[object] -= 5; // up arrow
      if ( k == 18 ) y[object] += 5; // down arrow
      if ( k == 20 ) x[object] -= 5; // left arrow
      if ( k == 19 ) x[object] += 5; // right arrow
      if ( k == 'w' ) y[object] -= 1; // up arrow
      if ( k == 'x' ) y[object] += 1; // down arrow
      if ( k == 'a' ) x[object] -= 1; // left arrow
      if ( k == 'd' ) x[object] += 1; // right arrow
      if ( k == 'o' ) font[object] = (font[object] == 0)?MAX_FONT_NUM-1:font[object]-1; // minus
      if ( k == 'p' ) font[object] = (font[object] == MAX_FONT_NUM-1)?0:font[object]+1; // plus
    }

    
    printf("%s: x,y,font = %d,%d,%d\n",object_name[object].c_str(),x[object],y[object],font[object]);
  }
  
  return 0;
}
// user menu example
//u8g2_UserInterfaceSelectionList(&u8g2, "Title", 0, "abc\ndef\nghi\njkl\n12345\n67890\nabcdefg\nxyz\n111\n222\n333\n444");

