/*
 *AVR:ATmega32 FSM-stepper driver
 *By : Mahmoud Aly
 *engma7moud3ly@gmail.com
*/

//Finite State Machine - Stepper Motor Driver
/*
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
    rotate(&PORTD, WAVE_STEP, 20, CW);
  }
  return 0;
}

*/

#include <config.h>

//rotation direction
#define CW 0
#define CCW 1
//step type
#define HALF_STEP 2
#define FULL_STEP 3
#define WAVE_STEP 4

struct state
{
  unsigned char out;           // Output
  const struct State *next[2]; // CW/CCW
};
typedef const struct state StepSequence;

/*rotate function accept 4 parameters
 * a refrence to the port connected to the motor ex:  &PORTB
 * step type :HALF_STEP/FULL_STEP/WAVE_STEP
 * step delay in ms
 * rotation direction : CW/CCW
*/
void rotate(uint16_t *portx, uint8_t step_type, uint16_t step_delay, uint8_t step_direction);