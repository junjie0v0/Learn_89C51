#include <REGX51.H>

void Delay(unsigned int xms)
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

void main()
{
	while(1)
	{
		if(P1_2==0)
		{
			Delay(20);
		while(P1_2==0);
			Delay(20);
			P2_1=~P2_1;
		}
	}
}
