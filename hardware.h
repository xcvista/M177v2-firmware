#ifndef HARDWARE_H
#define HARDWARE_H

#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal.h>

#define IRQ       2

#define LCD_BL    3
#define LCD_D7    5
#define LCD_D6    6
#define LCD_D5    7
#define LCD_D4    8
#define LCD_EN    9
#define LCD_RS    10
#define LCD_ROWS  2
#define LCD_COLS  16
extern LiquidCrystal lcd;

#define BTN_ESC   A0
#define BTN_PREV  A1
#define BTN_OK    A2
#define BTN_NEXT  A3
#define BTN_WAIT  10

#define BIT_ESC   _BV(3)
#define BIT_PREV  _BV(2)
#define BIT_OK    _BV(1)
#define BIT_NEXT  _BV(0)

#define IIC_ADDR  0x48
#define IIC_EEP   0x0

void reset(void) __attribute__((noreturn));

#endif
