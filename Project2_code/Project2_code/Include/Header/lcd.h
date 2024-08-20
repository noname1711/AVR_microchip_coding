/*
 * lcd.h
 *
 * Created: 02/08/2024 10:55:19
 * Tác giả: Test
 */ 

#ifndef LCD_H_
#define LCD_H_

// Định nghĩa tần số CPU là 8MHz
#define F_CPU 8000000UL 

// Bao gồm header đầu vào/đầu ra AVR
#include <avr/io.h>
// Bao gồm tiện ích cho việc tạo độ trễ
#include <util/delay.h>
// Bao gồm các hàm nhập/xuất tiêu chuẩn
#include <stdio.h>
// Bao gồm các hàm thao tác chuỗi
#include <string.h>

// Định nghĩa các chân điều khiển LCD
#define LCD_RS PD6
#define LCD_RW PD5
#define LCD_EN PD7
// Định nghĩa ký hiệu độ cho màn hình LCD
#define degree_symbol 0xdf
// Định nghĩa các chân dữ liệu của LCD
#define LCD_D4 PC4
#define LCD_D5 PC5
#define LCD_D6 PC6
#define LCD_D7 PC7

// Định nghĩa loại tham chiếu điện áp ADC
#define ADC_VREF_TYPE 0x00

// Bộ đệm để lưu trữ chuỗi
char buff[5];
// Biến để lưu giá trị ADC
int adc_value;
// Biến để lưu giá trị nhiệt độ
float nhietdo;

// Hàm khởi tạo ADC
void ADC_Init(){
    // Thiết lập cổng ADC là đầu vào
    DDRA = 0x00; 
    // Kích hoạt ADC với tần số/128
    ADCSRA = 0x87; 
    // Thiết lập Vref: Avcc và kênh ADC: 0
    ADMUX = 0x40; 
}

// Hàm đọc giá trị từ kênh ADC
int ADC_Read(char channel)
{
    // Thiết lập kênh đầu vào để đọc
    ADMUX = 0x40 | (channel & 0x07); 
    // Bắt đầu chuyển đổi ADC
    ADCSRA |= (1<<ADSC); 
    // Đợi đến khi kết thúc chuyển đổi bằng cách kiểm tra cờ ngắt ADC
    while (!(ADCSRA & (1<<ADIF))); 
    // Xóa cờ ngắt bằng cách đặt bit ADIF của thanh ghi ADCSRA
    ADCSRA |= (1<<ADIF); 
    // Đợi một chút
    _delay_ms(1); 
    // Trả về từ ADC
    return ADCW; 
}

// Hàm tạo xung kích hoạt trên chân EN để LCD nhận dữ liệu
void LCD_Enable(void)
{
    // Đặt chân EN
    PORTD |= (0x01 << LCD_EN);
    // Độ trễ nhỏ
    _delay_us(3);
    // Xóa chân EN
    PORTD &= ~(0x01 << LCD_EN);
    // Độ trễ nhỏ
    _delay_us(50);
}

// Hàm gửi 4 bit dữ liệu đến LCD
void LCD_Send4Bit(unsigned char Data)
{
    // Gửi bit 0
    (Data & 1) ? (PORTC |= (1 << LCD_D4)) : (PORTC &= ~(0x01 << LCD_D4));
    // Gửi bit 1
    ((Data >> 1) & 1) ? (PORTC |= (1 << LCD_D5)) : (PORTC &= ~(0x01 << LCD_D5));
    // Gửi bit 2
    ((Data >> 2) & 1) ? (PORTC |= (1 << LCD_D6)) : (PORTC &= ~(0x01 << LCD_D6));
    // Gửi bit 3
    ((Data >> 3) & 1) ? (PORTC |= (1 << LCD_D7)) : (PORTC &= ~(0x01 << LCD_D7));
}

// Hàm gửi lệnh đến LCD
void LCD_SendCommand(unsigned char command)
{
    // Gửi nibble cao trước
    LCD_Send4Bit((unsigned char)command >> 4);
    // Tạo xung kích hoạt
    LCD_Enable();
    // Gửi nibble thấp
    LCD_Send4Bit(command);
    // Tạo xung kích hoạt
    LCD_Enable();
}

// Hàm xóa màn hình LCD
void LCD_Clear()
{
    // Lệnh xóa màn hình
    LCD_SendCommand(0x01);
    // Độ trễ cho việc thực hiện lệnh
    _delay_ms(2);
}

// Hàm kích hoạt con trỏ nhấp nháy trên LCD
void LCD_BlinkPointer()
{
    // Bật màn hình, bật con trỏ, tắt nhấp nháy
    LCD_SendCommand(0x0E);
}

// Hàm kích hoạt con trỏ nhấp nháy cộng trên LCD
void LCD_BlinkPointerPlus()
{
    // Bật màn hình, bật con trỏ, bật nhấp nháy
    LCD_SendCommand(0x0F);
}

// Hàm khởi tạo LCD
void LCD_Init()
{
    // Gửi dữ liệu giả ban đầu
    LCD_Send4Bit(0x00); // Bật LCD
    _delay_ms(20); // Đợi LCD khởi động
    // Đặt RS và RW về 0 để ở chế độ lệnh
    PORTD &= ~(0x01 << LCD_RS);
    PORTD &= ~(0x01 << LCD_RW);
    // Thiết lập chức năng: chế độ 8-bit
    LCD_Send4Bit(0x03);
    LCD_Enable();
    _delay_ms(5); // Đợi lệnh thực thi
    LCD_Enable();
    _delay_us(100); // Độ trễ ngắn
    LCD_Enable();
    // Đặt LCD ở chế độ 4-bit
    LCD_Send4Bit(0x02);
    LCD_Enable();
    // Thiết lập chức năng: chế độ 4-bit, 2 dòng, 5x8 điểm
    LCD_SendCommand(0x28);
    // Bật màn hình, tắt con trỏ, tắt nhấp nháy
    LCD_SendCommand(0x0c);
    // Thiết lập chế độ nhập: tăng con trỏ, không dịch màn hình
    LCD_SendCommand(0x06);
    // Xóa màn hình LCD
    LCD_Clear();
}

// Hàm thiết lập vị trí con trỏ trên LCD
void LCD_GotoXY(unsigned char x, unsigned char y)
{
    unsigned char address;
    // Nếu y là 0, chuyển đến dòng đầu tiên
    if(!y) address = (0x80 + x);
    // Ngược lại, chuyển đến dòng thứ hai
    else address = (0xc0 + x);
    // Đặt địa chỉ trong LCD
    LCD_SendCommand(address);
}

// Hàm ghi ký tự lên LCD
void LCD_PutChar(unsigned char Data)
{
    // Đặt RS về 1 để ở chế độ dữ liệu
    PORTD |= (0x01 << LCD_RS);
    // Gửi dữ liệu
    LCD_SendCommand(Data);
    // Đặt RS trở lại 0
    PORTD &= ~(0x01 << LCD_RS);
}

// Hàm ghi chuỗi lên LCD
void LCD_Puts(char *s)
{
    // Vòng lặp qua từng ký tự trong chuỗi
    while (*s)
    {
        // Ghi ký tự lên LCD
        LCD_PutChar(*s);
        // Chuyển đến ký tự tiếp theo
        s++;
    }
}

#endif /* LCD_H_ */
