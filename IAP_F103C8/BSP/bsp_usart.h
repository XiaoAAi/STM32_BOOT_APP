#ifndef _BSP_USART_H
#define _BSP_USART_H
#include "stm32f10x_conf.h"

/***************************************************/
//串口接收队列缓存长度
#define USART_BUFFER_LEN 4000
/***************************************************/
//定义配置使能
#define USART1_CONFIG_ENABLED                (1)
#define USART2_CONFIG_ENABLED                (1)
#define USART3_CONFIG_ENABLED                (0)


//定义串口波特率
#define USART1_BAUDRATE                       115200
#define USART2_BAUDRATE                       115200
#define USART3_BAUDRATE                       9600

#define USART_PC_DEBUG			USART1
#define USART_WIFI				USART2

/**********************************************************/
#define None_Flash_Bod        0
#define Start_Flash_Bod       1
#define Stop_Flash_Bod        2
/**********************************************************/



//升级指令
#define  USART_SERVER_BUTTOM_WillUpdate					0x01AD	//将要升级
#define  USART_SERVER_BUTTOM_WillUpdateFeedBack			0x01BD	//将要升级回馈
#define  USART_SERVER_BUTTOM_StartUpdate				0x01AE	//开始升级
#define  USART_SERVER_BUTTOM_StartUpdateFeedBack		0x01BE	//开始升级回馈
#define  USART_SERVER_BUTTOM_StopUpdate					0x01AF	//停止升级
#define  USART_SERVER_BUTTOM_StopUpdateFeedBack			0x01BF	//停止升级回馈

//重启指令
#define  USART_SERVER_BUTTOM_ResetButtom				0x010E	//重启底层板子及回馈
/**********************************************************/

#if defined (STM32F10X_MD) || defined (STM32F10X_MD_VL)
#define PAGE_SIZE                         (0x400)    // 1 Kbyte
#define FLASH_SIZE                        (0x20000)  // 128 KBytes
#elif defined STM32F10X_CL
#define PAGE_SIZE                         (0x800)    // 2 Kbytes
#define FLASH_SIZE                        (0x40000)  // 256 KBytes
#elif defined STM32F10X_HD || defined (STM32F10X_HD_VL)
#define PAGE_SIZE                         (0x800)    // 2 Kbytes
#define FLASH_SIZE                        (0x80000)  // 512 KBytes
#elif defined STM32F10X_XL
#define PAGE_SIZE                         (0x800)    // 2 Kbytes
#define FLASH_SIZE                        (0x100000) // 1 MByte
#endif
/**********************************************************/
#define FLASH_IAP_ADDRESS                  0x8000000    //IAP起始地址
#define FLASH_APP_ADDRESS                  0x8002000    //APP起始地址

#define UPDATE_FLAG_FLASH_ADDR             0x800BB80    //写入升级标志地址

#define APP_FLASH_SIZE                     (0xC800)     // APP空间大小,50 KBytes
#define UPDATE_FLAG_FLASH_DATA             0xDDCCBBAA   //写入升级标志值
#define UPDATE_FLAG_FLASH_DATA1            0x3210ABCD   //写入升级标志值
/**********************************************************/
void IAP_Write_UpdateFLAG(void);
u8 IAP_Read_UpdateFLAG(void);
void IAP_Reset_UpdateFLAG(void);
void IAP_Erase_APP_Flash(void);
void IAP_Program_FlashData(u16 data);
void IAP_Start_Program_Flash_Init(void);
void IAP_Start_Program_Flash(u8 data);
void IAP_JumpToApplication(void);
void IAP_JumpToIAP(void);
void USART_SendByte(USART_TypeDef* USARTx, uint8_t byte);
void USART_SendBytes(USART_TypeDef* USARTx, uint8_t *str, uint8_t len);
void USART_SendBytess(USART_TypeDef* USARTx, char *str);
void USART_BufferWrite(u8 ntemp);
u8 USART_BufferRead(u8 *data);
void SendCmd(USART_TypeDef* USARTx, u16 cmd);								//发送不带数据区的数据包
void SendCmdDat(USART_TypeDef* USARTx, u16 cmd, char *dat, u16 dat_len);	//发送带数据区的数据包
void HandleDatCmd(u16 cmd, char* dat, u16 datLen);
/**********************************************************/
#endif  //_BSP_USART_H


