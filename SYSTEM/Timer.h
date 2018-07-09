#ifdef  _TIMER_H_
#define _TIMER_H_

void TIME_INIT(void);
void TIM3_Int_Init(void);
extern volatile unsigned long long FreeRTOSRunTimeTicks;

#endif


