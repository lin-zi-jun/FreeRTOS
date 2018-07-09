#include "header.h"

//����ListTask
#define ListTask_PRIO 2
#define ListSTK_SIZE 128
TaskHandle_t ListTask_Handler;
void ListTast(void *para);

List_t TestList;			//�������б�
ListItem_t ListItem1;	//�������б���1
ListItem_t ListItem2;	//�������б���2
ListItem_t ListItem3;	//�������б���3

static StackType_t IdleTaskStack[configMINIMAL_STACK_SIZE];
static StaticTask_t IdleTaskTCB;

static StackType_t TimerTaskStack[configTIMER_TASK_STACK_DEPTH];
static StaticTask_t TimerTaskTCB;
///********************************************************/
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

void CreateListTask(void)
{
				taskENTER_CRITICAL();
				xTaskCreate((TaskFunction_t )ListTast,
										(const char*    )"ListTast",
										(unsigned char  )ListSTK_SIZE,
										(void*          )NULL,
										(UBaseType_t    )ListTask_PRIO,
										(TaskHandle_t *  )&ListTask_Handler);	
								
		taskEXIT_CRITICAL();										
}


void ListTast(void *para)
{
		//��һ������ʼ���б���б���
		vListInitialise(&TestList);
		vListInitialiseItem(&ListItem1);
		vListInitialiseItem(&ListItem2);
		vListInitialiseItem(&ListItem3);
		
		ListItem1.xItemValue=40;			//ListItem1�б���ֵΪ40
		ListItem2.xItemValue=60;			//ListItem2�б���ֵΪ60
		ListItem3.xItemValue=50;			//ListItem3�б���ֵΪ50
	
		while(1){
						
				  	taskENTER_CRITICAL();
					
					UART_PRINTF("---------------------�б���б����ַ---------------------\r\n");
					UART_PRINTF("��Ŀ                              ��ַ				  \r\n");
					UART_PRINTF("TestList                          %#x					\r\n",(int)&TestList);
					UART_PRINTF("TestList->pxIndex                 %#x					\r\n",(int)&TestList.pxIndex);
					UART_PRINTF("TestList->xListEnd                %#x					\r\n",(int)(&TestList.xListEnd));
					UART_PRINTF("ListItem1                         %#x					\r\n",(int)&ListItem1);
					UART_PRINTF("ListItem2                         %#x					\r\n",(int)&ListItem2);
					UART_PRINTF("ListItem3                         %#x					\r\n",(int)&ListItem3);
					UART_PRINTF("-------------------------------1-------------------------------\r\n\r\n");


					vListInsert(&TestList,&ListItem1);		//�����б���ListItem1
					UART_PRINTF("---------------------����б���ListItem1---------------------\r\n");
					UART_PRINTF("��Ŀ                              ��ַ				    \r\n");
					UART_PRINTF("TestList->xListEnd->pxNext        %#x					\r\n",(int)(TestList.xListEnd.pxNext));
					UART_PRINTF("ListItem1->pxNext                 %#x					\r\n",(int)(ListItem1.pxNext));
					UART_PRINTF("---------------------ǰ�������ӷָ���---------------------\r\n");
					UART_PRINTF("TestList->xListEnd->pxPrevious    %#x					\r\n",(int)(TestList.xListEnd.pxPrevious));
					UART_PRINTF("ListItem1->pxPrevious             %#x					\r\n",(int)(ListItem1.pxPrevious));
					UART_PRINTF("-------------------------------2-------------------------------\r\n\r\n");



						vListInsert(&TestList,&ListItem2);	//�����б���ListItem2
						UART_PRINTF("---------------------����б���ListItem2---------------------\r\n");
						UART_PRINTF("��Ŀ                              ��ַ				    \r\n");
						UART_PRINTF("TestList->xListEnd->pxNext        %#x					\r\n",(int)(TestList.xListEnd.pxNext));
						UART_PRINTF("ListItem1->pxNext                 %#x					\r\n",(int)(ListItem1.pxNext));
						UART_PRINTF("ListItem2->pxNext                 %#x					\r\n",(int)(ListItem2.pxNext));
						UART_PRINTF("---------------------ǰ�������ӷָ���---------------------\r\n");
						UART_PRINTF("TestList->xListEnd->pxPrevious    %#x					\r\n",(int)(TestList.xListEnd.pxPrevious));
						UART_PRINTF("ListItem1->pxPrevious             %#x					\r\n",(int)(ListItem1.pxPrevious));
						UART_PRINTF("ListItem2->pxPrevious             %#x					\r\n",(int)(ListItem2.pxPrevious));
						UART_PRINTF("-------------------------------3-------------------------------\r\n\r\n");


						vListInsert(&TestList,&ListItem3);	//�����б���ListItem3
						UART_PRINTF("---------------------����б���ListItem3---------------------\r\n");
						UART_PRINTF("��Ŀ                              ��ַ				    \r\n");
						UART_PRINTF("TestList->xListEnd->pxNext        %#x					\r\n",(int)(TestList.xListEnd.pxNext));
						UART_PRINTF("ListItem1->pxNext                 %#x					\r\n",(int)(ListItem1.pxNext));
						UART_PRINTF("ListItem3->pxNext                 %#x					\r\n",(int)(ListItem3.pxNext));
						UART_PRINTF("ListItem2->pxNext                 %#x					\r\n",(int)(ListItem2.pxNext));
						UART_PRINTF("---------------------ǰ�������ӷָ���---------------------\r\n");
						UART_PRINTF("TestList->xListEnd->pxPrevious    %#x					\r\n",(int)(TestList.xListEnd.pxPrevious));
						UART_PRINTF("ListItem1->pxPrevious             %#x					\r\n",(int)(ListItem1.pxPrevious));
						UART_PRINTF("ListItem3->pxPrevious             %#x					\r\n",(int)(ListItem3.pxPrevious));
						UART_PRINTF("ListItem2->pxPrevious             %#x					\r\n",(int)(ListItem2.pxPrevious));
						UART_PRINTF("-------------------------------4-------------------------------\r\n\r\n");



						uxListRemove(&ListItem2);						//ɾ��ListItem2
						UART_PRINTF("---------------------ɾ���б���ListItem2---------------------\r\n");
						UART_PRINTF("��Ŀ                              ��ַ				    \r\n");
						UART_PRINTF("TestList->xListEnd->pxNext        %#x					\r\n",(int)(TestList.xListEnd.pxNext));
						UART_PRINTF("ListItem1->pxNext                 %#x					\r\n",(int)(ListItem1.pxNext));
						UART_PRINTF("ListItem3->pxNext                 %#x					\r\n",(int)(ListItem3.pxNext));
						UART_PRINTF("---------------------ǰ�������ӷָ���---------------------\r\n");
						UART_PRINTF("TestList->xListEnd->pxPrevious    %#x					\r\n",(int)(TestList.xListEnd.pxPrevious));
						UART_PRINTF("ListItem1->pxPrevious             %#x					\r\n",(int)(ListItem1.pxPrevious));
						UART_PRINTF("ListItem3->pxPrevious             %#x					\r\n",(int)(ListItem3.pxPrevious));
						UART_PRINTF("-------------------------------5-------------------------------\r\n\r\n");


							TestList.pxIndex=TestList.pxIndex->pxNext;			//pxIndex�����һ�����pxIndex�ͻ�ָ��ListItem1��
							vListInsertEnd(&TestList,&ListItem2);				//�б�ĩβ����б���ListItem2
							UART_PRINTF("---------------------��ĩβ����б���ListItem2---------------------\r\n");
							UART_PRINTF("��Ŀ                              ��ַ				    \r\n");
							UART_PRINTF("TestList->pxIndex                 %#x					\r\n",(int)TestList.pxIndex);
							UART_PRINTF("TestList->xListEnd->pxNext        %#x					\r\n",(int)(TestList.xListEnd.pxNext));
							UART_PRINTF("ListItem2->pxNext                 %#x					\r\n",(int)(ListItem2.pxNext));
							UART_PRINTF("ListItem1->pxNext                 %#x					\r\n",(int)(ListItem1.pxNext));
							UART_PRINTF("ListItem3->pxNext                 %#x					\r\n",(int)(ListItem3.pxNext));
							UART_PRINTF("---------------------ǰ�������ӷָ���---------------------\r\n");
							UART_PRINTF("TestList->xListEnd->pxPrevious    %#x					\r\n",(int)(TestList.xListEnd.pxPrevious));
							UART_PRINTF("ListItem2->pxPrevious             %#x					\r\n",(int)(ListItem2.pxPrevious));
							UART_PRINTF("ListItem1->pxPrevious             %#x					\r\n",(int)(ListItem1.pxPrevious));
							UART_PRINTF("ListItem3->pxPrevious             %#x					\r\n",(int)(ListItem3.pxPrevious));
							UART_PRINTF("-------------------------------6-------------------------------\r\n\r\n");	
							taskEXIT_CRITICAL();
							delay_xms(10000);
			}		
}

