#include "header.h"
UART_FIFO_TYPE UART1_FIFO;
USART1_PRAR U1;
u32 Uart1TxSem ;

void UART_FIFO_WRITE(UART_FIFO_TYPE *p,u8 data){
    
    if(p->UART_FIFO_LEN < UART_FIFO_LEN_MAX)     //没到512   
    {
        
        p->UART_FIFO_BUF[p->UART_FIFO_IN++] = data;  //写进来的数据 
        p->UART_FIFO_LEN++;
        if(p->UART_FIFO_IN >= UART_FIFO_LEN_MAX) p->UART_FIFO_IN = 0; 
    }
}
// 向FIFO缓冲区写入数据
u8 UART_FIFO_READ(UART_FIFO_TYPE *p){
    u8 ch = 0;
	
    if(p->UART_FIFO_LEN>0)    //缓冲区有数据
    {

        ch = p->UART_FIFO_BUF[p->UART_FIFO_OUT++]; 
        p->UART_FIFO_LEN--;
        if(p->UART_FIFO_OUT >= UART_FIFO_LEN_MAX) p->UART_FIFO_OUT = 0;
        
    }
    
	return ch;
}
// 读取FIFO缓冲区里面的数据
void UART_FIFO_CLEAR(UART_FIFO_TYPE *p){
    
    p->UART_FIFO_IN  = 0;
    p->UART_FIFO_OUT = 0;
    p->UART_FIFO_LEN = 0;
}
// 清除缓冲区中的所有数据

void MAIN_USART_DMA_CONFIGURATION(void){
    DMA_InitTypeDef DMA_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
  
    // DMA1 Channel4 (triggered by USART1 Tx event) Config
    DMA_DeInit(DMA1_Channel4);
    DMA_InitStructure.DMA_PeripheralBaseAddr = USART1_DR_Base;
    DMA_InitStructure.DMA_MemoryBaseAddr = (u32)0;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
    DMA_InitStructure.DMA_BufferSize = 0;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
    DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
    DMA_Init(DMA1_Channel4, &DMA_InitStructure);
    
    // Enable DMA1 Channel4 Transfer Complete interrupt
    DMA_ITConfig(DMA1_Channel4, DMA_IT_TC, ENABLE);
    
    // Enable DMA1 channel4 IRQ Channel
    NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel4_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 7;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}
// 主串口的DMA发送初始化
void USART1_INIT(void){
    GPIO_InitTypeDef GPIO_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    USART_InitTypeDef USART_InitStructure;   
   
    UART_FIFO_CLEAR(&UART1_FIFO);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_AFIO|RCC_APB2Periph_GPIOA, ENABLE);
    

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
      
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
		NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 7;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    
    USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
   
		USART_Init(USART1, &USART_InitStructure);
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
    USART_Cmd(USART1, ENABLE);
    MAIN_USART_DMA_CONFIGURATION();
}
// 主串口的硬件管脚配置，串口配置以及初始化

u8 URBuf[20]={0};
u8 Rnum=0;
extern QueueHandle_t Message_Queue;
void USART1_IRQHandler(void){
    u8 ch;
		BaseType_t err=errQUEUE_EMPTY;
		BaseType_t xHigherPriorityTaskWoken=pdFALSE;
    if(((USART1->SR)&(USART_FLAG_RXNE)) != 0)    
    {
        ch = USART1->DR;  
				URBuf[Rnum]=ch;
				Rnum++;
				if(ch=='\n')
				{
						if(Message_Queue!=NULL){
								err=xQueueSendFromISR(Message_Queue,URBuf,&xHigherPriorityTaskWoken);			
								if(err==errQUEUE_FULL) UART_PRINTF("队列已满\r\n");
								UART_PRINTF("USART发送：%s\r\n",URBuf);
								memset(URBuf,0,20);
								Rnum=0;
								portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
						}
				}
       
    }
}
// 主串口的中断处理程序

void DMA1_Channel4_IRQHandler_RUN(void){
    if(DMA_GetITStatus(DMA1_IT_TC4))
    {
        DMA_ClearITPendingBit(DMA1_IT_GL4);
        USART_DMACmd(USART1, USART_DMAReq_Tx, DISABLE);
        DMA_Cmd(DMA1_Channel4, DISABLE);
				Uart1TxSem = 0; 
    }
}
// 主串口的发送DMA中断处理程序

void USART1_DMA_SendNString(u8 *str,u32 n){
    DMA1_Channel4->CNDTR = n;     //数据量：传输数量寄存器
    DMA1_Channel4->CMAR = (u32)str;   //数据起始地址：储存器地址寄存器
    USART_DMACmd(USART1, USART_DMAReq_Tx, ENABLE);    //串口1DMA发送使能
    DMA_Cmd(DMA1_Channel4, ENABLE);   //通道使能
}
//DMA发送
void USART1_Printf(char *fmt,...){
		u32 len;
    va_list ap;
    va_start(ap,fmt);
		while(Uart1TxSem!=0);
    Uart1TxSem = 1;
    len = vsprintf((char *)U1.String,fmt,ap);  
		USART1_DMA_SendNString(U1.String,len);
    va_end(ap);
}
//串口1打印函数

void USART1PCReceiver(void){
    u8 ch;
    while(UART1_FIFO.UART_FIFO_LEN>0)   //UART1缓冲区有数据
    {
        ch = UART_FIFO_READ(&UART1_FIFO);  //读取缓冲UART1_FIFO的数据
        U1.R_BUF[U1.R_BUF_LEN++] = ch;  //存放到UART1_LINE中
		
        if(U1.R_BUF_LEN>(UART_FIFO_LEN_MAX-1))
        {
            U1.R_BUF_LEN = 0;
        }
        else
        {
            if(ch=='\n')  //如果遇到换行
            {
                U1.R_BUF[U1.R_BUF_LEN] = 0;   //用0代替\n
									
                U1.R_BUF_LEN = 0;
            }
        }
    }
}
//串口1接收函数

void UART_PutChar(USART_TypeDef* USARTx, uint8_t Data) {  
    USART_SendData(USARTx, Data);  
    while(USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET){}  
} 
//发送一个字节 

void UART_PutStr (USART_TypeDef* USARTx, uint8_t *str)  {    
    while (0 != *str)    
    {    
        UART_PutChar(USARTx, *str);    
        str++;    
    }    
}
//发送一串字符

void UART_PRINTF(char *fmt,...)
{
    va_list ap;
    va_start(ap,fmt);
    vsprintf((char *)U1.String,fmt,ap);  
		UART_PutStr (USART1, U1.String);
    va_end(ap);
}


//参数化发送

