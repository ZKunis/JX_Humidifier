/**
 ****************************************************************************************************
 * @file        adc.h
 * @author      正点原子团队(ALIENTEK)
 * @version     V1.0
 * @date        2020-05-31
 * @brief       ADC 驱动代码
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
 * 修改说明
 * V1.0 20200531
 * 第一次发布
 *
 ****************************************************************************************************
 */

#ifndef __ADC_H
#define __ADC_H

#include "./SYSTEM/sys/sys.h"


/******************************************************************************************/
/* ADC及引脚 定义 */

#define ADC_ADCX_CHY_GPIO_PORT              			GPIOA
#define ADC_ADCX_CHY_GPIO_PIN               			SYS_GPIO_PIN4
#define ADC_ADCX_CHY_GPIO_CLK_ENABLE()      			do{ RCC->APB2ENR |= 1 << 2; }while(0)   			/* PA口时钟使能 */

#define ADC_ADC2_CHY_GPIO_PORT              			GPIOA
#define ADC_ADC2_CHY_GPIO_PIN               			SYS_GPIO_PIN6
#define ADC_ADC2_CHY_GPIO_CLK_ENABLE()      			do{ RCC->APB2ENR |= 1 << 2; }while(0)   			/* PA口时钟使能 */

#define ADC_ADC_WATER_CHY_GPIO_PORT              	GPIOA
#define ADC_ADC_WATER_CHY_GPIO_PIN               	SYS_GPIO_PIN7
#define ADC_ADC_WATER_CHY_GPIO_CLK_ENABLE()      	do{ RCC->APB2ENR |= 1 << 2; }while(0)   	/* PA口时钟使能 */

#define ADC_ADC_DISPLAY_CHY_GPIO_PORT             GPIOA
#define ADC_ADC_DISPLAY_CHY_GPIO_PIN              SYS_GPIO_PIN3
#define ADC_ADC_DISPLAY_CHY_GPIO_CLK_ENABLE()     do{ RCC->APB2ENR |= 1 << 2; }while(0)  /* PA口时钟使能 */


/*KNOB input */
#define ADC_ADCX_KNOB_GPIO_PORT							GPIOA
#define ADC_ADCX_KNOB_GPIO_PIN              SYS_GPIO_PIN5
#define ADC_ADCX_KNOB_GPIO_CLK_ENABLE()     do{ RCC->APB2ENR |= 1 << 2; }while(0)   /* PA口时钟使能 */

#define ADC_ADCX                            	ADC1 
#define ADC_ADCX_CHY                        	4                                      /* 通道Y,  0 <= Y <= 17 */ 
#define ADC_ADCX_CHY_CLK_ENABLE()           	do{ RCC->APB2ENR |= 1 << 9; }while(0)   /* ADC1 时钟使能 */

#define ADC_ADC2_CHY                       		6                                      /* 通道Y,  0 <= Y <= 17 */ 
#define ADC_ADC2_CHY_CLK_ENABLE()           	do{ RCC->APB2ENR |= 1 << 9; }while(0)   /* ADC1 时钟使能 */

#define ADC_ADC_WATER_CHY                   	7                                      /* 通道Y,  0 <= Y <= 17 */ 
#define ADC_ADC_WATER_CHY_CLK_ENABLE()      	do{ RCC->APB2ENR |= 1 << 9; }while(0)   /* ADC1 时钟使能 */

#define ADC_ADC_DISPLAY_CHY                   3                                      /* 通道Y,  0 <= Y <= 17 */ 
#define ADC_ADC_DISPLAY_CHY_CLK_ENABLE()      do{ RCC->APB2ENR |= 1 << 9; }while(0)   /* ADC1 时钟使能 */


/* IIC???? */
#define ADC_ADCX_KNOB_ENBALE(x)         sys_gpio_pin_set(ADC_ADCX_KNOB_GPIO_PORT, ADC_ADCX_KNOB_GPIO_PIN, x)      /* KNOB */


/******************************************************************************************/
/* 函数声明 */

void adc_init(void);                                                /* ADC初始化 */
void adc_channel_set(ADC_TypeDef *adcx, uint8_t ch, uint8_t stime); /* ADC通道设置 */
uint32_t adc_get_result(uint8_t ch);                                /* 获得某个通道值  */
uint32_t adc_get_result_average(uint8_t ch, uint8_t times);         /* 得到某个通道给定次数采样的平均值 */
#endif 















