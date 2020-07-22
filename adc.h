/*
 *AVR:ATmega32 ADC driver
 *By : Mahmoud Aly
 *engma7moud3ly@gmail.com
*/

//ADC example
/*
  serial_begin(9600, false);
  //init  adc with AVCC ref voltage & pooling mode(no conversion intrrupt)
  adc_init(AVCC, false);
  while (true)
  {
    serial_print("ADC0 : ");
    //analog_read(Analog_Pin)
    //in2str() convert adc int value to string
    serial_println(int2str(adc_read(0)));
    delay(500);
    serial_print("ADC1 : ");
    serial_println(int2str(adc_read(1)));
    delay(100);
  }
*/

#include <config.h>

//_VREF adc refrence voltage selection
#define AREF 0
#define AVCC 0x40
#define A256 0xC0

#define A0 PA0
#define A1 PA1
#define A2 PA2
#define A3 PA3
#define A4 PA4
#define A5 PA5
#define A6 PA6
#define A7 PA7

//init  adc
//vref : adc refernce voltage, cam be AREFF,AVCC,A256 (internal 2.56 volt)
//enable_intrrupt : enable adc vonversion compelete intrrupt.
void adc_init(uint8_t vref, bool enable_intrrupt);

//read analog voltage on a specific adc channel
//pin : can be A0-A7
uint16_t analog_read(uint8_t pin);
