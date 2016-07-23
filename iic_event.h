#ifndef IIC_EVENT_H
#define IIC_EVENT_H

#include <Arduino.h>
#include <Wire.h>
#include "iic_commands.h"

typedef READ_HANDLER((* read_handler_t));
typedef WRITE_HANDLER((* write_handler_t));

void iic_read(int len);
void iic_write(void);

void print_byte(uint8_t x);

#endif
