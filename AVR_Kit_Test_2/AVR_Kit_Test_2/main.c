/*
 * AVR_Kit_Test_2.c
 *
 * Created: 17/08/2024 21:04:15
 * Author : Test
 */ 

// Khai b�o th? vi?n chu?n
#include <avr/io.h>

// ??nh ngh?a h?ng s? FRE = 8, l� xung nh?p c?a h? th?ng (t�nh b?ng MHz)
#define FRE	8

// Khai b�o file th? vi?n ri�ng
#include "thu_vien_rieng.h"

// L?p tr�nh h�m main()
int main()
{
	// G?i h�m INIT() trong file thu_vien_rieng.h ?? kh?i t?o
	INIT();

	// G?i h�m PORT() trong file thu_vien_rieng.h ?? ?i?u khi?n LED
	PORT();
	
	// L?nh return lu�n xu?t hi?n ? cu?i h�m main()
	return 0;
}


