#include "./SYSTEM/sys/sys.h"

/******************************************************************************************/
/* Òý½Å ¶¨Òå */
/***MOTOR1***************************************************************************************/

#define MOTOR_CLASS0 0x10
#define MOTOR_CLASS1 0x20
#define MOTOR_CLASS2 0x30
#define MOTOR_CLASS3 0x40
#define MOTOR_OFF		 0x00

typedef enum
{
	Motor_class0 = 0,
	Motor_class1 = 1,
	Motor_class2 = 2,
	Motor_class3 = 3,
	Motor_off
	
} MotorLevel_Type;


void Motor_Init(void);
void Motor_OutPut(uint32_t output);
void Motor_Ctrl_Task(void);
uint8_t Motor_LevelCheck(void);
