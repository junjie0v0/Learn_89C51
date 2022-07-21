#include <REGX51.H>
#include <INTRINS.H>
#include "A.H"

sbit Beep=P2^5;

unsigned char KeyNum;

/**
  * @brief  蜂鸣器私有延时函数，延时500us
  * @param  无
  * @retval 无
  */
void Buzzer_Delay500us()		//@12.000MHz
{
	unsigned char i;

	_nop_();
	i = 247;
	while (--i);
}

void Buzzer(unsigned int ms)
{
	unsigned int i;
	for(i=0;i<ms*2;i++)
	{
		Beep=!Beep;
		Buzzer_Delay500us();
	}
}

void main()
{
	while(1)
	{
		KeyNum=Key();
		if(KeyNum>0)
		{
			Buzzer(100);
		}
	}
}