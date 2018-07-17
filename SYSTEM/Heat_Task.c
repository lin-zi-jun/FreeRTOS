#include "header.h"
#define Heat_Task_PRIO 2
#define Heat_STK_SIZE 128
TaskHandle_t Heat_Task_Handler;
void Heat_Tast(void *para);

void CreateHeatTask(void)
{
			

			xTaskCreate((TaskFunction_t )Heat_Tast,
								(const char*    )"Heat_Tast",
								(unsigned char  )Heat_STK_SIZE,
								(void*          )NULL,
								(UBaseType_t    )Heat_Task_PRIO,
								(TaskHandle_t *  )&Heat_Task_Handler);
}


void Heat_Tast(void *para)
{
		static u8 HTime=0;
		u32 FreeMem=0;
		while(1)
		{
			 taskENTER_CRITICAL();
				HTime++;
				FreeMem=xPortGetFreeHeapSize();
				UART_PRINTF("$MCU:%d,%d\r\n",HTime,FreeMem);
			 taskEXIT_CRITICAL();
			delay_xms(1000);
			 
		}

}
