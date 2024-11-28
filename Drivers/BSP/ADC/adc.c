/**
 ****************************************************************************************************
 * @file        adc.c
 * @author      ÕýµãÔ­×ÓÍÅ¶Ó(ALIENTEK)
 * @version     V1.0
 * @date        2020-05-31
 * @brief       ADC Çý¶¯´úÂë
 * @license     Copyright (c) 2020-2032, ¹ãÖÝÊÐÐÇÒíµç×Ó¿Æ¼¼ÓÐÏÞ¹«Ë¾
 ****************************************************************************************************
 * @attention
 *
 * ÊµÑéÆ½Ì¨:ÕýµãÔ­×Ó STM32F103¿ª·¢°å
 * ÔÚÏßÊÓÆµ:www.yuanzige.com
 * ¼¼ÊõÂÛÌ³:www.openedv.com
 * ¹«Ë¾ÍøÖ·:www.alientek.com
 * ¹ºÂòµØÖ·:openedv.taobao.com
 *
 * ÐÞ¸ÄËµÃ÷
 * V1.0 20200531
 * µÚÒ»´Î·¢²¼
 *
 ****************************************************************************************************
 */

#include "./BSP/ADC/adc.h"
#include "./SYSTEM/delay/delay.h"


/**
 * @brief       ADC³õÊ¼»¯º¯Êý
 *   @note      ±¾º¯ÊýÖ§³ÖADC1/ADC2ÈÎÒâÍ¨µÀ, µ«ÊÇ²»Ö§³ÖADC3
 *              ÎÒÃÇÊ¹ÓÃ12Î»¾«¶È, ADC²ÉÑùÊ±ÖÓ=12M, ×ª»»Ê±¼äÎª: ²ÉÑùÖÜÆÚ + 12.5¸öADCÖÜÆÚ
 *              ÉèÖÃ×î´ó²ÉÑùÖÜÆÚ: 239.5, Ôò×ª»»Ê±¼ä = 252 ¸öADCÖÜÆÚ = 21us
 * @param       ÎÞ
 * @retval      ÎÞ
 */
void adc_init(void)
{
    ADC_ADCX_CHY_GPIO_CLK_ENABLE(); /* IO¿ÚÊ±ÖÓÊ¹ÄÜ */
    ADC_ADCX_CHY_CLK_ENABLE();      /* ADCÊ±ÖÓÊ¹ÄÜ */
		ADC_ADCX_KNOB_GPIO_CLK_ENABLE(); /*enable KNOB*/
		
	
    sys_gpio_set(ADC_ADCX_CHY_GPIO_PORT, ADC_ADCX_CHY_GPIO_PIN,
                 SYS_GPIO_MODE_AIN, SYS_GPIO_OTYPE_PP, SYS_GPIO_SPEED_MID, SYS_GPIO_PUPD_PU);   /* AD²É¼¯Òý½ÅÄ£Ê½ÉèÖÃ,Ä£ÄâÊäÈë */
	
    sys_gpio_set(ADC_ADCX_CHY_GPIO_PORT, ADC_ADCX_KNOB_GPIO_PIN,
                 SYS_GPIO_MODE_OUT, SYS_GPIO_OTYPE_PP, SYS_GPIO_SPEED_MID, SYS_GPIO_PUPD_PD);   /* KNOB ENBALë */
		ADC_ADCX_KNOB_ENBALE(1);

    RCC->APB2RSTR |= 3 << 9;        /* ADC1 & ADC2 ¸´Î» */
    RCC->APB2RSTR &= ~(3 << 9);     /* ¸´Î»½áÊø */

    /* ADCÊ±ÖÓÀ´×Ô APB2, ¼´PCLK2, ÆµÂÊÎª72Mhz, ADC×î´óÊ±ÖÓÒ»°ã²»Òª³¬¹ý14M
     * ÔÚ72MÖ÷ÆµÌõ¼þÏÂ, ÎÒÃÇÊ¹ÓÃ6·ÖÆµ, µÃµ½PCLK2 / 6 = 12Mhz µÄADCÊ±ÖÓ
     */
    RCC->CFGR &= ~(3 << 14);        /* ADCPRE[1:0] ADCÊ±ÖÓÔ¤·ÖÆµÇåÁã */
    RCC->CFGR |= 2 << 14;           /* ÉèÖÃADCÊ±ÖÓÔ¤·ÖÆµÏµÊýÎª 6, ¼´ PCLK2 / 6 = 12Mhz */

    ADC_ADCX->CR1 &= ~(0XF << 16);  /* ¹¤×÷Ä£Ê½ÇåÁã */
    ADC_ADCX->CR1 |= 0 << 16;       /* ¶ÀÁ¢¹¤×÷Ä£Ê½ */
    ADC_ADCX->CR1 &= ~(1 << 8);     /* ·ÇÉ¨ÃèÄ£Ê½ */

    ADC_ADCX->CR2 &= ~(1 << 1);     /* µ¥´Î×ª»»Ä£Ê½ */
    ADC_ADCX->CR2 &= ~(7 << 17);
    ADC_ADCX->CR2 |= 7 << 17;       /* Èí¼þ¿ØÖÆ×ª»» */
    ADC_ADCX->CR2 |= 1 << 20;       /* Ê¹ÓÃÓÃÍâ²¿´¥·¢(SWSTART)!!! ±ØÐëÊ¹ÓÃÒ»¸öÊÂ¼þÀ´´¥·¢ */
    ADC_ADCX->CR2 &= ~(1 << 11);    /* ÓÒ¶ÔÆë */
    
    ADC_ADCX->SQR1 &= ~(0XF << 20); /* L[3:0]ÇåÁã */
    ADC_ADCX->SQR1 |= 0 << 20;      /* 1¸ö×ª»»ÔÚ¹æÔòÐòÁÐÖÐ Ò²¾ÍÊÇÖ»×ª»»¹æÔòÐòÁÐ1 */

    ADC_ADCX->CR2 |= 1 << 0;        /* ¿ªÆôAD×ª»»Æ÷ */

    ADC_ADCX->CR2 |= 1 << 3;        /* Ê¹ÄÜ¸´Î»Ð£×¼ */

    while (ADC_ADCX->CR2 & 1 << 3); /* µÈ´ýÐ£×¼½áÊø */

    /* ¸ÃÎ»ÓÉÈí¼þÉèÖÃ²¢ÓÉÓ²¼þÇå³ý  ÔÚÐ£×¼¼Ä´æÆ÷±»³õÊ¼»¯ºó¸ÃÎ»½«±»Çå³ý */
    ADC_ADCX->CR2 |= 1 << 2;        /* ¿ªÆôADÐ£×¼ */

    while (ADC_ADCX->CR2 & 1 << 2); /* µÈ´ýÐ£×¼½áÊø */
}

