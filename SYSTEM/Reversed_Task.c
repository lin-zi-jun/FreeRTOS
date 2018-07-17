#include "header.h"	

#define LOW_TASK_PRIO 2
#define LOW_STK_SIZE  128
TaskHandle_t LOW_Task_Headler;
void LOW_Task(void *para);

#define MIDDLE_TASK_PRIO 3
#define MIDDLE_STK_SIZE  128
TaskHandle_t MIDDLE_Task_Headler;
void MIDDLE_Task(void *para);

#define HIGH_TASK_PRIO 4
#define HIGH_STK_SIZE  128
TaskHandle_t HIGH_Task_Headler;
void HIGH_Task(void *para);

SemaphoreHandle_t ReversedSemaphore;

void Create_Reversed_Task(void)
{	

		vSemaphoreCreateBinary(ReversedSemaphore);
		 if( ReversedSemaphore != NULL )
			{
					UART_PRINTF("在反转实验创建二值信号量失败\r\n");
			}else
			{
					xSemaphoreGive( ReversedSemaphore );
			}

		xTaskCreate((TaskFunction_t )LOW_Task,
								(const char*    )"LOW_Task",
								(unsigned char  )LOW_STK_SIZE,
								(void*          )NULL,
								(UBaseType_t    )LOW_TASK_PRIO,
								(TaskHandle_t *  )&LOW_Task_Headler);
								
		xTaskCreate((TaskFunction_t )MIDDLE_Task,
								(const char*    )"MIDDLE_Task",
								(unsigned char  )MIDDLE_STK_SIZE,
								(void*          )NULL,
								(UBaseType_t    )MIDDLE_TASK_PRIO,
								(TaskHandle_t *  )&MIDDLE_Task_Headler);

		xTaskCreate((TaskFunction_t )HIGH_Task,
										(const char*    )"HIGH_Task",
										(unsigned char  )HIGH_STK_SIZE,
										(void*          )NULL,
										(UBaseType_t    )HIGH_TASK_PRIO,
										(TaskHandle_t *  )&HIGH_Task_Headler);
}


void LOW_Task(void *para)
{
	while(1)
	{
			UART_PRINTF("Low 请求信号量\r\n");
			xSemaphoreTake(ReversedSemaphore,portMAX_DELAY);
			taskENTER_CRITICAL();
			UART_PRINTF("Low Task Runing\r\n");
			taskEXIT_CRITICAL();
			UART_PRINTF("Low 处理事件\r\n");
			delay_xms(10000);
			UART_PRINTF("Low 释放信号量\r\n");
			xSemaphoreGive( ReversedSemaphore );
			

	}
}

void MIDDLE_Task(void *para)
{
	while(1)
	{
			taskENTER_CRITICAL();
			UART_PRINTF("Middle Task Runing\r\n");
			taskEXIT_CRITICAL();
			vTaskDelay(5000);
	}
}

void HIGH_Task(void *para)
{
	while(1)
	{
		
			UART_PRINTF("High 请求信号量\r\n");
			xSemaphoreTake(ReversedSemaphore,portMAX_DELAY);
			taskENTER_CRITICAL();
			UART_PRINTF("High Task Runing\r\n");
			taskEXIT_CRITICAL();
			UART_PRINTF("High 释放信号量\r\n");
			xSemaphoreGive( ReversedSemaphore );
			
			vTaskDelay(5000);
	}
}




