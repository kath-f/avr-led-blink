#include <avr/io.h>
#include <avr/interrupt.h>

#define SET_LOW(REG, BIT)  (REG &= ~(1 << BIT))
#define SET_HIGH(REG, BIT) (REG |=  (1 << BIT))

#define GET_STATE(REG, BIT) ((REG >> BIT) & 1)

#define SET_OUTPUT(PORT, PIN) (SET_HIGH(PORT, PIN))
#define SET_INPUT(PORT, PIN)  (SET_LOW(PORT, PIN))

#define TIMER_PRELOAD (65536 - (F_CPU/1024))

#define LED_PIN PB5

ISR (TIMER1_OVF_vect){
  PORTB ^= (1 << LED_PIN);
  TCNT1 = TIMER_PRELOAD;
}

int main(void){
  SET_OUTPUT(DDRB, LED_PIN); //set LED_PIN to output

  SET_HIGH(PORTB, LED_PIN);
  
  TCNT1 = TIMER_PRELOAD;
  TCCR1A = 0x00;
  SET_HIGH(TIMSK1, TOIE1); //Sets overflow interrupt to enabled

  TCCR1B = 0b00000101; //Sets the clock source to internal clock with 1024 prescaler

  sei();

  while(1){
    
  }
}
