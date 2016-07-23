#ifndef BUTTON_H
#define BUTTON_H

#include <Arduino.h>
#include <Bounce2.h>
#include "iic_commands.h"
#include "hardware.h"

extern Bounce esc;
extern Bounce prev;
extern Bounce ok;
extern Bounce next;

extern uint8_t buttons;

void button_init(void);
void button_update(void);
void button_read_all(void);

#endif
