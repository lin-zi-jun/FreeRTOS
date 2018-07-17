#include "header.h"

char InfoBuffer[1000];
char RunTimeInfo[400];		//保存任务运行时间信息


//任务QueryIAP
#define Query_Task_PRIO 2
#define Query_STK_SIZE 128
TaskHandle_t Query_Task_Handler;
void Query_Tast(void *para);
/********************************************************/

void CreateQueryTask(void)
{
			xTaskCreate((TaskFunction_t )Query_Tast,
										(const char*    )"Query_Tast",
										(unsigned char  )Query_STK_SIZE,
										(void*          )NULL,
										(UBaseType_t    )Query_Task_PRIO,
										(TaskHandle_t *  )&Query_Task_Handler);		
}

void  Query_Tast(void *para)
{
	
	u32 TotalRunTime=0;
	UBaseType_t ArraySize,x;
	TaskStatus_t *StatusArray;
	TaskHandle_t TaskHandle;	
	TaskStatus_t TaskStatus;
	eTaskState TaskState;
	char TaskInfo[10]={0};
	memset(RunTimeInfo,0,400);

	while(1){
	taskENTER_CRITICAL();
	
//	UART_PRINTF("\r\n----------------------1.函数uxTaskGetSystemState()的使用---------------------------------\r\n");
//	ArraySize=uxTaskGetNumberOfTasks();
//	StatusArray=pvPortMalloc(ArraySize*sizeof(TaskStatus_t));
//	
//	if(StatusArray!=NULL)
//	{
//			ArraySize=uxTaskGetSystemState((TaskStatus_t*  )StatusArray,
//																			(UBaseType_t   )ArraySize,
//																			(uint32_t*      )&TotalRunTime);
//		
//			UART_PRINTF("%15s %13s  %10s %10s \r\n","任务名","基优先级","当前优先级","建立顺序");
//			for(x=0;x<ArraySize;x++)
//			UART_PRINTF("%15s %10d %10d %10d\r\n",
//			StatusArray[x].pcTaskName,
//			(int)StatusArray[x].uxCurrentPriority,
//			(int)StatusArray[x].uxBasePriority,
//			(int)StatusArray[x].xTaskNumber);
//	}
//	
//	vPortFree(StatusArray);
//	UART_PRINTF("---------------------------------------1-------------------------------------------------\r\n\r\n");

//	
//	
//	UART_PRINTF("\r\n--------------------------2.函数vTaskGetInfo()的使用-----------------------------\r\n");
//	TaskHandle=xTaskGetHandle("Query_Tast");		//根据任务名获取任务句柄。
//	vTaskGetInfo((TaskHandle_t	)TaskHandle, 		//任务句柄
//				 (TaskStatus_t*	)&TaskStatus, 				//任务信息结构体
//				 (BaseType_t	)pdTRUE,								//允许统计任务堆栈历史最小剩余大小
//			     (eTaskState	)eInvalid);						//函数自己获取任务运行壮态

//	UART_PRINTF("任务名:                %s\r\n",TaskStatus.pcTaskName);
//	UART_PRINTF("任务编号:              %d\r\n",(int)TaskStatus.xTaskNumber);
//	UART_PRINTF("任务壮态:              %d\r\n",TaskStatus.eCurrentState);
//	UART_PRINTF("任务当前优先级:        %d\r\n",(int)TaskStatus.uxCurrentPriority);
//	UART_PRINTF("任务基优先级:          %d\r\n",(int)TaskStatus.uxBasePriority);
//	UART_PRINTF("任务堆栈基地址:        %#x\r\n",(int)TaskStatus.pxStackBase);
//	UART_PRINTF("任务堆栈历史剩余最小值:%d\r\n",TaskStatus.usStackHighWaterMark);
//	UART_PRINTF("---------------------------------------2-------------------------------------------------\r\n\r\n");
//	
//	UART_PRINTF("\r\n-----------------------------3.函数eTaskGetState()的使用-----------------------------\r\n\r\n");
//	TaskHandle=xTaskGetHandle("Query_Tast");		//根据任务名获取任务句柄。
//	TaskState=eTaskGetState(TaskHandle);			//获取ETast任务的任务壮态			
//	
//	switch((int)TaskState)
//	{
//		case 0:
//			sprintf(TaskInfo,"Running");
//			break;
//		case 1:
//			sprintf(TaskInfo,"Ready");
//			break;
//		case 2:
//			sprintf(TaskInfo,"Suspend");
//			break;
//		case 3:
//			sprintf(TaskInfo,"Delete");
//			break;
//		case 4:
//			sprintf(TaskInfo,"Invalid");
//			break;
//	}
//	UART_PRINTF("任务壮态值:%d,对应的壮态为:%s\r\n",TaskState,TaskInfo);
//	UART_PRINTF("---------------------------------------3-------------------------------------------------\r\n\r\n");

	UART_PRINTF("\r\n-----------------------------4.函数vTaskList()的使用-----------------------------\r\n");
	vTaskList(InfoBuffer);										//获取所有任务的信息
	UART_PRINTF("State: B->阻塞态(Block)  R->就绪态(Ready)  X->执行态() S->挂起态(Suspend) D->删除态(delete)\r\n\r\n");
	
	UART_PRINTF("%s    %10s%10s%8s%6s\r\n\r\n","Name","State","Priorty","Stack","Num");
	UART_PRINTF("%s",InfoBuffer);					
	UART_PRINTF("---------------------------------------4-------------------------------------------------\r\n\r\n");
	
	UART_PRINTF("\r\n-----------------------------5.函vTaskGetRunTimeStats()的使用-----------------------------\r\n\r\n");				
	vTaskGetRunTimeStats(RunTimeInfo);		//获取任务运行时间信息
	UART_PRINTF("任务名      运行时间       运行所占百分比\r\n");
	UART_PRINTF("%s\r\n",RunTimeInfo);
	UART_PRINTF("---------------------------------------5-------------------------------------------------\r\n\r\n");
	
	taskEXIT_CRITICAL();
	vTaskDelay(20000); 
	}
	
}




