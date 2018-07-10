#include "header.h"

#define BIN_SEND_TASK_PRIO 2
#define BIN_SEND_STK_SIZE  128
TaskHandle_t BIN_SEND_Task_Headler;
void BIN_SEND_Task(void *para);

#define BIN_RECV_TASK_PRIO 3
#define BIN_RECV_STK_SIZE  128
TaskHandle_t BIN_RECV_Task_Headler;
void BIN_RECV_Task(void *para);

SemaphoreHandle_t BinarySemaphore;

void Create_BIN_Task(void)
{
		BinarySemaphore=xSemaphoreCreateBinary();	
	
		xTaskCreate((TaskFunction_t )BIN_SEND_Task,
								(const char*    )"BIN_SEND_Task",
								(unsigned char  )BIN_SEND_STK_SIZE,
								(void*          )NULL,
								(UBaseType_t    )BIN_SEND_TASK_PRIO,
								(TaskHandle_t *  )&BIN_SEND_Task_Headler);
								
		xTaskCreate((TaskFunction_t )BIN_RECV_Task,
								(const char*    )"BIN_RECV_Task",
								(unsigned char  )BIN_RECV_STK_SIZE,
								(void*          )NULL,
								(UBaseType_t    )BIN_RECV_TASK_PRIO,
								(TaskHandle_t *  )&BIN_RECV_Task_Headler);
}


void BIN_SEND_Task(void *para)
{
	BaseType_t err=pdFALSE;
	
	while(1)
	{
		taskENTER_CRITICAL();
//		if(BinarySemaphore!=NULL)
//		{
//				err=xSemaphoreGive(BinarySemaphore);
//				if(err==pdFALSE)
//				{
//						UART_PRINTF("Send Fail\t");
//				}else
//				{
//						UART_PRINTF("Send OK\t");
////				}
//		}
		
		taskEXIT_CRITICAL();
		delay_xms(1000);
	}
}



void BIN_RECV_Task(void *para)
{
	
		BaseType_t err=pdFALSE;
		while(1)
	{
				err=xSemaphoreTake(BinarySemaphore,portMAX_DELAY);
				if(err==pdFALSE)
				{
						UART_PRINTF("RECV Fail\t");
				}else
				{
						UART_PRINTF("RECV OK\t");
				}
				
				delay_xms(10000);
	}
}







