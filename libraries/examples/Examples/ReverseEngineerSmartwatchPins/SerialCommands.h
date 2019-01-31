#ifndef SERIALCOMMANDS_H
#define SERIALCOMMANDS_H

#include <SerialCommand.h> // https://github.com/kroimon/Arduino-SerialCommand
#include <Vector.h> // https://github.com/zacsketches/Arduino_Vector

SerialCommand sCmd;
SoftwareSerial Serial1(PIN_SERIAL1_RX, PIN_SERIAL1_TX);

Vector<uint8_t> UNUSED_PINS;
uint8_t NUM_UNUSED_PINS = 0;

void populate_UNUSED_PINS()
{
  // Note : AnalogPins arent dedicated to a function so will be used by rev eng tools
  for (uint8_t p=0; p < PINS_COUNT; ++p)
  {
    bool isAllocated = false;
    for (uint8_t idx=0; idx < DIGITAL_PINS; ++idx)
    {
      if (p == DigitalPins[idx])
      {
        isAllocated = true;
        break;
      }
    }

    // If it isnt one of the digital pins, save it as unused
    if (isAllocated == false)
    {
      UNUSED_PINS.push_back(p);
      ++NUM_UNUSED_PINS;
    }
  }
}

void unrecognized(const char *c)
{
  Serial1.println(
       F("Commands are :\n"
       "T pin_number - toggle digital pin\n"
       "KX - find Kx022/023 interrupt pin\n"
       "B - find battery voltage pin\n"
       "DO - toggle unused digital output pins (outputs pin number to serial)\n"
       "S - scan unused pins, which includes analog pins (outputs pin number and pin value to serial)\n"
       "SW - same as scan, but output is in wide format\n"
       "P - print all un-allocated (and Analog) pins\n"));

  Serial1.println("Example: T 4 -> toggle D4 high for 3 seconds, then set it low");
}

void findBatteryCommand()
{
  const uint8_t tolerance = 10; // tolerance on successive measurements (i.e. error margin)

  //pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LED_VIBRATE, OUTPUT);

  for (uint8_t p = 0; p < ANALOG_PINS; ++p)
  {
    pinMode(AnalogPins[p], OUTPUT);
    uint8_t val = analogRead(AnalogPins[p]);

    // if we are reading a value, try running down the battery for 1 minute
    if (val > 0)
    {
      Serial1.print(F("Testing pin "));
      Serial1.print(AnalogPins[p]);
      Serial1.println(F(" to see if it is the battery pin (test will take approximately 1 minute)"));

      //digitalWrite(LED_BUILTIN, HIGH);
      digitalWrite(PIN_VIBRATE, LOW); // vibration motor on
      for (uint8_t wait=0; wait < 60; ++wait)
      {
        delay(1000);
      }
      //digitalWrite(LED_BUILTIN, LOW);
      digitalWrite(PIN_VIBRATE, HIGH); // vibration motor off

      if (analogRead(AnalogPins[p] + tolerance < val))
      {
        Serial1.print(F("SUCCESS! Battery pin is "));
        Serial1.println(AnalogPins[p]);
      }
      else
      {
        Serial1.print(F("FAIL!    Battery pin is not"));
        Serial1.println(AnalogPins[p]);
      }
    }
  }
}

//"W device_address reg_num reg_val - writes 'reg_val' to register 'reg_num'\n"
void findKx022IntPinCommand()
{
  // setup the Kx022
  // clear the interrupt/s
  // set the interrupt/s as sticky bits
  // prompt the user to tap the watch and wait for 5 seconds
  // check for a change in status
}

void togglePinCommand()
{
   char *arg;

   arg                 = sCmd.next();
   uint8_t pin_number = strtoul(arg, NULL, 16);
   
   if (arg != NULL)
   {
      pinMode(pin_number, OUTPUT);
      digitalWrite(pin_number, HIGH);
      delay(3000);
      digitalWrite(pin_number, LOW);
   }
   else
   {
      Serial1.println("One argument is required : T pin_number");
   }
}

void digitalOutputCommand()
{
   for (uint8_t p = 0; p < NUM_UNUSED_PINS; ++p)
   {
      Serial1.print(F("D"));
      Serial1.println(UNUSED_PINS[p]);
      pinMode(UNUSED_PINS[p], OUTPUT);
      digitalWrite(UNUSED_PINS[p], HIGH);
      delay(3000);
      digitalWrite(UNUSED_PINS[p], LOW);
   }
}

void scanCommand()
{
   for (uint8_t p = 0; p < NUM_UNUSED_PINS; ++p)
   {
      pinMode(UNUSED_PINS[p], INPUT);
      uint8_t val = analogRead(UNUSED_PINS[p], HIGH);

      Serial1.print(F("D"));
      Serial1.print(UNUSED_PINS[p]);
      Serial1.print(F(" = "));
      Serial1.println(val);
   }
}

void scanWideCommand()
{
   for (uint8_t p = 0; p < NUM_UNUSED_PINS; ++p)
   {
      if (p%5 == 0)
      {
        Serial1.print(F("\n["));
        print3digits(UNUSED_PINS[p]);
        const uint8_t upper_value = min(NUM_UNUSED_PINS, p+4);
        for (uint8_t sp = p+1; sp < upper_value; ++sp)
        {
          Serial1.print(F(" "));
          print3digits(UNUSED_PINS[p]);
        }
        Serial1.println(F("]"));
      }
      pinMode(UNUSED_PINS[p], INPUT);
      uint8_t val = analogRead(UNUSED_PINS[p], HIGH);
      
      Serial1.print(F(" "));
      print3digits(val);
   }
}

void printCommand()
{
  Serial1.println(F("Unallocated and Analog pins:"));
  for (uint8_t p = 0; p < NUM_UNUSED_PINS; p+=4)
  {
    print3digits(UNUSED_PINS[p]);
    const uint8_t upper_value = min(NUM_UNUSED_PINS, p+4);
    for (uint8_t sp = p+1; sp < upper_value; ++sp)
    {
      Serial1.print(F(" "));
      print3digits(UNUSED_PINS[p]);
    }
    Serial1.println("");
  }
}

void print3digits(uint8_t val)
{
  if (val % 100 > 0)
  {
    Serial1.print(F("0"));
  }
  if (val % 10 > 0)
  {
    Serial1.print(F("0"));
  }
  Serial1.print(val);
}

#endif