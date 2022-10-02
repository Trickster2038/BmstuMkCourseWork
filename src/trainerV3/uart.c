#include <avr/io.h>
#define BAUD 9600
#include <util/setbaud.h>

int divider;
char cnt;

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

void uart_send_int(int data) {
	divider = 1;
	while((divider * 10) < data){
		divider *= 10;
	}
	if(divider < 1000){
		divider = 1000;
	}
	while(divider > 0){
		uart_send_byte(((data / divider) % 10) + '0');
		divider /= 10;
	}
	uart_send_byte(' ');
}
