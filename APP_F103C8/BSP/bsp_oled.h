#ifndef _BSP_OLED_H
#define _BSP_OLED_H

#include "stm32f10x.h"

#include "stm32f10x_rcc.h"

#include "stm32f10x_gpio.h"

#include "stm32f10x_conf.h"



#define		OLED_SCL(x)			PBout(12)=x
#define 	OLED_SDA(x)  		PBout(13)=x
#define 	OLED_RST(x)  		PBout(14)=x
#define 	OLED_DC(x)   		PBout(15)=x
#define 	OLED_CS(x)   		PAout(8)=x

void OLED_Init(void);
void OLED_Fill(u8 bmp_data);
void OLED_WrDat(u8 data);
void OLED_Wr6Dat(u8 data);
void OLED_PutPixel(u8 x,u8 y);
void OLED_ClrPixel(u8 x,u8 y);
void OLED_Set_Pos(u8 x, u8 y);
void OLED_HEXACSII(u16 hex,u8* Print);
void OLED_Print_Num1(u8 x, u8 y, s16 num);
void dis_bmp(u16 high, u16 width, u8 *p,u8 value);
void OLED_Print_Num(u8 x, u8 y, u16 num);
void OLED_P8x16Str(u8 x,u8 y,u8 ch[]);
void OLED_P6x8Str(u8 x,u8 y,u8 ch[]);

void RCC_congig(void);					//呼吸灯配置
void Oled_ShowTime(void);								//时间显示在OLED 屏幕上
void Get_date(u8 date[]);				//存储网络时间



#endif

