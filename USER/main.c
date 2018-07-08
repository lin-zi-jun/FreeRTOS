#include "header.h"
//开始任务
#define START_TASK_PRIO 1
#define START_STK_SIZE 128
TaskHandle_t Start_Task_Handler;
void Start_Tast(void *Para);

/******************创建任务与删除实验*******************/
//任务A
#define A_Task_PRIO 1
#define A_STK_SIZE 128
TaskHandle_t A_Task_Handler;
void ATast(void *para);

//任务B
#define B_Task_PRIO 2
#define B_STK_SIZE 128
TaskHandle_t B_Task_Handler;
void BTast(void *para);
/********************************************************/


/***************创建任务与删除实验(静态方法)*************/
//任务C
#define C_Task_PRIO 3
#define C_STK_SIZE 128
StackType_t CStack[C_STK_SIZE];
StaticTask_t C_TCB;
TaskHandle_t C_Task_Handler;
void CTast(void *para);

//任务D
#define D_Task_PRIO 4
#define D_STK_SIZE 128
StackType_t DStack[D_STK_SIZE];
StaticTask_t D_TCB;
TaskHandle_t D_Task_Handler;
void DTast(void *para);

//任务E
#define E_Task_PRIO 5
#define E_STK_SIZE 128
StackType_t EStack[E_STK_SIZE];
StaticTask_t E_TCB;
TaskHandle_t E_Task_Handler;
void ETast(void *para);



static StackType_t IdleTaskStack[configMINIMAL_STACK_SIZE];
static StaticTask_t IdleTaskTCB;

static StackType_t TimerTaskStack[configTIMER_TASK_STACK_DEPTH];
static StaticTask_t TimerTaskTCB;

void vApplicationGetIdleTaskMemory(StaticTask_t **ppxIdleTaskTCBBuffer, 
								   StackType_t **ppxIdleTaskStackBuffer, 
								   uint32_t *pulIdleTaskStackSize)
{
	*ppxIdleTaskTCBBuffer=&IdleTaskTCB;
	*ppxIdleTaskStackBuffer=IdleTaskStack;
	*pulIdleTaskStackSize=configMINIMAL_STACK_SIZE;
}

void vApplicationGetTimerTaskMemory(StaticTask_t **ppxTimerTaskTCBBuffer, 
									StackType_t **ppxTimerTaskStackBuffer, 
									uint32_t *pulTimerTaskStackSize)
{
	*ppxTimerTaskTCBBuffer=&TimerTaskTCB;
	*ppxTimerTaskStackBuffer=TimerTaskStack;
	*pulTimerTaskStackSize=configTIMER_TASK_STACK_DEPTH;
}
/********************************************************/







int main(void)
{
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
		delay_init();
		USART1_INIT();

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

		xTaskCreate((TaskFunction_t )ATast,
								(const char*    )"ATast",
								(unsigned char  )A_STK_SIZE,
								(void*          )NULL,
								(UBaseType_t    )A_Task_PRIO,
								(TaskHandle_t *  )&A_Task_Handler);

			xTaskCreate((TaskFunction_t )BTast,
								(const char*    )"BTast",
								(unsigned char  )B_STK_SIZE,
								(void*          )NULL,
								(UBaseType_t    )B_Task_PRIO,
								(TaskHandle_t *  )&B_Task_Handler);

			C_Task_Handler=xTaskCreateStatic((TaskFunction_t )CTast,
								(const char*    )"CTast",
								(unsigned char  )C_STK_SIZE,
								(void*          )NULL,
								(UBaseType_t    )C_Task_PRIO,
								(StackType_t*		)CStack,
								(StaticTask_t *  )&C_TCB);

			D_Task_Handler=xTaskCreateStatic((TaskFunction_t )DTast,
								(const char*    )"DTast",
								(unsigned char  )D_STK_SIZE,
								(void*          )NULL,
								(UBaseType_t    )D_Task_PRIO,
								(StackType_t*		)DStack,
								(StaticTask_t *  )&D_TCB);

			E_Task_Handler=xTaskCreateStatic((TaskFunction_t )ETast,
								(const char*    )"ETast",
								(unsigned char  )E_STK_SIZE,
								(void*          )NULL,
								(UBaseType_t    )E_Task_PRIO,
								(StackType_t*		)EStack,
								(StaticTask_t *  )&E_TCB);

		vTaskDelete(Start_Task_Handler);
		taskEXIT_CRITICAL();
}



















