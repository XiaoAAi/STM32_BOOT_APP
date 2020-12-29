#ifndef _BSP_USART_H
#define _BSP_USART_H
#include "stm32f10x_conf.h"

//串口接收队列缓存长度
#define USART_BUFFER_LEN    		4000
#define AT_BUFFER_LEN    				1000

//红外对射--对射升级HEX版本定义DUISHE_SYS_UPDATE宏，其他版本没有定义
#ifndef DUISHE_SYS_UPDATE
#define SYS_ENABLE_IAP      0
#else
#define SYS_ENABLE_IAP      1
#endif


//定义配置使能
#define USART1_CONFIG_ENABLED                (1)
#define USART2_CONFIG_ENABLED                (1)
#define USART3_CONFIG_ENABLED                (0)



//定义串口波特率
#define USART1_BAUDRATE                       115200
#define USART2_BAUDRATE                       115200
#define USART3_BAUDRATE                       9600


//串口功能定义
//升级指令
#define  USART_SERVER_BUTTOM_WillUpdate					0x01AD	//将要升级
#define  USART_SERVER_BUTTOM_WillUpdateFeedBack			0x01BD	//将要升级回馈
#define  USART_SERVER_BUTTOM_StartUpdate				0x01AE	//开始升级
#define  USART_SERVER_BUTTOM_StartUpdateFeedBack		0x01BE	//开始升级回馈
#define  USART_SERVER_BUTTOM_StopUpdate					0x01AF	//停止升级
#define  USART_SERVER_BUTTOM_StopUpdateFeedBack			0x01BF	//停止升级回馈

//重启指令
#define  USART_SERVER_BUTTOM_ResetButtom				0x010E	//重启底层板子及回馈


//芯片端指令
#define  USART_BUTTOM_SERVER_LightFeedback			0x0103	//接收开灯反馈
#define  USART_BUTTOM_SERVER_LockFeedback				0x0104	//接收锁指令状态反馈DATA[0]0xAA:表示开锁状态 0xBB：表示关锁状态
#define  USART_BUTTOM_SERVER_FanFeedback				0x0156	//接收风扇指令反馈
#define  USART_BUTTOM_SERVER_SendHumidity				0x0108	//发送湿度给服务器DATA[0]高位DATA[1]低位
#define  USART_BUTTOM_SERVER_SendTemperature		0x0109	//发送温度给服务器DATA[0]高位DATA[1]低位
#define  USART_BUTTOM_SERVER_SendCameraImage		0x010A	//发送摄像头数据
#define  USART_BUTTOM_SERVER_SendHeartbeat			0x010B	//发送心跳包
#define  USART_BUTTOM_SERVER_Oledshowback				0x0107	//返回接收到OLED 屏幕显示指令
#define  USART_BUTTOM_SERVER_Date								0x0100	//获取时间指令

//服务端指令
#define  USART_SERVER_BUTTOM_OpenLight					0x0101	//开灯指令
#define  USART_SERVER_BUTTOM_OffLight						0x0102	//关灯指令
#define  USART_SERVER_BUTTOM_OpenLock						0x0104	//开锁指令
#define  USART_SERVER_BUTTOM_OpenFan						0x0105	//开风扇指令
#define  USART_SERVER_BUTTOM_DownFan						0x0106	//关风扇指令
#define  USART_SERVER_BUTTOM_LCDShow						0x0107	//oled显示接收数据指令
#define  USART_SERVER_BUTTOM_Getdate						0x0100	//获取到时间 

//IAP系统升级
#define UPDATE_FLAG_FLASH_ADDR              0x800BB80    //写入升级标志地址
#define UPDATE_FLAG_FLASH_DATA             0xDDCCBBAA   //写入升级标志值
#define UPDATE_FLAG_FLASH_DATA1            0x3210ABCD   //写入升级标志值



//函数接口
void USART_SendByte(USART_TypeDef* USARTx, uint8_t byte);
void USART_SendBytes(USART_TypeDef* USARTx, uint8_t *str, uint8_t len);
void USART_SendBytess(USART_TypeDef* USARTx, char *str);
u8 USART_BufferRead(u8 *data);
void USART_BufferWrite(u8 ntemp);
void IAP_Write_UpdateFLAG(void);
void IAP_Reset_UpdateFLAG(void);
u8 IAP_Read_UpdateFLAG(void);
void HandleDatCmd(u16 cmd, u8* dat, u16 datLen);
void SendCmd(USART_TypeDef* USARTx, u16 cmd);								//发送不带数据区的数据包
void SendCmdDat(USART_TypeDef* USARTx, u16 cmd, char *dat, u16 dat_len);	//发送带数据区的数据包
void USART_DEBUG(char *str);	//打印到PC端    调试

#endif  //_BSP_USART_H


