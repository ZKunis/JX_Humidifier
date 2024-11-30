#include "./SYSTEM/sys/sys.h"

/******************************************************************************************/
/* Òý½Å ¶¨Òå */
/***MOTOR1***************************************************************************************/
#define MOTOR_HUMIDITY_DIFF   5

#define MOTOR_CLASS0 37500  
#define MOTOR_CLASS1 25000     
#define MOTOR_CLASS2 12500  
#define MOTOR_CLASS3 500   
#define MOTOR_OFF		 50000

#define MOTOR_HUMIDITY_1 50    //humidity level 1 
#define MOTOR_HUMIDITY_2 60    //humidity level 2  
#define MOTOR_HUMIDITY_3 70    //humidity level 3 
#define MOTOR_HUMIDITY_4 80    //humidity level 4 

typedef enum
{
	Motor_class3 = 0,
	Motor_class2 = 1,
	Motor_class1 = 2,
	Motor_class0 = 3,
	Motor_off
	
} MotorLevel_Type;


typedef enum
{
	Motor_Humidity_level_80 = 0,
	Motor_Humidity_level_70 = 1,
	Motor_Humidity_level_60 = 2,
	Motor_Humidity_level_50 = 3	
} Motor_HUMIDITY_Type;



void Motor_Init(void);
void Motor_OutPut(uint32_t output);
void Motor_Ctrl_Task(void);
uint8_t Motor_LevelCheck(void);
uint8_t Motor_HumidityRangeCheck(void);
