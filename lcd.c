#include <lcd.h>

uint8_t *DATA_PORT;
uint8_t *DATA_DIR;
uint8_t *CTRL_PORT;
uint8_t *CTRL_DIR;
uint8_t MODE;
uint8_t RE;
uint8_t RW;
uint8_t RS;

void lcd_init(uint8_t *dport, uint8_t *cport, uint8_t rE, uint8_t rW, uint8_t rS, uint8_t mode)
{
    DATA_PORT = dport;
    DATA_DIR = dport - 1;
    CTRL_PORT = cport;
    CTRL_DIR = cport - 1;
    RE = rE;
    RW = rW;
    RS = rS;
    MODE = mode;

    if (MODE == MODE_4_BIT)
        *(DATA_DIR) |= 0xF0;
    else
        *(DATA_DIR) = 0xFF;

    *(CTRL_DIR) |= (1 << RE) | (1 << RW) | (1 << RS);
    if (MODE == MODE_4_BIT)
    {
        lcd_cmd(0x33);
        lcd_cmd(0x32);
        lcd_cmd(0x28);
        lcd_cmd(0x0e);
    }
    lcd_cursor_on(true);
    lcd_clear();
}

void lcd_clear()
{
    lcd_cmd(0x01);
}
void lcd_cursor_on(bool on)
{
    lcd_cmd(on ? 0x0E : 0x0C);
}

void lcd_cursor_pos(uint8_t x, uint8_t y)
{
    uint8_t c[] = {0x80, 0xC0, 0x94, 0xD4};
    lcd_cmd(c[y - 1] + x - 1);
    delay(1);
}

void lcd_cmd(uint8_t data)
{
    *(CTRL_PORT) &= ~(1 << RS); //commands/data
    *(CTRL_PORT) &= ~(1 << RW); //write mode
    if (MODE == MODE_4_BIT)
    {
        load_cmd((*(CTRL_PORT)&0x0F) | (data & 0xF0));
        load_cmd((*(CTRL_PORT)&0x0F) | (data << 4));
    }
    else
    {
        load_cmd(data);
    }
}

void load_cmd(uint8_t data)
{
    *(DATA_PORT) = data;
    *(CTRL_PORT) |= (1 << RE);
    delay(1);
    *(CTRL_PORT) &= ~(1 << RE);
    delay(1);
}

void lcd_write(unsigned char data)
{
    *(CTRL_PORT) = (*(CTRL_PORT)&0x0F) | (data & 0xF0);

    *(CTRL_PORT) |= (1 << RS);  //write data
    *(CTRL_PORT) &= ~(1 << RW); //write mode
    if (MODE == MODE_4_BIT)
    {
        load_cmd((*(CTRL_PORT)&0x0F) | (data & 0xF0));
        load_cmd((*(CTRL_PORT)&0x0F) | (data << 4));
    }
    else
    {
        load_data(data);
    }
}
void load_data(unsigned char data)
{
    *(DATA_PORT) = data;
    *(CTRL_PORT) |= (1 << RE);
    delay(1);
    *(CTRL_PORT) &= ~(1 << RE);
    delay(1);
}
void lcd_write2(char data) //4 bit interface
{
    *(CTRL_PORT) |= (1 << RS);
    *(CTRL_PORT) &= ~(1 << RW);
    delay(1);

    *(DATA_PORT) = data & 0xF0;
    delay(1);
    *(CTRL_PORT) |= (1 << RE);
    delay(1);
    *(CTRL_PORT) &= ~(1 << RE);
    delay(1);

    *(DATA_PORT) = (data << 4) & 0xF0;
    delay(1);
    *(CTRL_PORT) |= (1 << RE);
    delay(1);
    *(CTRL_PORT) &= ~(1 << RE);
    delay(1);
}

void lcd_write_string(char *str)
{
    while (*str != '\0')
    {
        lcd_write(*str);
        str++;
    }
}
