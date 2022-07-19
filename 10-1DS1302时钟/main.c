#include <REGX51.H>
#include "A.H"
#include "LCD1602.H"

sbit DS1302_SCLK=P3^6;
sbit DS1302_CE=P3^5;
sbit DS1302_IO=P3^4;

//地址的定义
#define DS1302_Seconds 0x80
#define DS1302_Minutes 0x82
#define DS1302_Hour 0x84
#define DS1302_Date 0x86
#define DS1302_Month 0x88
#define DS1302_Week 0x8a
#define DS1302_Year 0x8c
#define DS1302_WP 0x8e

unsigned char Time[]={55,59,23,5,7,2,22};


void DS1302_Init()
{
	DS1302_CE=0;//在读和写时必须将CE信号置为高电平
	DS1302_SCLK=0;//SCLK用于同步串行接口上的数据移动。
}

void DS1302_Write(unsigned char Command,date)//秒寄存器的的七位被定义为始终停止(CH)标志
{
	char i;
	DS1302_CE=1;
	for(i=0;i<8;i++)
	{
		DS1302_IO=Command&(0x01<<i);
		DS1302_SCLK=1;
		DS1302_SCLK=0;
	}
	for(i=0;i<8;i++)
	{
		DS1302_IO=date&(0x01<<i);
		DS1302_SCLK=1;
		DS1302_SCLK=0;
	}
	DS1302_CE=0;
	
}

unsigned char DS1302_Read(unsigned char Command)
{
	unsigned char i,Data=0x00;
	Command|=0x01;	//将指令转换为读指令
	DS1302_CE=1;
	for(i=0;i<8;i++)
	{
		DS1302_IO=Command&(0x01<<i);
		DS1302_SCLK=0;
		DS1302_SCLK=1;
	}
	for(i=0;i<8;i++)
	{ 
		DS1302_SCLK=1;
		DS1302_SCLK=0;
		if(DS1302_IO){Data|=(0x01<<i);}
	}
	DS1302_CE=0;
	DS1302_IO=0;	//读取后将IO设置为0，否则读出的数据会出错
	return (Data/16*10+Data%16);
}

void DS1302_SetTime(void)
{
	DS1302_Write(DS1302_Seconds,Time[0]/10*6+Time[0]);
	DS1302_Write(DS1302_Minutes,Time[1]/10*6+Time[1]);
	DS1302_Write(DS1302_Hour,Time[2]/10*6+Time[2]);
	DS1302_Write(DS1302_Date,Time[3]/10*6+Time[3]);
	DS1302_Write(DS1302_Month,Time[4]/10*6+Time[4]);
	DS1302_Write(DS1302_Week,Time[5]/10*6+Time[5]);
	DS1302_Write(DS1302_Year,Time[6]/10*6+Time[6]);
	DS1302_Write(DS1302_WP,Time[7]/10*6+Time[7]);
}

void main()
{
	LCD_Init();
	DS1302_Init();
	DS1302_SetTime();
	while(1)
	{
		LCD_ShowString(1,1,"Time");
		LCD_ShowNum(2,1,DS1302_Read(0x89),2);
		LCD_ShowNum(2,4,DS1302_Read(0x87),2);
		LCD_ShowNum(2,7,DS1302_Read(0x85),2);
		LCD_ShowNum(2,10,DS1302_Read(0x83),2);
		LCD_ShowNum(2,13,DS1302_Read(0x81),2);
	}
}