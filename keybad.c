/*
 *AVR:ATmega32 keybad driver
 *By : Mahmoud Aly
 *engma7moud3ly@gmail.com
*/

#include <keybad.h>

//matrix of the keybad charchters
const unsigned char key_matrix[4][4] =
    {
        {'C', '0', '=', '+'},
        {'1', '2', '3', '-'},
        {'4', '5', '6', 'X'},
        {'7', '8', '9', '/'}};

void (*keybad_on_key_press)(char);

void keybad_init(uint8_t *portx, uint8_t rows[], uint8_t cols[], void (*call_back)(char c))
{
  keybad_on_key_press = call_back;
  KPORTX = portx;
  KDDRX = KPORTX - 1;
  KPINX = KDDRX - 1;

  uint8_t i;
  for (i = 0; i < 4; i++)
  {
    COLS[i] = cols[i];
    ROWS[i] = rows[i];
  }
  for (i = 0; i < 4; i++)
  {
    *(KDDRX) |= (1 << ROWS[i]);  //set keybad rows output
    *(KPORTX) |= (1 << ROWS[i]); //set keybad rows high

    *(KDDRX) &= ~(1 << COLS[i]); //set keybad cols input
    *(KPORTX) |= (1 << COLS[i]); //enable cols pull-up res
  }
}

void keybad_read(uint16_t delay)
{
  uint8_t c, r = 0;
  for (r = 0; r < 4; r++)
  {
    *(KPORTX) &= ~(1 << ROWS[r]);
    for (c = 0; c < 4; c++)
    {
      uint8_t btn = *(KPINX) & (1 << COLS[c]);
      if (!btn)
      {
        keybad_on_key_press(key_matrix[r][c]);
        delay(delay);
      }
    }
    delay(1);
    *(KPORTX) |= (1 << ROWS[r]);
  }
}
