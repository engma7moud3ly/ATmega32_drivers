/*
 *AVR:ATmega32 USART driver
 *By : Mahmoud Aly
 *engma7moud3ly@gmail.com
*/

#include <serial.h>

void serial_begin(uint16_t baud_rate, bool intrrupt_enable)
{
    UCSRA |= (1 << U2X);
    UCSRB = (1 << RXEN) | (1 << TXEN);
    if (intrrupt_enable)
    {
        UCSRB |= (1 << RXCIE);
        SREG |= (1 << 7);
    }
    UCSRC = (1 << URSEL) | (1 << UCSZ0) | (1 << UCSZ1);
    uint16_t _ubbr = (8000000 / (16 * baud_rate)) - 1;
    UBRRL = _ubbr;
}

char serial_read()
{
    return UDR;
}
char serial_read_blocking()
{
    while (!(UCSRA & (1 << RXC)))
        ;
    return UDR;
}
void serial_read_until(char c, char str[20])
{
    for (uint8_t i = 0; i < 20; i++)
        str[i] = 0;
    uint8_t i = 0;
    volatile char cc;
    while ((cc = serial_read_blocking()) != c)
    {
        str[i++] = cc;
    }
}

uint8_t serial_available()
{
    return UCSRA & (1 << RXC);
}
void serial_send(char data)
{
    while (!(UCSRA & (1 << UDRE)))
        ;
    UDR = data;
}
void serial_sendln(char data)
{
    serial_send(data);
    serial_send('\r');
}
void serial_print(char *data)
{
    while (*data != '\0')
    {
        serial_send(*data);
        data++;
    }
}
void serial_println(char *data)
{
    while (*data != '\0')
    {
        serial_send(*data);
        data++;
    }
    serial_send('\r');
}