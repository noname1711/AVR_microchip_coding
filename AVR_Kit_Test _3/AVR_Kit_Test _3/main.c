/*
 * AVR_Kit_Test _3.c
 *
 * Created: 17/08/2024 21:30:25
 * Author : Test
 */ 
// Khai báo th? vi?n chu?n
#include <avr/io.h>

// ??nh ngh?a h?ng s? FRE = 8, là xung nh?p c?a h? th?ng (tính b?ng MHz)
#define FRE	8

// Khai báo push_button là bi?n toàn c?c, l?u s? th? t? phím ???c ?n
unsigned char push_button = 0;

// Khai báo file th? vi?n riêng
#include "thu_vien_rieng.h"

// L?p trình hàm main()
int main()
{
	// G?i hàm INIT() trong file thu_vien_rieng.h ?? kh?i t?o
	INIT();

	// T?m vô hi?u hóa hàm PORT()
	// PORT();

	// G?i hàm PB_2_LED() trong file thu_vien_rieng.h
	PB_2_LED();

	// L?nh return luôn xu?t hi?n ? cu?i hàm main()
	return 0;
}

