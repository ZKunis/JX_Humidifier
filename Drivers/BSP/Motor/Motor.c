#include "./BSP/Motor/Motor.h"
#include "./BSP/TIMER/gtim.h"
#include "./BSP/ADC/adc.h"
#include "./BSP/AHT10/AHT10.h"

uint8_t HumidityRangeCheck_Result;
uint8_t Current_mortor_level;
uint16_t Current_Humidity_Value;
uint16_t Last_Humidity_Value;
uint16_t adcx_dig;
uint16_t adc2_dig;
uint16_t adcWater_dig;
float adc_phy = 0;
float adc2_phy = 0;
float adcWater_phy = 0;

void Motor_Init(void)
{
	  /* 清除 CNF8[1:0] = 0, MODE8[1:0] = 0, 将PA8设置成浮空输入模式, 避免和PA0冲突 */
    GPIOA->CRH &= ~(0X000F);
    
    /* PA0*/
    gtim_timx_pwm_chy_init(50000 - 1, 72 - 1);    /* 1Mhz的计数频率,2Khz的PWM. */
	
}

void Motor_Ctrl_Task(void)
{
	uint8_t get_setting;
	
	get_setting = Motor_LevelCheck();
	
	switch(get_setting)
	{
		case Motor_class3: Motor_OutPut(MOTOR_CLASS3);
			
											break;
		case Motor_class2: Motor_OutPut(MOTOR_CLASS2);
		
											break;	
		case Motor_class1: Motor_OutPut(MOTOR_CLASS1);
			
											break;
		case Motor_off: Motor_OutPut(MOTOR_OFF);
				break;
		
			break;
	}		
		
}

uint8_t Motor_HumidityRangeCheck(void)
{
	uint8_t ret = 1;
	uint16_t level = 0;
	
	Current_Humidity_Value = ATH_humidity(); 
	
	//get humidity speed  setting voltage
	adc2_dig = adc_get_result_average(ADC_ADC2_CHY, 10); 
	adc2_phy = (float)adc2_dig * (3.3 / 4096); 
	
	//check  Humidity_level setting 

  if(0.85 >= adc2_phy)
	{
		level = Motor_Humidity_level_60;
	}	
	else if((2.2 >= adc2_phy)&&(adc2_phy > 0.85))
	{
		level = Motor_Humidity_level_70;
	}
	else if(adc2_phy > 2.2)
	{
		level = Motor_Humidity_level_80;
	}
	//current humidiy < setting humidity level ,output motor
	if((Current_Humidity_Value < level)&&(HumidityRangeCheck_Result == 1))
	{
		 HumidityRangeCheck_Result = 0;
		 ret = 1;  //enable motor output;
	}	
	else if(Current_Humidity_Value >=  level)  //if current humidiy == setting humidity level 
	{
		if(Current_Humidity_Value < (level-50))
		{
			HumidityRangeCheck_Result = 1;
			ret = 1;  //enable motor output;
			return ret;
		}
		
		ret = 0;  //stop motor output;
	}
	
	
	return ret;
}	

uint8_t Motor_WaterLevelCheck(void)
{
	uint8_t ret = 0;
	//get water level  setting voltage
	adcWater_dig = adc_get_result_average(ADC_ADC_WATER_CHY, 10);    
	adcWater_phy = (float)adcWater_dig * (3.3 / 4096); 
	
	if(adcWater_phy >= 3)
	{
		ret = 1;//enable motor output;
	}
	else
	{
		ret = 0;//stop motor output;
	}
	
	return ret;
}


uint8_t Motor_LevelCheck(void)
{
	uint8_t level = 0;
	uint8_t motor_enable;
	uint8_t water_level;
	
	//get motor speed  setting voltage
	adcx_dig = adc_get_result_average(ADC_ADCX_CHY, 10);    
	adc_phy = (float)adcx_dig * (3.3 / 4096); 
	
	motor_enable = Motor_HumidityRangeCheck();
	water_level = Motor_WaterLevelCheck();

	if((1 == motor_enable)&&(1 == water_level))
	{
			//check  motor_level setting 
    if((0.85 >= adc_phy))
		{
			level = Motor_class3;
		}	
		else if((2.2>= adc_phy)&&(adc_phy > 0.85))
		{
			level = Motor_class2;
		}
		else if(adc_phy > 2.2)
		{
			level = Motor_class1;
		}			
	}	
	else
	{
		  level = Motor_off;
	}	
	
	return level;
}	


void Motor_OutPut(uint32_t output)
{		
		//PA0
		GTIM_TIMX_PWM_CHY_CCRX =output ;
		
}


