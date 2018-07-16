#include "header.h"
//开始任务
#define START_TASK_PRIO 1
#define START_STK_SIZE 128
TaskHandle_t Start_Task_Handler;
void Start_Tast(void *Para);
void CreateDynamicTask(void);
void CreateStaticTask(void);
void CreateListTask(void);
void CreateHeatTask(void);
void CreateQueryTask(void);
void TIME_INIT(void);
void Create_Reversed_Task(void);
void Create_COUNT_Task(void);
void Create_Mutex_Task(void);
void CreateTimerTask(void);
void CreateEventTask(void);
void Create_NOTIFY_BIN_Task(void);
void Create_NOTIFY_COUNT_Task(void);
void Create_NOTIFY_Post_Box_Task(void);
void Create_NOTIFY_Event_Group_Task(void);
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
//    CreateDynamicTask();
//    CreateStaticTask();
//    CreateListTask();
//		Create_Queue_Task();
		CreateQueryTask();
//		Create_BIN_Task();
//		Create_Reversed_Task();
//		Create_COUNT_Task();
//		Create_Mutex_Task();
//		CreateTimerTask();
//		CreateEventTask();
//		Create_NOTIFY_BIN_Task();
//		Create_NOTIFY_COUNT_Task();
//		Create_NOTIFY_Post_Box_Task();
//			Create_NOTIFY_Event_Group_Task();
		CreateHeatTask();
		vTaskDelete(Start_Task_Handler);
		taskEXIT_CRITICAL();
}



















