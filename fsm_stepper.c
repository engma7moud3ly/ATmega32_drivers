/*
 *AVR:ATmega32 FSM-stepper driver
 *By : Mahmoud Aly
 *engma7moud3ly@gmail.com
*/

#include <fsm_stepper.h>

StepSequence half_step[8] = {
    {0b1001, {&half_step[1], &half_step[7]}},
    {0b1000, {&half_step[2], 0}},
    {0b1100, {&half_step[3], &half_step[1]}},
    {0b0100, {&half_step[4], &half_step[2]}},
    {0b0110, {&half_step[5], &half_step[3]}},
    {0b0010, {&half_step[6], &half_step[4]}},
    {0b0011, {&half_step[7], &half_step[5]}},
    {0b0001, {0, &half_step[6]}},
};
StepSequence full_step[4] = {
    {0b1001, {&full_step[1], &full_step[3]}},
    {0b1100, {&full_step[2], 0}},
    {0b0110, {&full_step[3], &full_step[1]}},
    {0b0011, {0, &full_step[2]}},
};

StepSequence wave_step[4] = {
    {0b1000, {&wave_step[1], &wave_step[3]}},
    {0b0100, {&wave_step[2], 0}},
    {0b0010, {&wave_step[3], &wave_step[1]}},
    {0b0001, {0, &wave_step[2]}},
};

void rotate(uint16_t *portx, uint8_t step_type, uint16_t step_delay, uint8_t step_direction)
{
    StepSequence *ptr;

    switch (step_type)
    {
    case HALF_STEP:
        ptr = &half_step;
        break;
    case FULL_STEP:
        ptr = &full_step;
        break;
    case WAVE_STEP:
        ptr = &wave_step;
        break;
    default:
        ptr = &full_step;
        break;
    }

    while (ptr)
    {
        uint8_t out = ptr->out;
        *portx = out;
        ptr = ptr->next[step_direction];
        delay(step_delay);
    }
    *portx = 0;
}
