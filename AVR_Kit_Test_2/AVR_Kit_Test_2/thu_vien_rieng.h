// Khai báo các nguyên mẫu hàm
void INIT();
void PORT();
void LED7_OUT(unsigned char num);
void DELAY_MS(unsigned int mili_count);

/**************************************************************************
Hàm INIT() là hàm không có tham số và không trả lại giá trị, do người lập trình tự xây dựng để khởi tạo trạng thái các PORT của vi điều khiển. Như bất kỳ hàm tự xây dựng nào khác, người lập trình có thể đổi tên, chia nhỏ, gộp to, hoặc thay đổi các lệnh trong hàm này theo dụng ý riêng khi lập trình.
**************************************************************************/
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

/**************************************************************************
Hàm PORT() là hàm không có tham số và không trả lại giá trị, do người lập trình tự xây dựng để điều khiển trạng thái logic 0/1 của các chân trong các PORT của vi điều khiển. Trong mạch Kit này, trạng thái logic làm các đèn LED sáng/tắt theo quy tắc: 0 – LED sáng, 1 – LED tắt.
**************************************************************************/
void PORT()
{
	/* Khai báo các biến sẽ dùng tới trong hàm này */

	// Biến led_shift để điều khiển các LED đơn
	// Giá trị đầu là 255 = 0xFF = 0b11111111 -> tất cả các LED đều tắt
	unsigned char led_shift = 255;

	// Biến đếm cho LED 7 thanh, giá trị đầu là 0
	unsigned char led_7_count = 0;

	// Vòng for giúp các LED sáng/tắt theo quy luật lặp đi lặp lại
	for(;;)
	{
		/* Đoạn mã điều khiển các LED đơn */

		// Các LED sáng/tắt theo 8 bit của biến led_shift
		PORTD = led_shift;

		// Thay đổi biến led_shift
		if(led_shift != 0)			// Nếu led_shift khác 0
		led_shift = led_shift << 1;	// Dịch trái 1 bit
		else
		led_shift = 255;			// Trở lại giá trị 255
		
		/* Đoạn mã điều khiển LED 7 thanh */

		// Xuất giá trị đếm ra LED 7 thanh
		LED7_OUT(led_7_count);

		// Đảo trạng thái PC3 để nhấp nháy dấu chấm trên LED 7 thanh
		PORTC ^= (1<<PC3);

		// Tăng dần giá trị đếm
		led_7_count = led_7_count + 1;

		// Khi vượt quá 9, giá trị đếm được reset về 0
		if(led_7_count > 9)
		led_7_count = 0;

		// Hàm trễ khoảng 0.5 s = 500 ms
		DELAY_MS(500);
	}
}

/**************************************************************************
Hàm LED7_OUT() là hàm có tham số num nhưng không trả lại giá trị, do người lập trình tự xây dựng để điều khiển LED 7 thanh chỉ thị giá trị của num (0-9) bằng cách sáng/tắt các đoạn LED một cách phù hợp. Hàm LED7_OUT() không làm thay đổi trạng thái sáng/tắt của dấu chấm trên LED 7 thanh. Trong mạch Kit này, trạng thái logic làm các thanh LED sáng/tắt như sau: 0 – thanh LED sáng, 1 – thanh LED tắt.
**************************************************************************/
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

/**************************************************************************
Hàm DELAY_MS() là hàm có tham số mili_count nhưng không trả lại giá trị, do người lập trình tự xây dựng để tạo ra khoảng thời gian trễ (thời gian chờ) tính bằng mili giây. Việc trễ đươc thực hiện bằng các vòng lặp rỗng. Vòng lặp rỗng (cụ thể là vòng for) tuy không thực hiện công việc gì nhưng vẫn làm CPU tiêu tốn một khoảng thời gian nhất định cho việc khởi tạo và kết thúc. Nhiều vòng for liên tiếp sẽ tạo một khoảng trễ đáng kể.
**************************************************************************/
void DELAY_MS(unsigned int mili_count)
{
	// Khai báo hai biến chạy cho hai vòng for
	unsigned int i,j;

	// Xung nhịp của hệ thống càng cao, số vòng lặp càng tăng
	mili_count = mili_count * FRE;

	// Các vòng for gây trễ
	for(i = 0; i < mili_count; i++)
	for(j = 0; j < 53; j++);
}
