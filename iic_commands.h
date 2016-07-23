#ifndef IIC_COMMANDS_H
#define IIC_COMMANDS_H

#include <Arduino.h>

#define READ_HANDLER(x)   void x(uint8_t __attribute__((unused)) var, uint8_t __attribute__((unused)) val)
#define WRITE_HANDLER(x)  uint8_t x(uint8_t __attribute__((unused)) var)
READ_HANDLER(read_null);
WRITE_HANDLER(write_null);

// 0x00: FLAGS
// BITS:      MSB | N/A[2..0] | autoscroll  | textDirection  | cursor  | blink | display | LSB
// DIRECTION: MSB |    N/A    |     R/W     |       R/W      |   R/W   |  R/W  |   R/W   | LSB
// DEFAULT:   MSB |    000    |      0      |        0       |    0    |   0   |    0    | LSB
//
// FLAG            | Meaning 0                         | Meaning 1
// autoscroll      | Turn off automatic text scrolling | Turn on automatic text scrolling
// textDirection   | Text moves from left to right     | Text moves from right to left
// cursor          | Show the cursor                   | Hide thecursor
// blink           | Blink the cursor                  | Keep the cursor shown constnatly
// display         | Turn on display                   | Turn off display
READ_HANDLER(set_flags);
WRITE_HANDLER(get_flags);

// 0x01: ACTION
// BITS:      MSB | action[7..0]  | LSB
// DIRECTION: MSB |       W       | LSB
// DEFAULT:   MSB |   0000 0000   | LSB
//
// ACTION | meaning
// 0x00   | clear display, home cursor
// 0x01   | reset cursor to home location
// 0x02   | scroll display to left
// 0x03   | scroll display to right
// 0xff   | reset
READ_HANDLER(set_action);
#define get_action NULL

// 0x02: CURSOR
// BITS:      MSB | row[1..0] | column[5..0]  | LSB
// DIRECTION: MSB |     W     |       W       | LSB
// DEFAULT:   MSB |    0 0    |    000 000    | LSB
//
// Move the cursor to the location as specified here.
READ_HANDLER(set_cursor);
#define get_cursor NULL

// 0x03: BACKLIGHT
// BITS:      MSB | backlight[7..0] | LSB
// DIRECTION: MSB |       R/W       | LSB
// DEFAULT:   MSB |    1111 1111    | LSB
//
// Set the backlight level.
READ_HANDLER(set_backlight);
WRITE_HANDLER(get_backlight);

// 0x04: CHARACTER
// BITS:      MSB | character[7..0] | LSB
// DIRECTION: MSB |        W        | LSB
// DEFAULT:   MSB |    0000 0000    | LSB
//
// Send a character to the display.
READ_HANDLER(set_character);
#define get_character NULL

// 0x05: CHARGEN
// BITS       MSB | N/A[4..0] | char[2..0]  | LSB
// DIRECTION: MSB |    N/A    |      W      | LSB
// DEFAULT:   MSB |   00000   |     000     | LSB
//
// Commit a character to CGRAM. (See CGRAM for the staging area)
READ_HANDLER(set_chargen);
#define get_chargen NULL

// 0x06: BUSADDR
// BITS:      MSB | N/A | busaddr[6..0] | LSB
// DIRECTION: MSB | N/A |      R/W      | LSB
// DEFAULT:   MSB |  0  |    1001000    | LSB
//
// Get or set the I2C bus address. Active after a reset. Set anything outside norm leads to default value.
READ_HANDLER(set_busaddr);
WRITE_HANDLER(get_busaddr);

// 0x07: BUTTON
// BITS:      MSB | N/A[3..0] | esc | prev  | ok  | next  | LSB
// DIRECTION: MSB |    N/A    |  R  |   R   |  R  |   R   | LSB
// DEFAULT:   MSB |   00 00   |  -  |   -   |  -  |   -   | LSB
//
// Get button status. Clears interrupt upon reading this.
#define set_button NULL
WRITE_HANDLER(get_button);

// 0x08-0x0f: CGRAM
// BITS:      MSB | cgram[7..0] | LSB
// DIRECTION: MSB |     R/W     | LSB
// DEFAULT:   MSB |  0000 0000  | LSB
//
// Get or set the CGRAM staging area contents.
READ_HANDLER(set_cgram);
WRITE_HANDLER(get_cgram);

#endif
