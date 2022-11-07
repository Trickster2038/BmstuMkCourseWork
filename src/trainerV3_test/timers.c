#include <avr/io.h>

void timer0_init(){
	//TCCR0 = (1<<CS01) | (1 << CS00); // K = 64
	TCCR0 = (1<<CS01); // K = 8
	TIMSK |= (1<<TOIE0); // allow interrupt
}

void timer1_init(){
	TCNT1=0x00; // ticks
	TCCR1B |= (1<<CS10); // K = 1
	OCR1A = (unsigned int) (F_CPU / 1000); // compare num
	TIMSK |= (1<<OCIE1A); // launch timer	
}
