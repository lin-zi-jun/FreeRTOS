#include "header.h"

#define NOTIFY_BOX_SEND_TASK_PRIO 2
#define NOTIFY_BOX_SEND_STK_SIZE  128
TaskHandle_t NOTIFY_BOX_SEND_Task_Headler;
void NOTIFY_BOX_SEND_Task(void *para);

#define NOTIFY_BOX_RECV_TASK_PRIO 3
#define NOTIFY_BOX_RECV_STK_SIZE  128
TaskHandle_t NOTIFY_BOX_RECV_Task_Headler;
void NOTIFY_BOX_RECV_Task(void *para);

#define EVENTBIT_1 1
#define EVENTBIT_2 50
#define EVENTBIT_3 100


void Create_NOTIFY_Post_Box_Task(void)
{	
	
		xTaskCreate((TaskFunction_t )NOTIFY_BOX_SEND_Task,
								(const char*    )"NOTIFY_BOX_SEND_Task",
								(unsigned char  )NOTIFY_BOX_SEND_STK_SIZE,
								(void*          )NULL,
								(UBaseType_t    )NOTIFY_BOX_SEND_TASK_PRIO,
								(TaskHandle_t *  )&NOTIFY_BOX_SEND_Task_Headler);
								
		xTaskCreate((TaskFunction_t )NOTIFY_BOX_RECV_Task,
								(const char*    )"NOTIFY_BOX_RECV_Task",
								(unsigned char  )NOTIFY_BOX_RECV_STK_SIZE,
								(void*          )NULL,
								(UBaseType_t    )NOTIFY_BOX_RECV_TASK_PRIO,
								(TaskHandle_t *  )&NOTIFY_BOX_RECV_Task_Headler);
}


void NOTIFY_BOX_SEND_Task(void *para)
{
	while(1)
	{
		xTaskNotify((TaskHandle_t  )NOTIFY_BOX_RECV_Task_Headler,
								(uint32_t      )EVENTBIT_1,
								(eNotifyAction )eSetValueWithOverwrite);
		vTaskDelay(1000);
		
				xTaskNotify((TaskHandle_t  )NOTIFY_BOX_RECV_Task_Headler,
								(uint32_t      )EVENTBIT_2,
								(eNotifyAction )eSetValueWithOverwrite);
		vTaskDelay(1000);
		
				xTaskNotify((TaskHandle_t  )NOTIFY_BOX_RECV_Task_Headler,
								(uint32_t      )EVENTBIT_3,
								(eNotifyAction )eSetValueWithOverwrite);
		vTaskDelay(1000);
	}
		
}



void NOTIFY_BOX_RECV_Task(void *para)
{
		u32 NotifyValue=0;
		BaseType_t err=pdFAIL;
		while(1)
		{
				
				err=xTaskNotifyWait((u32   			)0X00,					
														(u32      	)ULONG_MAX,				
														(u32*  			)&NotifyValue,		
														(TickType_t	)portMAX_DELAY);
				if(err==pdPASS)
				{
						UART_PRINTF("NotifyValue:%d\r\n",NotifyValue);
				}
		}
		
}







