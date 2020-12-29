#ifndef _BSP_TIMER_H
#define _BSP_TIMER_H

#include "bsp_common.h"


//定时器中断优先级设置使能位
#define TIM2_CONFIG_ENABLED     (1)
#define TIM3_CONFIG_ENABLED     (1)



void TIM2_Int_Init(u16 arr, u16 psc);
void TIM3_Int_Init(u16 arr, u16 psc);




#endif  //_BSP_TIM_H


