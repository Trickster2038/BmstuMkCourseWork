#include <avr/io.h>
#include <util/delay.h>

char c1, c2, c3, c4;
char display_temp;

void display_set_bytes(char t1, char t2,
	char t3, char t4){
	c1 = 0x10 | (0x0F & t1);
	c2 = 0x20 | (0x0F & t2);
	c3 = 0x40 | (0x0F & t3);
	c4 = 0x80 | (0x0F & t4);
}

void display_flash_once(){
	PORTB = c1;
	_delay_us(100);
	PORTB = c2;
	_delay_us(100);
	PORTB = c3;
	_delay_us(100);
	PORTB = c4;
	_delay_us(100);
	display_off();
}

void display_off(){
	PORTB &= 0x0F;
}

void display_init_timer(){
	TCCR1A=0x00; //настройка таймера
	TCCR1B=0x05;
	TCNT1=0x00; //здесь увеличиваются тики
	//OCR1A=0x1E85; //записываем число в регистр сравнения
 	OCR1A=0x0001;
	TIMSK=0x10; //запускаем таймер

	//TCCR1B |= (1<<WGM12);
	//TIMSK |= (1<<OCIE1A);
	//OCR1AH = 0b01111010;
	//OCR1AL = 0b00010010;
	//TCCR1B |= (1<<CS12);
}
