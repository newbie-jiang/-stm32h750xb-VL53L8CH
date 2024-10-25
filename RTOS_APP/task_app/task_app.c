#include "task_app.h"

#include "freertos.h"
#include "task.h"

#include "gpio.h"
#include "stdio.h"
#include "shell.h"
#include "app_config.h"



   void LedTask(void)
  {
	 while (1)
    {
      HAL_GPIO_TogglePin(LED_B_GPIO_Port,LED_B_Pin);
			HAL_GPIO_TogglePin(LED_R_GPIO_Port,LED_R_Pin);
      vTaskDelay(500);   /* ��ʱ500��tick */
    }
  }	
	
	
	void ShellTask(void)
	{
	  while(1)
		{
		
	  	shell();
		  vTaskDelay(1);   /* ��ʱ500��tick */
		}

	}
	
	
	
	void DisplayTask(void)
	{
	  while(1)
		{
//		test_cjson_send();
//	    test_cjson_receive();
//			
 
//		  vTaskDelay(1000);   /* ��ʱ500��tick */
		}

	}
	
	
	/*
	  led task
	  display task
	
	  shell task
	  touch task
	  irda task
	  adc task
	  uart process task
	  usb task
*/
	
	
			