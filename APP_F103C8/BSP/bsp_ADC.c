#include "bsp_adc.h"

//static void RCC_ConfigInitail()
//{
//    ErrorStatus HSEStartUpStatus;
//    FlagStatus Status;

//    //RCC����
//    RCC_DeInit();//����
//    RCC_HSEConfig(RCC_HSE_ON);//�ⲿ8MHz����������
//    HSEStartUpStatus = RCC_WaitForHSEStartUp();
//    if(SUCCESS == HSEStartUpStatus)//�������ɹ�
//    {
//        RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_7);//56MHz PLL���
//        RCC_PLLCmd(ENABLE);//PLL���ʹ��
//        while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);//�ȴ�PLL����ɹ�  

//        //����ϵͳʱ��56MHz
//        RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
//        while(0x08 != RCC_GetSYSCLKSource());//�ȴ����óɹ�       

//        RCC_HCLKConfig(RCC_SYSCLK_Div1);
//        RCC_PCLK2Config(RCC_HCLK_Div1);//PLCK2 56MHz
//        RCC_PCLK1Config(RCC_HCLK_Div2);//PLCK1 28MHz 
//        //ʹ��APB2����ʱ�� ADC & GPIOA
//        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_ADC1, ENABLE);
//        RCC_ADCCLKConfig(RCC_PCLK2_Div4);//ADC1ʱ��Ƶ�� 14MHz
//    }
//}

//void ADC1_config()
//{
//	ADC_InitTypeDef ADC_InitStructure;
//	GPIO_InitTypeDef GPIO_InitStructure;

//	//GPIO����
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;//GPIO����ģ������
//	GPIO_Init(GPIOA, &GPIO_InitStructure);//��PA0��ʼ��
//	//��Ϊ��ʹ�õ���ADC1_IN5����ͨ��0�������ӦSTM32C8T6��PA5��
//	//���������ͺŵ�Ҫ���忴оƬ�ֲ�

//	//ADC����
//	ADC_DeInit(ADC1);//����

//	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;//ADC1��ADC2��������������Ӱ��
//	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;//ADC���β�����������һ�ξ�ֹͣ
//	ADC_InitStructure.ADC_ScanConvMode = DISABLE;   //ADC��ͨ������(ENABLE�Ƕ�ͨ��ɨ��)
//	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;//�������ADC
//	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;//�����Ҷ���
//	ADC_InitStructure.ADC_NbrOfChannel = 1;//ADCͨ��ת����Ŀ������ֻ��һ��ADC����ô����1
//	//���ڶ�ͨ���ɼ���ʹ���ֵ >= 2�� ȡֵ��Χ��1~16

//	ADC_Init(ADC1,&ADC_InitStructure);//��ʼ��
//	ADC_Cmd(ADC1, ENABLE);//ʹ��

//	//ADCУ׼
//	ADC_ResetCalibration(ADC1);//����ADCУ׼��
//	while(ADC_GetResetCalibrationStatus(ADC1));//�ȴ����ý���

//	ADC_StartCalibration(ADC1);//��ʼУ׼
//	while(ADC_GetCalibrationStatus(ADC1));//�ȴ�У׼���
////ADC_Channel_5��ͨ����ADC_SampleTime_1Cycles5���������ڵĲ���
////���ڼ��㣻������ADC_SampleTime_1Cycles5����1.5�����ڣ�����һ��12.5 + 1.5 = 14������ 
////ADCʱ��Ƶ��14KHZ / 14 = 1MHz���������Ǿ��ܵõ�1MHz���Ĳ�������
//	ADC_RegularChannelConfig(ADC1, ADC_Channel_5, 1, ADC_SampleTime_1Cycles5);

//}



void  Adc_Init(void)
{
    ADC_InitTypeDef ADC_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_ADC1, ENABLE);       //ʹ��ADC1ͨ��ʱ��
    RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //����ADC��Ƶ����6 72M/6=12,ADC���ʱ�䲻�ܳ���14M
    //PA1������������ĵ����PPA0�����ֱ������������ŵ���ĵ���
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;       //ģ����������
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    ADC_DeInit(ADC1);  //��λADC1
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;  //ADC����ģʽ:ADC1��ADC2�����ڶ���ģʽ
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;   //ģ��ת�������ڵ�ͨ��ģʽ
    ADC_InitStructure.ADC_ContinuousConvMode = DISABLE; //ģ��ת�������ڵ���ת��ģʽ
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None; //ת��������������ⲿ��������
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;  //ADC�����Ҷ���
    ADC_InitStructure.ADC_NbrOfChannel = 2; //˳����й���ת����ADCͨ������Ŀ
    ADC_Init(ADC1, &ADC_InitStructure); //����ADC_InitStruct��ָ���Ĳ�����ʼ������ADCx�ļĴ���
    ADC_Cmd(ADC1, ENABLE);  //ʹ��ָ����ADC1
    ADC_ResetCalibration(ADC1); //ʹ�ܸ�λУ׼

    while(ADC_GetResetCalibrationStatus(ADC1));    //�ȴ���λУ׼����

    ADC_StartCalibration(ADC1);  //����ADУ׼

    while(ADC_GetCalibrationStatus(ADC1));   //�ȴ�У׼����
}

/************************************************************************
���ܣ�����ADC��ͨ��
������ch:ͨ��ֵ 0~3
����ֵ�����ADC1��ֵ
˵����ADCx���������������ֻ����ADC1��Ӧ��ͨ��
*************************************************************************/
u16 Get_Adc(u8 ch)
{
    //����ָ��ADC�Ĺ�����ͨ����һ�����У�����ʱ��
    ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_239Cycles5);   //ADC1,ADCͨ��,����ʱ��Ϊ239.5����
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);     //ʹ��ָ����ADC1�����ת����������

    while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC)); //�ȴ�ת������

    return ADC_GetConversionValue(ADC1);    //�������һ��ADC1�������ת�����
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


