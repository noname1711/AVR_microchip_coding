/*
 * AVR_Kit_Test_2.c
 *
 * Created: 17/08/2024 21:04:15
 * Author : Test
 */ 

// Khai báo th? vi?n chu?n
#include <avr/io.h>

// ??nh ngh?a h?ng s? FRE = 8, là xung nh?p c?a h? th?ng (tính b?ng MHz)
#define FRE	8

// Khai báo file th? vi?n riêng
#include "thu_vien_rieng.h"

// L?p trình hàm main()
int main()
{
	// G?i hàm INIT() trong file thu_vien_rieng.h ?? kh?i t?o
	INIT();

	// G?i hàm PORT() trong file thu_vien_rieng.h ?? ?i?u khi?n LED
	PORT();
	
	// L?nh return luôn xu?t hi?n ? cu?i hàm main()
	return 0;
}


