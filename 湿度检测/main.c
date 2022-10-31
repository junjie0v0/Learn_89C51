#include <REGX51.H>
#include "Delay.H"
#include "DHT11.H"
#include "LCD1602.H"

unsigned char T;

void main()
{
	Delay(1000);
	LCD_Init();
	T=DHT11_Star();
	Delay(500);
	while(1)
	{
		LCD_ShowNum(1,1,T,3);
		Delay(1000);
	}
}
