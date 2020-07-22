/*
 *AVR:ATmega32 PWM driver
 *By : Mahmoud Aly
 *engma7moud3ly@gmail.com
*/

#include <pwm.h>

//function caculate the value loaded to OCRx register based on modulation mode & duty cycle
uint8_t OCR(uint8_t mode, uint8_t duty)
{
    uint8_t ocr = 0;
    if (mode == FAST_PWM_NON_INVERTED)
        ocr = 2.56 * duty - 1;
    else if (mode == FAST_PWM_INVERTED)
        ocr = 255 - 2.56 * duty;
    else if (mode == PHASE_PWM_NON_INVERTED)
        ocr = 2.55 * duty;
    else if (mode == PHASE_PWM_INVERTED)
        ocr = 255 - 2.55 * duty;

    if (ocr == 0 || duty < 0)
        ocr = 255 - 2.55 * 50;
    return ocr;
}


void pwm(uint8_t pin, uint8_t duty, uint8_t mode, uint8_t prescaler)
{
    uint8_t *OCRx, *TCCRx;
    switch (pin)
    {
    case OC0:
        DDRB |= (1 << OC0);
        OCRx = &OCR0;
        TCCRx = &TCCR0;
        break;
    case OC2:
        DDRD |= (1 << OC2);
        OCRx = &OCR2;
        TCCRx = &TCCR2;
        break;
    case OC1A:
        DDRD |= (1 << OC1A);
        TCCRx = &TCCR1B;
        OCRx = &OCR1AL;
        TCCR1A = 0x81;
        mode = 0x8;
    default:
        break;
    }
    *OCRx = OCR(mode, duty);
    *TCCRx = mode | prescaler;
}
