/**
 ****************************************************************************************************
 * @file        main.c
 * @author      正点原子团队(ALIENTEK)
 * @version     V1.0
 * @date        2020-05-31
 * @brief       单通道ADC采集 实验
 * @license     Copyright (c) 2020-2032, 广州市星翼电子科技有限公司
 ****************************************************************************************************
 * @attention
 *
 * 实验平台:正点原子 STM32F103开发板
 * 在线视频:www.yuanzige.com
 * 技术论坛:www.openedv.com
 * 公司网址:www.alientek.com
 * 购买地址:openedv.taobao.com
 *
 ****************************************************************************************************
 */

#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "./USMART/usmart.h"
#include "./BSP/LED/led.h"
#include "./BSP/LCD/lcd.h"
#include "./BSP/ADC/adc.h"
#include "./BSP/KEY/key.h"
#include "cmsis_armcc.h"
#include "./BSP/AHT10/AHT10.h"
#include "./BSP/HC595/HC595.h"

/******************************************************************************************/
/* 引脚 定义 */
/***MOTOR1***************************************************************************************/
#define MOTOR1_OUTPUT_GPIO_PORT               GPIOA
#define MOTOR1_OUTPUT_GPIO_PIN                SYS_GPIO_PIN0
#define MOTOR1_OUTPUT_GPIO_CLK_ENABLE()       do{ RCC->APB2ENR |= 1 << 2; }while(0)   /* PA口时钟使能 */

#define MOTOR1_AIN1_GPIO_PORT                  GPIOA
#define MOTOR1_AIN1_GPIO_PIN                   SYS_GPIO_PIN1
#define MOTOR1_AIN1_GPIO_CLK_ENABLE()          do{ RCC->APB2ENR |= 1 << 2; }while(0)   /* PA口时钟使能 */

#define MOTOR1_AIN2_GPIO_PORT                  GPIOA
#define MOTOR1_AIN2_GPIO_PIN                   SYS_GPIO_PIN2
#define MOTOR1_AIN2_GPIO_CLK_ENABLE()          do{ RCC->APB2ENR |= 1 << 2; }while(0)   /* PA口时钟使能 */

#define MOTOR2_OUTPUT_GPIO_PORT               GPIOA
#define MOTOR2_OUTPUT_GPIO_PIN                SYS_GPIO_PIN5
#define MOTOR2_OUTPUT_GPIO_CLK_ENABLE()       do{ RCC->APB2ENR |= 1 << 2; }while(0)   /* PA口时钟使能 */

#define MOTOR2_AIN1_GPIO_PORT                  GPIOA
#define MOTOR2_AIN1_GPIO_PIN                   SYS_GPIO_PIN3
#define MOTOR2_AIN1_GPIO_CLK_ENABLE()          do{ RCC->APB2ENR |= 1 << 2; }while(0)   /* PA口时钟使能 */

#define MOTOR2_AIN2_GPIO_PORT                  GPIOA
#define MOTOR2_AIN2_GPIO_PIN                   SYS_GPIO_PIN4
#define MOTOR2_AIN2_GPIO_CLK_ENABLE()          do{ RCC->APB2ENR |= 1 << 2; }while(0)   /* PA口时钟使能 */

#define MOTOR_OUTPUT(x)         sys_gpio_pin_set(MOTOR1_OUTPUT_GPIO_PORT, MOTOR1_OUTPUT_GPIO_PIN, x)      /* LED0 */
#define MOTOR_AIN1(x)           sys_gpio_pin_set(MOTOR1_AIN1_GPIO_PORT, MOTOR1_AIN1_GPIO_PIN, x)      /* LED0 */
#define MOTOR_AIN2(x)           sys_gpio_pin_set(MOTOR1_AIN2_GPIO_PORT, MOTOR1_AIN2_GPIO_PIN, x)      /* LED0 */

