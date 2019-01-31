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

#ifndef _VARIANT_DS_D6_
#define _VARIANT_DS_D6_

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
#define PIN_BUTTON1          30u
#define PIN_TOUCH            PIN_BUTTON1

#define PIN_VIBRATE          25u
#define PIN_HR_ON            26u

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

#define PIN_SERIAL_RX       22u
#define PIN_SERIAL_TX       23u

/*
 * SPI Interfaces
 */

#define SPI_INTERFACES_COUNT 1

#define PIN_SPI_MISO         31u // pin 31 unallocated
#define PIN_SPI_MOSI         5u // 128x32 SSD1306 OLED
#define PIN_SPI_SCK          6u
#define PIN_SPI_RST          4u
#define PIN_SPI_DC           28u
#define PIN_SPI_CS           29u

static const uint8_t SS   = PIN_SPI_CS;
static const uint8_t MOSI = PIN_SPI_MOSI;
static const uint8_t MISO = PIN_SPI_MISO;
static const uint8_t SCK  = PIN_SPI_SCK;

#define OLED_RST  PIN_SPI_RST
#define OLED_CS   PIN_SPI_CS
#define OLED_DC   PIN_SPI_DC

/*
 * Wire Interfaces
 */
#define WIRE_INTERFACES_COUNT 1

#ifdef ACCEL_HWI2C
#define PIN_WIRE_SDA        13u // Kx023 (Address 0x1f)- Accelerometer Sensor
#define PIN_WIRE_SCL        14u
#define PIN_WIRE_INT1       15u
#define PIN_WIRE1_SDA       7u // PAH8001 (Address 0x6b) - HeartRate Sensor
#define PIN_WIRE1_SCL       8u
#else
#define PIN_WIRE_SDA        7u // PAH8001 (Address 0x6b) - HeartRate Sensor
#define PIN_WIRE_SCL        8u
#define PIN_WIRE1_SDA       13u // Kx023 (Address 0x1f) - Accelerometer Sensor
#define PIN_WIRE1_SCL       14u
#define PIN_WIRE1_INT1      15u
#endif

#ifdef __cplusplus
}
#endif

#endif
