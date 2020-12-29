#include "bsp_common.h"

unsigned short ModBusCRC(unsigned char *pData, unsigned int siLen)
{
	unsigned short siRet = 0;
	unsigned short u16CRC = 0xFFFF;
	int i = 0;
	int j = 0;	
	if (NULL == pData || siLen <= 0)
	{
		return 0;
	}
	
	for (i = 0; i < siLen; i++)
	{
		u16CRC ^= (unsigned short)(pData[i]);
		for(j = 0; j <= 7; j++)
		{
			if (u16CRC & 0x0001)
			{
				u16CRC = (u16CRC >> 1) ^ 0xA001;
			}
			else
			{
				u16CRC = u16CRC >> 1;  
			}
		}
	}

	siRet = (u16CRC & 0x00FF) << 8; 
	siRet |= u16CRC >> 8;
	
	return siRet;
}


