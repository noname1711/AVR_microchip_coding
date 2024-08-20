/*
 * funcs.h
 *
 * Created: 02/08/2024 10:54:38
 *  Author: Test
 */ 
// hàm kiểm tra nút
#ifndef FUNCS_H_   // Kiem tra neu chua dinh nghia FUNCS_H_
#define FUNCS_H_   // Dinh nghia FUNCS_H_

#define FRE 8000000UL   // Dinh nghia tan so la 8MHz

unsigned char push_button;   // Khai bao bien push_button

// Khai bao ham buttCheck
uint8_t buttCheck();

/*-----------------------------------------------------*/
// Dinh nghia ham buttCheck
uint8_t buttCheck()
{
	// Kiem tra cac bit thap cua PINB neu khong phai tat ca deu la 1
	if ((PINB & 0x0F) != 0x0F)
	{
		// Kiem tra tung nut nhan tu PB0 den PB3

		// Kiem tra nut nhan PB0
		if(!(PINB & (1<<PINB0)))
		return 1;   // Tra ve 1 neu nut nhan PB0 duoc nhan
		
		// Kiem tra nut nhan PB1
		if(!(PINB & (1<<PINB1)))
		return 2;   // Tra ve 2 neu nut nhan PB1 duoc nhan
		
		// Kiem tra nut nhan PB2
		if(!(PINB & (1<<PINB2)))
		return 3;   // Tra ve 3 neu nut nhan PB2 duoc nhan
		
		// Kiem tra nut nhan PB3
		if(!(PINB & (1<<PINB3)))
		return 4;   // Tra ve 4 neu nut nhan PB3 duoc nhan
	}
	return 0;   // Tra ve 0 neu khong co nut nao duoc nhan
}

#endif /* FUNCS_H_ */  // Ket thuc kiem tra dinh nghia FUNCS_H_
