#include "header.h"

#define MESSAGE_QNUM 10
#define ITEM_SIZE 20
QueueHandle_t Message_Queue;

#define QUEUE_TASK_PRIO 2
#define QUEUE_STK_SIZE  128
TaskHandle_t Queue_Task_Headler;
void Queue_Task(void *para);

#define RQUEUE_TASK_PRIO 2
#define RQUEUE_STK_SIZE  128
TaskHandle_t RQueue_Task_Headler;
void RQueue_Task(void *para);

void Create_Queue_Task(void)
{
		Message_Queue=xQueueCreate(MESSAGE_QNUM,ITEM_SIZE);
		
		xTaskCreate((TaskFunction_t )Queue_Task,
								(const char*    )"Queue_Task",
								(unsigned char  )QUEUE_STK_SIZE,
								(void*          )NULL,
								(UBaseType_t    )QUEUE_TASK_PRIO,
								(TaskHandle_t *  )&Queue_Task_Headler);
								
								xTaskCreate((TaskFunction_t )RQueue_Task,
								(const char*    )"RQueue_Task",
								(unsigned char  )RQUEUE_STK_SIZE,
								(void*          )NULL,
								(UBaseType_t    )RQUEUE_TASK_PRIO,
								(TaskHandle_t *  )&RQueue_Task_Headler);
}

void Queue_Task(void *para)
{
			while(1)
			{
				taskENTER_CRITICAL();
				check_msg_queue();
				delay_xms(500);
				taskEXIT_CRITICAL();
			}
}

void RQueue_Task(void *para)
{
			BaseType_t err;
			u8 Rbuf[20]={0};
			while(1)
			{
				taskENTER_CRITICAL();
				err=xQueueReceive(Message_Queue,Rbuf,0);
				if(err==pdTRUE)
				UART_PRINTF("接收：%s\r\n",Rbuf);
				else
				UART_PRINTF("队列没有数据\r\n",Rbuf);
				delay_xms(510);
				taskEXIT_CRITICAL();
			}
}


void check_msg_queue(void)
{
		 u8 *p;
		u8 msgq_remain_size;	//消息队列剩余大小
		u8 msgq_total_size;     //消息队列总大小
		BaseType_t err;
    
    taskENTER_CRITICAL();   //进入临界区
    msgq_remain_size=uxQueueSpacesAvailable(Message_Queue);//得到队列剩余大小
    msgq_total_size=uxQueueMessagesWaiting(Message_Queue)+uxQueueSpacesAvailable(Message_Queue);//得到队列总大小，总大小=使用+剩余的。
		p=pvPortMalloc(20);	//申请内存
		sprintf((char*)p,"剩余项:%d/%d\t\t",msgq_remain_size,msgq_total_size);	//显示DATA_Msg消息队列总的大小
		err=xQueueSend(Message_Queue,p,0);
		if(err==errQUEUE_FULL) UART_PRINTF("队列已满\r\r");
		UART_PRINTF("%s\r\r",p);
		vPortFree(p);		//释放内存
    taskEXIT_CRITICAL();    //退出临界区
}

