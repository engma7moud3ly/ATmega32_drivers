/*
 *AVR:ATmega32 SPI driver
 *By : Mahmoud Aly
 *engma7moud3ly@gmail.com
*/


//spi master mode example
/*#include <config.h>
#include <spi.h>
int main()
{
  //init spi in master mode
  spi_master(&PORTB, MOSI, SCLK, SS, false);
  while (true)
  {
    //send a string "Hello World" + new line/carriage return '\n'
    spi_println("Hello World");
    delay(500);
  }
  return 0;
}
*/

//spi slave mode
/*
#include <config.h>
#include <serial.h>
#include <spi.h>

int main()
{

  //init UART in baud rate 9600
  serial_begin(9600, false);
  //init spi in slave mode
  spi_salve(&PORTB, MISO, false);
  while (true)
  {
    char str[10];
    
    //spi read the coming charachter stream untill carriage return' \r' and store it in (str) array
    //thats mean  spi receive a full line.
    spi_read_until('\r', str);
    //print the string  on UART
    serial_println(str);
  }
}
*/

#include <config.h>

#define MOSI 5
#define MISO 6
#define SCLK 7
#define SS 4

uint8_t *PORTX;
uint8_t *DDRX;

//init spi in master mode
/* portx : pointer to port of spi pins (miso/mosi/ss/sclk)
 * mosi  : pin mosi in portx
 * sclk  : pin sclk in portx
 * ss  : ss in portx 
 * enable_intrrupt  : if true, it set SPIE(intrrupt enable pin)
 */
void spi_master(uint8_t *portx, uint8_t mosi, uint8_t sclk, uint8_t ss, bool enable_intrrupt);
//init spi in slave mode
/* portx : pointer to port of spi pins (miso/mosi/ss/sclk)
 * miso  : pin miso in portx
 * enable_intrrupt  : if true, it set SPIE(intrrupt enable pin)
 */
void spi_salve(uint8_t *portx, uint8_t miso, bool enable_intrrupt);
//read data register (SPDR) when data available on it
char spi_read_blocking();
//read data (SPDR) register any why
char spi_read();
//return true if data compeletly received.
uint8_t spi_available();
//read a string untill..
void spi_read_until(char c, char str[]);
//send single char from master or slave
void spi_send(char);
//send single char + new line from master or slave
void spi_sendln(char);
//send a string from master or slave
void spi_print(char *);
//send a string  + new line from master or slave
void spi_println(char *);
