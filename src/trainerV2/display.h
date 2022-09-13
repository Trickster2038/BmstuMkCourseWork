#ifndef DISPLAY_H
#define DISPLAY_H

void display_set_bytes(char t1, char t2,
	char t3, char t4);

void display_flash_once();
void display_off();
void display_init_timer0();
void display_set_int(int target);

#endif
