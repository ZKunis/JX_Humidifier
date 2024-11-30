#ifndef __HC595_H
#define __HC595_H

#include "./SYSTEM/sys/sys.h"

////IO设置
//sbit SDI = P3^7;		//串行数据输入
//sbit CLK = P1^0;		//时钟上升沿移位数据
//sbit LE	 = P1^1;		//高电平更新，低电平锁存
////sbit OE	 = P1^2;		//OE为低电平时显示启动输出，OE为高电平时输出关闭 


/*HC595 SDI */
#define HC595_SDI_GPIO_PORT                  GPIOB
#define HC595_SDI_GPIO_PIN                   SYS_GPIO_PIN0
#define HC595_SDI_GPIO_CLK_ENABLE()           do{ RCC->APB2ENR |= 1 << 3; }while(0)   /* PB口时钟使能 */

/*HC595 CLK */
#define HC595_CLK_GPIO_PORT                  GPIOB
#define HC595_CLK_GPIO_PIN                   SYS_GPIO_PIN1
#define HC595_CLK_GPIO_CLK_ENABLE()           do{ RCC->APB2ENR |= 1 << 3; }while(0)   /* PB口时钟使能 */

/*HC595 LE */
#define HC595_LE_GPIO_PORT                  GPIOB
#define HC595_LE_GPIO_PIN                   SYS_GPIO_PIN10
#define HC595_LE_GPIO_CLK_ENABLE()           do{ RCC->APB2ENR |= 1 << 3; }while(0)   /* PB口时钟使能 */

#define HC595_SDI(x)            sys_gpio_pin_set(HC595_SDI_GPIO_PORT, HC595_SDI_GPIO_PIN, x)      /* SDA */
#define HC595_CLK(x)            sys_gpio_pin_set(HC595_CLK_GPIO_PORT, HC595_CLK_GPIO_PIN, x)      /* CLK */
#define HC595_LE(x)             sys_gpio_pin_set(HC595_LE_GPIO_PORT, HC595_LE_GPIO_PIN, x)      /* LE */

extern void HC595_Display(unsigned char Shi, unsigned char Ge);//数码管显示函数
extern void HC595_Off(void);									 //关闭显示
void HC595_Init(void);
#endif