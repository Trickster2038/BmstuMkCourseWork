#include <avr/io.h>
#include <util/delay.h>

void buzzer_beep(int time_amount_ms){
	PORTD |= 0x80;
	_delay_ms(time_amount_ms);
	PORTD &= 0x7F;
}
