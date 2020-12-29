#include<stdio.h>


unsigned short ModBusCRC(unsigned char *pData, unsigned int siLen)
{
	if (NULL == pData || siLen <= 0)
	{
		return 0;
	}
	
	unsigned short u16CRC = 0xFFFF;
	int i = 0;
	int j = 0;
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
 
	unsigned short siRet = 0;
	siRet = (u16CRC & 0x00FF) << 8; 
	siRet |= u16CRC >> 8;
	
	return siRet;
}



unsigned int CRC16 ( unsigned char *arr_buff, unsigned int len)
{

 unsigned int crc=0xFFFF;
 unsigned char i, j, Data;
 for ( j=0; j < len; j++)
 {

   crc=crc ^*arr_buff++;
   for ( i=0; i<8; i++)
  {

       if( ( crc&0x0001) >0)

       {

           crc=crc>>1;

           crc=crc^ 0xa001;

        }
      else

          crc=crc>>1;
   }
 }
return ( crc);

}


int main()
{
	 //查询初始化 温湿度的值，工作状态 ，升温启动值，升温停止值， 降温启动值 ， 降温停止值 ， 
	unsigned char temp1[7] = {0x01, 0x03, 0x00, 0x00, 0x00, 0x02};
	unsigned char temp2[7] = {0x01, 0x03, 0x00, 0x02, 0x00, 0x01};
	unsigned char temp3[7] = {0x01, 0x03, 0x00, 0x03, 0x00, 0x01};
	unsigned char temp4[7] = {0x01, 0x03, 0x00, 0x04, 0x00, 0x01};
	unsigned char temp5[7] = {0x01, 0x03, 0x00, 0x05, 0x00, 0x01};
	unsigned char temp6[7] = {0x01, 0x03, 0x00, 0x06, 0x00, 0x01};
	unsigned char temp7[7] = {0x01, 0x03, 0x00, 0x07, 0x00, 0x01};
	unsigned char temp8[7] = {0x01, 0x03, 0x00, 0x08, 0x00, 0x01};
	unsigned char temp9[7] = {0x01, 0x03, 0x00, 0x09, 0x00, 0x01};
	unsigned char temp10[7] = {0x01, 0x03, 0x00, 0x0A, 0x00, 0x01};
//	unsigned char temp10[7] = {0x01, 0x03, 0x04, 0x00, 0xDC, 0x01, 0xA4};

	//写入   升温启动值 8，升温停止值 11， 降温启动值 15， 降温停止值 12 ， 
	//，加湿启动值35， 加湿停止值 45， 除湿启动值55， 除湿停止值：45 
	unsigned char tep3[8] = {0x01, 0x06, 0x00, 0x03, 0x00, 0x08};
	unsigned char tep4[7] = {0x01, 0x06, 0x00, 0x04, 0x00, 0x0B};
	unsigned char tep5[7] = {0x01, 0x06, 0x00, 0x05, 0x00, 0x0F};
	unsigned char tep6[7] = {0x01, 0x06, 0x00, 0x06, 0x00, 0x0C};
	unsigned char tep7[7] = {0x01, 0x06, 0x00, 0x07, 0x00, 0x23};
	unsigned char tep8[7] = {0x01, 0x06, 0x00, 0x08, 0x00, 0x2D};
	unsigned char tep9[7] = {0x01, 0x06, 0x00, 0x09, 0x00, 0x37};
	unsigned char tep10[7] = {0x01, 0x06, 0x00, 0x0A, 0x00, 0x2D};
	 
	//测试使用
	unsigned char te3[7] = {0x01, 0x06, 0x00, 0x03, 0x00, 0x19};//25 
	unsigned char te4[7] = {0x01, 0x06, 0x00, 0x04, 0x00, 0x1A};//26
	unsigned char te5[7] = {0x01, 0x06, 0x00, 0x05, 0x00, 0x1B};//27
	unsigned char te6[7] = {0x01, 0x06, 0x00, 0x06, 0x00, 0x1A}; //26
	unsigned char te7[7] = {0x01, 0x06, 0x00, 0x07, 0x00, 0x3C};//60
	unsigned char te8[7] = {0x01, 0x06, 0x00, 0x08, 0x00, 0x41};//65 
	unsigned char te9[7] = {0x01, 0x03, 0x04, 0x00, 0xE6, 0x01, 0xE0};//70
	unsigned char te10[7] = {0x01, 0x06, 0x00, 0x03, 0x00, 0x00};	//65 
	//查询 
	unsigned int tp;
	printf("+++===============+++++===查询======++++=========+++++=====+++==\n");
	tp = ModBusCRC(temp1,6);
	printf("output：%X\n",tp);
	tp = ModBusCRC(temp2,6);
	printf("output：%X\n",tp);
	tp = ModBusCRC(temp3,6);
	printf("output：%X\n",tp);
	tp = ModBusCRC(temp4,6);
	printf("output：%X\n",tp);
	tp = ModBusCRC(temp5,6);
	printf("output：%X\n",tp);
	tp = ModBusCRC(temp6,6);
	printf("output：%X\n",tp);
	tp = ModBusCRC(temp7,6);
	printf("output：%X\n",tp);
	tp = ModBusCRC(temp8,6);
	printf("output：%X\n",tp);
	tp = ModBusCRC(temp9,6);
	printf("output：%X\n",tp);
	tp = ModBusCRC(temp10,6);
	printf("output：%X\n",tp);	
//	tp = CRC16(temp,2);
//	printf("output：%X",tp);
	printf("+++===============+++++===写入======++++=========+++++=====+++==\n"); 
	//写入
	tp = ModBusCRC(tep3,6);
	printf("output：%X\n",tp);
	tp = ModBusCRC(tep4,6);
	printf("output：%X\n",tp);
	tp = ModBusCRC(tep5,6);
	printf("output：%X\n",tp);
	tp = ModBusCRC(tep6,6);
	printf("output：%X\n",tp);
	tp = ModBusCRC(tep7,6);
	printf("output：%X\n",tp);
	tp = ModBusCRC(tep8,6);
	printf("output：%X\n",tp);
	tp = ModBusCRC(tep9,6);
	printf("output：%X\n",tp);
	tp = ModBusCRC(tep10,6);
	printf("output：%X\n",tp);		 

	printf("+++===============+++++===测试======++++=========+++++=====+++==\n"); 
	//测试 
	tp = ModBusCRC(te3,6);
	printf("output：%X\n",tp);
	tp = ModBusCRC(te4,6);
	printf("output：%X\n",tp);
	tp = ModBusCRC(te5,6);
	printf("output：%X\n",tp);
	tp = ModBusCRC(te6,6);
	printf("output：%X\n",tp);	
	tp = ModBusCRC(te7,6);
	printf("output：%X\n",tp);
	tp = ModBusCRC(te8,6);
	printf("output：%X\n",tp);
	tp = ModBusCRC(te9,7);
	printf("output：%X\n",tp);
	tp = ModBusCRC(te10,6);	
	printf("output：%X\n",tp);
	return 0;
}
