#include <REGX51.H>


void Delay(unsigned int xms)//延时函数；
{
	while(xms--)
	{
		unsigned char i, j;

	i = 2;
	j = 239;
	do
	{
		while (--j);
	} while (--i);
	}
}


unsigned char NixieTable[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
void DT(unsigned char location,number)//数码管的启动；
{
		switch (location)
		{
			case(1):P2_4=0;P2_3=0;P2_2=0;break;
			case(2):P2_4=0;P2_3=0;P2_2=1;break;
			case(3):P2_4=0;P2_3=1;P2_2=0;break;
			case(4):P2_4=0;P2_3=1;P2_2=1;break;
			case(5):P2_4=1;P2_3=0;P2_2=0;break;
			case(6):P2_4=1;P2_3=0;P2_2=1;break;
			case(7):P2_4=1;P2_3=1;P2_2=0;break;
			case(8):P2_4=1;P2_3=1;P2_2=1;break;
		}
		P0=NixieTable[number];
		Delay(1);//数码管消影;
		P0=0x00;
}


/**
  * @brief  获取独立按键键码
  * @param  无
  * @retval 按下按键的键码，范围：0~4，无按键按下时返回值为0
  */
unsigned char Key()
{
	unsigned char KeyNumber=0;
	
	if(P3_1==0){Delay(20);while(P3_1==0);Delay(20);KeyNumber=1;}
	if(P3_0==0){Delay(20);while(P3_0==0);Delay(20);KeyNumber=2;}
	if(P3_2==0){Delay(20);while(P3_2==0);Delay(20);KeyNumber=3;}
	if(P3_3==0){Delay(20);while(P3_3==0);Delay(20);KeyNumber=4;}
	
	return KeyNumber;
}




/**
  * @brief  定时器0初始化，1毫秒@12.000MHz
  * @param  无
  * @retval 无
  */
void Timer0Init(void)
{
	TMOD &= 0xF0;		//设置定时器模式
	TMOD |= 0x01;		//设置定时器模式
	TL0 = 0x18;		//设置定时初值
	TH0 = 0xFC;		//设置定时初值
	TF0 = 0;		//清除TF0标志
	TR0 = 1;		//定时器0开始计时
	ET0=1;
	EA=1;
	PT0=0;
}

/*定时器中断函数模板
void Timer0_Routine() interrupt 1
{
	static unsigned int T0Count;
	TL0 = 0x18;		//设置定时初值
	TH0 = 0xFC;		//设置定时初值
	T0Count++;
	if(T0Count>=1000)
	{
		T0Count=0;
		
	}
}
*/




