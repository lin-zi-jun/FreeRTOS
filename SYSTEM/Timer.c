#include "header.h"

/* 
	APB1ʱ�������36M��ָ���Ƿ�Ƶ������ʹ�õ�����£��������Ƶ�ṩ��tim2-tim7ͬ����72M��Ƶ
  �������ʱ�䣺Tout=((arr+1)*(psc+1))/Tclk;
  �����������Ƶ TclkΪ72M����1������72 000 000����Tout=72 000 000/Tclk��Ϊ��ʱ1�롣
*/	

/*
	NVIC���飬STM32ʹ�ø���λ���з��飬��Ϊ�����ȼ��������ȼ���
	���Է�Ϊ5���飨0~4�������ʹ�����ļ�Ϊ��λ�����ȼ�������Ϊ��0~15��
	FreeRTOS�Թ����������Լ����ж϶�
*/


volatile unsigned long long FreeRTOSRunTimeTicks;

void TIM2_Int_Init(void)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); 
	
	TIM_TimeBaseStructure.TIM_Period = 1999;  						//��װ�ؼĴ���
	TIM_TimeBaseStructure.TIM_Prescaler =35999;					//��ʱ��Ԥ��Ƶ 16λ�ɱ��   ��Ƶ����Ϊ������ʱ��
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;		//ʱ��Ԥ��Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; 		
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
 
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE ); 


	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;  
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 7;  
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; 
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);  

	TIM_Cmd(TIM2, ENABLE);   
}


void TIM3_Int_Init(void)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); 
	
	TIM_TimeBaseStructure.TIM_Period = 49; 					
	TIM_TimeBaseStructure.TIM_Prescaler =71; 					
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; 
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); 		
 
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE ); 					

	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  			
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  				//��Ϊ���й���ʱ�������ȼ�������ϵͳ����	
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  		
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 		
	NVIC_Init(&NVIC_InitStructure);  							

	TIM_Cmd(TIM3, ENABLE); 
	
	FreeRTOSRunTimeTicks=0;	
}

void TIM4_Int_Init(void)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); 
	
	TIM_TimeBaseStructure.TIM_Period = 1999;  						//��װ�ؼĴ���
	TIM_TimeBaseStructure.TIM_Prescaler =35999;					//��ʱ��Ԥ��Ƶ 16λ�ɱ��   ��Ƶ����Ϊ������ʱ��
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;		//ʱ��Ԥ��Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; 		
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
 
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE ); 


	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;  
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 7;  
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; 
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);  

	TIM_Cmd(TIM4, ENABLE);   
}


void TIM5_Int_Init(void)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE); 
	
	TIM_TimeBaseStructure.TIM_Period = 1999; 					
	TIM_TimeBaseStructure.TIM_Prescaler =35999; 					
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; 
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure); 		
 
	TIM_ITConfig(TIM5,TIM_IT_Update,ENABLE ); 					

	NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;  			
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 7;  	
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  		
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 		
	NVIC_Init(&NVIC_InitStructure);  							

	TIM_Cmd(TIM5, ENABLE);  									
}

void TIM6_Int_Init(void)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE); 
	
	TIM_TimeBaseStructure.TIM_Period = 1999;  						//��װ�ؼĴ���
	TIM_TimeBaseStructure.TIM_Prescaler =35999;					//��ʱ��Ԥ��Ƶ 16λ�ɱ��   ��Ƶ����Ϊ������ʱ��
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;		//ʱ��Ԥ��Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; 		
	TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStructure);
 
	TIM_ITConfig(TIM6,TIM_IT_Update,ENABLE ); 


	NVIC_InitStructure.NVIC_IRQChannel = TIM6_IRQn;  
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 7;  
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; 
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);  

	TIM_Cmd(TIM6, ENABLE);   
}


void TIM7_Int_Init(void)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE); 
	
	TIM_TimeBaseStructure.TIM_Period = 1999; 					
	TIM_TimeBaseStructure.TIM_Prescaler =35999; 					
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; 
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM7, &TIM_TimeBaseStructure); 		
 
	TIM_ITConfig(TIM7,TIM_IT_Update,ENABLE ); 					

	NVIC_InitStructure.NVIC_IRQChannel = TIM7_IRQn;  			
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 7;  	
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  		
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 		
	NVIC_Init(&NVIC_InitStructure);  							

	TIM_Cmd(TIM7, ENABLE);  									
}


