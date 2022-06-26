#include <REGX51.H>
#include "LCD1602.h"
#include "A.h"//延时函数头文件;

unsigned char KeyNum;

void main()
{
	LCD_Init();//初始化显示屏；
	LCD_ShowString(1,1,"MatrixKey:");
	while(1)
	{
		KeyNum=MatrixKey();
		if(KeyNum)
		{
			LCD_ShowNum(2,1,KeyNum,2);
		}
	}
}
