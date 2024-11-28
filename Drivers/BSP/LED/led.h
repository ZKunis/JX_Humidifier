/**
 ****************************************************************************************************
 * @file        led.h
 * @author      正点原子团队(ALIENTEK)
 * @version     V1.0
 * @date        2020-05-30
 * @brief       LED 驱动代码
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
 * V1.0 20200530
 * 第一次发布
 *
 ****************************************************************************************************
 */

#ifndef __LED_H
#define __LED_H

#include "./SYSTEM/sys/sys.h"

/******************************************************************************************/
/* 引脚 定义 */

#define LED0_GPIO_PORT                  GPIOC
#define LED0_GPIO_PIN                   SYS_GPIO_PIN13
#define LED0_GPIO_CLK_ENABLE()          do{ RCC->APB2ENR |= 1 << 4; }while(0)   /* PC口时钟使能 */

/******************************************************************************************/



/* LED端口定义 */
#define LED0(x)         sys_gpio_pin_set(LED0_GPIO_PORT, LED0_GPIO_PIN, x)      /* LED0 */
#define LED1(x)         sys_gpio_pin_set(LED1_GPIO_PORT, LED1_GPIO_PIN, x)      /* LED1 */

/* LED取反定义 */
#define LED0_TOGGLE()   do{ LED0_GPIO_PORT->ODR ^= LED0_GPIO_PIN; }while(0)      /* LED0 = !LED0 */
#define LED1_TOGGLE()   do{ LED1_GPIO_PORT->ODR ^= LED1_GPIO_PIN; }while(0)      /* LED1 = !LED1 */


void led_init(void);    /* 初始化 */

#endif

















