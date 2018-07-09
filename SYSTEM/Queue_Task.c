#include "header.h"

#define KEYMSG_Q_NUM 1
#define MESSAGE_QNUM 4
QueueHandle_t Key_Queue;
QueueHandle_t Message_Queue;


void check_msg_queue(void)
{
		 u8 *p;
	``u8 msgq_remain_size;	//��Ϣ����ʣ���С
    u8 msgq_total_size;     //��Ϣ�����ܴ�С
    
    taskENTER_CRITICAL();   //�����ٽ���
    msgq_remain_size=uxQueueSpacesAvailable(Message_Queue);//�õ�����ʣ���С
    msgq_total_size=uxQueueMessagesWaiting(Message_Queue)+uxQueueSpacesAvailable(Message_Queue);//�õ������ܴ�С���ܴ�С=ʹ��+ʣ��ġ�
		p=pvPortMalloc(20);	//�����ڴ�
		sprintf((char*)p,"Total Size:%d",msgq_total_size);	//��ʾDATA_Msg��Ϣ�����ܵĴ�С
		LCD_ShowString(10,150,100,16,16,p);
		sprintf((char*)p,"Remain Size:%d",msgq_remain_size);	//��ʾDATA_Msgʣ���С
		LCD_ShowString(10,190,100,16,16,p);
		myfree(SRAMIN,p);		//�ͷ��ڴ�
    taskEXIT_CRITICAL();    //�˳��ٽ���
}