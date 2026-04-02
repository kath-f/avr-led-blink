#include <avr/io.h>
#include <avr/interrupt.h>

#define SET_LOW(REG, BIT)  (REG &= ~(1 << BIT))
#define SET_HIGH(REG, BIT) (REG |=  (1 << BIT))

#define GET_STATE(REG, BIT) ((REG >> BIT) & 1)

#define SET_OUTPUT(PORT, PIN) (SET_HIGH(PORT, PIN))
#define SET_INPUT(PORT, PIN)  (SET_LOW(PORT, PIN))

//this is like the effective 0 of the counter, 
//because with the prescaler the timer is ticking at F_CPU/1024 hz effectively (its like 15k or something)
//and we want the interrupt to be triggered every second, but it still is only triggered when there's an overflow (16 bit max num = 65536)
//so by setting it back this amount we can ensure that it will be 1 second by the time the interrupt gets triggered

#define TIMER_PRELOAD (65536 - (F_CPU/1024))

#define LED_PIN PB5

ISR (TIMER1_OVF_vect){ //this function gets called when the TIMER OVERFLOW interrupt is triggered
  PORTB ^= (1 << LED_PIN); //flips the value of LED_PIN
}

int main(void){
  SET_OUTPUT(DDRB, LED_PIN); //set LED_PIN to output

  SET_HIGH(PORTB, LED_PIN);
  
  TCNT1 = TIMER_PRELOAD;
  TCCR1A = 0x00;
  SET_HIGH(TIMSK1, TOIE1); //Sets overflow interrupt to enabled

  TCCR1B = 0b00000101; //Sets the clock source to internal clock with 1024 prescaler

  sei(); //enable system interrupts

  while(1){
    
  }
}
