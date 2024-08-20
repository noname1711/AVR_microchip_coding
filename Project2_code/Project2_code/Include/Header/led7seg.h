/*
 * led7seg.h
 *
 * Created: 02/08/2024 10:53:11
 *  Author: Test
 */ 


#ifndef LED7SEG_H_   // Kiem tra neu chua dinh nghia LED7SEG_H_
#define LED7SEG_H_   // Dinh nghia LED7SEG_H_

// Khai bao ham _7seg
void _7seg(void);

// Dinh nghia ham _7seg
void _7seg(void)
{
	while (1)  // Vong lap vo han
	{
		// Ma hex cho cac so tu 0 den 9 de hien thi tren LED 7 doan
		unsigned int MaLed[10] ={0x88, 0xEB, 0x4C, 0x49, 0x2B, 0x19, 0x18, 0xCB, 0x08, 0x09}; // 0 den 9
		
		//unsigned int MaLed[8] ={0x9F, 0x3F, 0x7B, 0xF9, 0xFC, 0x7E, 0x6F, 0xCF}; // Vong so 8 (chu thich)

		for (int i = 0; i < 10; i++)  // Duyet tu dau mang MaLed den cuoi
		{
			PORTC = MaLed[i];  // Cap nhat gia tri PORTC de hien thi so tuong ung
			_delay_ms(500);  // Tri hoan 500ms
		}
	}
}

#endif /* LED7SEG_H_ */  // Ket thuc kiem tra dinh nghia LED7SEG_H_
