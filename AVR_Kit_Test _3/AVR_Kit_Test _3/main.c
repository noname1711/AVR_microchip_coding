/*
 * AVR_Kit_Test _3.c
 *
 * Created: 17/08/2024 21:30:25
 * Author : Test
 */ 
// Khai b�o th? vi?n chu?n
#include <avr/io.h>

// ??nh ngh?a h?ng s? FRE = 8, l� xung nh?p c?a h? th?ng (t�nh b?ng MHz)
#define FRE	8

// Khai b�o push_button l� bi?n to�n c?c, l?u s? th? t? ph�m ???c ?n
unsigned char push_button = 0;

// Khai b�o file th? vi?n ri�ng
#include "thu_vien_rieng.h"

// L?p tr�nh h�m main()
int main()
{
	// G?i h�m INIT() trong file thu_vien_rieng.h ?? kh?i t?o
	INIT();

	// T?m v� hi?u h�a h�m PORT()
	// PORT();

	// G?i h�m PB_2_LED() trong file thu_vien_rieng.h
	PB_2_LED();

	// L?nh return lu�n xu?t hi?n ? cu?i h�m main()
	return 0;
}

