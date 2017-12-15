/*
  Copyright (c) 2014-2015 Arduino LLC.  All right reserved.
  Copyright (c) 2016 Sandeep Mistry All right reserved.

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

const uint32_t g_ADigitalPinMap[] = {
  0,
  1,
  2,
  3, // RH 6051C = OC (touch)
  4,
  5,
  6,
  7,
  8,
  9,  // Mosfet - drives Si1143 / HRM (PULL HIGH = OFF)
  10, // Mosfet - drives vibrate motor (PULL HIGH = OFF)
  11, // ublox G7020-KT RX
  12,
  13, // Kx023 - SDA
  14,
  15,
  16, // Kx023 - SCL
  17,
  18,
  19, // G24A24 / GT22L - MISO
  20, // Button 1
  21, // G24A24 / GT22L - CS
  22, // G24A24 / GT22L - CLK
  23, // G24A24 / GT22L - MOSI
  24, // Button 2 ?
  25,
  26,
  27,
  28,
  29,
  30,
  31
};
