#include <avr/io.h>
#include <util/delay.h>
#include "test1.h"
#include "keyboard.h"
#include "uart.h"
#include "display.h"
//#include "MEGA8515.h"
#include <avr/interrupt.h>

#define F_CPU 1000000UL

char hh = 0;

int test(void){
	DDRB=0x00; // PB7,PB6 ??? ?????? ?? LED7,LED6 PB0- ??? ?????
	PORTB=0b10010101; // ????????? LED7, PB0-????????????? ???????? ??????
}

ISR (TIMER1_COMPA_vect)
{
  display_flash_once();
  //display_set_bytes(1,2,3,1);
  TCNT1=0; //обнуляем таймер
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
	PORTB=0x67;
	//test();
	//test1_func();
	//PORTC=0b10011001;
	//uart_init();
	//uart_send_byte('h');
	//uart_send_byte('3');
	display_set_bytes(1,2,3,4);
	leds_random_line();
	display_init_timer();
	sei();

	while(1) {
		leds_move_column();
		leds_update();
		_delay_ms(100);

		hh++;
		if(hh % 4 == 0){
			leds_random_line();
		}
		//display_flash_once();
		
		//uart_send_byte1('e');

		//PORTB=keyboard_get_state();
		//PORTC=keyboard_get_state();
		//PORTC |= 0b10000000;
		
		//PORTB |= 1<<PB7;
		//PORTB &= 0x7F;

 		//asm("sleep"); // ??????? ? ????? Idle
 		//asm("nop");
 	}
}
