#include "header.h"

/* 
	APB1时钟最大是36M，指的是分频给外设使用的情况下，如果不分频提供给tim2-tim7同样是72M主频
  计算溢出时间：Tout=((arr+1)*(psc+1))/Tclk;
  比如如果不分频 Tclk为72M，即1秒钟跑72 000 000，则Tout=72 000 000/Tclk即为定时1秒。
*/	

/*
	NVIC分组，STM32使用高四位进行分组，分为主优先级与亚优先级。
	可以分为5个组（0~4），如果使用组四即为四位主优先级，级别为（0~15）
	FreeRTOS自管理属于它自己的中断段
*/


volatile unsigned long long FreeRTOSRunTimeTicks;

void TIM2_Int_Init(void)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); 
	
	TIM_TimeBaseStructure.TIM_Period = 1999;  						//重装载寄存器
	TIM_TimeBaseStructure.TIM_Prescaler =35999;					//定时器预分频 16位可编程   分频后作为计数器时钟
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;		//时钟预分频
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
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  				//作为运行管理时基，优先级需脱离系统管理	
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
	
	TIM_TimeBaseStructure.TIM_Period = 1999;  						//重装载寄存器
	TIM_TimeBaseStructure.TIM_Prescaler =35999;					//定时器预分频 16位可编程   分频后作为计数器时钟
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;		//时钟预分频
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
	
	TIM_TimeBaseStructure.TIM_Period = 1999;  						//重装载寄存器
	TIM_TimeBaseStructure.TIM_Prescaler =35999;					//定时器预分频 16位可编程   分频后作为计数器时钟
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;		//时钟预分频
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


u8 UQRBuf[10]={"你好"};
extern QueueHandle_t Message_Queue;
void TIM2_IRQHandler(void)
{
	
		BaseType_t err=errQUEUE_EMPTY;
		BaseType_t xHigherPriorityTaskWoken=pdFALSE;
	if(TIM_GetITStatus(TIM2,TIM_IT_Update)==SET) //溢出中断
	{
			if(Message_Queue!=NULL){
						err=xQueueSendFromISR(Message_Queue,UQRBuf,&xHigherPriorityTaskWoken);
						if(err==errQUEUE_FULL) UART_PRINTF("队列已满\r\r");
						UART_PRINTF("Time2发送：%s\r\n",UQRBuf);
//						memset(UQRBuf,0,10);
						portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
			}
	}
	
	TIM_ClearITPendingBit(TIM2,TIM_IT_Update);  //清除中断标志位
}


void TIM3_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)==SET) //溢出中断
	{
		FreeRTOSRunTimeTicks++;
	}
	TIM_ClearITPendingBit(TIM3,TIM_IT_Update);  //清除中断标志位
}

extern SemaphoreHandle_t BinarySemaphore;
extern TaskHandle_t NOTIFY_BIN_RECV_Task_Headler;
void TIM4_IRQHandler(void)
{
	BaseType_t err=pdFALSE;
	BaseType_t pxHigherPriorityTaskWoken;
	if(TIM_GetITStatus(TIM4,TIM_IT_Update)==SET) //溢出中断
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
	
	
	
	TIM_ClearITPendingBit(TIM4,TIM_IT_Update);  //清除中断标志位
}

extern SemaphoreHandle_t CountSemaphore;
void TIM5_IRQHandler(void)
{
//				BaseType_t err=pdFALSE;
//			 BaseType_t pxHigherPriorityTaskWoken;
//			u8 semavalue=0;
	if(TIM_GetITStatus(TIM5,TIM_IT_Update)==SET) //溢出中断
	{
//			err=xSemaphoreGiveFromISR(CountSemaphore,&pxHigherPriorityTaskWoken);
//			if(err==pdFALSE)
//			UART_PRINTF("定时器：信号量已满\t");
	}
//	portYIELD_FROM_ISR(pxHigherPriorityTaskWoken);
	TIM_ClearITPendingBit(TIM5,TIM_IT_Update);  //清除中断标志位
}
void TIM6_IRQHandler(void)
{
	
	if(TIM_GetITStatus(TIM6,TIM_IT_Update)==SET) //溢出中断
	{
//		UART_PRINTF("TIM6输出.......\r\n");
	}
	TIM_ClearITPendingBit(TIM6,TIM_IT_Update);  //清除中断标志位
}

void TIM7_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM7,TIM_IT_Update)==SET) //溢出中断
	{
//		UART_PRINTF("TIM7输出.......\r\n");
	}
	TIM_ClearITPendingBit(TIM7,TIM_IT_Update);  //清除中断标志位
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













