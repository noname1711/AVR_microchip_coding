/*
 * AVR_Kit_Test.c
 *
 * Created: 17/08/2024 20:55:08
 * Author : Test
 */ 

#include <avr/io.h>

int main()
{
	DDRD |= 0xFF;
	PORTD |= 0xAA;
	DDRC |= 0xFF;
	PORTC |= 0x00;
	return 0;
}


