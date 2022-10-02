#define F_CPU 4000000UL

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
#define DEFAULT_DELAY 200
#define MIN_DELAY 50
#define MAX_DELAY 300
#define DELAY_STEP 10
#define OTHER_KEYS_DELAY 500
#define BEFORE_RESET_CYCLES 3

#define K 3

char hh = 0;
int debug_activate_ms;

char lock_reset = 1;
char lock_reset_cnt = 0;
char display_on = 0;
char key = 0;
char led_line = 0;
char active = 0;
int timer_ms = 0;
int timer_ms_buff;
int timer_control; // for debug
int delay_amount = DEFAULT_DELAY;

char tries_counter = 0;
int sum_timer_ms = 0;

ISR (TIMER1_COMPA_vect)
{
  timer_ms++;
  timer_control++; // for debug
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
	led_line = leds_random_line();
	display_set_bytes(0, 0, 0, 0);

	while(1){
		key = keyboard_get_state();

		if(lock_reset_cnt < BEFORE_RESET_CYCLES){
			lock_reset_cnt++;
		} else {
			lock_reset = 0;
		}

		if(active == 1){
			leds_move_column();
			leds_update();

			if((key != 0) && (key <= 8)){
				if(key == led_line){
					timer_ms_buff = timer_ms; // not really necessary
					display_set_int(timer_ms_buff);
					sum_timer_ms += timer_ms_buff;
					tries_counter++;
					timer_ms = 0;
					led_line = leds_random_line();
					leds_update(); // why necessary here?
				} else {
					buzzer_beep(BUZZER_DELAY);
				}
			} 

			if((key == 9) && (lock_reset == 0)){
				lock_reset_cnt = 0;
				display_on = 0;
				active = 0;
				lock_reset = 1;

				display_set_bytes(0, 0, 0, 0); // discard display buffer
				leds_off();
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
			if((key == 9) && (lock_reset == 0)){
				lock_reset_cnt = 0;
				display_on = 1;
				active = 1;

				tries_counter = 0;
				sum_timer_ms = 0;
				timer_ms = 0;
				led_line = leds_random_line(); // refresh line after reset
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