/**
 * @brief       ÉèÖÃADCÍ¨µÀ²ÉÑùÊ±¼ä
 * @param       adcx : adc½á¹¹ÌåÖ¸Õë, ADC1 / ADC2
 * @param       ch   : Í¨µÀºÅ, 0~17
 * @param       stime: ²ÉÑùÊ±¼ä  0~7, ¶ÔÓ¦¹ØÏµÎª:
 *   @arg       000, 1.5¸öADCÊ±ÖÓÖÜÆÚ        001, 7.5¸öADCÊ±ÖÓÖÜÆÚ
 *   @arg       010, 13.5¸öADCÊ±ÖÓÖÜÆÚ       011, 28.5¸öADCÊ±ÖÓÖÜÆÚ
 *   @arg       100, 41.5¸öADCÊ±ÖÓÖÜÆÚ       101, 55.5¸öADCÊ±ÖÓÖÜÆÚ
 *   @arg       110, 71.5¸öADCÊ±ÖÓÖÜÆÚ       111, 239.5¸öADCÊ±ÖÓÖÜÆÚ
 * @retval      ÎÞ
 */
void adc_channel_set(ADC_TypeDef *adcx, uint8_t ch, uint8_t stime)
{
    if (ch < 10)    /* Í¨µÀ0~9,Ê¹ÓÃSMPR2ÅäÖÃ */
    {
        adcx->SMPR2 &= ~(7 << (3 * ch));        /* Í¨µÀch ²ÉÑùÊ±¼äÇå¿Õ */
        adcx->SMPR2 |= 7 << (3 * ch);           /* Í¨µÀch ²ÉÑùÖÜÆÚÉèÖÃ,ÖÜÆÚÔ½¸ß¾«¶ÈÔ½¸ß */
    }
    else            /* Í¨µÀ10~17,Ê¹ÓÃSMPR1ÅäÖÃ */
    {
        adcx->SMPR1 &= ~(7 << (3 * (ch - 10))); /* Í¨µÀch ²ÉÑùÊ±¼äÇå¿Õ */
        adcx->SMPR1 |= 7 << (3 * (ch - 10));    /* Í¨µÀch ²ÉÑùÖÜÆÚÉèÖÃ,ÖÜÆÚÔ½¸ß¾«¶ÈÔ½¸ß */
    }
}

/**
 * @brief       »ñµÃADC×ª»»ºóµÄ½á¹û
 * @param       ch: Í¨µÀºÅ, 0~17
 * @retval      ADC×ª»»ºóµÄÖµ
 */
uint32_t adc_get_result(uint8_t ch)
{
    adc_channel_set(ADC_ADCX, ch, 7);   /* ÉèÖÃADCX¶ÔÓ¦Í¨µÀ²ÉÑùÊ±¼äÎª239.5¸öÊ±ÖÓÖÜÆÚ */

    ADC_ADCX->SQR3 &= ~(0X1F << 5 * 0); /* ¹æÔòÐòÁÐ1Í¨µÀÇåÁã */
    ADC_ADCX->SQR3 |= ch << (5 * 0);    /* ¹æÔòÐòÁÐ1 Í¨µÀ = ch */
    ADC_ADCX->CR2 |= 1 << 22;           /* Æô¶¯¹æÔò×ª»»Í¨µÀ */

    while (!(ADC_ADCX->SR & 1 << 1));   /* µÈ´ý×ª»»½áÊø */

    return ADC_ADCX->DR;                /* ·µ»ØadcÖµ */
}

/**
 * @brief       »ñÈ¡Í¨µÀchµÄ×ª»»Öµ£¬È¡times´Î,È»ºóÆ½¾ù
 * @param       ch      : Í¨µÀºÅ, 0~17
 * @param       times   : »ñÈ¡´ÎÊý
 * @retval      Í¨µÀchµÄtimes´Î×ª»»½á¹ûÆ½¾ùÖµ
 */
uint32_t adc_get_result_average(uint8_t ch, uint8_t times)
{
    uint32_t temp_val = 0;
    uint8_t t;

    for (t = 0; t < times; t++)     /* »ñÈ¡times´ÎÊý¾Ý */
    {
        temp_val += adc_get_result(ch);
        delay_ms(5);
    }

    return temp_val / times;        /* ·µ»ØÆ½¾ùÖµ */
}









