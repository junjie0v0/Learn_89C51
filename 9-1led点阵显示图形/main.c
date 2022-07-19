#include <REGX51.H>
#include "A.H"

sbit RCK=P3^5;		//RCLK 置1对穿行寄存器的数据进行搬运
sbit SCK=P3^6;		//SRCLK 上升沿移位(置1进行移位，移位完进行置0)
sbit SER=P3^4;		//SER 串行数据输入移位寄存器

#define MATRIX_LED_PORT		P0//点阵屏io口宏定义。

///**
//  * @brief  74HC595写入一个字节
//  * @param  Byte 要写入的字节
//  * @retval 无
//  */
//void _74HC595_WriteByte(unsigned char Byte)
//{
//	unsigned char i;
//	for(i=0;i<8;i++)
//	{
//		SER=Byte&(0x80>>i);//只要SER不等于0.那就为1；
//		SCK=1;
//		SCK=0;
//	}
//	RCK=1;
//	RCK=0;
//}

///**
//  * @brief  LED点阵屏显示一列数据
//  * @param  Column 要选择的列，范围：0~7，0在最左边
//  * @param  Data 选择列显示的数据，高位在上，1为亮，0为灭
//  * @retval 无
//  */
//void MatrixLED_ShowColumn(unsigned char Column,Data)
//{
//	_74HC595_WriteByte(Data);
//	MATRIX_LED_PORT=~(0x80>>Column);//0列为选中
//	Delay(1);
//	MATRIX_LED_PORT=0xFF;//消影
//}

void main()
{
	SCK=0;
	RCK=0;
	while(1)
	{
		MatrixLED_ShowColumn(0,0x00);
		MatrixLED_ShowColumn(1,0x60);
		MatrixLED_ShowColumn(2,0x6e);
		MatrixLED_ShowColumn(3,0x1c);
		MatrixLED_ShowColumn(4,0x1c);
		MatrixLED_ShowColumn(5,0x6e);
		MatrixLED_ShowColumn(6,0x60);
		MatrixLED_ShowColumn(7,0x00);
	}
}