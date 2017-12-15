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

#ifndef _VARIANT_T28_
#define _VARIANT_T28_

/** Master clock frequency */
#ifdef NRF52
#define VARIANT_MCK       (64000000ul)
#else
#define VARIANT_MCK       (16000000ul)
#endif

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "WVariant.h"

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

// Number of pins defined in PinDescription array
#define PINS_COUNT           32u
#define NUM_DIGITAL_PINS     20u
#define NUM_ANALOG_INPUTS    8u
#define NUM_ANALOG_OUTPUTS   0u

// Buttons
#define PIN_BUTTON1          20u // TOP
#define PIN_BUTTON2          24u // BOTTOM
#define PIN_TOUCH            2u // RH6015-C, input OC

#define PIN_VIBRATE          10u
#define PIN_HR_ON             9u

#define PIN_OLED_VPP          1u
#define PIN_OLED_SW           3u

#define LED_BUILTIN PIN_VIBRATE

/*
 * Analog pins
 */
#define PIN_A0               2u
#define PIN_A1               3u
#define PIN_A2               4u
#define PIN_A3               5u
#define PIN_A4               28u
#define PIN_A5               29u
#define PIN_A6               30u
#define PIN_A7               31u

static const uint8_t A0  = PIN_A0;
static const uint8_t A1  = PIN_A1;
static const uint8_t A2  = PIN_A2;
static const uint8_t A3  = PIN_A3;
static const uint8_t A4  = PIN_A4;
static const uint8_t A5  = PIN_A5;
#ifdef NRF52
#define ADC_RESOLUTION    14
#else
#define ADC_RESOLUTION    10
#endif

/*
 * Serial interfaces
 */
// Serial

#define PIN_SERIAL_RX       25u//31u // ublox TX (9600 BAUD)
#define PIN_SERIAL_TX       26u//11u // ublox RX

// To vacant pads near HR ribbon
// +------------------ribbon-------------
// | [  Top ] - To K42 Mosfet P0.09
// | [      ] - P0.04
// | [      ] - VSS
// +-------------------------------------
//   [      ] - P0.02
//   [      ] - P0.26 // debug Tx
//   [Bottom] - P0.25 // debug Rx
//
#define PIN_SERIAL1_RX       31u
#define PIN_SERIAL1_TX       11u

/*
 * SPI Interfaces
 */

#define SPI_INTERFACES_COUNT 2

#define PIN_SPI_MISO         5u // -1// OLED - 4 wire SPI
#define PIN_SPI_MOSI         18u
#define PIN_SPI_SCK          17u
//#define PIN_SPI_CS           28u

#define PIN_SPI1_MISO        19u // GT22
#define PIN_SPI1_MOSI        23u
#define PIN_SPI1_SCK         22u
#define PIN_SPI1_CS          21u

static const uint8_t SS   = 28u;
static const uint8_t MOSI = PIN_SPI_MOSI;
static const uint8_t MISO = PIN_SPI_MISO;
static const uint8_t SCK  = PIN_SPI_SCK;

#define OLED_RST  14u
#define OLED_CS   28u
#define OLED_DC   30u

/*
 * Wire Interfaces
 */
#define WIRE_INTERFACES_COUNT 0

#define PIN_WIRE_SDA         13u // Kx023
#define PIN_WIRE_SCL         16u // Kx023

#ifdef __cplusplus
}
#endif

#endif
