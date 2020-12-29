#ifndef _BSP_COMMON_H
#define _BSP_COMMON_H
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <stdlib.h>
#include "stm32f10x_conf.h"

#include "user.h"

#if SYSTEM_SUPPORT_UCOS
#include "includes.h"
#endif

#include "bsp_usart.h"
#include "bsp_gpio.h"
#include "bsp_delay.h"

#define   Prefix             "IAP_BUTTOM"    //前缀，区分不同机型
#define   Version_Year       "19"      // year
#define   Version_Month      "02"      // month
#define   Version_Day        "26"      // day

#define HBYTE(a)               ((unsigned char)(((unsigned short)(a) >> 8) & 0xFF))
#define LBYTE(a)               ((unsigned char)((unsigned short)(a)& 0xff))
#define MAKEWORD(bHigh, bLow)   ((unsigned short)((((unsigned short)((unsigned char)(bHigh)))<<8)) | ((unsigned char)(bLow)))


typedef enum
{
    FALSE = 0, TRUE = 1
} bool;



unsigned short ModBusCRC(unsigned char *pData, unsigned int siLen);

void delay_init(void);
void delay_ms(u16 nms);
void delay_us(u32 nus);


#endif  //_BSP_COMMON_H