u8 UQRBuf[10]={"���"};
extern QueueHandle_t Message_Queue;
void TIM2_IRQHandler(void)
{
	
		BaseType_t err=errQUEUE_EMPTY;
		BaseType_t xHigherPriorityTaskWoken=pdFALSE;
	if(TIM_GetITStatus(TIM2,TIM_IT_Update)==SET) //����ж�
	{
			if(Message_Queue!=NULL){
						err=xQueueSendFromISR(Message_Queue,UQRBuf,&xHigherPriorityTaskWoken);
						if(err==errQUEUE_FULL) UART_PRINTF("��������\r\r");
						UART_PRINTF("Time2���ͣ�%s\r\n",UQRBuf);
//						memset(UQRBuf,0,10);
						portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
			}
	}
	
	TIM_ClearITPendingBit(TIM2,TIM_IT_Update);  //����жϱ�־λ
}


void TIM3_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)==SET) //����ж�
	{
		FreeRTOSRunTimeTicks++;
	}
	TIM_ClearITPendingBit(TIM3,TIM_IT_Update);  //����жϱ�־λ
}

extern SemaphoreHandle_t BinarySemaphore;
extern TaskHandle_t NOTIFY_BIN_RECV_Task_Headler;
void TIM4_IRQHandler(void)
{
	BaseType_t err=pdFALSE;
	BaseType_t pxHigherPriorityTaskWoken;
	if(TIM_GetITStatus(TIM4,TIM_IT_Update)==SET) //����ж�
	{
		if(BinarySemaphore!=NULL)
		{
				err=xSemaphoreGiveFromISR(BinarySemaphore,&pxHigherPriorityTaskWoken);
				if(err==pdFALSE)
				{
						UART_PRINTF("Send Fail\t");
				}else
				{
						UART_PRINTF("Send OK\t");
				}
				portYIELD_FROM_ISR(pxHigherPriorityTaskWoken);
		}
		
		
		if(NOTIFY_BIN_RECV_Task_Headler!=NULL)
		{
				vTaskNotifyGiveFromISR(NOTIFY_BIN_RECV_Task_Headler,&pxHigherPriorityTaskWoken);
				portYIELD_FROM_ISR(pxHigherPriorityTaskWoken);
		}
		

	}
	
	
	
	TIM_ClearITPendingBit(TIM4,TIM_IT_Update);  //����жϱ�־λ
}

extern SemaphoreHandle_t CountSemaphore;
void TIM5_IRQHandler(void)
{
//				BaseType_t err=pdFALSE;
//			 BaseType_t pxHigherPriorityTaskWoken;
//			u8 semavalue=0;
	if(TIM_GetITStatus(TIM5,TIM_IT_Update)==SET) //����ж�
	{
//			err=xSemaphoreGiveFromISR(CountSemaphore,&pxHigherPriorityTaskWoken);
//			if(err==pdFALSE)
//			UART_PRINTF("��ʱ�����ź�������\t");
	}
//	portYIELD_FROM_ISR(pxHigherPriorityTaskWoken);
	TIM_ClearITPendingBit(TIM5,TIM_IT_Update);  //����жϱ�־λ
}
void TIM6_IRQHandler(void)
{
	
	if(TIM_GetITStatus(TIM6,TIM_IT_Update)==SET) //����ж�
	{
//		UART_PRINTF("TIM6���.......\r\n");
	}
	TIM_ClearITPendingBit(TIM6,TIM_IT_Update);  //����жϱ�־λ
}

void TIM7_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM7,TIM_IT_Update)==SET) //����ж�
	{
//		UART_PRINTF("TIM7���.......\r\n");
	}
	TIM_ClearITPendingBit(TIM7,TIM_IT_Update);  //����жϱ�־λ
}

void TIME_INIT(void)
{
	TIM2_Int_Init();
	TIM3_Int_Init();
	TIM4_Int_Init();
	TIM5_Int_Init();
	TIM6_Int_Init();
	TIM7_Int_Init();
}













