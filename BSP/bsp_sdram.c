	#include "bsp_sdram.h"
	#include "fmc.h"


	/* USER CODE BEGIN 0 */
	static FMC_SDRAM_CommandTypeDef Command;

	#define sdramHandle hsdram1
	#define SDRAM_TIMEOUT                    ((uint32_t)0xFFFF)  //���峬ʱʱ��
	 
	 uint32_t bsp_sdram_init(void)
	{
	 
	  MX_FMC_Init();
		return 0;
	 
	}
	 

	 void SDRAM_InitSequence(void)
	{
		uint32_t tmpr = 0;

		/* Step 1 ----------------------------------------------------------------*/
		/* ������������ṩ��SDRAM��ʱ�� */
		Command.CommandMode = FMC_SDRAM_CMD_CLK_ENABLE; //ʱ������ʹ��
		Command.CommandTarget = FMC_SDRAM_CMD_TARGET_BANK1;     //Ŀ��SDRAM�洢����
		Command.AutoRefreshNumber = 1;
		Command.ModeRegisterDefinition = 0;
		/* ������������ */
		HAL_SDRAM_SendCommand(&sdramHandle, &Command, SDRAM_TIMEOUT);

		/* Step 2: ��ʱ100us */ 
		
//		HAL_Delay(1);
		
		/* Step 3 ----------------------------------------------------------------*/
		/* ������������е�bankԤ��� */ 
		Command.CommandMode = FMC_SDRAM_CMD_PALL;    //Ԥ�������
		Command.CommandTarget = FMC_SDRAM_CMD_TARGET_BANK1;    //Ŀ��SDRAM�洢����
		Command.AutoRefreshNumber = 1;
		Command.ModeRegisterDefinition = 0;
		/* ������������ */
		HAL_SDRAM_SendCommand(&sdramHandle, &Command, SDRAM_TIMEOUT);   

		/* Step 4 ----------------------------------------------------------------*/
		/* ��������Զ�ˢ�� */   
		Command.CommandMode = FMC_SDRAM_CMD_AUTOREFRESH_MODE;  //�Զ�ˢ������
		Command.CommandTarget = FMC_SDRAM_CMD_TARGET_BANK1;
		Command.AutoRefreshNumber = 4;  //������ˢ�´��� 
		Command.ModeRegisterDefinition = 0;  
		/* ������������ */
		HAL_SDRAM_SendCommand(&sdramHandle, &Command, SDRAM_TIMEOUT);

		/* Step 5 ----------------------------------------------------------------*/
		/* ����sdram�Ĵ������� */
		tmpr = (uint32_t)SDRAM_MODEREG_BURST_LENGTH_1          |  //����ͻ������:1(������1/2/4/8)
						 SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL   |  //����ͻ������:����(����������/���)
						 SDRAM_MODEREG_CAS_LATENCY_2           |   //����CASֵ:3(������2/3)
						 SDRAM_MODEREG_OPERATING_MODE_STANDARD |   //���ò���ģʽ:0,��׼ģʽ
						 SDRAM_MODEREG_WRITEBURST_MODE_SINGLE;    //����ͻ��дģʽ:1,�������

		/* �����������SDRAM�Ĵ��� */
		Command.CommandMode = FMC_SDRAM_CMD_LOAD_MODE;  //����ģʽ�Ĵ�������
		Command.CommandTarget = FMC_SDRAM_CMD_TARGET_BANK1;
		Command.AutoRefreshNumber = 1;
		Command.ModeRegisterDefinition = tmpr;
		/* ������������ */
		HAL_SDRAM_SendCommand(&sdramHandle, &Command, SDRAM_TIMEOUT);

		/* Step 6 ----------------------------------------------------------------*/

		/* ������ˢ������ */
		
				//ˢ��Ƶ�ʼ�����(��SDCLKƵ�ʼ���),���㷽��:
		//COUNT=SDRAMˢ������/����-20=SDRAMˢ������(us)*SDCLKƵ��(Mhz)/����
			//����ʹ�õ�SDRAMˢ������Ϊ64ms,SDCLK=200/2=100Mhz,����Ϊ8192(2^13).
		//����,COUNT=64*1000*100/8192-20=761
		HAL_SDRAM_ProgramRefreshRate(&sdramHandle, 761); 
	}


	//��ָ����ַ(WriteAddr+Bank5_SDRAM_ADDR)��ʼ,����д��n���ֽ�.
	//pBuffer:�ֽ�ָ��
	//WriteAddr:Ҫд��ĵ�ַ
	//n:Ҫд����ֽ���
	void FMC_SDRAM_WriteBuffer(uint8_t *pBuffer,uint32_t WriteAddr,uint32_t n)
	{
		for(;n!=0;n--)
		{
			*(__IO uint8_t*)(SDRAM_BANK_ADDR+WriteAddr)=*pBuffer;
			WriteAddr++;
			pBuffer++;
		}
	}

	//��ָ����ַ((WriteAddr+Bank5_SDRAM_ADDR))��ʼ,��������n���ֽ�.
	//pBuffer:�ֽ�ָ��
	//ReadAddr:Ҫ��������ʼ��ַ
	//n:Ҫд����ֽ���
	void FMC_SDRAM_ReadBuffer(uint8_t *pBuffer,uint32_t ReadAddr,uint32_t n)
	{
		for(;n!=0;n--)
		{
			*pBuffer++=*(__IO uint8_t*)(SDRAM_BANK_ADDR+ReadAddr);
			ReadAddr++;
		}
	}




	void fsmc_sdram_test(void)
	{  
		__IO uint32_t i=0;  	  
		__IO uint32_t temp=0;	   
		__IO uint32_t sval=0;	//�ڵ�ַ0����������	  				   
		
		//ÿ��16K�ֽ�,д��һ������,�ܹ�д��2048������,�պ���32M�ֽ�
		for(i=0;i<32*1024*1024;i+=16*1024)
		{
			*(__IO uint32_t*)(SDRAM_BANK_ADDR+i)=temp; 
			temp++;
		}
		//���ζ���֮ǰд�������,����У��		  
		for(i=0;i<32*1024*1024;i+=16*1024) 
		{	
				temp=*(__IO uint32_t*)(SDRAM_BANK_ADDR+i);    //SDRAM_BANK_ADDR   BACK0�Ļ���ַ
			if(i==0)sval=temp;
			else if(temp<=sval)break;//�������������һ��Ҫ�ȵ�һ�ζ��������ݴ�.	   		   
			printf("SDRAM Capacity:%dKB\r\n",(uint16_t)(temp-sval+1)*16);//��ӡSDRAM����
		}					 
	}






	/* ��ʼ����У�� */
