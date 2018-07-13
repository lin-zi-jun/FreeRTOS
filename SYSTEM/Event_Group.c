#include "header.h"



#define EVENT_SET_BIT_TASK_PRIO	2
#define EVENT_SET_BIT_STK_SIZE 	256  
TaskHandle_t Event_Set_Bit_Task_Handler;
void Event_Set_Bit_Task(void *Para);

#define EVENT_QUERY_TASK_PRIO	3
#define EVENT_QUERY_STK_SIZE 	256  
TaskHandle_t Event_Query_Task_Handler;
void Event_Query_Task(void *Para);

#define EVENT_WAIT_TASK_PRIO	4
#define EVENT_WAIT_STK_SIZE 	256  
TaskHandle_t Event_Wait_Task_Handler;
void Event_Wait_Task(void *Para);

EventGroupHandle_t EventGroupHandle;
#define EVENTBIT_0	(1<<0)				
#define EVENTBIT_1	(1<<1)
#define EVENTBIT_2	(1<<2)
#define EVENTBIT_ALL	(EVENTBIT_0|EVENTBIT_1|EVENTBIT_2)

void CreateEventTask(void)
{			  
	
			EventGroupHandle = xEventGroupCreate();
	    xTaskCreate((TaskFunction_t )Event_Set_Bit_Task,             
                (const char*    )"Event_Set_Bit_Task",           
                (uint16_t       )EVENT_SET_BIT_STK_SIZE,        
                (void*          )NULL,                  
                (UBaseType_t    )EVENT_SET_BIT_TASK_PRIO,        
                (TaskHandle_t*  )&Event_Set_Bit_Task_Handler);    
								
			xTaskCreate((TaskFunction_t )Event_Query_Task,             
                (const char*    )"Event_Query_Task",           
                (uint16_t       )EVENT_QUERY_STK_SIZE,        
                (void*          )NULL,                  
                (UBaseType_t    )EVENT_QUERY_TASK_PRIO,        
                (TaskHandle_t*  )&Event_Query_Task_Handler);    
								
			xTaskCreate((TaskFunction_t )Event_Wait_Task,             
                (const char*    )"Event_Wait_Task",           
                (uint16_t       )EVENT_WAIT_STK_SIZE,        
                (void*          )NULL,                  
                (UBaseType_t    )EVENT_WAIT_TASK_PRIO,        
                (TaskHandle_t*  )&Event_Wait_Task_Handler); 																				
}


void Event_Set_Bit_Task(void *Para)
{
	EventBits_t uxBits;
	while(1)
	{
			uxBits=xEventGroupSetBits( EventGroupHandle, EVENTBIT_0 );
//			UART_PRINTF("Set_Bit0 :%d\r\n",uxBits);
			vTaskDelay(1000);
			uxBits=xEventGroupSetBits( EventGroupHandle, EVENTBIT_1);
//			UART_PRINTF("Set_Bit1 :%d\r\n",uxBits);
			vTaskDelay(1000);
			uxBits=xEventGroupSetBits( EventGroupHandle, EVENTBIT_2 );
//			UART_PRINTF("Set_Bit2 :%d\r\n",uxBits);
			vTaskDelay(1000);
	}
}

void Event_Query_Task(void *Para)
{
	EventBits_t NewValue,LastValue;
	while(1)
	{
			NewValue=xEventGroupGetBits(EventGroupHandle);
		  UART_PRINTF("Query:%d\r\n",NewValue);
			vTaskDelay(1000);
	}
	
}


void Event_Wait_Task(void *Para)
{
	EventBits_t EventValue;
	while(1)
	{
			
			EventValue=xEventGroupWaitBits((EventGroupHandle_t	)EventGroupHandle,		
										   (EventBits_t			)EVENTBIT_ALL,
										   (BaseType_t			)pdTRUE,				
										   (BaseType_t			)pdTRUE,
								       (TickType_t			)portMAX_DELAY);	
			UART_PRINTF("事件标志组的值:%d\r\n",EventValue);
			vTaskDelay(1000);
	}
	
}


