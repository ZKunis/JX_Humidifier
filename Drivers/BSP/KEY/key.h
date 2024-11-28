/**
 ****************************************************************************************************
 * @file        key.h
 * @author      ����ԭ���Ŷ�(ALIENTEK)
 * @version     V1.0
 * @date        2020-05-30
 * @brief       �������� ��������
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
 * V1.0 20200530
 * ��һ�η���
 *
 ****************************************************************************************************
 */

#ifndef __KEY_H
#define __KEY_H

#include "./SYSTEM/sys/sys.h"

/******************************************************************************************/
/* ���� ���� */

#define KEY0_GPIO_PORT                  GPIOA
#define KEY0_GPIO_PIN                   SYS_GPIO_PIN10
#define KEY0_GPIO_CLK_ENABLE()          do{ RCC->APB2ENR |= 1 << 2; }while(0)   /* PC��ʱ��ʹ�� */

#define KEY1_GPIO_PORT                  GPIOA
#define KEY1_GPIO_PIN                   SYS_GPIO_PIN15
#define KEY1_GPIO_CLK_ENABLE()          do{ RCC->APB2ENR |= 1 << 2; }while(0)   /* PA��ʱ��ʹ�� */

#define WKUP_GPIO_PORT                  GPIOA
#define WKUP_GPIO_PIN                   SYS_GPIO_PIN0
#define WKUP_GPIO_CLK_ENABLE()          do{ RCC->APB2ENR |= 1 << 2; }while(0)   /* PA��ʱ��ʹ�� */

/******************************************************************************************/

#define KEY0        sys_gpio_pin_get(KEY0_GPIO_PORT, KEY0_GPIO_PIN)     /* ��ȡKEY0���� */
#define KEY1        sys_gpio_pin_get(KEY1_GPIO_PORT, KEY1_GPIO_PIN)     /* ��ȡKEY1���� */
#define WK_UP       sys_gpio_pin_get(WKUP_GPIO_PORT, WKUP_GPIO_PIN)     /* ��ȡWKUP���� */


#define KEY0_PRES    1      /* KEY0���� */
#define KEY1_PRES    2      /* KEY1���� */
#define WKUP_PRES    3      /* KEY_UP����(��WK_UP) */

void key_init(void);        /* ������ʼ������ */
uint8_t key_scan(uint8_t mode);/* ����ɨ�躯�� */

#endif

