/*
xTaskCreate();
xTaskCreateStatic();
vTaskDelete();
vTaskSuspend();
vTaskResume();


vListInitialise(�б�);
��ʼ������:
pxList->pxIndex = ( ListItem_t * ) &( pxList->xListEnd );		//��ǰ����ָ���б�����һ��
pxList->xListEnd.xItemValue = portMAX_DELAY;								//�����ֵΪĬ��ֵ
pxList->xListEnd.pxNext = ( ListItem_t * ) &( pxList->xListEnd );			//�������һ�����Լ�
pxList->xListEnd.pxPrevious = ( ListItem_t * ) &( pxList->xListEnd );	//�����ǰһ�����Լ�
pxList->uxNumberOfItems = ( UBaseType_t ) 0U;													//���б�ǰ����Ϊ����

vListInitialiseItem();
pxItem->pvContainer = NULL;

vListInsert();
const TickType_t xValueOfInsertion = pxNewListItem->xItemValue;
listTEST_LIST_INTEGRITY( pxList );
listTEST_LIST_ITEM_INTEGRITY( pxNewListItem );

if( xValueOfInsertion == portMAX_DELAY )
pxIterator = pxList->xListEnd.pxPrevious;

for( pxIterator = ( ListItem_t * ) &( pxList->xListEnd ); 
pxIterator->pxNext->xItemValue <= xValueOfInsertion; 
pxIterator = pxIterator->pxNext ) 

pxNewListItem->pxNext = pxIterator->pxNext;
pxNewListItem->pxNext->pxPrevious = pxNewListItem;
pxNewListItem->pxPrevious = pxIterator;
pxIterator->pxNext = pxNewListItem;
*/	



