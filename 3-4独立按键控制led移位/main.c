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
	unsigned char lednum;
	P2=0xfe;
	while(1)
	{
		if(P1_2==0)
		{
		Delay(20);
		while(P1_2==0);
		Delay(20);
		
		lednum++;
		if(lednum>=8)
			lednum=0;
		P2=~(0x01<<lednum);
		}
		
		if(P1_3==0)
		{
		Delay(20);
		while(P1_3==0);
		Delay(20);
		
		
		if(lednum==0)
			lednum=7;
		else
			lednum--;
		P2=~(0x01<<lednum);
		}
	}
	
}