# M177v2 Reduced User Interface for Raspberry Pi

SushiBits M177v2 is a HAT that provides your Raspberry Pi with 4 programmable
buttons, a 16x2 character LCD screen and a high-percision real time clock.

Somewhat similar to the [Adafruit I2C 16x2 LCD Pi Plate][adafruit] by Adafruit,
this HAT have one fundamental difference: there is an onboard microcontroller
handling the LCD and button debouncing, and your program is presented a nicely
wrapped I2C interface with an interrupt line, making the programming on the Pi
much simpler.

[adafruit]: https://www.adafruit.com/product/1115

## What's on the board?

The major components on the PCB includes:

*   One 16x2 LCD compatible with Hitachi HD44780 interface,
*   Four tactile buttons,
*   One Maxim DS3231 high-percision real time clock with CR2032 backup battery,
*   One Atmel ATmega328P I/O Microcontroller
*   UARTs for the Pi and the ATmega328P

## Do not fry your Pi!

**Beware that the ATmega328P, while being powered by the +5V rail, is connected
directly to the I2C pins of the Pi without current limiting resistors or level
translators, pulled up to the 3.3V rail. You will fry your Pi if you forced +5V
into the Pi!** This arrangement allows me to use the cheaper 5V LCD modules and
run the microcontroller at 16MHz.

## Firmware features

This firmware implemented two features: high-level HD44780 LCD module access and
button interface with debouncing and interrupts. Both features are accessed over
I2C bus.

Refer to [the datasheet](M177v2-2A726a-Datasheet.pdf) for more details on the
interface.

## Acknowledgements

The firmware is an Arduino sketch, written using [Arduino IDE 1.6.9][arduino]
with its accompanying libraries under LGPLv3 licnese.

The sketch includes the following libraries:

*   [Bounce2](https://github.com/thomasfredericks/Bounce2) by Thomas Ouellet
    Fredericks, under MIT license

[arduino]: https://www.arduino.cc

## License

This program is writen by Max Chan. This code is licensed under the [3-clause
BSD license](LICENSE.md)

Copyright © 2015-2016 Max Chan. All rights reserved.