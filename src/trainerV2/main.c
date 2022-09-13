#define F_CPU 1000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "leds.h"
#include "keyboard.h"
#include "uart.h"
#include "display.h"
#include "buzzer.h"
#include "timer1.h"

char hh = 0;

int timer_ms = 0;

ISR (TIMER1_COMPA_vect)
{
  timer_ms++;
  TCNT1=0; //clear ticks
}

ISR (TIMER0_OVF_vect){
	display_flash_once();
}

void init_main(void){
	timer1_init();
	DDRA=0xF0;
	PORTA=0x0F; // resistors on buttons
	DDRC=0xFF; // PORTC - OUTPUT
	DDRB=0xFF; // PORTB - OUTPUT
	DDRD=0xFF; // PORTD - OUTPUT
	display_init_timer0();
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
