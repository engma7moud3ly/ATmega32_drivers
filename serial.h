/*
 *AVR:ATmega32 USART driver
 *By : Mahmoud Aly
 *engma7moud3ly@gmail.com
*/

//USART example
/*

#include <serial.h>
int main()
{

  serial_begin(9600, true);
  serial_send('H'); //send single char
  serial_send('i');
  serial_send('\r');
  serial_println("Hello World"); //send a string
  while (true);
  return 0;
}

ISR(USART_RXC_vect) //receive data when it is available on RX
{
  if (serial_available())
  {
    serial_send(serial_read());
    serial_send('\r');
  }
}
*/

#include<config.h>
/*
*baud_rad : UART baud rate , ex 9600..
*intrrupt_enable : true | false
* if intrrupt_enable=true,  it will set RXCIE (receive intrrupt enable)
*/
void serial_begin(uint16_t baud_rate, bool intrrupt_enable);

//read data register content
//this does not check if data compeletly received
//shoud be used with available() function
char serial_read();
//read charchter if available
char serial_read_blocking();
//read a string untill..
void serial_read_until(char c, char str[]);
//return true if data received compeletly and available on data register (UDR)
uint8_t serial_available();
//send a single char on TX
void serial_send(char c);
//send single char + new line \r
void serial_sendln(char c);
//send a string
void serial_print(char *str);
//send a string + new line.
void serial_println(char *str);
