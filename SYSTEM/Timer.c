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
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 4;  
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
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  	
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
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 4;  
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
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 5;  	
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
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 4;  
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
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 5;  	
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  		
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 		
	NVIC_Init(&NVIC_InitStructure);  							

	TIM_Cmd(TIM7, ENABLE);  									
}



void TIM2_IRQHandler(void)
{
	
	if(TIM_GetITStatus(TIM2,TIM_IT_Update)==SET) //����ж�
	{
		UART_PRINTF("TIM2���.......\r\n");
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


void TIM4_IRQHandler(void)
{
	
	if(TIM_GetITStatus(TIM4,TIM_IT_Update)==SET) //����ж�
	{
		UART_PRINTF("TIM4���.......\r\n");
	}
	TIM_ClearITPendingBit(TIM4,TIM_IT_Update);  //����жϱ�־λ
}

void TIM5_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM5,TIM_IT_Update)==SET) //����ж�
	{
		UART_PRINTF("TIM5���.......\r\n");
	}
	TIM_ClearITPendingBit(TIM5,TIM_IT_Update);  //����жϱ�־λ
}
void TIM6_IRQHandler(void)
{
	
	if(TIM_GetITStatus(TIM6,TIM_IT_Update)==SET) //����ж�
	{
		UART_PRINTF("TIM6���.......\r\n");
	}
	TIM_ClearITPendingBit(TIM6,TIM_IT_Update);  //����жϱ�־λ
}

void TIM7_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM7,TIM_IT_Update)==SET) //����ж�
	{
		UART_PRINTF("TIM7���.......\r\n");
	}
	TIM_ClearITPendingBit(TIM7,TIM_IT_Update);  //����жϱ�־λ
}

void TIME_INIT(void)
{
//	TIM2_Int_Init();
//	TIM3_Int_Init();
//	TIM4_Int_Init();
//	TIM5_Int_Init();
//	TIM6_Int_Init();
//	TIM7_Int_Init();
}












