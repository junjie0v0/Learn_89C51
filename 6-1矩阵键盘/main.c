#include <REGX51.H>
#include "LCD1602.h"
#include "A.h"//延时函数头文件;

unsigned char KeyNum;

void main()
{
	LCD_Init();//初始化显示屏；
	LCD_ShowString(1,1,"MatrixKey:");//显示字符；
	while(1)
	{
		KeyNum=MatrixKey();//获取按键的序号；
		if(KeyNum)
		{
			LCD_ShowNum(2,1,KeyNum,2);
		}
	}
}
