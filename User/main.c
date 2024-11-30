
#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "./USMART/usmart.h"
#include "./BSP/LED/led.h"
#include "./BSP/LCD/lcd.h"
#include "./BSP/KEY/key.h"
#include "cmsis_armcc.h"
#include "./BSP/AHT10/AHT10.h"
#include "./BSP/HC595/HC595.h"
#include "./BSP/Motor/Motor.h"
#include "./BSP/ADC/adc.h"

/******************************************************************************************/
volatile int  c1_sum;
volatile int  c1_sum_temp;
volatile int  c1_sum_average;

uint8_t key; 
uint8_t Motor_Out;
uint8_t Motor_DIR;
uint8_t Key_Pressed = 0;
uint8_t c1_ath_counter;
uint8_t Qian_Wei,Bai_Wei,Shi_Wei = 0x89,Ge_Wei = 0xf9;	//千位、百位、十位和个位
uint8_t table[] = 
{0xc0,0xf9,0xa4,0xb0,0x99,
0x92,0x82,0xf8,0x80,0x90,
0xff,0x00,0x90,0x96,0xaf,
0xc0,0x89,0xc7,0x8e,0xc1,0x7f};
//0,1,2,3,4,5,6,7,8,9,全暗，全亮,g,E,r,O,H,L,F,U，小数点，共阳数码管使用

uint16_t HC595_couter;
uint16_t b = 0,c = 0;
uint16_t led0pwmval = 0;
uint16_t adc_DisplayMode_dig;

uint32_t ATH_Couter;
uint32_t HC595_couter_num = 25;

float adc_DisplayMode_phy = 0;
/******************************************************************************************/

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

void Humidifier_inforProcess(void)
{

	
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
		}
		HC595_Display(Shi_Wei,Ge_Wei);
		HC595_couter ++;
	 
}

int main(void)
{   
	/*init function*/
  sys_stm32_clock_init(9);    /* 设置时钟, 72Mhz */
	led_init();
  delay_init(72);             /* 延时初始化 */
	HC595_Init();
	adc_init();                 /* 初始化ADC */
	Motor_Init();
	// JH_Init(); //初始化
	
	while(1)
	{
		//get display mode
		adc_DisplayMode_dig = adc_get_result_average(ADC_ADC_DISPLAY_CHY, 10); 
		adc_DisplayMode_phy = (float)adc_DisplayMode_dig * (3.3 / 4096); 
		
		LED0(0);    /* 关闭 LED0 */

		if(adc_DisplayMode_phy > 3.0)
		{
				HC595_Display(0xff,0xff);	
		}
		else
		{		
			/*Nixie tube display */
			Humidifier_inforProcess();
		}

		/*motor ctrl */
		Motor_Ctrl_Task();
		
	}
	
}