#define MOTOR2_OUTPUT(x)         sys_gpio_pin_set(MOTOR2_OUTPUT_GPIO_PORT, MOTOR2_OUTPUT_GPIO_PIN, x)      /* LED0 */
#define MOTOR2_AIN1(x)           sys_gpio_pin_set(MOTOR2_AIN1_GPIO_PORT, MOTOR2_AIN1_GPIO_PIN, x)      /* LED0 */
#define MOTOR2_AIN2(x)           sys_gpio_pin_set(MOTOR2_AIN2_GPIO_PORT, MOTOR2_AIN2_GPIO_PIN, x)      /* LED0 */



/******************************************************************************************/

/******************************************************************************************/
/* 引脚 定义 */
/***MOTOR2***************************************************************************************/
// #define MOTOR2_OUTPUT_GPIO_PORT               GPIOC
// #define MOTOR2_OUTPUT_GPIO_PIN                SYS_GPIO_PIN13
// #define MOTOR2_OUTPUT_GPIO_CLK_ENABLE()       do{ RCC->APB2ENR |= 1 << 4; }while(0)   /* PC口时钟使能 */

// #define MOTOR2_AIN1_GPIO_PORT                  GPIOC
// #define MOTOR2_AIN1_GPIO_PIN                   SYS_GPIO_PIN13
// #define MOTOR2_AIN1_GPIO_CLK_ENABLE()          do{ RCC->APB2ENR |= 1 << 4; }while(0)   /* PC口时钟使能 */

// #define MOTOR2_AIN2_GPIO_PORT                  GPIOC
// #define MOTOR2_AIN2_GPIO_PIN                   SYS_GPIO_PIN13
// #define MOTOR2_AIN2_GPIO_CLK_ENABLE()          do{ RCC->APB2ENR |= 1 << 4; }while(0)   /* PC口时钟使能 */

/******************************************************************************************/
void GPIO_Configuration(void);
void TIM3_PWM_Init(uint16_t arr,uint16_t psc);
void Led_Test(void);
void Motor1_Init(void);
void Motot2_GPIOPB4_ConfigurationInit(void);

void Motor_Init(void);
void Motor1_OutPut(uint8_t output);
void Motor1_Dir(uint8_t dir);

void Motor2_OutPut(uint8_t output);
void Motor2_Dir(uint8_t dir);

void Motor1_turnon(void);
void Motor1_turnoff(void);

void Motor2_turnon(uint32_t time);
void Motor2_turnoff(void);

uint16_t adcx;
float temp;
uint8_t key; 
uint8_t Motor_Out;
uint8_t Motor_DIR;
uint8_t Key_Pressed = 0;

void delay(uint64_t mstime)
{
	int i;
	mstime = mstime * 1000;
	for(i=0;i < mstime;i++)//50MS delay
	{
		__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();
	}
}
uint32_t CT_data[2];
volatile int  c1,t1;
volatile int  c1_sum;
volatile int  c1_sum_temp;
volatile int  c1_sum_average;
uint8_t c1_ath_counter;
uint8_t flag;
//数码管编码
uint8_t table[] = 
{0xc0,0xf9,0xa4,0xb0,0x99,
0x92,0x82,0xf8,0x80,0x90,
0xff,0x00,0x90,0x96,0xaf,
0xc0,0x89,0xc7,0x8e,0xc1,0x7f};
//0,1,2,3,4,5,6,7,8,9,全暗，全亮,g,E,r,O,H,L,F,U，小数点，共阳数码管使用
uint8_t Qian_Wei,Bai_Wei,Shi_Wei,Ge_Wei;	//千位、百位、十位和个位
float temp;
uint16_t adcx;

uint16_t led0pwmval = 0;