//	int bsp_sdram_init(void)
//	{
//		__IO uint32_t i=0;  	  
//		__IO uint32_t temp=0;	   
//		__IO uint32_t read_val=0;	//���ڶ�ȡSDRAM�е�����
//		__IO uint8_t success_flag=1; //��־λ�����ڼ�������Ƿ�һ��
//		
////		SDRAM_InitSequence();/*��ʼ��sdram*/

//		//ÿ��16K�ֽ�,д��һ������,�ܹ�д��2048������,�պ���32M�ֽ�
//		for(i=0;i<32*1024*1024;i+=16*1024)
//		{
//			*(__IO uint32_t*)(SDRAM_BANK_ADDR+i)=temp; 
//			temp++;
//		}

//		//����tempֵ
//		temp=0;

//		//���ζ���֮ǰд�������,����У��		  
//		for(i=0;i<32*1024*1024;i+=16*1024) 
//		{	
//				read_val=*(__IO uint32_t*)(SDRAM_BANK_ADDR+i);    //SDRAM_BANK_ADDR   BACK0�Ļ���ַ
//			if(read_val != temp)
//			{
//				success_flag=0; //�����ȡ��������д������ݲ�ƥ�䣬���ñ�־λΪ0
//				break;
//			}
//			temp++;
//		}	
//		

//			if(success_flag)
//			{
//				printf("  checkout sdram : success!!!\r\n");
//				return 0;
//			}
//			else
//			{
//				printf("  checkout sdram : err!!!\r\n");
//				return -1;
//			}		
//	}

