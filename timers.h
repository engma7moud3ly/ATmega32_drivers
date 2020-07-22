#include <config.h>

#define PRESCALER_1 1
#define PRESCALER_8 2
#define PRESCALER_64 3
#define PRESCALER_256 4
#define PRESCALER_1024 5

void counter0_init();
void counter0_count();
void timer0_delay(uint8_t tcnt, uint8_t prescaler);
void timer1_delay(uint16_t tcnt, uint8_t prescaler);
void timer2_delay(uint8_t tcnt, uint8_t prescaler);
void timer_delay_ms(uint16_t ms);
