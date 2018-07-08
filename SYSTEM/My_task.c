#include "header.h"

extern TaskHandle_t A_Task_Handler;
extern TaskHandle_t B_Task_Handler;
extern TaskHandle_t C_Task_Handler;
extern TaskHandle_t D_Task_Handler;
extern TaskHandle_t E_Task_Handler;

List_t TestList;		//测试用列表
ListItem_t ListItem1;	//测试用列表项1
ListItem_t ListItem2;	//测试用列表项2
ListItem_t ListItem3;	//测试用列表项3
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


vListInitialise(列表);
初始化解析:
pxList->pxIndex = ( ListItem_t * ) &( pxList->xListEnd );		//当前索引指向列表的最后一项
pxList->xListEnd.xItemValue = portMAX_DELAY;								//该项的值为默认值
pxList->xListEnd.pxNext = ( ListItem_t * ) &( pxList->xListEnd );			//该项的下一项是自己
pxList->xListEnd.pxPrevious = ( ListItem_t * ) &( pxList->xListEnd );	//该项的前一项是自己
pxList->uxNumberOfItems = ( UBaseType_t ) 0U;													//该列表当前的项为零项

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
	
								UART_PRINTF("/*******************列表和列表项地址*******************\r\n");
								UART_PRINTF("项目                              地址				    \r\n");
								UART_PRINTF("TestList                          %#x					\r\n",(int)&TestList);
								UART_PRINTF("TestList->pxIndex                 %#x					\r\n",(int)TestList.pxIndex);
								UART_PRINTF("TestList->xListEnd                %#x					\r\n",(int)(&TestList.xListEnd));
								UART_PRINTF("ListItem1                         %#x					\r\n",(int)&ListItem1);
								UART_PRINTF("ListItem2                         %#x					\r\n",(int)&ListItem2);
								UART_PRINTF("ListItem3                         %#x					\r\n",(int)&ListItem3);
								UART_PRINTF("/************************结束**************************/\r\n");

							break;

							case 10:
								vListInsert(&TestList,&ListItem1);		//插入列表项ListItem1
								UART_PRINTF("/******************添加列表项ListItem1*****************/\r\n");
								UART_PRINTF("项目                              地址				    \r\n");
								UART_PRINTF("TestList->xListEnd->pxNext        %#x					\r\n",(int)(TestList.xListEnd.pxNext));
								UART_PRINTF("ListItem1->pxNext                 %#x					\r\n",(int)(ListItem1.pxNext));
								UART_PRINTF("/*******************前后向连接分割线********************/\r\n");
								UART_PRINTF("TestList->xListEnd->pxPrevious    %#x					\r\n",(int)(TestList.xListEnd.pxPrevious));
								UART_PRINTF("ListItem1->pxPrevious             %#x					\r\n",(int)(ListItem1.pxPrevious));
								UART_PRINTF("/************************结束**************************/\r\n");
		
							break;

							case 15:
	
									vListInsert(&TestList,&ListItem2);	//插入列表项ListItem2
									UART_PRINTF("/******************添加列表项ListItem2*****************/\r\n");
									UART_PRINTF("项目                              地址				    \r\n");
									UART_PRINTF("TestList->xListEnd->pxNext        %#x					\r\n",(int)(TestList.xListEnd.pxNext));
									UART_PRINTF("ListItem1->pxNext                 %#x					\r\n",(int)(ListItem1.pxNext));
									UART_PRINTF("ListItem2->pxNext                 %#x					\r\n",(int)(ListItem2.pxNext));
									UART_PRINTF("/*******************前后向连接分割线********************/\r\n");
									UART_PRINTF("TestList->xListEnd->pxPrevious    %#x					\r\n",(int)(TestList.xListEnd.pxPrevious));
									UART_PRINTF("ListItem1->pxPrevious             %#x					\r\n",(int)(ListItem1.pxPrevious));
									UART_PRINTF("ListItem2->pxPrevious             %#x					\r\n",(int)(ListItem2.pxPrevious));
									UART_PRINTF("/************************结束**************************/\r\n");

							break;

							case 20:
									vListInsert(&TestList,&ListItem3);	//插入列表项ListItem3
									UART_PRINTF("/******************添加列表项ListItem3*****************/\r\n");
									UART_PRINTF("项目                              地址				    \r\n");
									UART_PRINTF("TestList->xListEnd->pxNext        %#x					\r\n",(int)(TestList.xListEnd.pxNext));
									UART_PRINTF("ListItem1->pxNext                 %#x					\r\n",(int)(ListItem1.pxNext));
									UART_PRINTF("ListItem3->pxNext                 %#x					\r\n",(int)(ListItem3.pxNext));
									UART_PRINTF("ListItem2->pxNext                 %#x					\r\n",(int)(ListItem2.pxNext));
									UART_PRINTF("/*******************前后向连接分割线********************/\r\n");
									UART_PRINTF("TestList->xListEnd->pxPrevious    %#x					\r\n",(int)(TestList.xListEnd.pxPrevious));
									UART_PRINTF("ListItem1->pxPrevious             %#x					\r\n",(int)(ListItem1.pxPrevious));
									UART_PRINTF("ListItem3->pxPrevious             %#x					\r\n",(int)(ListItem3.pxPrevious));
									UART_PRINTF("ListItem2->pxPrevious             %#x					\r\n",(int)(ListItem2.pxPrevious));
									UART_PRINTF("/************************结束**************************/\r\n");
		
							break;

							case 25:

									uxListRemove(&ListItem2);						//删除ListItem2
									UART_PRINTF("/******************删除列表项ListItem2*****************/\r\n");
									UART_PRINTF("项目                              地址				    \r\n");
									UART_PRINTF("TestList->xListEnd->pxNext        %#x					\r\n",(int)(TestList.xListEnd.pxNext));
									UART_PRINTF("ListItem1->pxNext                 %#x					\r\n",(int)(ListItem1.pxNext));
									UART_PRINTF("ListItem3->pxNext                 %#x					\r\n",(int)(ListItem3.pxNext));
									UART_PRINTF("/*******************前后向连接分割线********************/\r\n");
									UART_PRINTF("TestList->xListEnd->pxPrevious    %#x					\r\n",(int)(TestList.xListEnd.pxPrevious));
									UART_PRINTF("ListItem1->pxPrevious             %#x					\r\n",(int)(ListItem1.pxPrevious));
									UART_PRINTF("ListItem3->pxPrevious             %#x					\r\n",(int)(ListItem3.pxPrevious));
									UART_PRINTF("/************************结束**************************/\r\n");
		
							break;

							case 30:
										TestList.pxIndex=TestList.pxIndex->pxNext;			//pxIndex向后移一项，这样pxIndex就会指向ListItem1。
										vListInsertEnd(&TestList,&ListItem2);				//列表末尾添加列表项ListItem2
										UART_PRINTF("/***************在末尾添加列表项ListItem2***************/\r\n");
										UART_PRINTF("项目                              地址				    \r\n");
										UART_PRINTF("TestList->pxIndex                 %#x					\r\n",(int)TestList.pxIndex);
										UART_PRINTF("TestList->xListEnd->pxNext        %#x					\r\n",(int)(TestList.xListEnd.pxNext));
										UART_PRINTF("ListItem2->pxNext                 %#x					\r\n",(int)(ListItem2.pxNext));
										UART_PRINTF("ListItem1->pxNext                 %#x					\r\n",(int)(ListItem1.pxNext));
										UART_PRINTF("ListItem3->pxNext                 %#x					\r\n",(int)(ListItem3.pxNext));
										UART_PRINTF("/*******************前后向连接分割线********************/\r\n");
										UART_PRINTF("TestList->xListEnd->pxPrevious    %#x					\r\n",(int)(TestList.xListEnd.pxPrevious));
										UART_PRINTF("ListItem2->pxPrevious             %#x					\r\n",(int)(ListItem2.pxPrevious));
										UART_PRINTF("ListItem1->pxPrevious             %#x					\r\n",(int)(ListItem1.pxPrevious));
										UART_PRINTF("ListItem3->pxPrevious             %#x					\r\n",(int)(ListItem3.pxPrevious));
										UART_PRINTF("/************************结束**************************/\r\n\r\n\r\n");
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

	UART_PRINTF("/**************1.函数uxTaskGetSystemState()的使用***********************************/\r\n");
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

	
	
	UART_PRINTF("/************2.函数vTaskGetInfo()的使用**************/\r\n");
	TaskHandle=xTaskGetHandle("ETast");			//根据任务名获取任务句柄。
	//获取LED0_Task的任务信息
	vTaskGetInfo((TaskHandle_t	)TaskHandle, 		//任务句柄
				 (TaskStatus_t*	)&TaskStatus, 		//任务信息结构体
				 (BaseType_t	)pdTRUE,			//允许统计任务堆栈历史最小剩余大小
			     (eTaskState	)eInvalid);			//函数自己获取任务运行壮态
	//通过串口打印出指定任务的有关信息。
	UART_PRINTF("任务名:                %s\r\n",TaskStatus.pcTaskName);
	UART_PRINTF("任务编号:              %d\r\n",(int)TaskStatus.xTaskNumber);
	UART_PRINTF("任务壮态:              %d\r\n",TaskStatus.eCurrentState);
	UART_PRINTF("任务当前优先级:        %d\r\n",(int)TaskStatus.uxCurrentPriority);
	UART_PRINTF("任务基优先级:          %d\r\n",(int)TaskStatus.uxBasePriority);
	UART_PRINTF("任务堆栈基地址:        %#x\r\n",(int)TaskStatus.pxStackBase);
	UART_PRINTF("任务堆栈历史剩余最小值:%d\r\n",TaskStatus.usStackHighWaterMark);
	UART_PRINTF("/**************************结束***************************/\r\n");


	
	UART_PRINTF("/***********3.函数eTaskGetState()的使用*************/\r\n");
	TaskHandle=xTaskGetHandle("ETast");		//根据任务名获取任务句柄。
	TaskState=eTaskGetState(TaskHandle);			//获取ETast任务的任务壮态					
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
	UART_PRINTF("任务壮态值:%d,对应的壮态为:%s\r\n",TaskState,TaskInfo);
	UART_PRINTF("/**************************结束**************************/\r\n");

	UART_PRINTF("/*************4.函数vTaskList()的使用*************/\r\n");
	vTaskList(InfoBuffer);							//获取所有任务的信息
	UART_PRINTF("%s\r\n",InfoBuffer);					//通过串口打印所有任务的信息
	UART_PRINTF("/**************************结束**************************/\r\n");


}






























