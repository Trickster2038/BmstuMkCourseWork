#include <avr/io.h>
#define BAUD 9600
#include <util/setbaud.h>

int divider;
char cnt;

void uart_init() {
    UBRRH = UBRRH_VALUE;
    UBRRL = UBRRL_VALUE;

#if USE_2X
    UCSRA |= _BV(U2X);
#else
    UCSRA &= ~(_BV(U2X));
#endif

    UCSRC = _BV(UCSZ1) | _BV(UCSZ0); /* 8-bit data */
    UCSRB = _BV(RXEN) | _BV(TXEN);   /* Enable RX and TX */
}

void uart_send_byte(char c) {
   loop_until_bit_is_set(UCSRA, UDRE); /* Wait until data register empty. */
   UDR = c;
}

void uart_send_int(int data) {
	divider = 1000;
	for(cnt=0; cnt<4; cnt++){
		uart_send_byte(((data / divider) % 10) + '0');
		divider /= 10;
	}
	uart_send_byte(' ');
}
