## Nordic Semiconductor nRF5 Smartwatches

This work piggy backs on previous work by many people, mainly : [@goran-mahovlic](https://github.com/goran-mahovlic), [@rogerclarkmelbourne](https://github.com/rogerclarkmelbourne/), [@curtpw](https://github.com/curtpw/), [@Gordon](http://forum.espruino.com/profiles/224/)

Most of these watches are made by [idoosmart](http://www.idoosmart.com) and can be purchased from their [aliexpress](https://ido-smart.en.alibaba.com/productgrouplist-0/Ungrouped.html?) company site.

Be careful when purchasing from a third party reseller as there have been instances where the received watch does not contain a nRF5 chip, or you purchase a ID107HR Plus and receive a ID107HR instead.

Note : I have no affiliation with idoosmart / Shenzhen DO Intelligent Technology Co,. Ltd, nor any aliexpress or smartwatch retailer.

Included smartwatches:
1. [IDO003](https://github.com/micooke/micooke.github.io/blob/master/arduino-nRF5-smartwatches/images/IDO003_back.jpg)
2. [ID100HR](https://github.com/micooke/micooke.github.io/blob/master/arduino-nRF5-smartwatches/images/ID100HR_back.jpg)
3. [ID107HR](https://github.com/micooke/micooke.github.io/blob/master/arduino-nRF5-smartwatches/images/ID107HR_back.jpg)
4. [ID107HR Plus](https://github.com/micooke/micooke.github.io/blob/master/arduino-nRF5-smartwatches/images/ID107HRPlus_disected.jpg) (alpha) - dont expect this to work
5. [LEMDOIE T28](https://github.com/micooke/micooke.github.io/blob/master/nRF52832_Lemdoie_T28.md)
6. [MyPow DS-D6](https://github.com/fanoush/ds-d6)

Included Generic development boards:
6. [Taida Century nRF52 mini board / nRF52832 Gold Core](https://github.com/micooke/micooke.github.io/blob/master/nRF52832_TaidaCentury_GoldCore.md)
7. [Waveshare BLE400](https://www.waveshare.com/wiki/BLE400)

I am happy to accept pull requests for any nRF51 or nRF52 based smartwatch, but will be unable to test anything except for the ID107HR (v2.4) and T28 unless you are feeling generous and want to send me one :wink:.

### Libraries
The following libraries (which work with this core) have been added as submodules:
1. U8g2_Arduino (OLED library) https://github.com/olikraus/U8g2_Arduino
2. sparkfun-based OLED library https://github.com/micooke/sparkfun_OLED
3. Software I2C https://github.com/micooke/SoftwareI2C
4. Software Serial https://github.com/micooke/SoftwareSerial - requirement: https://github.com/sandeepmistry/arduino-nRF5/pull/205
5. Accelerometer https://github.com/micooke/Kx022-1020
6. (work in progress) Si1143 Heartrate sensor https://github.com/micooke/Si1143

#### I recommend using the u8g2 library over any of my OLED libraries!

My Squix78 based OLED [library](https://github.com/micooke/squix78_OLED) also works.

To get these libraries without using the board manager:
```
git clone https://github.com/micooke/arduino-nRF5-smartwatches.git
git submodule update --init --recursive
```

### Note
Im not sure about the ID100HR variant. The pin mapping has been taken from posts about the ID100HR, as well as posts on the ID107HR which appeared to have the same pin mapping.

My ID107HR is a v2.4 and it does not match the pin mapping of the ID100HR. So if you have a ID107HR that is a v2.3 or earlier you will need to use the ID100HR (at this stage).

### Programming
These watches can be programmed by soldering directly to the SWDIO, SWCLK and GND pins.
You can also connect to the TX and RX pins for debugging.

The T28 and ID107HR Plus do not label these pads by silkscreen so please see [ID107HR Plus pads](images/ID107HRPlus_pads.jpg), ![T28 Front1](nRF52832_Lemdoie_T28/T28_Front1.jpg), ![T28 Front2](nRF52832_Lemdoie_T28/T28_Front2.jpg) for these pins.

The ID107HR+ UART Tx,Rx were chosen to be on p23,p24 because the pads are next to the programming pins.

The T28 UART Tx,Rx were chosen to be on p26,p25 as their pads are near the OLED ribbon.

Progamming is via a SWD programmer (J-Link, ST-Link etc.) using sandeep's core.

### Installing via Board Manager
1. [Download and install the Arduino IDE](https://www.arduino.cc/en/Main/Software) (At least v1.6.12)
2. Start the Arduino IDE
3. Go into Preferences
4. Install the board package(s)
    4.1 (If you havent already done so) Install @sandeepmistry's nRF5 core [arduino-nRF5](https://github.com/sandeepmistry/arduino-nRF5)
    4.2 Add ```https://sandeepmistry.github.io/arduino-nRF5/package_nRF5_boards_index.json``` as an "Additional Board Manager URL"
    4.3 Install [arduino-nRF5-smartwatches](https://github.com/micooke/arduino-nRF5-smartwatches)
    4.4 Add ```https://micooke.github.io/package_nRF5_smartwatches_index.json``` as an "Additional Board Manager URL"
5. Open the Boards Manager from the Tools -> Board menu and install "Nordic Semiconductor nRF5 Smartwatches"
6. Select your nRF5 smartwatch from the Tools -> Board menu

### Pin allocation

The nRF52 based T28 is quite different. Its pin allocation table is located [here](https://github.com/micooke/micooke.github.io/blob/master/nRF52832_Lemdoie_T28.md)
@fanoush has done a great job on getting the DS-D6 pin allocation. It is hosted [here](https://github.com/fanoush/ds-d6)


| peripheral type         | name   | pin          | IDO003 | ID100HR | ID107HR | ID107HR Plus
| :---:                   | :---:  | :---:        | :---:  | :---:   | :---:   | :---:
| accelerometer           | Kx022  | SCL          | 14     | 14      | 14      | 5 
|                         |        | SDA          | 16     | 16      | 16      | 3 
|                         |        | INT          | ---    | ---     | ---     | 6 
|                         |        | ADDR         | ---    | ---     | ---     | 4
|                         |        | NCS          | ---    | ---     | ---     | 7
| optical HR sensor       | Si1143 | SCL          | ---    | 26      | 22      | 18
|                         |        | SDA          | ---    | 28      | 23      | 10
|                         |        | INT          | ---    | ---     | 24      | 8
|                         |        | LED          | ---    | ---     | ---     | 9
| SPI flash memory        | MX25L  | MISO         | ---    | ---     | ---     | 27
|                         |        | MOSI         | ---    | ---     | ---     | 31
|                         |        | SCK          | ---    | ---     | ---     | 30
|                         |        | CE           | ---    | ---     | ---     | 28
| side tactile button     | ---    | BUTTON1      | 4      | 4       | 4       | ---
| capacitive touch button | RH6015C| BUTTON2      | 4      | 7       | 7       | ?
| capacitive touch screen | IQS263 | ---          | ---    | ---     | ---     | ?
| vibrate motor           | ---    | VIBRATE -or- | 7      | 8       | 6       | ?
|                         |        | LED_BUILTIN  |        |         |         |    
| serial UART             | ---    | Tx           | 18     | 18      | 18      | 23
|                         |        | Rx           | 17     | 17      | 17      | 24
| OLED                    | ---    | MISO         | 31     | 3       | 3       | ?
|                         | ---    | MOSI         | 29     | 2       | 2       | ?
|                         | ---    | SCK          | 30     | 1       | 1       | ?
|                         | ---    | RST          | 1      | 30      | 30      | ?
|                         | ---    | CS           | 2      | 29      | 29      | ?
|                         | ---    | DC           | 0      | 0       | 0       | ?
| battery voltage level   | ---    | ---          | ?      | ?       | \*      | ?

* --- : not applicable
*  ?  : unknown
* \*  : unknown (easily found - perform an analog read on each pin), but AIN{0:7} = p{28,27,1,2,3,4,9,10} so it must be one of p9,p10,p27,p28

### I2C addresses
1. 0x1F : Accelerometer (Kx022/Kx023)
2. 0x5A : Heart Rate Sensor / PPG (Si1143)
3. 0x76 : Altitude / Pressure / Temperature (HP203B)

### References
* nRF5 core is written and maintained by Sandeep Mistry
* Support for these smartwatches originate from Roger's [arduino-nRF5-customised](https://github.com/rogerclarkmelbourne/arduino-nRF5-customised) repo
* [ID100HR picture](http://www.rogerclark.net/wp-content/uploads/2016/09/ID100HR_back_smart_watch-1024x576.jpg) is from Roger, embedded on his website [article](http://www.rogerclark.net/arduino-on-the-id100hr-fitness-tracker/)
* (Modified) [IDO003 picture](https://espruino.microco.sm/api/v1/files/ba591802419c40145d825db2924360eb162cc026.JPG) is from Gordon, embedded in this [conversation](http://forum.espruino.com/conversations/280747/)
* ID107HR picture is my own
* [ID107HR Plus picture](http://www.rogerclark.net/wp-content/uploads/2017/06/id107plus-7-770x1024.jpg) is from Curt, embedded on Roger's website [article](http://www.rogerclark.net/new-nrf52832-based-smart-watch-available/)
* (Modified) [ID107HR Plus pads](http://www.rogerclark.net/wp-content/uploads/2017/06/id107plus-3.jpg) is from Curt, embedded on Roger's website [article](http://www.rogerclark.net/new-nrf52832-based-smart-watch-available/)
* [DS-D6](https://github.com/fanoush/ds-d6) from [@fanoush](https://github.com/fanoush)