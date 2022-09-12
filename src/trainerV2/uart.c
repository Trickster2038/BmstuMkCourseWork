#include <avr/io.h>
#define F_CPU 1000000UL
#define BAUD 9600
#include <util/setbaud.h>

void uart_init(void) {
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
