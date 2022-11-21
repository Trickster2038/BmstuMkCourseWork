#include <avr/io.h>

/*
	F_CPU / (2^8 * K) = 24 * 4
	2^8 - 8 bit T0
	24 - 24 Hz for stable picture at human eye
	4 - number of digits

	4_000_000 / (2^8 * K) = 24 * 4
	(K < 163) => (K = 64)
*/
void timer0_init(){
	// TCCR0 = (1<<CS01) | (1 << CS00); // K = 64
	TCCR0 = (1<<CS01); // K = 8 (simulation freezes)
	TIMSK |= (1<<TOIE0); // allow interrupt
}

void timer1_init(){
	TCNT1=0x00; // ticks
	TCCR1B |= (1<<CS10); // K = 1
	OCR1A = (unsigned int) (F_CPU / 1000); // tick per 1ms = 1000 tick per second
	TIMSK |= (1<<OCIE1A); // launch timer	
}
