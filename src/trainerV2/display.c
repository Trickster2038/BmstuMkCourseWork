#include <avr/io.h>

char c1, c2, c3, c4;
char display_temp;

void display_set_bytes(char t1, char t2,
	char t3, char t4){
	c1 = t1;
	c2 = t2;
	c3 = t3;
	c4 = t4;
}

void display_flash_once(){
	display_temp = 0x0F & c1;
	PORTB = 0x10 | display_temp;
	display_temp = 0x0F & c2;
	PORTB = 0x20 | display_temp;
	display_temp = 0x0F & c3;
	PORTB = 0x40 | display_temp;
	display_temp = 0x0F & c4;
	PORTB = 0x80 | display_temp;
}

void display_off(){
	PORTB &= 0x0F;
}
