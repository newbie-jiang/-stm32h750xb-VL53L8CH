#include "bsp_usart.h" 
//#include "ring_buffer.h"



extern UART_HandleTypeDef huart4;



//static ring_buffer rx_buf;

void uart4_init(void)
{
  
 //hal���Ѿ����˳�ʼ��	
//	ring_buffer_init(&rx_buf);
}





/*****************************************************
*function:	д�ַ��ļ�����
*param1:	������ַ�
*param2:	�ļ�ָ��
*return:	����ַ���ASCII��
******************************************************/
 int fputc(int ch, FILE *f)
{
	HAL_UART_Transmit(&huart4, (uint8_t*)&ch, 1,0xff);
	return ch;
}


/*****************************************************
*function:	���ַ��ļ�����
*param1:	�ļ�ָ��
*return:	��ȡ�ַ���ASCII��
******************************************************/
 int fgetc(FILE *f)
{
    uint8_t ch = 0;
    HAL_UART_Receive(&huart4, (uint8_t*)&ch, 1, 10);
    return (int)ch;
}


/*
 * ������´��룬����Ҫ�ڹ��������й�ѡUse MicroLIB
*/


#ifndef __MICROLIB

#pragma import(__use_no_semihosting)
 
struct __FILE
{
	int a;
};
 
FILE __stdout;
FILE __stdin;
void _sys_exit(int x)
{
	
}

#endif




void bsp_debug_uart4_init(void)
{
  uart4_init();
	
}


void putstr(const char *str)
{
	while (*str)
	{
		putchar(*str);
		str++;
	}
}



int my_getchar(void)
{
  unsigned char c;
  FILE * ch;
	c=fgetc(ch);
	return c;
}


void putdatas(const char *datas, int len)
{
	int i;
	for (i = 0; i < len; i++)
	{
		putchar(datas[i]);
	}
}


const unsigned char hex_tab[]={'0','1','2','3','4','5','6','7',\
		                 '8','9','a','b','c','d','e','f'};

void puthex(unsigned int val)
{
	/* val: 0x12345678 */
	int i;
	int index;
	putstr("0x");
	for (i = 7; i >=0 ; i--)
	{
		index = (val >> (i*4)) & 0xf;
		putchar(hex_tab[index]);
	}
}




