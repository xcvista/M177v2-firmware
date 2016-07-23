
#include "iic_event.h"
#include "hardware.h"

bool initialized = false;

const PROGMEM read_handler_t read_handlers[256] =
{
  set_flags,  set_action, set_cursor, set_backlight,  set_character,  set_chargen,  set_busaddr,  set_button,
  set_cgram,  set_cgram,  set_cgram,  set_cgram,      set_cgram,      set_cgram,    set_cgram,    set_cgram,
  NULL
};

const PROGMEM write_handler_t write_handlers[256] =
{
  get_flags,  get_action, get_cursor, get_backlight,  get_character,  get_chargen,  get_busaddr,  get_button,
  get_cgram,  get_cgram,  get_cgram,  get_cgram,      get_cgram,      get_cgram,    get_cgram,    get_cgram, 
  NULL
};

void print_byte(uint8_t x)
{
  Serial.print(F("0x"));
  if (x < 0x10) Serial.print('0');
  Serial.print(x, HEX);
}

READ_HANDLER(read_null)
{
  Serial.print(F("Unknown set command: "));
  print_byte(var);
  Serial.print(':');
  print_byte(val);
  Serial.println();
}

WRITE_HANDLER(write_null)
{
  Serial.print(F("Unknown get command: "));
  print_byte(var);
  Serial.println();
  return 0;
}

uint8_t var = 0;

void check_init(void)
{
  if (!initialized)
  {
    initialized = true;
    lcd.clear();
  }
}

void iic_read(int len)
{
  if (len > 0)
  {
    check_init();
    var = Wire.read();

    while (Wire.available())
    {
      uint8_t val = Wire.read();
      read_handler_t read_handler = (read_handler_t)pgm_read_ptr((uintptr_t)(&read_handlers[var])) ?: read_null;
      read_handler(var, val);
    }
  }
}

void iic_write(void)
{
  check_init();
  write_handler_t write_handler = (write_handler_t)pgm_read_ptr((uintptr_t)(&write_handlers[var])) ?: write_null;
  Wire.write(write_handler(var));
}

