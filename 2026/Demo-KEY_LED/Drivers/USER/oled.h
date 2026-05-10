#ifndef __OLED_H
#define __OLED_H			  	 
#include "main.h"
#include "spi.h"
#include "stdlib.h"	    
//////////////////////////////////////////////////////////////////////////////////	 

//STM32F4开发板
//OLED 驱动代码	   
								  
////////////////////////////////////////////////////////////////////////////////// 	  
 

//OLED模式设置
//4线串行模式  

		    						  
////-----------------OLED端口定义----------------  					   
//#define OLED_CS 	PBout(12)//cs
//#define OLED_RST  PBout(14)	//rst
//#define OLED_RS 	PBout(10)//DC

// 
////使用4线串行接口时使用 
//#define OLED_SCLK 	PBout(13)//clk
//#define OLED_SDIN 	PBout(15)//mosi
		     
#define OLED_CMD  	0		//写命令
#define OLED_DATA 	1		//写数据
//OLED控制用函数
void OLED_WR_Byte(uint8_t dat,uint8_t cmd);	    
void OLED_Display_On(void);
void OLED_Display_Off(void);
void OLED_Refresh_Gram(void);		//非常重要，做完oled操作后都要调用这个函数，用来刷新屏幕，显示在屏幕上   
							   		    
void OLED_Init(void);
void OLED_Clear(void);
void OLED_DrawPoint(uint8_t x,uint8_t y,uint8_t t);
void OLED_Fill(uint8_t x1,uint8_t y1,uint8_t x2,uint8_t y2,uint8_t dot);
void OLED_ShowChar(uint8_t x,uint8_t y,char chr,uint8_t size,uint8_t mode);
void OLED_ShowNum(uint8_t x,uint8_t y,uint32_t num,uint8_t len,uint8_t size);
void OLED_ShowString(uint8_t x,uint8_t y,const char *p,uint8_t size);	
void OLED_ShowGBK(uint8_t x, uint8_t y,  uint8_t num, uint8_t size,uint8_t mode);
void OLED_ShowGBK_String(uint8_t x, uint8_t y, uint8_t num,uint8_t size,uint8_t mode);
void OLED_ShowPicture(uint8_t x,uint8_t y,uint8_t index,uint8_t clom,uint8_t row,uint8_t mode);
void OLED_ShowGIF(uint8_t x,uint8_t y,uint8_t index,uint8_t clom,uint8_t row,uint8_t mode);//clom宽度，row高度
#endif  
	 

