#ifndef THU_VIEN_RIENG_H_
#define THU_VIEN_RIENG_H_

void INIT();
void PORT();
void LED7_OUT(unsigned char num);
void DELAY_MS(unsigned int mili_count);
void PB_2_LED();
unsigned char PB_CHECK();
void ADC_2_LCD();
void LCD4_DIS_SHIFT(unsigned char lcd4_direct, unsigned char lcd4_step);
void UART();


void INIT()
{
	// Kh?i t?o tr?ng thái Output cho các chân n?i t?i các LED ??n
	DDRD |= 0xFF;

	// Kh?i t?o tr?ng thái logic 1 cho các chân n?i t?i các LED ??n
	PORTD |= 0xFF;

	// Kh?i t?o tr?ng thái Output cho các chân n?i t?i LED 7 thanh
	DDRC |= 0xFF;

	// Kh?i t?o tr?ng thái logic 1 cho các chân n?i t?i LED 7 thanh
	PORTC |= 0xFF;
	
	// Kh?i t?o tr?ng thái input th? n?i cho 8 ??u vào ADC
	DDRA = 0x00;
	PORTA = 0x00;

	// G?i các hàm kh?i t?o tham s? cho b? ADC
	ADC_PRES(128);
	ADC_AVCC();
	ADC_IN(0);

}

void PORT()
{
	unsigned char led_shift = 255;
	unsigned char led_7_count = 0;

	for(;;)
	{
		PORTD = led_shift;

		if(led_shift != 0)
			led_shift = led_shift << 1;	
		else led_shift = 255;
		
		LED7_OUT(led_7_count);
		PORTC ^= (1<<PC3);

		led_7_count = led_7_count + 1;

		if(led_7_count > 9)
			led_7_count = 0;

		DELAY_MS(500);
	}
}

void LED7_OUT(unsigned char num)
{
	unsigned char temp = PORTC;
	
	// Các chân vi ?i?u khi?n ?ng v?i các thanh LED
	// a - PC5				PC5
	// b - PC4			PC6		PC4
	// c - PC2			PC6		PC4
	// d - PC1				PC7
	// e - PC0			PC0		PC2
	// f - PC6			PC0		PC2
	// g - PC7				PC1		PC3
	// dot - PC3

	temp &= 0B00001000;

	switch(num)
	{
		case 0: temp |= 0B10000000; break;
		case 1: temp |= 0B11100011; break;
		case 2: temp |= 0B01000100; break;
		case 3: temp |= 0B01000001; break;
		case 4: temp |= 0B00100011; break;
		case 5: temp |= 0B00010001; break;
		case 6: temp |= 0B00010000; break;
		case 7: temp |= 0B11000011; break;
		case 8: temp |= 0B00000000; break;
		case 9: temp |= 0B00000001; break;
	}
	
	PORTC = temp;
}

void DELAY_MS(unsigned int mili_count)
{
	while(mili_count--)
	{
		_delay_ms(1);
	}
}

void PB_2_LED()
{
	for(;;)
	{
		push_button = PB_CHECK();

		LED7_OUT(push_button);

		switch (push_button)
		{
			case 1: PORTD = 0b11111100; break;
			case 2: PORTD = 0b11110011; break;
			case 3: PORTD = 0b11001111; break;
			case 4: PORTD = 0b00111111; break;
			default: PORTD = 0xFF;
		}
	}
}

unsigned char PB_CHECK()
{
	// Ki?m tra tr?ng thái logic c?a 4 chân PB0-3. N?u khác 1111
	if((PINB & 0x0F) != 0x0F)
	{
		// Ki?m tra PB0. N?u là m?c logic 0, hàm k?t thúc và = 1
		if(!(PINB & (1<<PB0)))
			return 1;

		// Ki?m tra PB1. N?u là m?c logic 0, hàm k?t thúc và = 2
		if(!(PINB & (1<<PB1)))
			return 2;

		// Ki?m tra PB2. N?u là m?c logic 0, hàm k?t thúc và = 3
		if(!(PINB & (1<<PB2)))
			return 3;

		// Ki?m tra PB3. N?u là m?c logic 0, hàm k?t thúc và = 4
		if(!(PINB & (1<<PB3)))
			return 4;
	}
	return 0;
}

void ADC_2_LCD()
{
	// Khoi tao LCD
	DDRD |= (1<<PD5); // = 1: output
	PORTD &= ~(1<<PD5); // PD5 = 0: data tu vdk gui toi LCD
	PORTC |= 0x0F; // giu nguyen 4 bit cao, dua 4 bit thap ve (k dung)

	LCD4_INIT(0,0);

	// Display static text
	LCD4_CUR_GOTO(1,0);
	LCD4_OUT_STR("Test ADC & LCD");
	LCD4_CUR_GOTO(2,0);
	LCD4_OUT_STR("ADC0: 0000/1024");

	// Declare a variable to hold the ADC value
	unsigned int adc_value;

	// Loop to read and update ADC value
	for(;;)
	{
		ADC_STA_CONVERT();
		while (ADCSRA & (1 << ADSC)); // ADCSRA: dieu khien trang thai cua ADC; ADSC = 1: bat dau chuyen doi, duoc xoa khi xong

		adc_value = ADC;

		LCD4_CUR_GOTO(2,6);
		LCD4_OUT_DEC(adc_value, 4);
		DELAY_MS(500);
	}
}

void LCD4_DIS_SHIFT(unsigned char lcd4_direct, unsigned char lcd4_step) {
	unsigned char i;
	if(lcd4_direct == 0)
	//Kiem tra lcd4_direct, bang 0 thi dich phai, 1 thi dich trai
	//Vong for de dich du lieu theo step
		for(i = 0; i < lcd4_step; i++)
			LCD4_OUT_CMD(0x1C);
	else
	//Vong for de dich du lieu theo step
		for(i = 0; i < lcd4_step; i++)
			LCD4_OUT_CMD(0x18);
}


void UART()
{
	//Khoi tao UART voi cac thong so ve braud rate, uart size, parity bit, stop bit
	UART_INIT(51,8,0,1);
	//Khoi tao LCD
	DDRD |= (1<<PD5);
	PORTD &= ~(1<<PD5);
	PORTC |= 0x0F;
	LCD4_INIT(0,0);
	//Hien thi dong text tinh len LCD
	LCD4_CUR_GOTO(1,0);
	LCD4_OUT_STR("Le Viet Hung, 20213942, DT09 – K66");
	//LCD4_OUT_STR("Bui Nhu Hanh, 20213904, DT09 – K66");
	LCD4_CUR_GOTO(2,0);
	LCD4_OUT_STR("Vien DTVT, DHBK HN");
	//Ham tao tre
	DELAY_MS(1000);
	//Vong for vo han, gui du lieu cho may tinh thong qua UART
	for(;;)
	{
		UART_TRAN_STR("Le Viet Hung, 20213942, DT09 – K66");
		//UART_TRAN_STR("Bui Nhu Hanh, 20213904, DT09 – K66");
		UART_TRAN_BYTE(13);
		UART_TRAN_BYTE(10);
		UART_TRAN_STR("Vien DTVT, DHBK HN");
		UART_TRAN_BYTE(13);
		UART_TRAN_BYTE(10);
		UART_TRAN_BYTE(13);
		UART_TRAN_BYTE(10);
		DELAY_MS(1000);
		//Ham dich toan bo du lieu cua LCD sang trai 1 don vi
		LCD4_DIS_SHIFT(1,1); 
	}
}

#endif /* THU_VIEN_RIENG_H_ */