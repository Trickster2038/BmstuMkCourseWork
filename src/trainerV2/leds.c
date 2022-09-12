#include <stdlib.h>
#include <avr/io.h>

char line = 0;
char column = 0;
char direction = 1; // forward

char leds_random_line(){
	line = rand() % 4;
	return line;
}

void leds_move_column(){
	if(direction == 1){
		if(column < 3){
			column++;
		} else {
			direction = 0;
			column--;
		}
	} else {
		if(column > 0){
			column--;
		} else {
			direction = 1;
			column++;
		}
	}
}

void leds_update(){
	PORTC = 0x80 | (column << 3) | line;
}

void leds_off(){
	PORTC &= 0x7F;
}
