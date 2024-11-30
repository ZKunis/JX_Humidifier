#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "stdint.h"

/*AHT10 SDA */
#define AHT10_SDA_GPIO_PORT                  GPIOA
#define AHT10_SDA_GPIO_PIN                   SYS_GPIO_PIN2
#define AHT10_SDA_GPIO_CLK_ENABLE()           do{ RCC->APB2ENR |= 1 << 2; }while(0)   /* PA口时钟使能 */

/*AHT10 SCL */
#define AHT10_SCL_GPIO_PORT                  GPIOA
#define AHT10_SCL_GPIO_PIN                   SYS_GPIO_PIN1
#define AHT10_SCL_GPIO_CLK_ENABLE()           do{ RCC->APB2ENR |= 1 << 2; }while(0)   /* PA口时钟使能 */


/* IIC端口定义 */
#define AHT10_SDA_OUT(x)         sys_gpio_pin_set(AHT10_SDA_GPIO_PORT, AHT10_SDA_GPIO_PIN, x)      /* SDA */
#define AHT10_SCL_OUT(x)         sys_gpio_pin_set(AHT10_SCL_GPIO_PORT, AHT10_SCL_GPIO_PIN, x)      /* SCL */


uint8_t JH_Init(void);
void JH_Read_CTdata(uint32_t *ct); //读取AHT10的温度和湿度数据
uint8_t JH_Read_Cal_Enable(void);  //查询cal enable位有没有使能？
void SCL_Pin_Output_High(void); //SCL输出高电平，P14作为I2C的SCL
void SCL_Pin_Output_Low(void); //SCL输出低电平
void SDA_Pin_Output_Low(void);  //将P15配置为输出  并设置为低电平
void SDA_Pin_IN_FLOATING(void);  //SDA配置为悬浮输入  SYS_GPIO_MODE_IN	
void SDA_Pin_Output_High(void);
uint16_t ATH_humidity(void);