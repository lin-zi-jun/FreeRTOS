#include "header.h"

#define NOTIFY_BIN_SEND_TASK_PRIO 2
#define NOTIFY_BIN_SEND_STK_SIZE  128
TaskHandle_t NOTIFY_BIN_SEND_Task_Headler;
void NOTIFY_BIN_SEND_Task(void *para);

#define NOTIFY_BIN_RECV_TASK_PRIO 3
#define NOTIFY_BIN_RECV_STK_SIZE  128
TaskHandle_t NOTIFY_BIN_RECV_Task_Headler;
void NOTIFY_BIN_RECV_Task(void *para);


void Create_NOTIFY_BIN_Task(void)
{	
	
		xTaskCreate((TaskFunction_t )NOTIFY_BIN_SEND_Task,
								(const char*    )"NOTIFY_BIN_SEND_Task",
								(unsigned char  )NOTIFY_BIN_SEND_STK_SIZE,
								(void*          )NULL,
								(UBaseType_t    )NOTIFY_BIN_SEND_TASK_PRIO,
								(TaskHandle_t *  )&NOTIFY_BIN_SEND_Task_Headler);
								
		xTaskCreate((TaskFunction_t )NOTIFY_BIN_RECV_Task,
								(const char*    )"NOTIFY_BIN_RECV_Task",
								(unsigned char  )NOTIFY_BIN_RECV_STK_SIZE,
								(void*          )NULL,
								(UBaseType_t    )NOTIFY_BIN_RECV_TASK_PRIO,
								(TaskHandle_t *  )&NOTIFY_BIN_RECV_Task_Headler);
}


void NOTIFY_BIN_SEND_Task(void *para)
{
	BaseType_t err=pdFALSE;
	
	while(1)
	{
//		taskENTER_CRITICAL();
//		xTaskNotifyGive(NOTIFY_BIN_RECV_Task_Headler);
//		UART_PRINTF("NOTIFY_BIN_SEND_Task OK\t");
//		taskEXIT_CRITICAL();
//		vTaskDelay(3000);
	}
		
}



void NOTIFY_BIN_RECV_Task(void *para)
{
	
		BaseType_t err=pdFALSE;
		while(1)
		{
				ulTaskNotifyTake(pdTRUE,portMAX_DELAY);
				UART_PRINTF("NOTIFY_BIN_RECV_Task OK\t");
				vTaskDelay(1000);
		}
		
}







