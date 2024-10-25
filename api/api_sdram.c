#include "api_sdram.h"
#include "bsp_sdram.h"



uint32_t api_sdram_init(void)
{
	 return bsp_sdram_init();
	
}

uint32_t api_sdram_config(void)
{
	 SDRAM_InitSequence();
}


 sdram_driver ssdram_driver = {
  .sdram_init = api_sdram_init,
	.sdram_config = api_sdram_config,
 };
 
#define SDRAM_BANK_ADDRESS     ((uint32_t)0xC0000000)

uint32_t tets_sdram_driver(sdram_driver * psdram_driver)
{
	uint8_t test_buffer_arr[1024] ={0};
	psdram_driver->sdram_init();
	psdram_driver->sdram_config();
	

	volatile uint32_t i=0;  	  
	volatile uint32_t temp=0;	   
	volatile uint32_t read_val=0;	//���ڶ�ȡSDRAM�е�����
	volatile uint8_t success_flag=1; //��־λ�����ڼ�������Ƿ�һ��
		

		//ÿ��16K�ֽ�,д��һ������,�ܹ�д��2048������,�պ���32M�ֽ�
		for(i=0;i<32*1024*1024;i+=16*1024)
		{
			*(__IO uint32_t*)(SDRAM_BANK_ADDRESS+i)=temp; 
			temp++;
		}

		//����tempֵ
		temp=0;

		//���ζ���֮ǰд�������,����У��		  
		for(i=0;i<32*1024*1024;i+=16*1024) 
		{	
				read_val=*(__IO uint32_t*)(SDRAM_BANK_ADDRESS+i);    //SDRAM_BANK_ADDR   BACK0�Ļ���ַ
			if(read_val != temp)
			{
				success_flag=0; //�����ȡ��������д������ݲ�ƥ�䣬���ñ�־λΪ0
				break;
			}
			temp++;
		}	
		

			if(success_flag)
			{
				printf("  checkout sdram : success!!!\r\n");
				return 0;
			}
			else
			{
				printf("  checkout sdram : err!!!\r\n");
				return -1;
			}		
	

}

