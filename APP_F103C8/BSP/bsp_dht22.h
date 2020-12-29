#ifndef _BSP_DHT22_H
#define _BSP_DHT22_H

#include "stm32f10x_conf.h"
//


#define 	DHT22_out_high()	PBout(8)=1
#define 	DHT22_out_low()		PBout(8)=0
#define 	DHT22_port_out()	{GPIOB->CRH&=0XFFFFFFF0;GPIOB->CRH|=(u32)3<<0;}	//输出													
#define 	DHT22_port_in()		{GPIOB->CRH&=0XFFFFFFF0;GPIOB->CRH|=(u32)8<<0;}	//输入
#define		DHT22_DQ_IN  								PBin(8)  //数据端口		
//#define		DHT22_port_out()				 	PBout(8)														
//#define 	DHT22_port_in()						PBin(8)								
												
														
			

u8 DHT22_Read_Data(u16 *humi,u16 *temp);	//DHT22读取温度
//函数功能：显示DHT22的温湿度
//参数：Temperature（温度）、Humidity（湿度）
//返回值：无
void oled_DHT22(u16 Humidity,u16 Temperature);


#endif

