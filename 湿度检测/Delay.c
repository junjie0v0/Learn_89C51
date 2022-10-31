//#include <intrins.h>
void Delay(unsigned int x) //@11.0592MHz 1ms
{
	unsigned int i,y;
	for(i=x;i>0;i--)
	{
	for(y=115;y>0;y--);
	}
}