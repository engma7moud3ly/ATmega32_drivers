#ifndef CONFIG_H
#define CONFIG_H

typedef enum
{
  true = 1,
  false = 0
} bool;

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define high(port, pin) (port |= (1 << pin))
#define low(port, pin) (port &= ~(1 << pin))
#define port_high(port) (port = 0xFF)
#define port_low(port) (port = 0x00)
#define toggle(port, pin) (port ^= (1 << pin))
#define port_toggle(port) (port = !port)
#define delay(d) (_delay_ms(d))
/*
#define DDRA *((volatile uint8_t *)0x3A)
#define PORTA *((volatile uint8_t *)0x3B)
#define PINA *((volatile uint8_t *)0x39)
*/

char *int2str(uint16_t n);
char *float2str(float n, uint8_t point);
#endif