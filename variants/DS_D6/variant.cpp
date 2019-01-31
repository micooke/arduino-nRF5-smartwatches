/*
  Copyright (c) 2014-2015 Arduino LLC.  All right reserved.
  Copyright (c) 2019 Mark Cooke All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "variant.h"

// https://github.com/fanoush/ds-d6/wiki/Hardware
const uint32_t g_ADigitalPinMap[] = {
  0,
  1,
  2, // charge detect: vmul-5/analogRead(D2)
  3, // battery voltage: vmul*analogRead(D3)
  4, // OLED RST - 128x32 SSD1306
  5, // OLED MOSI - 128x32 SSD1306
  6, // OLED SCK - 128x32 SSD1306
  7, // HR sensor SCL - PAH8001
  8, // HR sensor SDA - PAH8001
  9, 
  10,
  11,
  12,
  13, // Accel SCL - Kx023
  14, // Accel SDA - Kx023
  15, // Accel INT1 - Kx023
  16, 
  17,
  18,
  19,
  20,
  21,
  22, // UART RX
  23, // UART TX
  24,
  25, // Vibration Motor
  26, // HR sensor ENABLE - PAH8001
  27,
  28, // OLED DC - 128x32 SSD1306
  29, // OLED CS - 128x32 SSD1306
  30, // Button1 / Touch Button (Pull Up)
  31
};
