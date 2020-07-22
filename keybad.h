/*
 *AVR:ATmega32 keybad driver
 *By : Mahmoud Aly
 *engma7moud3ly@gmail.com
*/

/*

//keybad example

#include <config.h>
#include <serial.h>
#include <keybad.h>

//when user press  key, send it on serial port.
void on_key_press(char c)
{
  serial_sendln(c);
  delay(100);
}

int main()
{
  serial_begin(9600, false); //init serial communication

  uint8_t rows[4] = {0, 1, 2, 3}; //an array for pins used for keybad  rows
  uint8_t cols[4] = {4, 5, 6, 7}; //an array for pins used for keybad  cols

  //initialization function
  //-- &PORTB a reference to port B connected to keybad
  //-- row,cols pin numbers array
  //-- on_key_press a callback functions,invoked when user press a key

  keybad_init(&PORTB, rows, cols, &on_key_press);
  while (true)
  {
    //pooling for keys being pressed.
    keybad_read(100);
  }

  return 0;
}
*/

#include <config.h>
//pointers for the register of the port connected to the keybad.
uint8_t *KPORTX;
uint8_t *KDDRX;
uint8_t *KPINX;

uint8_t ROWS[4];
uint8_t COLS[4];

/*initialization of keybad 4*4
 *portx : a pointer to the reference of port connected to keybad , ex:&PORTB 
 *rows : an array of pins of portx connected to keybad rows.
 *cols : an array of pins of portx connected to keybad columns
 * call_back : a function pointer, to the function invoked in main.c when user press on a key.
 */
void keybad_init(uint8_t *portx, uint8_t rows[], uint8_t cols[], void (*call_back)(char c));

/*
 *read function start pooling to get keybad pressed key
 *delay : delay occurs when MCU detects a key pressed to avoid debouncing effects..
 */
void keybad_read(uint16_t delay);
