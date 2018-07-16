#include "header.h"

#define NOTIFY_COUNT_SEND_TASK_PRIO 2
#define NOTIFY_COUNT_SEND_STK_SIZE  128
TaskHandle_t NOTIFY_COUNT_SEND_Task_Headler;
void NOTIFY_COUNT_SEND_Task(void *para);

#define NOTIFY_COUNT_RECV_TASK_PRIO 3
#define NOTIFY_COUNT_RECV_STK_SIZE  128
TaskHandle_t NOTIFY_COUNT_RECV_Task_Headler;
void NOTIFY_COUNT_RECV_Task(void *para);


void Create_NOTIFY_COUNT_Task(void)
{	
	
		xTaskCreate((TaskFunction_t )NOTIFY_COUNT_SEND_Task,
								(const char*    )"NOTIFY_COUNT_SEND_Task",
								(unsigned char  )NOTIFY_COUNT_SEND_STK_SIZE,
								(void*          )NULL,
								(UBaseType_t    )NOTIFY_COUNT_SEND_TASK_PRIO,
								(TaskHandle_t *  )&NOTIFY_COUNT_SEND_Task_Headler);
								
		xTaskCreate((TaskFunction_t )NOTIFY_COUNT_RECV_Task,
								(const char*    )"NOTIFY_COUNT_RECV_Task",
								(unsigned char  )NOTIFY_COUNT_RECV_STK_SIZE,
								(void*          )NULL,
								(UBaseType_t    )NOTIFY_COUNT_RECV_TASK_PRIO,
								(TaskHandle_t *  )&NOTIFY_COUNT_RECV_Task_Headler);
}


void NOTIFY_COUNT_SEND_Task(void *para)
{
	while(1)
	{
		taskENTER_CRITICAL();
		if(NOTIFY_COUNT_RECV_Task!=NULL)
		xTaskNotifyGive(NOTIFY_COUNT_RECV_Task_Headler);
//		UART_PRINTF("NOTIFY_COUT_SEND_Task OK\r\n");
		taskEXIT_CRITICAL();
		vTaskDelay(50);
	}
		
}



void NOTIFY_COUNT_RECV_Task(void *para)
{
		u32 NotifyValue=0;
		while(1)
		{
				NotifyValue=ulTaskNotifyTake(pdFALSE,portMAX_DELAY);
				UART_PRINTF("NOTIFY_COUNT_RECV: %d\r\n",NotifyValue);
				vTaskDelay(1000);
		}
		
}







