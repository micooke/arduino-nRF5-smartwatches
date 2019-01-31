#include <Arduino.h>

#include "SerialCommands.h"

#include <SerialCommand.h> // https://github.com/kroimon/Arduino-SerialCommand
#include <Vector.h> // https://github.com/zacsketches/Arduino_Vector

#define ANALOG_PINS = 8;
#define DIGITAL_PINS = 28;

DigitalPins[DIGITAL_PINS] = {
  PIN_BUTTON1,PIN_BUTTON2,PIN_TOUCH,PIN_VIBRATE,LED_BUILTIN,  /*1-5*/
  PIN_HR_ON,PIN_OLED_VPP,PIN_OLED_SW,  /*6-8*/
  PIN_SERIAL_RX,PIN_SERIAL_TX,PIN_SERIAL1_RX,PIN_SERIAL1_TX,  /*9-12*/
  PIN_SPI_MISO,PIN_SPI_MOSI,PIN_SPI_SCK, /*13-15*/
  PIN_SPI1_MISO,PIN_SPI1_MOSI,PIN_SPI1_SCK, /*16-18*/
  PIN_SPI1_CS,SS,MOSI,MISO,SCK, /*19-23*/
  OLED_RST,OLED_CS,OLED_DC, /*24-26*/
  PIN_WIRE_SDA,PIN_WIRE_SCL}; /*27-28*/

AnalogPins[ANALOG_PINS] = { PIN_A0, PIN_A1, PIN_A2, PIN_A3, PIN_A4, PIN_A5, PIN_A6, PIN_A7 };

void setup()
{
  // turn off the vibration motor
  digitalWrite(PIN_VIBRATE, HIGH);
  pinMode(PIN_VIBRATE, OUTPUT);

  Serial1.begin(9600);

  populate_UNUSED_PINS();

  sCmd.addCommand("T", togglePinCommand);
  sCmd.addCommand("KX", findKx022IntPinCommand);
  sCmd.addCommand("B", findBatteryCommand);
  sCmd.addCommand("DO", digitalOutputCommand);
  sCmd.addCommand("S", scanCommand);
  sCmd.addCommand("S", scanWideCommand);
  sCmd.addCommand("P", printCommand);
  
  sCmd.setDefaultHandler(unrecognized);
  
  unrecognized(NULL);
}

void loop(void) { sCmd.readSerial(); }
