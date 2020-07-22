/*
 *AVR:ATmega32 I2C driver
 *By : Mahmoud Aly
 *engma7moud3ly@gmail.com
*/

#include <spi.h>

void i2c_start()
{
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
    while (!(TWCR & (1 << TWINT)))
        ;
}
void i2c_stop()
{
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);
    delay(1);
    //no intrrupt pooling after stop :3
}

void i2c_send(unsigned char c)
{
    TWDR = c;
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
    while (!(TWCR & (1 << TWINT)))
        ;
}

void i2c_listen()
{
    while (!(TWCR & (1 << TWINT)))
        ;
}

unsigned char i2c_read(bool multiple_byte)
{
    TWCR = (1 << TWINT) | (1 << TWEN) | (multiple_byte << TWEA); //enable ack to read multiple
    while (!(TWCR & (1 << TWINT)))
        ;
    return TWDR;
}

void i2c_master()
{
    TWSR = 0;    //zero prescaler
    TWBR = 0x47;   //Fsdl=Fclk/(16+2*71*4^0)=50K
    TWCR = 0x04; //TWE enable
}

void i2c_salve(uint8_t address)
{
    TWCR = 0x04; //TWE enable
    TWAR = address;
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
}
uint8_t address(uint8_t a)
{
    return ((0b01111111 & a) << 1);
}