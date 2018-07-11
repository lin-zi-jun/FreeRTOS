#include "header.h"

TimerHandle_t 	AutoReloadTimer_Handle;			
TimerHandle_t	OneShotTimer_Handle;			

void AutoReloadCallback(TimerHandle_t xTimer); 	
void OneShotCallback(TimerHandle_t xTimer);		


#define TIMERCONTROL_TASK_PRIO	2
#define TIMERCONTROL_STK_SIZE 	256  
TaskHandle_t TimerControlTask_Handler;
void Timerc_Control_Task(void *Para);

void CreateTimerTask(void)
{
	    AutoReloadTimer_Handle=xTimerCreate((const char*		)"AutoReloadTimer",
									    (TickType_t			)1000,
							            (UBaseType_t		)pdTRUE,
							            (void*				)1,
							            (TimerCallbackFunction_t)AutoReloadCallback); 

			OneShotTimer_Handle=xTimerCreate((const char*			)"OneShotTimer",
							         (TickType_t			)2000,
							         (UBaseType_t			)pdFALSE,
							         (void*					)2,
							         (TimerCallbackFunction_t)OneShotCallback); 				  
	
	    xTaskCreate((TaskFunction_t )Timerc_Control_Task,             
                (const char*    )"Timerc_Control_Task",           
                (uint16_t       )TIMERCONTROL_STK_SIZE,        
                (void*          )NULL,                  
                (UBaseType_t    )TIMERCONTROL_TASK_PRIO,        
                (TaskHandle_t*  )&TimerControlTask_Handler);    
								
}

void Timerc_Control_Task(void *Para)
{
	while(1)
		{
				xTimerStart(AutoReloadTimer_Handle,0);	
				UART_PRINTF("������ʱ��1\r\n");
				vTaskDelay(1000);

				xTimerStart(OneShotTimer_Handle,0);		
				UART_PRINTF("������ʱ��2\r\n");
				vTaskDelay(10000);
			
				xTimerStop(AutoReloadTimer_Handle,0); 
				xTimerReset(OneShotTimer_Handle,0); 		
				UART_PRINTF("�رն�ʱ��1�͸�λ2\r\n");
				vTaskDelay(5000);
		}
}


void AutoReloadCallback(TimerHandle_t xTimer)
{
		UART_PRINTF("��ʱ��1Runing\r\n");
}


void OneShotCallback(TimerHandle_t xTimer)	
{
	
	UART_PRINTF("��ʱ��2Runing\r\n");
	
}







