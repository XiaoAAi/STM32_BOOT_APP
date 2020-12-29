#ifndef _BSP_COMMON_H
#define _BSP_COMMON_H
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <stdlib.h>
#include "stm32f10x_conf.h"
#include "stm32f10x.h"
#include <core_cm3.h>

typedef enum
{
    FALSE = 0, TRUE = 1
} bool;

//extern char strtemp[128];

#include "bsp_usart.h"
#include "bsp_gpio.h"
#include "bsp_timer.h"
#include "bsp_delay.h"
#include "bsp_sys.h"
#include "bsp_oled.h"
#include "bsp_wifi.h"
#include "bsp_dht22.h"
#include "bsp_adc.h"

#define HBYTE(a)               ((unsigned char)(((unsigned short)(a) >> 8) & 0xFF))
#define LBYTE(a)               ((unsigned char)((unsigned short)(a)& 0xff))
#define MAKEWORD(bHigh, bLow)   ((unsigned short)((((unsigned short)((unsigned char)(bHigh)))<<8)) | ((unsigned char)(bLow)))



//版本号及前缀
#define   Prefix            "APP_BUTTOM"    //前缀，区分不同机型
#define   Version_Year      "19"       // year
#define   Version_Month     "05"      // month
#define   Version_Day       "08"      // day







//函数定义
unsigned short ModBusCRC(unsigned char *pData, unsigned int siLen);

void HexToStr(u8 *pbDest, u8 *pbSrc, int nLen);		//16进制转字符串



#endif  //_BSP_COMMON_H



