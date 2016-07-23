
#include "iic_commands.h"
#include "hardware.h"
#include <avr/wdt.h>
#include <EEPROM.h>

LiquidCrystal lcd(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

void wdt_init(void) __attribute__((naked, section(".init3")));
// Function Implementation
void wdt_init(void)
{
  noInterrupts();
  MCUSR = 0;
  wdt_disable();

  return;
}

void reset(void)
{
  wdt_enable(WDTO_15MS);
  for (;;);
}

READ_HANDLER(set_busaddr)
{
  if (val < 0x03 || val > 0x77) val = IIC_ADDR;
  EEPROM.update(IIC_EEP, val);
}

WRITE_HANDLER(get_busaddr)
{
  uint8_t val = EEPROM.read(IIC_EEP);
  if (val < 0x03 || val > 0x77) val = IIC_ADDR;
  return val;
}

