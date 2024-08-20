// Khai báo các nguyên mẫu hàm
//void INIT();
void INIT()
{
	// Khởi tạo trạng thái Output cho các chân nối tới các LED đơn
	DDRD |= 0xFF;

	// Khởi tạo trạng thái logic 1 cho các chân nối tới các LED đơn
	PORTD |= 0xFF;

	// Khởi tạo trạng thái Output cho các chân nối tới LED 7 thanh
	DDRC |= 0xFF;

	// Khởi tạo trạng thái logic 1 cho các chân nối tới LED 7 thanh
	PORTC |= 0xFF;
}

void PORT();
//void LED7_OUT(unsigned char num);
void DELAY_MS(unsigned int mili_count);
void PB_2_LED();
unsigned char PB_CHECK();
void LED7_OUT(unsigned char num)
{
	// Khai báo biến temp lưu trạng thái của PORTC
	unsigned char temp = PORTC;
	
	// Các chân vi điều khiển ứng với các thanh LED
	// a - PC5				PC5
	// b - PC4			PC6		PC4
	// c - PC2			PC6		PC4
	// d - PC1				PC7
	// e - PC0			PC0		PC2
	// f - PC6			PC0		PC2
	// g - PC7				PC1		PC3
	// dot - PC3

	// Tắt các đoạn LED hiện đang sáng trước khi sáng các đoạn LED mới
	temp &= 0B00001000;

	// Gán mức logic cho 8 bit của biến temp ứng với giá trị của biến num
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
	
	// Xuất giá trị logic mới ra PORTC để làm sáng LED 7 thanh
	PORTC = temp;
}

//Bổ sung hai hàm:
/**************************************************************************
Hàm PB_2_LED() là hàm không có tham số và không trả lại giá trị, do người lập trình tự xây dựng để điều khiển các LED theo phím ấn với quy tắc mô tả tại Mục 3.3.1.
**************************************************************************/
void PB_2_LED()
{
	// Vòng for giúp việc quét phím ấn được lặp đi lặp lại
	for(;;)
	{
		// Gọi hàm quét phím, lưu kết quả phím ấn vào biến push_button
		push_button = PB_CHECK();

		// Hiện số thứ tự phím ấn ra LED 7 thanh
		LED7_OUT(push_button);

		// Điều khiển hàng LED đơn
		switch (push_button)
		{
			// Nếu push_button = 1, sáng 2 LED ngoài cùng bên trái
			case 1: PORTD = 0b11111100; break;

			// Nếu push_button = 2, …
			case 2: PORTD = 0b11110011; break;
			case 3: PORTD = 0b11001111; break;
			case 4: PORTD = 0b00111111; break;

			// push_button = 0, tắt tất cả các LED
			default: PORTD = 0xFF;
		}
	}
}

/**************************************************************************
Hàm PB_CHECK() là hàm không có tham số và có trả lại giá trị, do người lập trình tự xây dựng để nhận diện phím đang được ấn. Giá trị trả lại của hàm chính là thứ tự của phím. Khi được ấn, phím sẽ kết nối chân tương ứng của VĐK tới GND (mức logic 0). Khi nhả phím, chân tương ứng của VĐK được treo lên mức logic 1 nhờ các trở kéo có sẵn. Lưu ý: phím 1 được nối tới PB0, phím 2 được nối tới PB1,... phím 4 được nối tới PB3.
**************************************************************************/
unsigned char PB_CHECK()
{
	// Kiểm tra trạng thái logic của 4 chân PB0-3. Nếu khác 1111
	if((PINB & 0x0F) != 0x0F)
	{
		// Kiểm tra PB0. Nếu là mức logic 0, hàm kết thúc và = 1
		if(!(PINB & (1<<PB0)))
		return 1;

		// Kiểm tra PB1. Nếu là mức logic 0, hàm kết thúc và = 2
		if(!(PINB & (1<<PB1)))
		return 2;

		// Kiểm tra PB2. Nếu là mức logic 0, hàm kết thúc và = 3
		if(!(PINB & (1<<PB2)))
		return 3;

		// Kiểm tra PB3. Nếu là mức logic 0, hàm kết thúc và = 4
		if(!(PINB & (1<<PB3)))
		return 4;
	}

	// Nếu không có phím nào được ấn, hàm kết thúc và = 0
	return 0;  //phải giữ nút
	//return push_button;   //ko phải giữ nút
	
}
