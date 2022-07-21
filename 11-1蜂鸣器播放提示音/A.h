#ifndef __A_H__
#define __A_H__


void Delay(unsigned int xms);
void DT(unsigned char location,number);
unsigned char Key();
void Timer0Init(void);
void UART_Init();
void UART_SendByte(unsigned char Byte);
void MatrixLED_ShowColumn(unsigned char Column,Data);
void _74HC595_WriteByte(unsigned char Byte);

#endif