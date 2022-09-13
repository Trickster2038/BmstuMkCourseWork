#include <avr/io.h>
#include <util/delay.h>

char c1, c2, c3, c4;
char display_temp;

void display_set_bytes(char t1, char t2,
	char t3, char t4){
	c1 = 0x10 | (0x0F & t1);
	c2 = 0x20 | (0x0F & t2);
	c3 = 0x40 | (0x0F & t3);
	c4 = 0x80 | (0x0F & t4);
}

void display_off(){
	PORTB &= 0x0F;
}

void display_flash_once(){
	PORTB = c1;
	_delay_ms(1); // minimal delay just to init port
	PORTB = c2;
	_delay_ms(1);
	PORTB = c3;
	_delay_ms(1);
	PORTB = c4;
	_delay_ms(1);
	display_off();
}

void display_init_timer(){
	TCNT1=0x00; // ticks
	TCCR1B |= (1<<CS10); // K = 0
	OCR1A = (unsigned int) (F_CPU / 60); // compare num
	TIMSK |= (1<<OCIE1A); // launch timer	
}
