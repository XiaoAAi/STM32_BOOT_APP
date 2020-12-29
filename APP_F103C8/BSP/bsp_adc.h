#ifndef _BSP_ADC_H
#define _BSP_ADC_H


#include "bsp_common.h"

//extern void GPIO_Configuration_ADC(void);
//extern void Set_ADC_Init(void);

//extern int Smoke;									//—ÃŒÌ≈®∂»
//extern int Set_smoke;								//…Ë÷√—ÃŒÌ≈®∂»
//void ADC1_config(void);

void  Adc_Init(void);
u16 Get_Adc(u8 ch);
u16 GetAdcValue(u8 ch);

#endif
