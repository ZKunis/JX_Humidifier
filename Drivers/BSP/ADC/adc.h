/**
 ****************************************************************************************************
 * @file        adc.h
 * @author      ����ԭ���Ŷ�(ALIENTEK)
 * @version     V1.0
 * @date        2020-05-31
 * @brief       ADC ��������
 * @license     Copyright (c) 2020-2032, �������������ӿƼ����޹�˾
 ****************************************************************************************************
 * @attention
 *
 * ʵ��ƽ̨:����ԭ�� STM32F103������
 * ������Ƶ:www.yuanzige.com
 * ������̳:www.openedv.com
 * ��˾��ַ:www.alientek.com
 * �����ַ:openedv.taobao.com
 *
 * �޸�˵��
 * V1.0 20200531
 * ��һ�η���
 *
 ****************************************************************************************************
 */

#ifndef __ADC_H
#define __ADC_H

#include "./SYSTEM/sys/sys.h"


/******************************************************************************************/
/* ADC������ ���� */

#define ADC_ADCX_CHY_GPIO_PORT              GPIOA
#define ADC_ADCX_CHY_GPIO_PIN               SYS_GPIO_PIN4
#define ADC_ADCX_CHY_GPIO_CLK_ENABLE()      do{ RCC->APB2ENR |= 1 << 2; }while(0)   /* PA��ʱ��ʹ�� */

/*KNOB input */
#define ADC_ADCX_KNOB_GPIO_PORT							GPIOA
#define ADC_ADCX_KNOB_GPIO_PIN              SYS_GPIO_PIN5
#define ADC_ADCX_KNOB_GPIO_CLK_ENABLE()     do{ RCC->APB2ENR |= 1 << 2; }while(0)   /* PA��ʱ��ʹ�� */

#define ADC_ADCX                            ADC1 
#define ADC_ADCX_CHY                        4                                      /* ͨ��Y,  0 <= Y <= 17 */ 
#define ADC_ADCX_CHY_CLK_ENABLE()           do{ RCC->APB2ENR |= 1 << 9; }while(0)   /* ADC1 ʱ��ʹ�� */

/* IIC???? */
#define ADC_ADCX_KNOB_ENBALE(x)         sys_gpio_pin_set(ADC_ADCX_KNOB_GPIO_PORT, ADC_ADCX_KNOB_GPIO_PIN, x)      /* KNOB */


/******************************************************************************************/
/* �������� */

void adc_init(void);                                                /* ADC��ʼ�� */
void adc_channel_set(ADC_TypeDef *adcx, uint8_t ch, uint8_t stime); /* ADCͨ������ */
uint32_t adc_get_result(uint8_t ch);                                /* ���ĳ��ͨ��ֵ  */
uint32_t adc_get_result_average(uint8_t ch, uint8_t times);         /* �õ�ĳ��ͨ����������������ƽ��ֵ */
#endif 














