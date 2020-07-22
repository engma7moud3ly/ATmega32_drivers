#include <config.h>
#include <serial.h>
#include <keybad.h>
#include <lcd.h>
#include <adc.h>
#include <fsm_stepper.h>
#include <pwm.h>

#define F_CPU 8000000UL

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