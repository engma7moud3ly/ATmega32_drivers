/*
  --->how to 

  //drive lcd1 in 4 bit mode on PORTC  ,use PC4-7 for data & PC0,PC1,PC2 for RE,RW,RS.
  lcd_init(&PORTC, &PORTC, 0, 1, 2, MODE_4_BIT);
  lcd_write_string("hello");
  //drive lcd2 in 8 bit mode on PORTB,A  ,use PB0-7 for data & PA7,PA6,PA5 for RE,RW,RS.
  lcd_init(&PORTB, &PORTA, 7, 6, 5, MODE_8_BIT);
  lcd_write_string("wrold");

*/
#include <config.h>

#define MODE_4_BIT 1
#define MODE_8_BIT 0

/*dport -> data port refernce &PORTA ex..
 *cport -> lcd control port (in 4 bit mode can be the same data port) 
 *RE    -> RE pin
 *RW    -> RW pin
 *RS    -> RS pin
 *mode -> MODE_4_BIT or MODE_8_BIT
 */
void lcd_init(uint8_t *dport, uint8_t *cport, uint8_t rE, uint8_t rW, uint8_t rS, uint8_t mode);
void lcd_cmd(uint8_t data);
void lcd_write(unsigned char data);
void lcd_cursor_on(bool on);
void lcd_cursor_pos(uint8_t x, uint8_t y);
void lcd_clear();
void lcd_write_string(char *str);