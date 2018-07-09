#include "header.h"

#define KEYMSG_Q_NUM 1
#define MESSAGE_QNUM 4
QueueHandle_t Key_Queue;
QueueHandle_t Message_Queue;


void check_msg_queue(void)
{
		 u8 *p;
	``u8 msgq_remain_size;	//消息队列剩余大小
    u8 msgq_total_size;     //消息队列总大小
    
    taskENTER_CRITICAL();   //进入临界区
    msgq_remain_size=uxQueueSpacesAvailable(Message_Queue);//得到队列剩余大小
    msgq_total_size=uxQueueMessagesWaiting(Message_Queue)+uxQueueSpacesAvailable(Message_Queue);//得到队列总大小，总大小=使用+剩余的。
		p=pvPortMalloc(20);	//申请内存
		sprintf((char*)p,"Total Size:%d",msgq_total_size);	//显示DATA_Msg消息队列总的大小
		LCD_ShowString(10,150,100,16,16,p);
		sprintf((char*)p,"Remain Size:%d",msgq_remain_size);	//显示DATA_Msg剩余大小
		LCD_ShowString(10,190,100,16,16,p);
		myfree(SRAMIN,p);		//释放内存
    taskEXIT_CRITICAL();    //退出临界区
}