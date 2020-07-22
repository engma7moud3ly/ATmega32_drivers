/*
 *AVR:ATmega32 PWM driver
 *By : Mahmoud Aly
 *engma7moud3ly@gmail.com
*/
/*
  //write a PWM signal on pin PB3(OC0),with duty cycle 50, and no clock divider F=Fosc
  //pwm modulation=non-inverted fast pwm
  pwm(OC0, 50, FAST_PWM_NON_INVERTED, PRESCALER_1);
  //write a PWM signal on pin PD7(OC2),with duty cycle 75, and clock divider F=Fosc/8
  //pwm modulation=inverted phase correct
  pwm(OC2, 75, PHASE_PWM_INVERTED, PRESCALER_8);
*/

#include <config.h>

#define PRESCALER_1 1
#define PRESCALER_8 2
#define PRESCALER_64 3
#define PRESCALER_256 4
#define PRESCALER_1024 5
#define FAST_PWM_NON_INVERTED 0x68
#define FAST_PWM_INVERTED 0x78
#define PHASE_PWM_NON_INVERTED 0x60
#define PHASE_PWM_INVERTED 0x70
#define OC0 PB3
#define OC1A PD5
#define OC2 PD7

/*
 *a function generates PWM on specified pin.
 *pin  : can be PB3(OC0),PD7(OC2),PD5(OCA1)
 *duty : pwm duty cycle 1-100
 *mode : FAST_PWM_NON_INVERTED,FAST_PWM_INVERTED,
 PHASE_PWM_NON_INVERTED,PHASE_PWM_INVERTED 0x70
 *prescaler :clock divider  PRESCALER_1,PRESCALER_8,
 PRESCALER_64,PRESCALER_256,PRESCALER_1024
 */
void pwm(uint8_t pin, uint8_t duty, uint8_t mode, uint8_t prescaler);