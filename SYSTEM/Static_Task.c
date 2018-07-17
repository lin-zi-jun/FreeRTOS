#include "header.h"

/***************����������ɾ��ʵ��(��̬����)*************/
//����C
#define C_Task_PRIO 2
#define C_STK_SIZE 128
StackType_t CStack[C_STK_SIZE];
StaticTask_t C_TCB;
TaskHandle_t C_Task_Handler;
void CTast(void *para);

//����D
#define D_Task_PRIO 2
#define D_STK_SIZE 128
StackType_t DStack[D_STK_SIZE];
StaticTask_t D_TCB;
TaskHandle_t D_Task_Handler;
void DTast(void *para);

//����E
#define E_Task_PRIO 2
#define E_STK_SIZE 128
StackType_t EStack[E_STK_SIZE];
StaticTask_t E_TCB;
TaskHandle_t E_Task_Handler;
void ETast(void *para);




void CreateStaticTask(void)
{
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
}

void CTast(void *para)
{
		static u8 CTimer=0;
		while(1)
		{
				CTimer++;
				taskENTER_CRITICAL();
				UART_PRINTF("��̬��������C:%d\r\n",CTimer);
				taskEXIT_CRITICAL();
				vTaskDelay(10000);	
		}

}

void DTast(void *para)
{
		static u8 DTimer=0;
		while(1)
		{
			 DTimer++;
				taskENTER_CRITICAL();
			 UART_PRINTF("��̬��������D:%d\r\n",DTimer);
				taskEXIT_CRITICAL();
			 vTaskDelay(10000);
		}

}

void ETast(void *para)
{
		static u8 ETimer=0;
		while(1)
		{
			 ETimer++;
				taskENTER_CRITICAL();
			 UART_PRINTF("��̬��������E:%d\r\n",ETimer);
				taskEXIT_CRITICAL();
			 vTaskDelay(10000);
		}

}
