#include <avr/io.h>
#include <util/delay.h>

char c[4];
char d1, d2, d3, d4;
char display_pos = 0;

void display_set_bytes(char t1, char t2,
	char t3, char t4){
	c[0] = ~0x1F | (0x0F & t1);
	c[1] = ~0x2F | (0x0F & t2);
	c[2] = ~0x4F | (0x0F & t3);
	c[3] = ~0x8F | (0x0F & t4);
}

void display_set_long(long target){
	if(target < 10000){
		d4 = target % 10;
		d3 = (target / 10) % 10;
		d2 = (target / 100) % 10;
		d1 = (target / 1000) % 10;
		display_set_bytes(d1, d2, d3, d4);
	} else {
		display_set_bytes(0x0E, 0x0E, 0x0E, 0x0E);
	}
}

void display_off(){
	PORTB |= 0xFF;
}

void display_flash_once(){
	display_pos++;
	if(display_pos > 3){
		display_pos = display_pos % 4;
	}
	PORTB = c[(int) display_pos];
}

void display_init_timer0(){
	//TCCR0 = (1<<CS01) | (1 << CS00); // K = 64
	TCCR0 = (1<<CS01); // K = 8
	TIMSK |= (1<<TOIE0); // allow interrupt
}
