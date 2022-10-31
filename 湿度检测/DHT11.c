#include <REGX51.H>

#define DHT11 P1_0

unsigned char DHT11_Star(void)
{
	unsigned char i, j;
	DHT11=1;
	DHT11=0;	
	//主机拉低20ms以发送开始信号
	i = 36;
	j = 217;
	do
	{
		while (--j);
	} while (--i);

	//拉高并等待30us,DHT11拉低以响应主机
	i = 11;
	while (--i);
	return DHT11;
}
