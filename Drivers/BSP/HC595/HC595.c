#include "./BSP/HC595/HC595.h"
#include "./SYSTEM/delay/delay.h"
#define uint  unsigned int
#define uchar unsigned char

void HC595_Init(void)
{
	HC595_SDI_GPIO_CLK_ENABLE();
	HC595_CLK_GPIO_CLK_ENABLE();
	HC595_LE_GPIO_CLK_ENABLE();
	HC595_OE_GPIO_CLK_ENABLE();
	sys_gpio_set(HC595_SDI_GPIO_PORT, HC595_SDI_GPIO_PIN,
				SYS_GPIO_MODE_OUT, SYS_GPIO_OTYPE_PP, SYS_GPIO_SPEED_MID, SYS_GPIO_PUPD_PD);   /* Motor1 OUTPUT引脚模式设置 */
	sys_gpio_set(HC595_CLK_GPIO_PORT, HC595_CLK_GPIO_PIN,
				SYS_GPIO_MODE_OUT, SYS_GPIO_OTYPE_PP, SYS_GPIO_SPEED_MID, SYS_GPIO_PUPD_PD);   /* Motor1 AN1脚模式设置 */
	sys_gpio_set(HC595_LE_GPIO_PORT, HC595_LE_GPIO_PIN,
				SYS_GPIO_MODE_OUT, SYS_GPIO_OTYPE_PP, SYS_GPIO_SPEED_MID, SYS_GPIO_PUPD_PD);   /* Motor1 AN1脚模式设置 */
	sys_gpio_set(HC595_OE_GPIO_PORT, HC595_OE_GPIO_PIN,
				SYS_GPIO_MODE_OUT, SYS_GPIO_OTYPE_PP, SYS_GPIO_SPEED_MID, SYS_GPIO_PUPD_PD);   /* Motor1 AN1脚模式设置 */


}

void HC595_Display(unsigned char Shi, unsigned char Ge)
{
	//uint s = 0;
	uchar k;
	uchar n = Shi;
	uchar m = Ge;
		for(k=0;k<8;k++)
	{
		if(m&0x80)HC595_SDI(1);
		else HC595_SDI(0);    //判断当前发送位数据
		m <<= 1;      	//左移一位
		HC595_CLK(0);
		//SM16126_Delay_ms(1);
		HC595_CLK(1);       	//移位寄存器操作	
	}
	for(k=0;k<8;k++)
	{
		if(n&0x80)HC595_SDI(1);
		else HC595_SDI(0);    //判断当前发送位数据
		n <<= 1;      	//左移一位
		HC595_CLK(0);
		//SM16126_Delay_ms(1);
		delay_ms(1);
		HC595_CLK(1);       	//移位寄存器操作	
	}		


	HC595_LE(1);
	//SM16126_Delay_ms(1);
	delay_ms(1);
	HC595_LE(0);			//锁存数据
	//SM16126_Delay_ms(1);
	//OE = 0;			//OE为低电平时显示启动输出，OE为高电平时输出关闭
	//Delay_ms(1000);
	//OE = 1;		//这里不关闭显示，让数码管静态长亮
	//Delay_ms(1000);
}
