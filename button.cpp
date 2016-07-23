#include "button.h"

Bounce esc;
Bounce prev;
Bounce ok;
Bounce next;

uint8_t buttons = 0;

void button_init(void)
{
  pinMode(IRQ, OUTPUT);
  
  esc.attach(BTN_ESC);
  esc.interval(BTN_WAIT);

  prev.attach(BTN_PREV);
  prev.interval(BTN_WAIT);

  ok.attach(BTN_OK);
  ok.interval(BTN_WAIT);

  next.attach(BTN_NEXT);
  next.interval(BTN_WAIT);

  button_read_all();
}

void button_update(void)
{
  bool irq = false;
  irq |= esc.update();
  irq |= prev.update();
  irq |= ok.update();
  irq |= next.update();

  if (irq)
  {
    // Assert the interrupt signal. Requires critical section.
    noInterrupts();
    button_read_all();
    digitalWrite(IRQ, HIGH);
    interrupts();
  }
}

void button_read_all(void)
{
  buttons = 0;
  if (!esc.read()) buttons |= BIT_ESC;
  if (!prev.read()) buttons |= BIT_PREV;
  if (!ok.read()) buttons |= BIT_OK;
  if (!next.read()) buttons |= BIT_NEXT;
}

WRITE_HANDLER(get_button)
{
  digitalWrite(IRQ, LOW);
  return buttons;
}

