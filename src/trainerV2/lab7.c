#include <avr/io.h>
#include "test1.h"
#include "keyboard.h"
#include "uart.h"
#include "display.h"

int test(void){
	DDRB=0x00; // PB7,PB6 ??? ?????? ?? LED7,LED6 PB0- ??? ?????
	PORTB=0b10010101; // ????????? LED7, PB0-????????????? ???????? ??????
}

void init_main(void){
	DDRA=0xF0;
	PORTA=0x0F;
	DDRC=0xFF;
	DDRB=0xFF;
	//PORTB=0xF3;
}

int main(void){
	init_main();
	//test();
	//test1_func();
	//PORTC=0b10011001;
	//uart_init();
	//uart_send_byte('h');
	//uart_send_byte('3');
	display_set_bytes(1,2,3,4);

	while(1) {
		display_flash_once();
		
		//uart_send_byte1('e');
		PORTB=keyboard_get_state();
		PORTC=keyboard_get_state();
		PORTC |= 0b10000000;
		
		PORTB |= 1<<PB7;
		PORTB &= 0x7F;
 		//asm("sleep"); // ??????? ? ????? Idle
 		//asm("nop");
 	}
}
