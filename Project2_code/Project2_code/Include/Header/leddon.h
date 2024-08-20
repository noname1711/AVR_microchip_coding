/*
 * leddon.h
 *
 * Created: 02/08/2024 10:52:23
 *  Author: Test
 */ 


#ifndef LEDDON_H_   // Kiem tra neu chua dinh nghia LEDDON_H_
#define LEDDON_H_   // Dinh nghia LEDDON_H_

// Khai bao ham _leddon
void _leddon(void);

// Dinh nghia ham _leddon
void _leddon(void)
{
	while (1)  // Vong lap vo han
	{
		// Day LED bat dan
		//0x01 = 00000001 (bật bit đầu tiên)
		//0x03 = 00000011 (bật hai bit đầu tiên)
		//0x07 = 00000111 (bật ba bit đầu tiên)
		//0x0F = 00001111 (bật bốn bit đầu tiên)
		//0x1F = 00011111 (bật năm bit đầu tiên)
		//0x3F = 00111111 (bật sáu bit đầu tiên)
		//0x7F = 01111111 (bật bảy bit đầu tiên)
		//0xFF = 11111111 (bật tất cả tám bit)
		unsigned int sangDan[] = {0x01, 0x03, 0x07, 0x0F, 0x1F, 0x3F, 0x7F, 0xFF};
		PORTD = 0xFF;  // Bat tat ca cac LED
		_delay_ms(200);  // Tri hoan 200ms
		for (int i = 7; i >= 0; i--)  // Duyet tu cuoi mang sangDan den dau
		{
			PORTD = sangDan[i];  // Cap nhat gia tri PORTD de bat LED dan
			_delay_ms(200);  // Tri hoan 200ms
		}

		// Day LED tat dan
		unsigned int tatDan[] = {0x01, 0x03, 0x07, 0x0F, 0x1F, 0x3F, 0x7F, 0xFF};
		PORTD = 0x00;  // Tat tat ca cac LED
		_delay_ms(200);  // Tri hoan 200ms
		for (int i = 0; i <= 7; i++)  // Duyet tu dau mang tatDan den cuoi
		{
			PORTD = tatDan[i];  // Cap nhat gia tri PORTD de tat LED dan
			_delay_ms(200);  // Tri hoan 200ms
		}
		
		// Day LED bat lan luot
		//0b11111110 = 254 (bit đầu tiên tắt, các bit còn lại bật)
		//0b11111101 = 253 (bit thứ hai tắt, các bit còn lại bật)
		//0b11111011 = 251 (bit thứ ba tắt, các bit còn lại bật)
		//0b11110111 = 247 (bit thứ tư tắt, các bit còn lại bật)
		//0b11101111 = 239 (bit thứ năm tắt, các bit còn lại bật)
		//0b11011111 = 223 (bit thứ sáu tắt, các bit còn lại bật)
		//0b10111111 = 191 (bit thứ bảy tắt, các bit còn lại bật)
		//0b01111111 = 127 (bit thứ tám tắt, các bit còn lại bật)
		unsigned int lanLuot[] = {0b11111110, 0b11111101, 0b11111011, 0b11110111, 0b11101111, 0b11011111, 0b10111111, 0b01111111};
		PORTD = 0xFF;  // Bat tat ca cac LED
		_delay_ms(200);  // Tri hoan 200ms
		for (int i = 0; i <= 7; i++)  // Duyet tu dau mang lanLuot den cuoi
		{
			PORTD = lanLuot[i];  // Cap nhat gia tri PORTD de bat LED lan luot
			_delay_ms(200);  // Tri hoan 200ms
		}
		_delay_ms(200);  // Tri hoan 200ms
		for (int i = 7; i >= 0; i--)  // Duyet tu cuoi mang lanLuot den dau
		{
			PORTD = lanLuot[i];  // Cap nhat gia tri PORTD de tat LED lan luot
			_delay_ms(200);  // Tri hoan 200ms
		}
		
		// Day LED bat theo mau ve giua
		unsigned int veGiua[] = {0b01111110, 0b10111101, 0b11011011, 0b11100111, 0b11011011, 0b10111101, 0b01111110};
		PORTD = 0xFF;  // Bat tat ca cac LED
		_delay_ms(200);  // Tri hoan 200ms
		for (int i = 0; i <= 6; i++)  // Duyet tu dau mang veGiua den cuoi
		{
			PORTD = veGiua[i];  // Cap nhat gia tri PORTD de bat LED theo mau
			_delay_ms(200);  // Tri hoan 200ms
		}
	}
}

#endif /* LEDDON_H_ */  // Ket thuc kiem tra dinh nghia LEDDON_H_

