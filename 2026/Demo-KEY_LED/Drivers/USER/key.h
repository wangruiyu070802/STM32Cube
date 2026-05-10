#ifndef _KEY_H
#define _KEY_H
#include "sys.h"
#include "main.h"
//////////////////////////////////////////////////////////////////////////////////	 

// NANO STM32F4开发板
//KEY驱动代码	   
								  
//////////////////////////////////////////////////////////////////////////////////

//下面的方式是通过位带操作方式读取IO
//#define KEY0   PCin(8)   	
//#define KEY1   PCin(9)
//#define KEY2   PDin(2)	 
//#define WK_UP  PAin(0)	

//下面的方式是通过直接操作HAL库函数方式读取IO
#define KEY1        HAL_GPIO_ReadPin(L_UP_GPIO_Port,L_UP_Pin)  //KEY0按键PC8
#define KEY2        HAL_GPIO_ReadPin(L_DOWN_GPIO_Port,L_DOWN_Pin)  //KEY1按键PC9
#define KEY3        HAL_GPIO_ReadPin(L_LEFT_GPIO_Port,L_LEFT_Pin)  //KEY2按键PD2
#define KEY4        HAL_GPIO_ReadPin(L_RIGHT_GPIO_Port,L_RIGHT_Pin)  //KEY0按键PC8
#define KEY5        HAL_GPIO_ReadPin(L_CENTER_GPIO_Port,L_CENTER_Pin)  //KEY1按键PC9
#define KEY6        HAL_GPIO_ReadPin(R_UP_GPIO_Port,R_UP_Pin)  //KEY0按键PC8
#define KEY7        HAL_GPIO_ReadPin(R_DOWN_GPIO_Port,R_DOWN_Pin)  //KEY1按键PC9
#define KEY8        HAL_GPIO_ReadPin(R_LEFT_GPIO_Port,R_LEFT_Pin)  //KEY2按键PD2
#define KEY9        HAL_GPIO_ReadPin(R_RIGHT_GPIO_Port,R_RIGHT_Pin)  //KEY0按键PC8
#define KEY10        HAL_GPIO_ReadPin(R_CENTER_GPIO_Port,R_CENTER_Pin)  //KEY1按键PC9


#define KEY1_PRES	1	//KEY1  
#define KEY2_PRES	2	//KEY2 
#define KEY3_PRES	3	//KEY3
#define KEY4_PRES	4	//KEY4  
#define KEY5_PRES	5	//KEY5 
#define KEY6_PRES	6	//KEY1  
#define KEY7_PRES	7	//KEY2 
#define KEY8_PRES	8	//KEY3
#define KEY9_PRES	9	//KEY4  
#define KEY10_PRES	10	//KEY5 


uint8_t KEY_Scan(u8 mode);//函数申明
#endif
