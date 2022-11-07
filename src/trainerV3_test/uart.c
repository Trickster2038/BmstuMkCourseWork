#include <avr/io.h>
#define BAUD 9600
#include <util/setbaud.h>

long divider;
char cnt;
char i;

void uart_init() {
    UBRRH = UBRRH_VALUE;
    UBRRL = UBRRL_VALUE;

#if USE_2X
    UCSRA |= (1 << U2X);
#else
    UCSRA &= ~(1 << U2X);
#endif

    UCSRC = (1 << UCSZ1) | (1 << UCSZ0); // 8-bit data 
    UCSRB = (1 << RXEN) | (1 << TXEN);   // Enable RX and TX 
}

void uart_send_byte(char c) {
   loop_until_bit_is_set(UCSRA, UDRE); // Wait until data register empty. */
   UDR = c;
}

void uart_send_long(long data) {
	divider = 1; 
	while((divider*10) < data){
		divider *= 10;
	}
	while(divider > 0){
		uart_send_byte(((data / divider) % 10) + '0');
		divider /= 10;	
	}
	uart_send_byte(' ');
}

void uart_send_data(long* res_array, char range, long average) {
	for(i=0; i<range; i++){
		uart_send_byte(i+1+'0');
		uart_send_byte(':');
		uart_send_long(res_array[(int) i]);
		uart_send_byte('\n');
	}
	uart_send_byte('A');
	uart_send_byte('V');
	uart_send_byte('G');
	uart_send_byte(':');
	uart_send_long(average);
	uart_send_byte('\n');
}
