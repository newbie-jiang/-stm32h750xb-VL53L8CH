#include "creat_task.h"

#include "task_app.h"

#include "stdio.h"
#include "api_information.h"
#include "api_sdram.h"
#include "api_led.h"



	static void hardware_init(void);

/********************************************************************************************************/
		/* ������ */
		static TaskHandle_t StartTask_Handle = NULL;    /* ��������������*/
		static TaskHandle_t LedTask_Handle = NULL;      /* LED     ������     */
		static TaskHandle_t ShellTask_Handle = NULL;    /* Shell   ������     */
    static TaskHandle_t DisplayTask_Handle = NULL;  /* display ������     */
/********************************************************************************************************/

/********************************************************************************************************/
		/* ���������� */
	  static void StartTask(void);/* ���ڴ�������� ���� */
/********************************************************************************************************/


  


  /*����������������������������֮��ͽ��Լ�ɾ�����߹���*/
   int FreeRTOS_Start(void)
   {
		 BaseType_t xReturn = pdPASS;/* ����һ��������Ϣ����ֵ��Ĭ��ΪpdPASS */

     
  
     /* ����AppTaskCreate���� */
     xReturn = xTaskCreate((TaskFunction_t )StartTask,  /* ������ں��� */
                        (const char*    )"AppTaskCreate",/* �������� */
                        (uint16_t       )512,  /* ����ջ��С */
                        (void*          )NULL,/* ������ں������� */
                        (UBaseType_t    )1, /* ��������ȼ� */
                        (TaskHandle_t*  )&StartTask_Handle);/* ������ƿ�ָ�� */ 
     /* ����������� */           
     if(pdPASS == xReturn)
       vTaskStartScheduler();   /* �������񣬿������� */
    else
    return -1;  
  
    while(1);   /* ��������ִ�е����� */  
	}




   void StartTask(void)
	{
	  BaseType_t xReturn = pdPASS;/* ����һ��������Ϣ����ֵ��Ĭ��ΪpdPASS */
  
    taskENTER_CRITICAL();           //�����ٽ���
		
		hardware_init(); //Ӳ����ʼ��
  
    /* ����LedTask���� */
    xReturn = xTaskCreate((TaskFunction_t )LedTask, /* ������ں��� */
                        (const char*    )"LED_Task",/* �������� */
                        (uint16_t       )128,   /* ����ջ��С */
                        (void*          )NULL,	/* ������ں������� */
                        (UBaseType_t    )2,	    /* ��������ȼ� */
                        (TaskHandle_t*  )&LedTask_Handle);/* ������ƿ�ָ�� */
    if(pdPASS != xReturn){
		
		  printf(" create LedTask err  \r\n");
		}
		
	 
		/* ����ShellTask���� */
    xReturn = xTaskCreate((TaskFunction_t )ShellTask, /* ������ں��� */
                        (const char*    )"Shell_Task",/* �������� */
                        (uint16_t       )256,   /* ����ջ��С */
                        (void*          )NULL,	/* ������ں������� */
                        (UBaseType_t    )2,	    /* ��������ȼ� */
                        (TaskHandle_t*  )&ShellTask_Handle);/* ������ƿ�ָ�� */
    if(pdPASS != xReturn){
		 printf(" create ShellTask err  \r\n");
		}
		
		
		
		/* ����display���� */
    xReturn = xTaskCreate((TaskFunction_t )DisplayTask, /* ������ں��� */
                        (const char*    )"Display_Task",/* �������� */
                        (uint16_t       )256,   /* ����ջ��С */
                        (void*          )NULL,	/* ������ں������� */
                        (UBaseType_t    )2,	    /* ��������ȼ� */
                        (TaskHandle_t*  )&DisplayTask_Handle);/* ������ƿ�ָ�� */
    if(pdPASS != xReturn){
		 printf(" create DisplayTask err  \r\n");
		}
		
	  /* Other Task  ���� */
		
		
		
		
		
		
		vTaskDelete(StartTask_Handle);  //ɾ��AppTaskCreate����
		
    taskEXIT_CRITICAL();            //�˳��ٽ���
		
		
		
	}
		

  






	void display_app_logo(void)
	{
	
  printf("               AAA               PPPPPPPPPPPPPPPPP   PPPPPPPPPPPPPPPPP     1111111   \r\n");
  printf("              A:::A              P::::::::::::::::P  P::::::::::::::::P   1::::::1    \r\n");
  printf("             A:::::A             P::::::PPPPPP:::::P P::::::PPPPPP:::::P 1:::::::1    \r\n");
  printf("            A:::::::A            PP:::::P     P:::::PPP:::::P     P:::::P111:::::1     \r\n");
  printf("           A:::::::::A             P::::P     P:::::P  P::::P     P:::::P   1::::1    \r\n");
  printf("          A:::::A:::::A            P::::P     P:::::P  P::::P     P:::::P   1::::1    \r\n");
  printf("         A:::::A A:::::A           P::::PPPPPP:::::P   P::::PPPPPP:::::P    1::::1    \r\n");
  printf("        A:::::A   A:::::A          P:::::::::::::PP    P:::::::::::::PP     1::::l    \r\n");
  printf("       A:::::A     A:::::A         P::::PPPPPPPPP      P::::PPPPPPPPP       1::::l    \r\n");
  printf("      A:::::AAAAAAAAA:::::A        P::::P              P::::P               1::::l     \r\n");
  printf("     A:::::::::::::::::::::A       P::::P              P::::P               1::::l    \r\n");
  printf("    A:::::AAAAAAAAAAAAA:::::A      P::::P              P::::P               1::::l     \r\n");
  printf("   A:::::A             A:::::A    PP::::::PP          PP::::::PP          111::::::111 \r\n");
  printf("  A:::::A               A:::::A  P::::::::P          P::::::::P          1::::::::::1 \r\n");
  printf(" A:::::A                 A:::::A P::::::::P          P::::::::P          1::::::::::1 \r\n");
  printf("AAAAAAA                   AAAAAAAPPPPPPPPPP          PPPPPPPPPP          111111111111 \r\n\r\n\r\n");
  printf(" jump to app1 success\r\n");                                                                           

	}
	
	
	void hardware_init(void)
	{
		//��ӡlogo
		display_app_logo();
		
		//��ȡ�豸��Ϣ
		uint32_t SysClock,HCLKFreq,PCLK1Freq,PCLK2Freq;
		api_clock_info * papi_clock_info =&sapi_clock_info;
		SysClock = papi_clock_info->get_SysClockFreq();
	  HCLKFreq = papi_clock_info->get_HCLKFreq();
		PCLK1Freq = papi_clock_info->get_PCLK1Freq();
	  PCLK2Freq = papi_clock_info->get_PCLK2Freq();
		printf("SysClock:%d \r\n ",SysClock);
		printf("HCLKFreq:%d \r\n ",HCLKFreq);
		printf("PCLK1Freq:%d \r\n ",PCLK1Freq);
		printf("PCLK2Freq:%d \r\n ",PCLK2Freq);
		
		//��ʼ��sdram
		sdram_driver * psdram_driver =&ssdram_driver;
		psdram_driver->sdram_init();
		psdram_driver->sdram_config();
		
		
	}





