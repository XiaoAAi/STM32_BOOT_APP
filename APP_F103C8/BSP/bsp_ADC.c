#include "bsp_adc.h"

//static void RCC_ConfigInitail()
//{
//    ErrorStatus HSEStartUpStatus;
//    FlagStatus Status;

//    //RCC配置
//    RCC_DeInit();//重置
//    RCC_HSEConfig(RCC_HSE_ON);//外部8MHz晶振启动！
//    HSEStartUpStatus = RCC_WaitForHSEStartUp();
//    if(SUCCESS == HSEStartUpStatus)//若启动成功
//    {
//        RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_7);//56MHz PLL输出
//        RCC_PLLCmd(ENABLE);//PLL输出使能
//        while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);//等待PLL输出成功  

//        //设置系统时钟56MHz
//        RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
//        while(0x08 != RCC_GetSYSCLKSource());//等待设置成功       

//        RCC_HCLKConfig(RCC_SYSCLK_Div1);
//        RCC_PCLK2Config(RCC_HCLK_Div1);//PLCK2 56MHz
//        RCC_PCLK1Config(RCC_HCLK_Div2);//PLCK1 28MHz 
//        //使能APB2外设时钟 ADC & GPIOA
//        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_ADC1, ENABLE);
//        RCC_ADCCLKConfig(RCC_PCLK2_Div4);//ADC1时钟频率 14MHz
//    }
//}

//void ADC1_config()
//{
//	ADC_InitTypeDef ADC_InitStructure;
//	GPIO_InitTypeDef GPIO_InitStructure;

//	//GPIO配置
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;//GPIO采用模拟输入
//	GPIO_Init(GPIOA, &GPIO_InitStructure);//对PA0初始化
//	//因为我使用的是ADC1_IN5就是通道0，而这对应STM32C8T6的PA5口
//	//对于其它型号的要具体看芯片手册

//	//ADC配置
//	ADC_DeInit(ADC1);//重置

//	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;//ADC1和ADC2单独工作，互不影响
//	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;//ADC单次采样，即采样一次就停止
//	ADC_InitStructure.ADC_ScanConvMode = DISABLE;   //ADC单通道采样(ENABLE是多通道扫描)
//	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;//软件触发ADC
//	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;//数据右对齐
//	ADC_InitStructure.ADC_NbrOfChannel = 1;//ADC通道转换数目，我们只用一个ADC，那么就是1
//	//对于多通道采集才使这个值 >= 2， 取值范围是1~16

//	ADC_Init(ADC1,&ADC_InitStructure);//初始化
//	ADC_Cmd(ADC1, ENABLE);//使能

//	//ADC校准
//	ADC_ResetCalibration(ADC1);//重置ADC校准器
//	while(ADC_GetResetCalibrationStatus(ADC1));//等待重置结束

//	ADC_StartCalibration(ADC1);//开始校准
//	while(ADC_GetCalibrationStatus(ADC1));//等待校准完成
////ADC_Channel_5是通道，ADC_SampleTime_1Cycles5是设置周期的参数
////周期计算；如下面ADC_SampleTime_1Cycles5就是1.5个周期，所以一共12.5 + 1.5 = 14个周期 
////ADC时钟频率14KHZ / 14 = 1MHz，这样我们就能得到1MHz最大的采样率了
//	ADC_RegularChannelConfig(ADC1, ADC_Channel_5, 1, ADC_SampleTime_1Cycles5);

//}



void  Adc_Init(void)
{
    ADC_InitTypeDef ADC_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_ADC1, ENABLE);       //使能ADC1通道时钟
    RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //设置ADC分频因子6 72M/6=12,ADC最大时间不能超过14M
    //PA1：检测货道电机的电流PA0：检测直流升降电机和门电机的电流
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;       //模拟输入引脚
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    ADC_DeInit(ADC1);  //复位ADC1
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;  //ADC工作模式:ADC1和ADC2工作在独立模式
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;   //模数转换工作在单通道模式
    ADC_InitStructure.ADC_ContinuousConvMode = DISABLE; //模数转换工作在单次转换模式
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None; //转换由软件而不是外部触发启动
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;  //ADC数据右对齐
    ADC_InitStructure.ADC_NbrOfChannel = 2; //顺序进行规则转换的ADC通道的数目
    ADC_Init(ADC1, &ADC_InitStructure); //根据ADC_InitStruct中指定的参数初始化外设ADCx的寄存器
    ADC_Cmd(ADC1, ENABLE);  //使能指定的ADC1
    ADC_ResetCalibration(ADC1); //使能复位校准

    while(ADC_GetResetCalibrationStatus(ADC1));    //等待复位校准结束

    ADC_StartCalibration(ADC1);  //开启AD校准

    while(ADC_GetCalibrationStatus(ADC1));   //等待校准结束
}

/************************************************************************
功能：配置ADC的通道
参数：ch:通道值 0~3
返回值：获得ADC1的值
说明：ADCx由软件触发采样，只采样ADC1对应的通道
*************************************************************************/
u16 Get_Adc(u8 ch)
{
    //设置指定ADC的规则组通道，一个序列，采样时间
    ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_239Cycles5);   //ADC1,ADC通道,采样时间为239.5周期
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);     //使能指定的ADC1的软件转换启动功能

    while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC)); //等待转换结束

    return ADC_GetConversionValue(ADC1);    //返回最近一次ADC1规则组的转换结果
}

u16 GetAdcValue(u8 ch)
{
//    char strtemp[100] = {0};
    u16 adcValue = Get_Adc(ch);
    float temp = 0.0;
    temp = (float)adcValue * (3.3 / 4096);
    adcValue = temp * 1000;
//    memset(strtemp, 0, sizeof(strtemp));
//    sprintf(strtemp, "ADC_value:%u mA\r\n", adcValue);
//    USART_DEBUG(strtemp);
    return adcValue;
}