uint16_t ATH_humidity(void)
{
		while(JH_Read_Cal_Enable()==0)//等到校准输出使能位为1，才读取。
		{
		JH_Init();//如果为0再使能一次
		delay_ms(30);
		}
		//DisableIrq(); //由于是模拟I2C,为读取数据更准确 ，读取之前禁止中断
		JH_Read_CTdata(CT_data);  //读取温度和湿度 ， 可间隔1.5S读一次
		c1 = CT_data[0]*1000/1024/1024;  //计算得到湿度值（放大了10倍,如果c1=523，表示现在湿度为52.3%）
		t1 = CT_data[1] *200*10/1024/1024-500;//计算得到温度值（放大了10倍，如果t1=245，表示现在温度为24.5℃）
		//EnableIrq(); //恢复中断
		
		return c1;
}	
uint32_t ATH_Couter;
uint16_t HC595_couter;
uint32_t HC595_couter_num = 100;
	uint16_t a,b,c,d,e;
int main(void)
{   
	uint8_t ret=0;

	b=0;
	c=0;
  sys_stm32_clock_init(9);    /* 设置时钟, 72Mhz */
	led_init();
  delay_init(72);             /* 延时初始化 */
	HC595_Init();
  adc_init();                 /* 初始化ADC */
	// key_init();
	Motor_Init();
	// JH_Init(); //初始化
	HC595_OE(0);   //拉低启动显示

	/*PWM Init*/
//  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);    //??NVIC????2:2??????,2??????
//  TIM3_PWM_Init(7199,0);  //????PWM??=72000000/900=80Khz
//	

	
	while(1)
	{
		LED0(0);    /* 关闭 LED0 */
		adcx = adc_get_result_average(ADC_ADCX_CHY, 10);    /* ????5????,10???? */
		temp = (float)adcx * (3.3 / 4096); 
/////////////////////////////////////////////////////////////////////////////////////////////////		

		c1_sum_temp = ATH_humidity();
		c1_sum = c1_sum + c1_sum_temp;
		if(c1_ath_counter == 20)
		{
			c1_ath_counter = 0;
			c1_sum_average = c1_sum/21; 
			c1_sum_average = c1_sum_average/10;
			c1_sum = 0;
		}
		else
		{
			c1_ath_counter++;
		}
		if(HC595_couter == HC595_couter_num)
		{		
			HC595_couter = 0;
			
			c = c1_sum_average/10;
			b = c1_sum_average%10;
			Shi_Wei = table[c];
			Ge_Wei = table[b];
			HC595_Display(Shi_Wei,Ge_Wei);	
		}
		HC595_couter ++;

	 }

}

void Motor_Init(void)
{
			MOTOR1_OUTPUT_GPIO_CLK_ENABLE();
			MOTOR1_AIN1_GPIO_CLK_ENABLE();
			MOTOR1_AIN2_GPIO_CLK_ENABLE();

			MOTOR2_OUTPUT_GPIO_CLK_ENABLE();
			MOTOR2_AIN1_GPIO_CLK_ENABLE();
			MOTOR2_AIN2_GPIO_CLK_ENABLE();
	
	    sys_gpio_set(MOTOR1_OUTPUT_GPIO_PORT, MOTOR1_OUTPUT_GPIO_PIN,
                 SYS_GPIO_MODE_OUT, SYS_GPIO_OTYPE_PP, SYS_GPIO_SPEED_MID, SYS_GPIO_PUPD_PD);   /* Motor1 OUTPUT引脚模式设置 */
	    sys_gpio_set(MOTOR1_AIN1_GPIO_PORT, MOTOR1_AIN1_GPIO_PIN,
                 SYS_GPIO_MODE_OUT, SYS_GPIO_OTYPE_PP, SYS_GPIO_SPEED_MID, SYS_GPIO_PUPD_PD);   /* Motor1 AN1脚模式设置 */
	    sys_gpio_set(MOTOR1_AIN2_GPIO_PORT, MOTOR1_AIN2_GPIO_PIN,
                 SYS_GPIO_MODE_OUT, SYS_GPIO_OTYPE_PP, SYS_GPIO_SPEED_MID, SYS_GPIO_PUPD_PD);   /* Motor1 AN2脚模式设置 */

		sys_gpio_set(MOTOR2_OUTPUT_GPIO_PORT, MOTOR2_OUTPUT_GPIO_PIN,
                 SYS_GPIO_MODE_OUT, SYS_GPIO_OTYPE_PP, SYS_GPIO_SPEED_MID, SYS_GPIO_PUPD_PD);   /* Motor1 OUTPUT引脚模式设置 */
	    sys_gpio_set(MOTOR2_AIN1_GPIO_PORT, MOTOR2_AIN1_GPIO_PIN,
                 SYS_GPIO_MODE_OUT, SYS_GPIO_OTYPE_PP, SYS_GPIO_SPEED_MID, SYS_GPIO_PUPD_PD);   /* Motor2 BN1脚模式设置 */
	    sys_gpio_set(MOTOR2_AIN2_GPIO_PORT, MOTOR2_AIN2_GPIO_PIN,
                 SYS_GPIO_MODE_OUT, SYS_GPIO_OTYPE_PP, SYS_GPIO_SPEED_MID, SYS_GPIO_PUPD_PD);   /* Motor2 BN2脚模式设置 */

}