#define REFRESH_COUNT        677
#define SDRAM_TIMEOUT                            ((uint32_t)0xFFFF)
#define SDRAM_MODEREG_BURST_LENGTH_1             ((uint16_t)0x0000)
#define SDRAM_MODEREG_BURST_LENGTH_2             ((uint16_t)0x0001)
#define SDRAM_MODEREG_BURST_LENGTH_4             ((uint16_t)0x0002)
#define SDRAM_MODEREG_BURST_LENGTH_8             ((uint16_t)0x0004)
#define SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL      ((uint16_t)0x0000)
#define SDRAM_MODEREG_BURST_TYPE_INTERLEAVED     ((uint16_t)0x0008)
#define SDRAM_MODEREG_CAS_LATENCY_2              ((uint16_t)0x0020)
#define SDRAM_MODEREG_CAS_LATENCY_3              ((uint16_t)0x0030)
#define SDRAM_MODEREG_OPERATING_MODE_STANDARD    ((uint16_t)0x0000)
#define SDRAM_MODEREG_WRITEBURST_MODE_PROGRAMMED ((uint16_t)0x0000) 
#define SDRAM_MODEREG_WRITEBURST_MODE_SINGLE     ((uint16_t)0x0200) 
void MX_SDRAM_InitEx(void)
{
  __IO uint32_t tmpmrd = 0;
  
  /* Step 1: Configure a clock configuration enable command */
  Command.CommandMode            = FMC_SDRAM_CMD_CLK_ENABLE;
  Command.CommandTarget          =  FMC_SDRAM_CMD_TARGET_BANK1;
  Command.AutoRefreshNumber      = 1;
  Command.ModeRegisterDefinition = 0;

  /* Send the command */
  HAL_SDRAM_SendCommand(&hsdram1, &Command, SDRAM_TIMEOUT);

  /* Step 2: Insert 100 us minimum delay */ 
  /* Inserted delay is equal to 1 ms due to systick time base unit (ms) */
  HAL_Delay(1);
    
  /* Step 3: Configure a PALL (precharge all) command */ 
  Command.CommandMode            = FMC_SDRAM_CMD_PALL;
  Command.CommandTarget          = FMC_SDRAM_CMD_TARGET_BANK1;
  Command.AutoRefreshNumber      = 1;
  Command.ModeRegisterDefinition = 0;

  /* Send the command */
  HAL_SDRAM_SendCommand(&hsdram1, &Command, SDRAM_TIMEOUT);  
  
  /* Step 4: Configure an Auto Refresh command */ 
  Command.CommandMode            = FMC_SDRAM_CMD_AUTOREFRESH_MODE;
  Command.CommandTarget          = FMC_SDRAM_CMD_TARGET_BANK1;
  Command.AutoRefreshNumber      = 4;
  Command.ModeRegisterDefinition = 0;

  /* Send the command */
  HAL_SDRAM_SendCommand(&hsdram1, &Command, SDRAM_TIMEOUT);
  
  /* Step 5: Program the external memory mode register */
  tmpmrd = (uint32_t)SDRAM_MODEREG_BURST_LENGTH_4          |\
                     SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL   |\
                     SDRAM_MODEREG_CAS_LATENCY_2           |\
                     SDRAM_MODEREG_OPERATING_MODE_STANDARD |\
                     SDRAM_MODEREG_WRITEBURST_MODE_SINGLE;

  Command.CommandMode            = FMC_SDRAM_CMD_LOAD_MODE;
  Command.CommandTarget          = FMC_SDRAM_CMD_TARGET_BANK1;
  Command.AutoRefreshNumber      = 1;
  Command.ModeRegisterDefinition = tmpmrd;

  /* Send the command */
  HAL_SDRAM_SendCommand(&hsdram1, &Command, SDRAM_TIMEOUT);
  
  /* Step 6: Set the refresh rate counter */
  /* Set the device refresh rate */
  HAL_SDRAM_ProgramRefreshRate(&hsdram1, REFRESH_COUNT); 
}

