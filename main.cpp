
#include "hardware.h"
#include "iic_event.h"
#include "button.h"

void setup(void)
{
  // Initialize LCD
  lcd.begin(LCD_ROWS, LCD_COLS);
  pinMode(LCD_BL, OUTPUT);
  digitalWrite(LCD_BL, 1);

  // Initialize IIC
  Wire.begin(get_busaddr(0));
  Wire.onReceive(iic_read);
  Wire.onRequest(iic_write);

  // Initialize buttons
  button_init();

  // Initialize debug UART
  Serial.begin(115200);

  // Print the version information
  lcd.clear();
  lcd.print(F("M177v2 FW 2A726a"));
  lcd.home();
}

void loop(void)
{
  button_update();
}


