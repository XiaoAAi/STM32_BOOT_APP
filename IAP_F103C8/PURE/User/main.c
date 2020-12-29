#include "stm32f10x.h"
#include "bsp_common.h"

extern u8 UsartBuffer[USART_BUFFER_LEN];  //数据缓冲区
extern u16 UsartWptr;
extern u16 UsartRptr;

extern u8 start_flash_flag;
extern u8 flag_dis_jump;

int main(void)
{
	u8 data = 0;
	u8 cnt = 0;
	u16 nlen = 0;
	u8 ntemp[512] = {0};
	u8 ndat[512] = {0};
	u16 ncrc = 0;
	u16 ncmd = 0;
    __enable_irq();
    GPIO_Configure();
    NVIC_Configure();
    USART_Configure();

    sprintf((char*)ndat, "%s-%s.%s%s\r\n", Prefix, Version_Year, Version_Month, Version_Day);
    USART_SendBytess(USART_PC_DEBUG, (char*)ndat);
    start_flash_flag = None_Flash_Bod;
    //IAP_Reset_UpdateFLAG();

    if(IAP_Read_UpdateFLAG() == 1)
    {
        __disable_irq();
        IAP_JumpToApplication();
    }
    else
    {
        while(1)
        {
            if(USART_BufferRead(&data) != 0)
            {
                if(start_flash_flag == None_Flash_Bod)
                {
					ntemp[((++cnt) % 512)] = data;
					if(ntemp[cnt] == 0xEE && ntemp[cnt - 1] == 0xDD)
					{						
						nlen = MAKEWORD(ntemp[cnt - 5], ntemp[cnt - 4]);
						if(cnt > nlen)
						{
							ncrc = ModBusCRC(&ntemp[cnt - nlen - 5], nlen + 2);

							if(ncrc == MAKEWORD(ntemp[cnt - 3], ntemp[cnt - 2]))
							{
								ncmd = MAKEWORD(ntemp[cnt - nlen - 5], ntemp[cnt - nlen - 4]);		//指令
								memset(ndat, 0, sizeof(ndat));
								memcpy(&ndat[0], &ntemp[cnt - nlen - 3], nlen - 2);				//数据
								//命令及数据处理								
								HandleDatCmd(ncmd, (char *)ndat, nlen - 2);	
								cnt = 0;	//清空计数	
							}							   
						}	
					}
				}
                else if(start_flash_flag == Start_Flash_Bod) // 开始升级对射
                {
                    IAP_Start_Program_Flash(data);
                    //USART_SendByte(USART1, data);
                }
                else if(start_flash_flag == Stop_Flash_Bod) // 结束升级对射
                {
                    if(flag_dis_jump == 0)
                    {
                        flag_dis_jump = 1;
                        start_flash_flag = None_Flash_Bod;
                        //Send_CMD(USART2, 0x03, LBYTE(USARTCMD_DIANJI_DUISHE_StopUpdateDuishe));
                        USART_SendBytess(USART_PC_DEBUG, "StopUpdateButtom\r\n");
                        //for(i = 0; i < 20 * 1024; i = i + 4)
                        //{
                        //memset(strtemp, 0, sizeof(strtemp));
                        //sprintf((char *)strtemp, "%08x ", *(__IO uint32_t*)(FLASH_APP_ADDRESS + i));
                        //USART_SendBytess(USART_PC_DEBUG, (char *)strtemp);
                        //}
                        //IAP_Write_UpdateFLAG();
                        __disable_irq();
						USART_Cmd(USART2, DISABLE);
                        IAP_JumpToApplication();
                    }
                }
            }
        }
    }
}




