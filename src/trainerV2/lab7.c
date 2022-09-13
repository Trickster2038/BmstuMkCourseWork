#include <avr/io.h>
#include <util/delay.h>
#include "test1.h"
#include "keyboard.h"
#include "uart.h"
#include "display.h"
#include <avr/interrupt.h>
#include "buzzer.h"

#define F_CPU 1000000UL

char hh = 0;

ISR (TIMER1_COMPA_vect)
{
  display_flash_once();
  TCNT1=0; //clear ticks
}

void init_main(void){
	DDRA=0xF0;
	PORTA=0x0F; // resistors on buttons
	DDRC=0xFF; // PORTC - OUTPUT
	DDRB=0xFF; // PORTB - OUTPUT
	DDRD=0xFF; // PORTD - OUTPUT
	display_init_timer();
	uart_init();
	sei();
}

int main(void){
	init_main();
	//uart_init();
	//uart_send_byte('h');
	//uart_send_byte('3');
	display_set_bytes(1,2,3,4);
	leds_random_line();
	//buzzer_beep(15);

	while(1) {
		leds_move_column();
		leds_update();
		_delay_ms(100);

		hh++;
		if(hh % 4 == 0){
			leds_random_line();
		}
		//uart_send_byte1('e');
		//PORTB=keyboard_get_state();
 	}
}
