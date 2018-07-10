#include "header.h"	

#define MLOW_TASK_PRIO 2
#define MLOW_STK_SIZE  128
TaskHandle_t MLOW_Task_Headler;
void MLOW_Task(void *para);

#define MMIDDLE_TASK_PRIO 3
#define MMIDDLE_STK_SIZE  128
TaskHandle_t MMIDDLE_Task_Headler;
void MMIDDLE_Task(void *para);

#define MHIGH_TASK_PRIO 4
#define MHIGH_STK_SIZE  128
TaskHandle_t MHIGH_Task_Headler;
void MHIGH_Task(void *para);

SemaphoreHandle_t MutualSemaphore;

void Create_Mutex_Task(void)
{	

			MutualSemaphore=xSemaphoreCreateMutex();
		 if( MutualSemaphore != NULL )
			{
					UART_PRINTF("在反转实验创建二值信号量失败\r\n");
			}

		xTaskCreate((TaskFunction_t )MLOW_Task,
								(const char*    )"MLOW_Task",
								(unsigned char  )MLOW_STK_SIZE,
								(void*          )NULL,
								(UBaseType_t    )MLOW_TASK_PRIO,
								(TaskHandle_t *  )&MLOW_Task_Headler);
								
		xTaskCreate((TaskFunction_t )MMIDDLE_Task,
								(const char*    )"MMIDDLE_Task",
								(unsigned char  )MMIDDLE_STK_SIZE,
								(void*          )NULL,
								(UBaseType_t    )MMIDDLE_TASK_PRIO,
								(TaskHandle_t *  )&MMIDDLE_Task_Headler);

		xTaskCreate((TaskFunction_t )MHIGH_Task,
										(const char*    )"MHIGH_Task",
										(unsigned char  )MHIGH_STK_SIZE,
										(void*          )NULL,
										(UBaseType_t    )MHIGH_TASK_PRIO,
										(TaskHandle_t *  )&MHIGH_Task_Headler);
}


void MLOW_Task(void *para)
{
	while(1)
	{
			UART_PRINTF("Low 请求信号量\r\n");
			xSemaphoreTake(MutualSemaphore,portMAX_DELAY);
			taskENTER_CRITICAL();
			UART_PRINTF("Low Task Runing\r\n");
			taskEXIT_CRITICAL();
			UART_PRINTF("Low 处理事件\r\n");
			delay_xms(10000);
			UART_PRINTF("Low 释放信号量\r\n");
			xSemaphoreGive( MutualSemaphore );
	}
}

void MMIDDLE_Task(void *para)
{
	while(1)
	{
			taskENTER_CRITICAL();
			UART_PRINTF("Middle Task Runing\r\n");
			taskEXIT_CRITICAL();
			vTaskDelay(1000);
	}
}

void MHIGH_Task(void *para)
{
	while(1)
	{
		
			UART_PRINTF("High 请求信号量\r\n");
			xSemaphoreTake(MutualSemaphore,portMAX_DELAY);
			taskENTER_CRITICAL();
			UART_PRINTF("High Task Runing\r\n");
			taskEXIT_CRITICAL();
			UART_PRINTF("High 释放信号量\r\n");
			xSemaphoreGive( MutualSemaphore );
			
			vTaskDelay(1000);
	}
}




