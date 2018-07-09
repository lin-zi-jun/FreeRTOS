#include "header.h"
//开始任务
#define START_TASK_PRIO 1
#define START_STK_SIZE 128
TaskHandle_t Start_Task_Handler;
void Start_Tast(void *Para);
void CreateListTask(void);
void CreateHeatTask(void);
int main(void)
{
		USART1_INIT();
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
		delay_init();
		TIME_INIT();
		xTaskCreate((TaskFunction_t )Start_Tast,
								(const char*    )"Start",
								(unsigned char  )START_STK_SIZE,
								(void*          )NULL,
								(UBaseType_t    )START_TASK_PRIO,
								(TaskHandle_t *  )&Start_Task_Handler);
		vTaskStartScheduler();
 }



void Start_Tast(void *Para)
{
		taskENTER_CRITICAL();

//    CreateListTask();
		CreateQueryTask();
		CreateHeatTask();
		vTaskDelete(Start_Task_Handler);
		taskEXIT_CRITICAL();
}



