//void TIM3_PWM_Init(uint16_t arr,uint16_t psc)
//{
//  GPIO_InitTypeDef  GPIO_InitStructure;
//  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
//  TIM_OCInitTypeDef TIM_OCInitStructure;

//  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);//?????3??
//  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO,ENABLE);//??GPIO?AFIO??????
//  GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3,ENABLE); //???TM3_CH2->PB5


//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;        //LED0-->PB.5 ????
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;      //??????
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;    //IO????50MHz
//  GPIO_Init(GPIOB, &GPIO_InitStructure);           //?????????GPIOB.5


//  TIM_TimeBaseStructure.TIM_Period=arr;
//  TIM_TimeBaseStructure.TIM_Prescaler=psc;
//  TIM_TimeBaseStructure.TIM_ClockDivision=0;
//  TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //
//  TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure); //???TIM3

//  TIM_OCInitStructure.TIM_OCMode =TIM_OCMode_PWM2;
//  TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;
//  TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High;//?????
//  TIM_OC2Init(TIM3,&TIM_OCInitStructure);  //?????TIM3_OC2

//  TIM_OC2PreloadConfig(TIM3,TIM_OCPreload_Enable);
//  TIM_Cmd(TIM3,ENABLE);  //??TIM3
//}




void Motor1_OutPut(uint8_t output)
{
	if(1 == output)
	{
		MOTOR_OUTPUT(1);  //enable motor1
	}
	else
	{
		MOTOR_OUTPUT(0);  //disable motor1
	}
}


void Motor1_Dir(uint8_t dir)
{
	if(1 == dir)
	{
		MOTOR_AIN1(1);  //Forword
		MOTOR_AIN2(0);
	}
	else
	{
		MOTOR_AIN1(0);  //Reversal
		MOTOR_AIN2(1);
	}
}

void Motor2_OutPut(uint8_t output)
{
	if(1 == output)
	{
		MOTOR2_OUTPUT(1);  //enable motor1
	}
	else
	{
		MOTOR2_OUTPUT(0);  //disable motor1
	}
}


void Motor2_Dir(uint8_t dir)
{
	if(1 == dir)
	{
		MOTOR2_AIN1(1);  //Forword
		MOTOR2_AIN2(0);
	}
	else
	{
		MOTOR2_AIN1(0);  //Reversal
		MOTOR2_AIN2(1);
	}
}

void Motor1_turnon(void)
{
	Motor1_Dir(1);		
	Motor1_OutPut(1); 
	delay(80);
	Motor1_OutPut(0);
}

void Motor1_turnoff(void)
{
	Motor1_Dir(0);		
	Motor1_OutPut(1); 
	delay(120);
	Motor1_OutPut(0);
}

void Motor2_turnon(uint32_t time)
{
	Motor2_Dir(1);		
	Motor2_OutPut(1); 
	delay(time);
	Motor2_OutPut(0);
}

void Motor2_turnoff(void)
{
	Motor2_Dir(0);		
	Motor2_OutPut(1); 
	delay(30);
	Motor2_OutPut(0);
}















