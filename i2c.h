/*
 *AVR:ATmega32 ADC driver
 *By : Mahmoud Aly
 *engma7moud3ly@gmail.com
*/
#include <config.h>

void i2c_start();
void i2c_stop();
void i2c_send(unsigned char);
unsigned char i2c_read(bool);
void i2c_master();
void i2c_salve(uint8_t);
void i2c_listen();
uint8_t address(uint8_t);
