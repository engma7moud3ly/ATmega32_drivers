#include <timers.h>

#ifndef F_CPU
#define F_CPU 8000000UL
#endif

uint16_t tcnt1(float d)
{
  return 65536 - ((d * F_CPU) / 1024);
}

void timer_delay_ms(uint16_t ms)
{
  if (ms > 8338)
    ms = 8388;
  timer1_delay(tcnt1(ms / 1000.0), PRESCALER_1024);
}

void timer0_delay(uint8_t tcnt, uint8_t prescaler)
{
  TCNT0 = tcnt;
  if (prescaler > 5)
    prescaler = 1;
  TCCR0 = prescaler;
  while (!(TIFR & (1 << TOV0)))
    ;
  TCCR0 = 0;
  TIFR |= (1 << TOV0);
}

void timer2_delay(uint8_t tcnt, uint8_t prescaler)
{
  TCNT2 = tcnt;
  if (prescaler > 5)
    prescaler = 1;
  TCCR2 = prescaler;
  while (!(TIFR & (1 << TOV2)))
    ;
  TCCR2 = 0;
  TIFR |= (1 << TOV2);
}

void timer1_delay(uint16_t tcnt, uint8_t prescaler)
{
  TCNT1L = (tcnt & 0x00FF);
  TCNT1H = ((tcnt & 0xFF00) >> 8);
  TCCR1A = 0x00;
  if (prescaler > 5)
    prescaler = 1;
  TCCR1B = prescaler;
  while (!(TIFR & (1 << TOV1)))
    ;
  TCCR1B = 0x00;
  TIFR |= 1 << TOV1;
}

void counter0_init()
{
  TCCR0 = 0x06;
  TCNT0 = 0;
}
void counter0_count()
{
  do
  {
    PORTC = TCNT0;
  } while (!(TIFR = 1 << TOV0));
  TIFR = 1 << TOV0;
}

/*

void init_TIMER1_INT(uint16_t n)
{
  TCNT1L = (n & 0x00FF);
  TCNT1H = ((n & 0xFF00) >> 8);
  TCCR1A = 0x00;
  TCCR1B = 0x02; //256 prescaler
  TIMSK = (1 << TOIE1);
  SREG = (1 << 7); //set I
}*/
