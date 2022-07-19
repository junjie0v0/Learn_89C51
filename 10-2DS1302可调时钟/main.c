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

char Time[]={55,59,23,5,7,2,22},Mode,KeyNum,TimeSetSelect,TimeSetFlashFlag;
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

unsigned char DS1302_ReadTime()
	{
	Time[4]=DS1302_Read(0x89);
	Time[3]=DS1302_Read(0x87);
	Time[2]=DS1302_Read(0x85);
	Time[1]=DS1302_Read(0x83);
	Time[0]=DS1302_Read(0x81);
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

void TimeShow()
{
	LCD_ShowString(1,1,"Time");
	LCD_ShowNum(1,15,Mode,2);
	LCD_ShowNum(2,1,Time[4],2);
	LCD_ShowNum(2,4,Time[3],2);
	LCD_ShowNum(2,7,Time[2],2);
	LCD_ShowNum(2,10,Time[1],2);
	LCD_ShowNum(2,13,Time[0],2);
}

void TimeSet()
{
	if(KeyNum==2)
	{
	TimeSetSelect++;
	TimeSetSelect%=6;
	}
	if(KeyNum==3)		//如果按键2被按下则时间++；
	{
		Time[TimeSetSelect]++;
		if(TimeSetSelect==0)				//秒
			Time[TimeSetSelect]%=60;
		else if(TimeSetSelect==1)			//分
			Time[TimeSetSelect]%=60;
		else if(TimeSetSelect==2)			//时
			Time[TimeSetSelect]%=24;
		else if(TimeSetSelect==3)			//日
		{
			if(Time[6]%4==0 && Time[4]==2)//闰年并且是二月
			{
				Time[TimeSetSelect]%=30;
			}
			switch(Time[4])
				{
				case 1:
				case 3:
				case 5:
				case 7:
				case 8:
				case 10:
				case 12:Time[TimeSetSelect]%=32;break;
				case 2:Time[TimeSetSelect]%=29;break;
				default:Time[TimeSetSelect]%=31;break;
				}
		}
			
		else if(TimeSetSelect==4)	//月
			if(Time[TimeSetSelect]>12)
				Time[TimeSetSelect]=1;
		
		else if(TimeSetSelect==6)	//星期
			Time[TimeSetSelect]%=8;
		else if(TimeSetSelect==5)	//年	
			Time[TimeSetSelect]%=99;
	}
	
	
	
	if(KeyNum==3)		//如果按键3被按下则时间--；
	{
		Time[TimeSetSelect]--;
		if(TimeSetSelect==0 && Time[TimeSetSelect]<0)				//秒
			Time[TimeSetSelect]=59;
		else if(TimeSetSelect==1 && Time[TimeSetSelect]<0)			//分
			Time[TimeSetSelect]=59;
		else if(TimeSetSelect==2 && Time[TimeSetSelect]<0)			//时
			Time[TimeSetSelect]=23;
		else if(TimeSetSelect==1 && Time[TimeSetSelect]<1)			//日
		{
			if(Time[6]%4==0 && Time[4]==2  && Time[TimeSetSelect]<1)//闰年并且是二月
			{
				Time[TimeSetSelect]=29;
			}
			switch(Time[4])
				{
				case 1:
				case 3:
				case 5:
				case 7:
				case 8:
				case 10:
				case 12:Time[TimeSetSelect]=31;break;
				case 2:Time[TimeSetSelect]=28;break;
				default:Time[TimeSetSelect]=30;break;
				}
		}
			
		else if(TimeSetSelect==4 && Time[TimeSetSelect]<0)	//月
				Time[TimeSetSelect]=12;
		
		else if(TimeSetSelect==6 && Time[TimeSetSelect]<0)	//星期
			Time[TimeSetSelect]=7;
		else if(TimeSetSelect==5 && Time[TimeSetSelect]<0)	//年	
			Time[TimeSetSelect]=99;
	}
	
	
	//Mode=1时时间设置位闪烁
//	if(TimeSetSelect==0 && TimeSetFlashFlag==0){LCD_ShowString(2,1,"  ");}
//	else{{LCD_ShowNum(2,1,Time[4],2);}}
//	if(TimeSetSelect==1 && TimeSetFlashFlag==0){LCD_ShowString(2,4,"  ");}
//	else{{LCD_ShowNum(2,1,Time[3],2);}}
//	if(TimeSetSelect==1 && TimeSetFlashFlag==0){LCD_ShowString(2,7,"  ");}
//	else{{LCD_ShowNum(2,1,Time[2],2);}}
//	if(TimeSetSelect==1 && TimeSetFlashFlag==0){LCD_ShowString(2,10,"  ");}
//	else{{LCD_ShowNum(2,1,Time[1],2);}}
//	if(TimeSetSelect==1 && TimeSetFlashFlag==0){LCD_ShowString(2,13,"  ");}
//	else{{LCD_ShowNum(2,1,Time[0],2);}}

	
	
}

void main()
{
	LCD_Init();
	DS1302_Init();
	DS1302_SetTime();
	while(1)
	{
		KeyNum=Key();
		if(KeyNum==1)
			{
				if(Mode==0){Mode=1;TimeSetSelect=0;}//设置按键模式1为设置模式和显示模式互换  2时间+1  3时间-1
				else if(Mode==1){Mode=0;DS1302_SetTime();}
			}
		switch(Mode)
		{
			case 0:TimeShow();break;
			case 1:TimeSet();break;
		}
		TimeShow();
	}
}



void Timer0_Routine() interrupt 1
{
	static unsigned int T0Count;
	TL0 = 0x18;		//设置定时初值
	TH0 = 0xFC;		//设置定时初值
	T0Count++;
	if(T0Count>=500)
	{
		T0Count=0;
		TimeSetFlashFlag=!TimeSetFlashFlag;
	}
}