#include "header.h"

extern TaskHandle_t A_Task_Handler;
extern TaskHandle_t B_Task_Handler;
extern TaskHandle_t C_Task_Handler;
extern TaskHandle_t D_Task_Handler;
extern TaskHandle_t E_Task_Handler;

List_t TestList;		//�������б�
ListItem_t ListItem1;	//�������б���1
ListItem_t ListItem2;	//�������б���2
ListItem_t ListItem3;	//�������б���3
char InfoBuffer[1000];
void ListTest(u8 ETimer);
void  Query(void);

void ATast(void *para)
{
	  u8 ATimer=0;
		while(1)
		{
				ATimer++;
				taskENTER_CRITICAL();
				UART_PRINTF("A:%d\r\n",ATimer);
				taskEXIT_CRITICAL();	
				delay_xms(1000);	
		}
}

void BTast(void *para)
{
		static u8 BTimer=0;
		while(1)
		{
			 BTimer++;
			 taskENTER_CRITICAL();
			 UART_PRINTF("B:%d\r\n",BTimer);
			 taskEXIT_CRITICAL();
			 delay_xms(1000);
		}

}
/**************************************************/
void CTast(void *para)
{
		static u8 CTimer=0;
		while(1)
		{
				CTimer++;
				UART_PRINTF("C:%d\r\n",CTimer);
				delay_xms(1000);	
		}

}

void DTast(void *para)
{
		static u8 DTimer=0;
		while(1)
		{
			 DTimer++;
			 UART_PRINTF("D:%d\r\n",DTimer);
			 delay_xms(1000);
		}

}

