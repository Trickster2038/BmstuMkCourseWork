#ifndef UART_H
#define UART_H

void uart_init();
void uart_send_byte(char target);
void uart_send_long(int data);
void uart_send_data(long* res_array, char range, long average);

#endif
