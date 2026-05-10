#include "key.h"
#include "delay.h"
//////////////////////////////////////////////////////////////////////////////////	 
// NANO STM32F4开发板
//KEY驱动代码	   
									  
//////////////////////////////////////////////////////////////////////////////////

//按键处理函数
//返回按键值
//mode:0,不支持连续按;1,支持连续按;
//返回值：
//0，没有任何按键按下
//KEY0_PRES，KEY0按下
//KEY1_PRES，KEY1按下
//KEY2_PRES，KEY2按下
//WKUP_PRES，WK_UP按下 
//注意此函数有响应优先级,KEY0>KEY1>KEY2>WK_UP!!
uint8_t KEY_Scan(u8 mode)//函数定义
{	 
	static u8 key_up=1;//按键按松开标志
	if(mode)key_up=1;  //支持连按		  
	if(key_up&&(KEY1==0||KEY2==0||KEY3==0||KEY4==0||KEY5==0
		||KEY6==0||KEY7==0||KEY8==0||KEY9==0||KEY10==0))//如果有按键被按下
	{
		delay_ms(10);//去抖动 
		key_up=0;
		if(KEY1==0)
			return KEY1_PRES;
		else if(KEY2==0)
			return KEY2_PRES;
		else if(KEY3==0)
			return KEY3_PRES; 
		else if(KEY4==0)
			return KEY4_PRES;
		else if(KEY5==0)
			return KEY5_PRES; 
		else if(KEY6==0)
			return KEY6_PRES;
		else if(KEY7==0)
			return KEY7_PRES;
		else if(KEY8==0)
			return KEY8_PRES; 
		else if(KEY9==0)
			return KEY9_PRES;
		else if(KEY10==0)
			return KEY10_PRES; 
	}
	else if(KEY1==1&&KEY2==1&&KEY3==1&&KEY4==1
		&&KEY5==1
		&&KEY6==1&&KEY7==1&&KEY8==1&&KEY9==1
		&&KEY10==1
	  )
		key_up=1; 	     
	return 0;// 无按键按下
}