void ETast(void *para)
{
		static u8 ETimer=0;
		while(1)
		{
			 ETimer++;
			 Query();
			 delay_xms(1000);
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




void ListTest(u8 ETimer)
{
		switch(ETimer)
				{
							case 5:
	
								UART_PRINTF("/*******************�б���б����ַ*******************\r\n");
								UART_PRINTF("��Ŀ                              ��ַ				    \r\n");
								UART_PRINTF("TestList                          %#x					\r\n",(int)&TestList);
								UART_PRINTF("TestList->pxIndex                 %#x					\r\n",(int)TestList.pxIndex);
								UART_PRINTF("TestList->xListEnd                %#x					\r\n",(int)(&TestList.xListEnd));
								UART_PRINTF("ListItem1                         %#x					\r\n",(int)&ListItem1);
								UART_PRINTF("ListItem2                         %#x					\r\n",(int)&ListItem2);
								UART_PRINTF("ListItem3                         %#x					\r\n",(int)&ListItem3);
								UART_PRINTF("/************************����**************************/\r\n");

							break;

							case 10:
								vListInsert(&TestList,&ListItem1);		//�����б���ListItem1
								UART_PRINTF("/******************����б���ListItem1*****************/\r\n");
								UART_PRINTF("��Ŀ                              ��ַ				    \r\n");
								UART_PRINTF("TestList->xListEnd->pxNext        %#x					\r\n",(int)(TestList.xListEnd.pxNext));
								UART_PRINTF("ListItem1->pxNext                 %#x					\r\n",(int)(ListItem1.pxNext));
								UART_PRINTF("/*******************ǰ�������ӷָ���********************/\r\n");
								UART_PRINTF("TestList->xListEnd->pxPrevious    %#x					\r\n",(int)(TestList.xListEnd.pxPrevious));
								UART_PRINTF("ListItem1->pxPrevious             %#x					\r\n",(int)(ListItem1.pxPrevious));
								UART_PRINTF("/************************����**************************/\r\n");
		
							break;

							case 15:
	
									vListInsert(&TestList,&ListItem2);	//�����б���ListItem2
									UART_PRINTF("/******************����б���ListItem2*****************/\r\n");
									UART_PRINTF("��Ŀ                              ��ַ				    \r\n");
									UART_PRINTF("TestList->xListEnd->pxNext        %#x					\r\n",(int)(TestList.xListEnd.pxNext));
									UART_PRINTF("ListItem1->pxNext                 %#x					\r\n",(int)(ListItem1.pxNext));
									UART_PRINTF("ListItem2->pxNext                 %#x					\r\n",(int)(ListItem2.pxNext));
									UART_PRINTF("/*******************ǰ�������ӷָ���********************/\r\n");
									UART_PRINTF("TestList->xListEnd->pxPrevious    %#x					\r\n",(int)(TestList.xListEnd.pxPrevious));
									UART_PRINTF("ListItem1->pxPrevious             %#x					\r\n",(int)(ListItem1.pxPrevious));
									UART_PRINTF("ListItem2->pxPrevious             %#x					\r\n",(int)(ListItem2.pxPrevious));
									UART_PRINTF("/************************����**************************/\r\n");

							break;

							case 20:
									vListInsert(&TestList,&ListItem3);	//�����б���ListItem3
									UART_PRINTF("/******************����б���ListItem3*****************/\r\n");
									UART_PRINTF("��Ŀ                              ��ַ				    \r\n");
									UART_PRINTF("TestList->xListEnd->pxNext        %#x					\r\n",(int)(TestList.xListEnd.pxNext));
									UART_PRINTF("ListItem1->pxNext                 %#x					\r\n",(int)(ListItem1.pxNext));
									UART_PRINTF("ListItem3->pxNext                 %#x					\r\n",(int)(ListItem3.pxNext));
									UART_PRINTF("ListItem2->pxNext                 %#x					\r\n",(int)(ListItem2.pxNext));
									UART_PRINTF("/*******************ǰ�������ӷָ���********************/\r\n");
									UART_PRINTF("TestList->xListEnd->pxPrevious    %#x					\r\n",(int)(TestList.xListEnd.pxPrevious));
									UART_PRINTF("ListItem1->pxPrevious             %#x					\r\n",(int)(ListItem1.pxPrevious));
									UART_PRINTF("ListItem3->pxPrevious             %#x					\r\n",(int)(ListItem3.pxPrevious));
									UART_PRINTF("ListItem2->pxPrevious             %#x					\r\n",(int)(ListItem2.pxPrevious));
									UART_PRINTF("/************************����**************************/\r\n");
		
							break;

							case 25:

									uxListRemove(&ListItem2);						//ɾ��ListItem2
									UART_PRINTF("/******************ɾ���б���ListItem2*****************/\r\n");
									UART_PRINTF("��Ŀ                              ��ַ				    \r\n");
									UART_PRINTF("TestList->xListEnd->pxNext        %#x					\r\n",(int)(TestList.xListEnd.pxNext));
									UART_PRINTF("ListItem1->pxNext                 %#x					\r\n",(int)(ListItem1.pxNext));
									UART_PRINTF("ListItem3->pxNext                 %#x					\r\n",(int)(ListItem3.pxNext));
									UART_PRINTF("/*******************ǰ�������ӷָ���********************/\r\n");
									UART_PRINTF("TestList->xListEnd->pxPrevious    %#x					\r\n",(int)(TestList.xListEnd.pxPrevious));
									UART_PRINTF("ListItem1->pxPrevious             %#x					\r\n",(int)(ListItem1.pxPrevious));
									UART_PRINTF("ListItem3->pxPrevious             %#x					\r\n",(int)(ListItem3.pxPrevious));
									UART_PRINTF("/************************����**************************/\r\n");
		
							break;

							case 30:
										TestList.pxIndex=TestList.pxIndex->pxNext;			//pxIndex�����һ�����pxIndex�ͻ�ָ��ListItem1��
										vListInsertEnd(&TestList,&ListItem2);				//�б�ĩβ����б���ListItem2
										UART_PRINTF("/***************��ĩβ����б���ListItem2***************/\r\n");
										UART_PRINTF("��Ŀ                              ��ַ				    \r\n");
										UART_PRINTF("TestList->pxIndex                 %#x					\r\n",(int)TestList.pxIndex);
										UART_PRINTF("TestList->xListEnd->pxNext        %#x					\r\n",(int)(TestList.xListEnd.pxNext));
										UART_PRINTF("ListItem2->pxNext                 %#x					\r\n",(int)(ListItem2.pxNext));
										UART_PRINTF("ListItem1->pxNext                 %#x					\r\n",(int)(ListItem1.pxNext));
										UART_PRINTF("ListItem3->pxNext                 %#x					\r\n",(int)(ListItem3.pxNext));
										UART_PRINTF("/*******************ǰ�������ӷָ���********************/\r\n");
										UART_PRINTF("TestList->xListEnd->pxPrevious    %#x					\r\n",(int)(TestList.xListEnd.pxPrevious));
										UART_PRINTF("ListItem2->pxPrevious             %#x					\r\n",(int)(ListItem2.pxPrevious));
										UART_PRINTF("ListItem1->pxPrevious             %#x					\r\n",(int)(ListItem1.pxPrevious));
										UART_PRINTF("ListItem3->pxPrevious             %#x					\r\n",(int)(ListItem3.pxPrevious));
										UART_PRINTF("/************************����**************************/\r\n\r\n\r\n");
							break;
	
							default:
							break;

				}
}

void  Query(void)
{
	u32 TotalRunTime=0;
	UBaseType_t ArraySize,x;
	TaskStatus_t *StatusArray;
	TaskHandle_t TaskHandle;	
	TaskStatus_t TaskStatus;
	eTaskState TaskState;
	char TaskInfo[10]={0};

	UART_PRINTF("/**************1.����uxTaskGetSystemState()��ʹ��***********************************/\r\n");
	ArraySize=uxTaskGetNumberOfTasks();
	StatusArray=pvPortMalloc(ArraySize*sizeof(TaskStatus_t));
	if(StatusArray!=NULL)
	{
			ArraySize=uxTaskGetSystemState((TaskStatus_t*  )StatusArray,
																			(UBaseType_t   )ArraySize,
																			(uint32_t*      )&TotalRunTime);
		
			for(x=0;x<ArraySize;x++)
			UART_PRINTF("%s\t\t%d\t\t\t%d\t\t%d\t\t%d\r\n",
			StatusArray[x].pcTaskName,
			(int)StatusArray[x].uxCurrentPriority,
			(int)StatusArray[x].xTaskNumber,
			(int)StatusArray[x].ulRunTimeCounter,
			(int)StatusArray[x].uxBasePriority);
	}
	
	vPortFree(StatusArray);
	UART_PRINTF("/*************************************************************************************\r\n/");

	
	
	UART_PRINTF("/************2.����vTaskGetInfo()��ʹ��**************/\r\n");
	TaskHandle=xTaskGetHandle("ETast");			//������������ȡ��������
	//��ȡLED0_Task��������Ϣ
	vTaskGetInfo((TaskHandle_t	)TaskHandle, 		//������
				 (TaskStatus_t*	)&TaskStatus, 		//������Ϣ�ṹ��
				 (BaseType_t	)pdTRUE,			//����ͳ�������ջ��ʷ��Сʣ���С
			     (eTaskState	)eInvalid);			//�����Լ���ȡ��������׳̬
	//ͨ�����ڴ�ӡ��ָ��������й���Ϣ��
	UART_PRINTF("������:                %s\r\n",TaskStatus.pcTaskName);
	UART_PRINTF("������:              %d\r\n",(int)TaskStatus.xTaskNumber);
	UART_PRINTF("����׳̬:              %d\r\n",TaskStatus.eCurrentState);
	UART_PRINTF("����ǰ���ȼ�:        %d\r\n",(int)TaskStatus.uxCurrentPriority);
	UART_PRINTF("��������ȼ�:          %d\r\n",(int)TaskStatus.uxBasePriority);
	UART_PRINTF("�����ջ����ַ:        %#x\r\n",(int)TaskStatus.pxStackBase);
	UART_PRINTF("�����ջ��ʷʣ����Сֵ:%d\r\n",TaskStatus.usStackHighWaterMark);
	UART_PRINTF("/**************************����***************************/\r\n");


	
	UART_PRINTF("/***********3.����eTaskGetState()��ʹ��*************/\r\n");
	TaskHandle=xTaskGetHandle("ETast");		//������������ȡ��������
	TaskState=eTaskGetState(TaskHandle);			//��ȡETast���������׳̬					
	switch((int)TaskState)
	{
		case 0:
			sprintf(TaskInfo,"Running");
			break;
		case 1:
			sprintf(TaskInfo,"Ready");
			break;
		case 2:
			sprintf(TaskInfo,"Suspend");
			break;
		case 3:
			sprintf(TaskInfo,"Delete");
			break;
		case 4:
			sprintf(TaskInfo,"Invalid");
			break;
	}
	UART_PRINTF("����׳ֵ̬:%d,��Ӧ��׳̬Ϊ:%s\r\n",TaskState,TaskInfo);
	UART_PRINTF("/**************************����**************************/\r\n");

	UART_PRINTF("/*************4.����vTaskList()��ʹ��*************/\r\n");
	vTaskList(InfoBuffer);							//��ȡ�����������Ϣ
	UART_PRINTF("%s\r\n",InfoBuffer);					//ͨ�����ڴ�ӡ�����������Ϣ
	UART_PRINTF("/**************************����**************************/\r\n");


}






























