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

#define BUZZER_DELAY 50
#define DEFAULT_DELAY 100
#define MIN_DELAY 50
#define MAX_DELAY 300
#define DELAY_STEP 10
#define OTHER_KEYS_DELAY 500

#define K 3

char hh = 0;
int debug_activate_ms;

char lock_reset = 1;
char display_on = 1;
char key = 0;
char led_line = 0;
char active = 0;
int timer_ms = 0;
int timer_ms_buff;
int delay_amount = DEFAULT_DELAY;

char tries_counter = 0;
int sum_timer_ms = 0;

/*
	key9 = start
*/

ISR (TIMER1_COMPA_vect)
{
  timer_ms++;
  TCNT1=0; //clear ticks
}

ISR (TIMER0_OVF_vect){
	if(display_on == 1){
		display_flash_once();
	} else {
		display_off();
	}
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

int main(){
	init_main();
	display_set_bytes(0, 0, 0, 0);
	led_line = leds_random_line();

	while(1){
		key = keyboard_get_state();
		if(active == 1){
			leds_move_column();
			leds_update();

			if((key != 0) && (key <= 8)){
				if(key == led_line){
					display_set_int(timer_ms);
					sum_timer_ms += timer_ms;
					tries_counter++;
					timer_ms = 0;
					led_line = leds_random_line();
					leds_update(); // why necessary here?
				} else {
					buzzer_beep(BUZZER_DELAY);
				}
			} 

			if(key == 9){
				if(lock_reset == 0){
					display_on = 0; // necessary?
					leds_off();
					active = 0;
					lock_reset = 1;
				}
			} else {
				lock_reset = 0;
			}

			if((key == 10) && (delay_amount > MIN_DELAY)){
				delay_amount -= DELAY_STEP;
			}

			if((key == 11) && (delay_amount < MAX_DELAY)){
				delay_amount += DELAY_STEP;
			}
			
			if(tries_counter == K){
				display_set_int(sum_timer_ms / K);
				leds_off();
				active = 0;
			}			

			_delay_ms(delay_amount);	
		} else {
			if(key == 9){
				sum_timer_ms = 0;
				tries_counter = 0;
				display_on = 1;
				//debug_activate_ms = timer_ms;
				active = 1;
				timer_ms = 0;
				lock_reset = 1; // prevent double click, delay works strange
			} 

			if(key == 12){
				uart_send_int(sum_timer_ms / K);
				_delay_ms(OTHER_KEYS_DELAY);
			}
		}
	}

	return 0;
}
