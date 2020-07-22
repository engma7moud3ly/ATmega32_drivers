/*
 *AVR:ATmega32 SPI driver
 *By : Mahmoud Aly
 *engma7moud3ly@gmail.com
*/
#include <spi.h>

void spi_master(uint8_t *portx, uint8_t mosi, uint8_t sclk, uint8_t ss, bool enable_intrrupt)
{
    PORTX = portx;
    DDRX = portx - 1;
    *(DDRX) |= (1 << sclk) | (1 << ss) | (1 << mosi);
    SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR0) | (enable_intrrupt << SPIE); //Fclk/16
}

void spi_salve(uint8_t *portx, uint8_t miso, bool enable_intrrupt)
{
    DDRX = portx - 1;
    *(DDRX) |= (1 << miso);
    SPCR = (1 << SPE) | (0 << MSTR) | (enable_intrrupt << SPIE);
}

char spi_read_blocking()
{
    while (!(SPSR & (1 << SPIF)))
        ;
    return SPDR;
}

char spi_read()
{
    return SPDR;
}

void spi_read_until(char c, char str[20])
{
    for (uint8_t i = 0; i < 20; i++)
        str[i] = 0;
    uint8_t i = 0;
    volatile char cc;
    while ((cc = spi_read_blocking()) != c)
    {
        str[i++] = cc;
    }
}

uint8_t spi_available()
{
    return SPSR & (1 << SPIF);
}

void spi_send(char c)
{
    SPDR = c;
    while (!(SPSR & (1 << SPIF)))
        ;
    delay(1);
}

void spi_sendln(char c)
{
    spi_send(c);
    spi_send('\r');
}

void spi_print(char *data)
{
    while (*data != '\0')
    {
        spi_send(*data);
        data++;
    }
}
void spi_println(char *data)
{
    while (*data != '\0')
    {
        spi_send(*data);
        data++;
    }
    spi_send('\r');
}