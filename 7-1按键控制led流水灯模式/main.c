#include <REGX51.H>
#include <INTRINS.H>
#include "A.H"

unsigned char KeyNum,LEDMode;

void main()
{
	P2=0xfe;//初始化led灯；
	Timer0Init();
	while(1)
	{
		KeyNum=Key();//获取按键位置；
		if(KeyNum)
		{
		if(KeyNum==1)//第一个按键被按下时；
			{
				LEDMode++;
				if(LEDMode>=2)
					LEDMode=0;
			}
		}
	}
	
	
}

void Timer0_Routine() interrupt 1
{
	static unsigned int T0Count;//设置全局静态变量防止丢失；
	TL0 = 0x18;		//设置定时初值
	TH0 = 0xFC;		//设置定时初值
	T0Count++;		//每次溢出后记一次数；溢出时间为500ms；
	if(T0Count==500)//溢出时间为500ms；
	{
		T0Count=0;	//重新计数；
		if(LEDMode==0)			//模式判断
			P2=_crol_(P2,1);	//LED输出
		if(LEDMode==1)
			P2=_cror_(P2,1);
	}
}