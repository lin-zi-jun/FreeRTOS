#include "header.h"

char InfoBuffer[1000];
char RunTimeInfo[400];		//������������ʱ����Ϣ


//����QueryIAP
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
	
//	UART_PRINTF("\r\n----------------------1.����uxTaskGetSystemState()��ʹ��---------------------------------\r\n");
//	ArraySize=uxTaskGetNumberOfTasks();
//	StatusArray=pvPortMalloc(ArraySize*sizeof(TaskStatus_t));
//	
//	if(StatusArray!=NULL)
//	{
//			ArraySize=uxTaskGetSystemState((TaskStatus_t*  )StatusArray,
//																			(UBaseType_t   )ArraySize,
//																			(uint32_t*      )&TotalRunTime);
//		
//			UART_PRINTF("%15s %13s  %10s %10s \r\n","������","�����ȼ�","��ǰ���ȼ�","����˳��");
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
//	UART_PRINTF("\r\n--------------------------2.����vTaskGetInfo()��ʹ��-----------------------------\r\n");
//	TaskHandle=xTaskGetHandle("Query_Tast");		//������������ȡ��������
//	vTaskGetInfo((TaskHandle_t	)TaskHandle, 		//������
//				 (TaskStatus_t*	)&TaskStatus, 				//������Ϣ�ṹ��
//				 (BaseType_t	)pdTRUE,								//����ͳ�������ջ��ʷ��Сʣ���С
//			     (eTaskState	)eInvalid);						//�����Լ���ȡ��������׳̬

//	UART_PRINTF("������:                %s\r\n",TaskStatus.pcTaskName);
//	UART_PRINTF("������:              %d\r\n",(int)TaskStatus.xTaskNumber);
//	UART_PRINTF("����׳̬:              %d\r\n",TaskStatus.eCurrentState);
//	UART_PRINTF("����ǰ���ȼ�:        %d\r\n",(int)TaskStatus.uxCurrentPriority);
//	UART_PRINTF("��������ȼ�:          %d\r\n",(int)TaskStatus.uxBasePriority);
//	UART_PRINTF("�����ջ����ַ:        %#x\r\n",(int)TaskStatus.pxStackBase);
//	UART_PRINTF("�����ջ��ʷʣ����Сֵ:%d\r\n",TaskStatus.usStackHighWaterMark);
//	UART_PRINTF("---------------------------------------2-------------------------------------------------\r\n\r\n");
//	
//	UART_PRINTF("\r\n-----------------------------3.����eTaskGetState()��ʹ��-----------------------------\r\n\r\n");
//	TaskHandle=xTaskGetHandle("Query_Tast");		//������������ȡ��������
//	TaskState=eTaskGetState(TaskHandle);			//��ȡETast���������׳̬			
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
//	UART_PRINTF("����׳ֵ̬:%d,��Ӧ��׳̬Ϊ:%s\r\n",TaskState,TaskInfo);
//	UART_PRINTF("---------------------------------------3-------------------------------------------------\r\n\r\n");

	UART_PRINTF("\r\n-----------------------------4.����vTaskList()��ʹ��-----------------------------\r\n");
	vTaskList(InfoBuffer);										//��ȡ�����������Ϣ
	UART_PRINTF("State: B->����̬(Block)  R->����̬(Ready)  X->ִ��̬() S->����̬(Suspend) D->ɾ��̬(delete)\r\n\r\n");
	
	UART_PRINTF("%s    %10s%10s%8s%6s\r\n\r\n","Name","State","Priorty","Stack","Num");
	UART_PRINTF("%s",InfoBuffer);					
	UART_PRINTF("---------------------------------------4-------------------------------------------------\r\n\r\n");
	
	UART_PRINTF("\r\n-----------------------------5.��vTaskGetRunTimeStats()��ʹ��-----------------------------\r\n\r\n");				
	vTaskGetRunTimeStats(RunTimeInfo);		//��ȡ��������ʱ����Ϣ
	UART_PRINTF("������      ����ʱ��       ������ռ�ٷֱ�\r\n");
	UART_PRINTF("%s\r\n",RunTimeInfo);
	UART_PRINTF("---------------------------------------5-------------------------------------------------\r\n\r\n");
	
	taskEXIT_CRITICAL();
	vTaskDelay(20000); 
	}
	
}




