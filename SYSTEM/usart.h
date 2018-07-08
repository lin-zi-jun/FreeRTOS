#ifndef __USART_H
#define __USART_H
#include "stdio.h"	
#include "sys.h" 

#define USART1_DR_Base            0x40013804
#define UART_FIFO_LEN_MAX        	1200
	  	
typedef struct _UART_FIFO_TYPE
{
    u32 UART_FIFO_IN;
    u32 UART_FIFO_OUT;
    u32 UART_FIFO_LEN;
	u8  UART_FIFO_BUF[UART_FIFO_LEN_MAX];
    
}UART_FIFO_TYPE;
      	

typedef struct USART1_ARRAY
{
		u8 String[256];
		u16 R_BUF_LEN;
		u8 R_BUF[UART_FIFO_LEN_MAX];
}USART1_PRAR;


void USART1_INIT(void);
void USART1_Printf(char *fmt,...);
void UART_PutStr (USART_TypeDef* USARTx, uint8_t *str);
void UART_PRINTF(char *fmt,...);
#endif


