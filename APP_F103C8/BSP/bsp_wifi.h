#ifndef _BSP_WIFI_H
#define _BSP_WIFI_H

#include "stm32f10x_conf.h"




















u8 wifi_start_trans(void);																	//WiFi开启透传模式
u8 wifi_dis_trans(void);																		//终止1WiFi透传模式
u8 esp8266_send_cmd(u16 *cmd,u16 waittime);							//WiFi发送数据函数
u8 send_AT_cmd(char *AT_cmd,char *AT_ack,u16 waittime);			//发送AT指令给ESP8266


#endif

