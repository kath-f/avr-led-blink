#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

#define LED_PIN PB0 //PB0 is mapped to port 8 on an arduino uno r3

int main(void){
  DDRB |= (1 << LED_PIN); //sets pin to be output
  
  //the DDRx register dictate pin direction (input or output) and each byte in it correponds to a pin
  //so we are writing for pin 0 in bank B to be output (1 is output, 0 is input)
  while(1){
    PORTB ^= (1 << LED_PIN); //the PORTx register dictates wether the pin is high or low
    //each bit in PORTx is equivalent to a pin, so PORTB 0b00000001 sets the 0th pin in bank B to high
    _delay_ms(500); //finally do a little delay before changing the state
  }
}
