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

unsigned char NixieTable[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};

void DT(unsigned char location,number)
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
		Delay(1);
		P0=0x00;
}

void main()
{
	
	while(1)
	{
		DT(1,1);
		DT(2,2);
		DT(3,3);
		DT(4,4);
		DT(5,5);
		DT(6,6);
		DT(7,7);
		DT(8,8);
	}
}