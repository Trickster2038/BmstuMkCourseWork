#define F_CPU 4000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "leds.h"
#include "keyboard.h"
#include "uart.h"
#include "display.h"
#include "buzzer.h"
#include "timers.h"

#define BUZZER_DELAY 50
#define DEFAULT_DELAY 200
#define MIN_DELAY 100
#define MAX_DELAY 500
#define DELAY_STEP 10
#define KEYS_DELAY 500
#define BYPASS_DELAY 10

#define K 3

long debug_activate_ms;

char display_on = 0;
char key = 0;
char led_line = 0;
char active = 0;
long timer_ms = 0;
long timer_ms_buff;
long timer_control; // for debug
int delay_amount = DEFAULT_DELAY;

char tries_counter = 0;
long sum_timer_ms = 0;

long results[K];

ISR (TIMER1_COMPA_vect)
{
  timer_ms++;
  if((active == 1) && (timer_ms % delay_amount == 0)){
 	leds_move_column();
	leds_update();
  }
  TCNT1=0; //clear ticks
  timer_control++; // for debug
}

ISR (TIMER0_OVF_vect){
	if(display_on == 1){
		display_flash_once();
	}
}

void init_main(void){
	timer0_init();
	timer1_init();
	DDRA=0xF0;
	PORTA=0x0F; // resistors on buttons
	DDRC=0xFF; // PORTC - OUTPUT
	DDRB=0xFF; // PORTB - OUTPUT
	DDRD=0xFF; // PORTD - OUTPUT
	uart_init();
	sei();

	display_off();
	led_line = leds_random_line();
	display_set_long(0);
}

int main(){
	init_main();

	while(1){
		key = keyboard_get_state();

		if(active == 1){

			if((key != 0) && (key <= 8)){
				if(key == (led_line + 1)){
					timer_ms_buff = timer_ms; 
					display_set_long(timer_ms_buff);
					results[(int) tries_counter] = timer_ms_buff;
					sum_timer_ms += timer_ms_buff;
					tries_counter++;
					timer_ms = 0;
					led_line = leds_random_line();
				} else {
					buzzer_beep(BUZZER_DELAY);
				}
			} 

			if(key == 9){
				display_on = 0;
				display_off();
				active = 0;

				leds_off();
			} 

			if((key == 10) && (delay_amount > MIN_DELAY)){
				delay_amount -= DELAY_STEP;
			}

			if((key == 11) && (delay_amount < MAX_DELAY)){
				delay_amount += DELAY_STEP;
			}
			
			if(tries_counter == K){
				display_set_long(sum_timer_ms / K);
				leds_off();
				active = 0;
			}			

		} else {

			if(key == 9){
				display_set_long(0);
				display_on = 1;
				active = 1;

				tries_counter = 0;
				sum_timer_ms = 0;
				timer_ms = 0;
				led_line = leds_random_line(); // refresh line after reset
			} 

			if((key == 12)&&(tries_counter == K)){
					uart_send_data(results, K, sum_timer_ms / K);
				}
		}

		if(key != 0){
			_delay_ms(KEYS_DELAY);
		} else {
			_delay_ms(BYPASS_DELAY);
		}
	}

	return 0;
}
