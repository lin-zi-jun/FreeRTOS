#include "header.h"


/******************����������ɾ��ʵ��*******************/
//����A
#define A_Task_PRIO 2
#define A_STK_SIZE 128
TaskHandle_t A_Task_Handler;
void ATast(void *para);

//����B
#define B_Task_PRIO 2
#define B_STK_SIZE 128
TaskHandle_t B_Task_Handler;
void BTast(void *para);
/********************************************************/

void CreateDynamicTask(void)
{
		xTaskCreate((TaskFunction_t )ATast,
										(const char*    )"ATast",
										(unsigned char  )A_STK_SIZE,
										(void*          )NULL,
										(UBaseType_t    )A_Task_PRIO,
										(TaskHandle_t *  )&A_Task_Handler);

			xTaskCreate((TaskFunction_t )BTast,
								(const char*    )"BTast",
								(unsigned char  )B_STK_SIZE,
								(void*          )NULL,
								(UBaseType_t    )B_Task_PRIO,
								(TaskHandle_t *  )&B_Task_Handler);

			
}

void ATast(void *para)
{
	  u8 ATimer=0;
		while(1)
		{
				ATimer++;
				taskENTER_CRITICAL();
				UART_PRINTF("��̬������ʽA:%d\r\n",ATimer);
				taskEXIT_CRITICAL();	
				vTaskDelay(10000);	
		}
}

void BTast(void *para)
{
		static u8 BTimer=0;
		while(1)
		{
			 BTimer++;
			 taskENTER_CRITICAL();
			 UART_PRINTF("��̬������ʽB:%d\r\n",BTimer);
			 taskEXIT_CRITICAL();
			 vTaskDelay(10000);
		}

}

