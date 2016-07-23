
#include "iic_commands.h"
#include "hardware.h"

uint8_t lcd_flags = 0;
READ_HANDLER(set_flags)
{
  val &= 0x1f;
  uint8_t updated_flags = lcd_flags ^ val;

#define CHECK_UPDATE(x, set, clear) do { if (updated_flags & _BV(x)) { if (val & _BV(x)) { set; } else { clear; } } } while(0)
  CHECK_UPDATE(0, lcd.display(), lcd.noDisplay());
  CHECK_UPDATE(1, lcd.blink(), lcd.noBlink());
  CHECK_UPDATE(2, lcd.cursor(), lcd.noCursor());
  CHECK_UPDATE(3, lcd.leftToRight(), lcd.rightToLeft());
  CHECK_UPDATE(4, lcd.autoscroll(), lcd.noAutoscroll());
#undef CHECK_UPDATE

  lcd_flags = val;
}

WRITE_HANDLER(get_flags)
{
  return lcd_flags;
}

READ_HANDLER(set_action)
{
  switch (val)
  {
    case 0:
      lcd.clear();
      break;
    case 1:
      lcd.home();
      break;
    case 2:
      lcd.scrollDisplayLeft();
      break;
    case 3:
      lcd.scrollDisplayRight();
      break;
    case 0xff:
      reset();
      break;
    default:
      read_null(var, val);
      break;
  }
}

READ_HANDLER(set_cursor)
{
  uint8_t row = val >> 6;
  uint8_t col = val & 0x3f;

  lcd.setCursor(col, row);
}

uint8_t backlight_level = 0xff;
READ_HANDLER(set_backlight)
{
  analogWrite(LCD_BL, backlight_level = val);
}

WRITE_HANDLER(get_backlight)
{
  return backlight_level;
}

READ_HANDLER(set_character)
{
  lcd.write(val);
}

uint8_t cgram[8] = {0};
READ_HANDLER(set_chargen)
{
  uint8_t ch = val % 0x7;
  lcd.createChar(ch, cgram);
}

READ_HANDLER(set_cgram)
{
  uint8_t addr = var % 8;
  cgram[addr] = val;
}

WRITE_HANDLER(get_cgram)
{
  uint8_t addr = var % 8;
  return cgram[addr];
}

