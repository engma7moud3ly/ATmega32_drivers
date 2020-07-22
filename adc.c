/*
 *AVR:ATmega32 USART driver
 *By : Mahmoud Aly
 *engma7moud3ly@gmail.com
*/

#include <adc.h>

void adc_init(uint8_t _VREF, bool enable_intrrupt)
{
    ADCSRA = 0x87; //128 prescaler/aden
    if (enable_intrrupt)
    {
        ADCSRA |= (1 << ADIE); //enable conversion intrrupt
        SREG |= (1 << 7);      //enable intrrupts globally
        ADCSRA |= (1 << ADSC); //start conversion
    }
    ADMUX |= _VREF; //voltage refrence
}
uint16_t analog_read(uint8_t pin)
{
    ADMUX &= 0xF0;
    ADMUX |= pin;
    volatile uint16_t analog;
    ADCSRA |= (1 << ADSC);          //start conversion
    while (!(ADCSRA & (1 << ADIF))) //wait until convert
        ;
    analog = ADCL;
    analog = (ADCH << 8) | analog;
    return analog;
}