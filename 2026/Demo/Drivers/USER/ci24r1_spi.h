#ifndef __CI24R1_SPI_H__
#define __CI24R1_SPI_H__     
#include "main.h"   


void APP_ConfigSpi(void);

void Ci24R1_Write_Buf(uint8_t reg, uint8_t *pBuf,uint8_t length);
void Ci24R1_Read_Buf(uint8_t reg, uint8_t *pBuf, uint8_t length);
uint8_t  SPI1_ReadWriteByte(uint8_t TxData);
void	 SPI1_WriteByte(uint8_t	src);
uint8_t		SPI1_ReadByte(void);
uint8_t		Ci24R1_Read_Reg(uint8_t reg);
void	Ci24R1_Write_Reg(uint8_t	reg,uint8_t	value);
void Ci24R1_Write_Reg(uint8_t reg,uint8_t value);
uint8_t Ci24R1_Read_Reg(uint8_t reg);
void DATA_IN(void);
void DATA_OUT(void);




#endif /* __SPI_H__ */

