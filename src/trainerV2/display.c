#include <avr/io.h>
#include <util/delay.h>

char c1, c2, c3, c4;
char d1, d2, d3, d4;
char display_temp;

void display_set_bytes(char t1, char t2,
	char t3, char t4){
	c1 = 0x10 | (0x0F & t1);
	c2 = 0x20 | (0x0F & t2);
	c3 = 0x40 | (0x0F & t3);
	c4 = 0x80 | (0x0F & t4);
}

void display_set_int(int target){
	d4 = target % 10;
	d3 = (target / 10) % 10;
	d2 = (target / 100) % 10;
	d1 = (target / 1000) % 10;
	display_set_bytes(d1, d2, d3, d4);
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

void display_init_timer0(){
	TCCR0 = (1<<CS01); // K = 8
	TIMSK |= (1<<TOIE0); // allow interrupt
}
