#include "./BSP/Motor/Motor.h"
#include "./BSP/TIMER/gtim.h"
#include "./BSP/ADC/adc.h"

uint16_t adcx_dig;
float adc_phy = 0;

void Motor_Init(void)
{
	  /* 清除 CNF8[1:0] = 0, MODE8[1:0] = 0, 将PA8设置成浮空输入模式, 避免和PA0冲突 */
    GPIOA->CRH &= ~(0X000F);
    
    /* PA0*/
    gtim_timx_pwm_chy_init(500 - 1, 72 - 1);    /* 1Mhz的计数频率,2Khz的PWM. */
	
}

void Motor_Ctrl_Task(void)
{
	uint8_t get_level;
	
	get_level = Motor_LevelCheck();
	
	switch(get_level)
	{
		case Motor_class0: Motor_OutPut(MOTOR_CLASS0);
			
											break;
		case Motor_class1: Motor_OutPut(MOTOR_CLASS1);
		
											break;	
		case Motor_class2: Motor_OutPut(MOTOR_CLASS2);
			
											break;
		case Motor_class3: Motor_OutPut(MOTOR_CLASS3);
			
											break;
		default: Motor_OutPut(MOTOR_OFF);
			
			break;
	}		
		
}

uint8_t Motor_LevelCheck(void)
{
	uint8_t level = 0;
	
	adcx_dig = adc_get_result_average(ADC_ADCX_CHY, 10);    
	adc_phy = (float)adcx_dig * (3.3 / 4096); 
	
	if(adc_phy < 0.03)
	{
		level = Motor_off;
	}
	else if((0.012 > adc_phy)&&(adc_phy > 0.08))
	{
		level = Motor_class0;
	}	
	else if((0.026 > adc_phy)&&(adc_phy > 0.012))
	{
		level = Motor_class1;
	}
	else if((3.1 > adc_phy)&&(adc_phy > 0.026 ))
	{
		level = Motor_class2;
	}	
	else if(adc_phy > 3.1)
	{
		level = Motor_class3;
	}
	
	return level;
}	

void Motor_OutPut(uint32_t output)
{		
		//PA0
		GTIM_TIMX_PWM_CHY_CCRX = output;
}


