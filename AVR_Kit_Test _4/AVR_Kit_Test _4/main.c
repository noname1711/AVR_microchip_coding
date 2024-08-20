/*
 * Test.c
 *
 * Created: 8/6/2024 11:27:27 AM
 * Author : Duong175
 */ 
#define F_CPU 8000000UL
#define FRE 8
#include <avr/io.h>
#include <util/delay.h>
#include "hunget_adc.h"
#include "hunget_lcd.h"
#include "hunget_uart.h"

unsigned char push_button = 0;
#include "thu_vien_rieng.h"

int main()
{
	INIT();

	//Bai 1
	//PORT();
	
	//Bai 2
	//PB_2_LED();
	
	//Bai 3
	//ADC_2_LCD();
	
	//Bai 4
	UART();

	return 0;
}
