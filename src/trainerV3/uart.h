#ifndef UART_H
#define UART_H

void uart_init();
void uart_send_byte(char target);
void uart_send_int(int data);
void uart_send_data(int* res_array, char range, int average);

#endif
