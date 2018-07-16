#include "header.h"

#define COUNT_SEND_TASK_PRIO 2
#define COUNT_SEND_STK_SIZE  128
TaskHandle_t COUNT_SEND_Task_Headler;
void COUNT_SEND_Task(void *para);

#define COUNT_RECV_TASK_PRIO 3
#define COUNT_RECV_STK_SIZE  128
TaskHandle_t COUNT_RECV_Task_Headler;
void COUNT_RECV_Task(void *para);

SemaphoreHandle_t CountSemaphore;//计数型信号量

void Create_COUNT_Task(void)
{	
	
		CountSemaphore=xSemaphoreCreateCounting(10,5);	

		xTaskCreate((TaskFunction_t )COUNT_SEND_Task,
								(const char*    )"COUNT_SEND_Task",
								(unsigned char  )COUNT_SEND_STK_SIZE,
								(void*          )NULL,
								(UBaseType_t    )COUNT_SEND_TASK_PRIO,
								(TaskHandle_t *  )&COUNT_SEND_Task_Headler);
								
		xTaskCreate((TaskFunction_t )COUNT_RECV_Task,
								(const char*    )"COUNT_RECV_Task",
								(unsigned char  )COUNT_RECV_STK_SIZE,
								(void*          )NULL,
								(UBaseType_t    )COUNT_RECV_TASK_PRIO,
								(TaskHandle_t *  )&COUNT_RECV_Task_Headler);
}


void COUNT_SEND_Task(void *para)
{
	BaseType_t err=pdFALSE;
	u8 semavalue=0;
	while(1)
	{
			taskENTER_CRITICAL();
			err=xSemaphoreGive(CountSemaphore);
			if(err==pdFALSE)
			UART_PRINTF("信号量已满\t");
			semavalue=uxSemaphoreGetCount(CountSemaphore);
			UART_PRINTF("当前计数信号量:%d\t",semavalue);
			taskEXIT_CRITICAL();
			vTaskDelay(1000);
	}
}



void COUNT_RECV_Task(void *para)
{
	
	  u8 semavalue=0;
		while(1)
		{
//				taskENTER_CRITICAL();				//若在此处进入临界区，导致在临界区挂起任务，任务会卡在这里出不来
				xSemaphoreTake(CountSemaphore,portMAX_DELAY);
				semavalue=uxSemaphoreGetCount(CountSemaphore); 
				UART_PRINTF("Take后还剩:%d\r\n",semavalue);
//				taskEXIT_CRITICAL();
				vTaskDelay(1500);
		}
}
