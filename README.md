# ATmega32_drivers
friendly C drivers for Atmega32 microcontroller.
#### drivers includes :
- serial library
- spi library
- i2c library
- timers/pwm library
- keybad/lcd library
- stepper motor library

#### ِAn example covers all libraries 
- See Protues schematic & simulation (all_drivers.pdsprj)
![Protues schematic](/screenshot.jpg)
- main.c for full code
```
#include <config.h>
#include <serial.h>
#include <keybad.h>
#include <lcd.h>
#include <adc.h>
#include <fsm_stepper.h>
#include <pwm.h>

#define F_CPU 8000000UL

//callback function invoked when user press on keybad key
void on_key_press(char c)
{
  lcd_clear();
  lcd_write_string("you pressed :");
  lcd_write(c);
}

volatile uint8_t pwm_duty = 90;
volatile uint8_t stepper_direction = CCW;

int main()
{
  //init keybad on PORTC, with on_key_press callback function.
  uint8_t rows[4] = {0, 1, 2, 3};
  uint8_t cols[4] = {4, 5, 6, 7};
  keybad_init(&PORTC, rows, cols, &on_key_press);

  //init lcd on PORTA in 4 bit mode
  lcd_init(&PORTA, &PORTA, PA3, PA2, PA1, MODE_4_BIT);
  lcd_write_string("Press On Keybad :)");
  lcd_cursor_on(false);

  //init UART in baud rate 9600.
  serial_begin(9600, false);

  //init adc with AVCC reference voltage.
  adc_init(AVCC, false);

  //generate PWM signal on pin(PD7) with duty cycle pwm_duty=90
  //to control DC motor speed
  pwm(PD7, pwm_duty, FAST_PWM_NON_INVERTED, PRESCALER_1024);

  //configure pin INT0(PD2),INT1(PD3) to respond to extrenal buttons triggers
  PORTD |= (1 << INT0) | (1 << INT1); //enable pull-up resistor of pin PD2,PD3
  GICR = (1 << INT0) | (1 << INT1);   //enable INT0,INT1 tntrrupt
  SREG = (1 << 7);                    //set I flag (enable global intrrupt)

  //set portB output to drive the stepper motor
  DDRB = 0xFF;
  while (true)
  {
    //check if user click on keybad
    keybad_read(100);

    //read/convert analog voltage on (PA0) and print it through serial port.
    serial_print("PA0 voltage = ");
    uint16_t val = analog_read(A0);
    char *str_val = float2str(val * 5 / 1023.0, 2);
    serial_println(str_val);

    //rotate stepper motor in (half step) mode with step delay (10ms)
    rotate(&PORTB, HALF_STEP, 10, stepper_direction);
  }
  return 0;
}

//INT0 intrrupt service routine
//this changes the speed of the DC motor M1
//by changing the PWM duty cycle
ISR(INT0_vect)
{
  //increase duty cycle
  pwm_duty += 10;
  if (pwm_duty > 100)
    pwm_duty = 10;
  //set new PWM duty cycle
  pwm(PD7, pwm_duty, FAST_PWM_NON_INVERTED, PRESCALER_1024);
  //write duty cyclel on LCD
  lcd_clear();
  lcd_write_string("duty cycle = ");
  lcd_write_string(int2str(pwm_duty));
}

//INT1 intrrupt service routine
//this changes the rotation direction of the stepper motor
ISR(INT1_vect)
{
  lcd_clear();
  lcd_write_string("rotation:");
  if (stepper_direction == CW)
  {
    stepper_direction = CCW;
    lcd_write_string("CCW");
  }
  else
  {
    stepper_direction = CW;
    lcd_write_string("CW");
  }
  delay(50);
}
```

#### UART example
```
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
```

#### SPI example
- SPI Master
```
#include <config.h>
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
````
- SPI Slave
```

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
    
    //spi read the coming charachter stream untill carriage return' \r'
    //and store it in (str) array
    //thats mean  spi receive a full line.
    spi_read_until('\r', str);
    //print the string  on UART
    serial_println(str);
  }
}
```
#### LCD example
```
  //drive lcd1 in 4 bit mode on PORTC
  //use PC4-7 for data & PC0,PC1,PC2 for RE,RW,RS.
  lcd_init(&PORTC, &PORTC, 0, 1, 2, MODE_4_BIT);
  lcd_write_string("hello");
  //drive lcd2 in 8 bit mode on PORTB,A
  //use PB0-7 for data & PA7,PA6,PA5 for RE,RW,RS.
  lcd_init(&PORTB, &PORTA, 7, 6, 5, MODE_8_BIT);
  lcd_write_string("wrold");
  ```
  #### Keybad example
  ```
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
````
#### PWM example
```
  //write a PWM signal on pin PB3(OC0),with duty cycle 50, and no clock divider F=Fosc
  //pwm modulation=non-inverted fast pwm
  pwm(OC0, 50, FAST_PWM_NON_INVERTED, PRESCALER_1);
  //write a PWM signal on pin PD7(OC2),with duty cycle 75, and clock divider F=Fosc/8
  //pwm modulation=inverted phase correct
  pwm(OC2, 75, PHASE_PWM_INVERTED, PRESCALER_8);
  ```
  
  #### Stepper Motor dexample
  ```
  #include <fsm_stepper.h>

int main()
{
  DDRB = DDRC = DDRD = 0xFF;
  while (true)
  {
    //rotate function accept 4 parameters
    //a refrence to the port connected to the motor
    //type of step full/half/wave step
    //step delay in ms
    //rotation direction CW/CCW
    rotate(&PORTB, FULL_STEP, 20, CW);
    rotate(&PORTC, HALF_STEP, 20, CW);
    rotate(&PORTD, WAVE_STEP, 20, CCW);
  }
  return 0;
}
````
  
  
  
  
  
