/*
  Copyright (c) 2014-2015 Arduino LLC.  All right reserved.
  Copyright (c) 2018 Mark Cooke All right reserved.
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

#ifndef _VARIANT_ID107HR_
#define _VARIANT_ID107HR_

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
#define PINS_COUNT           (31u)
#define NUM_DIGITAL_PINS     (31u)
#define NUM_ANALOG_INPUTS    (6u)
#define NUM_ANALOG_OUTPUTS   (0u)

// Buttons
#define PIN_BUTTON1             (4)
#define PIN_BUTTON2             (7)

#define PIN_VIBRATE				(6)
#define LED_BUILTIN				PIN_VIBRATE

/*
 * Analog pins
 */
#define PIN_A0               (2)
#define PIN_A1               (3)
#define PIN_A2               (4)
#define PIN_A3               (5)
#define PIN_A4               (6)
#define PIN_A5               (7)

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
#define PIN_SERIAL_RX       (17)
#define PIN_SERIAL_TX       (18)

/*
 * SPI Interfaces
 */
#define SPI_INTERFACES_COUNT 1

#define PIN_SPI_MISO         (3)
#define PIN_SPI_MOSI         (2)
#define PIN_SPI_SCK          (1)

static const uint8_t SS   = 29;
static const uint8_t MOSI = PIN_SPI_MOSI;
static const uint8_t MISO = PIN_SPI_MISO;
static const uint8_t SCK  = PIN_SPI_SCK;

#define OLED_RST	(30)
#define OLED_CS		(29)
#define OLED_DC		(0)

/*
 * Wire Interfaces
 */
#define WIRE_INTERFACES_COUNT 1

#ifdef ACCEL_HWI2C
#define PIN_WIRE_SDA        14 // Kx022 - Accelerometer Sensor
#define PIN_WIRE_SCL        16
#define PIN_WIRE1_SDA       22u // Si1143 - HeartRate Sensor
#define PIN_WIRE1_SCL       23u
#else
#define PIN_WIRE_SDA        22u // Si1143 - HeartRate Sensor
#define PIN_WIRE_SCL        23u
#define PIN_WIRE1_SDA       14 // Kx022 - Accelerometer Sensor
#define PIN_WIRE1_SCL       16
#endif

#ifdef __cplusplus
}
#endif

#endif
