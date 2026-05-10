#include "ci24r1_spi.h"
#include "ci24r1.h"


void APP_ConfigSpi(void) {
    // 使能 GPIOA 时钟
    __HAL_RCC_GPIOA_CLK_ENABLE();

    // 定义 GPIO 初始化结构体
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    // 配置 SCK (PB13) -> 推挽输出，无上下拉
    GPIO_InitStruct.Pin = GPIO_PIN_13;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH; // 高速模式
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    // 配置 MOSI DATA (PB15) -> 推挽输出，无上下拉
    GPIO_InitStruct.Pin = GPIO_PIN_15;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    // 配置 NSS (PB12) -> 推挽输出，无上下拉
    GPIO_InitStruct.Pin = GPIO_PIN_12;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}


void DATA_OUT(void) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    // 配置 PA1 为推挽输出，带内部上拉，低速模式
    GPIO_InitStruct.Pin = GPIO_PIN_15;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}

void DATA_IN(void) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    // 配置 PA1 为浮空输入，带内部上拉，低速模式
    GPIO_InitStruct.Pin = GPIO_PIN_15;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}

/*************************************************************************************************
函数名称：SPI1_ReadWriteBye
功能：SPI1读写一个字节
参数：TxData,待写入值
返回值：读到的字节数据
***************************************************************************************************/

////ByteSend
void SPI1_WriteByte(uint8_t src)
{
    CI24R1_SCK_0;
    DATA_OUT();
    for(uint8_t i = 0;i<8;i++){
       CI24R1_SCK_0;
        if(src&0x80){
            CI24R1_DATA_1;
        }else{
            CI24R1_DATA_0;
        }
        CI24R1_SCK_1;//拉高，ci24r1 读入1位
        src=src<<1;
    }
    CI24R1_SCK_0;
    
}

////ByteRead
uint8_t SPI1_ReadByte(void)
{
    uint8_t RxData;
    CI24R1_SCK_0;
    DATA_IN();
    for(uint8_t i = 0;i<8;i++){
        RxData=RxData<<1;
        CI24R1_SCK_1;
        if(CI24R1_DATA == 1){
            RxData|= 0X01;
        }else{
            RxData&= 0XFE;
        }
        CI24R1_SCK_0;
    }
    CI24R1_SCK_0;
    return RxData;
}

/********************************************
功能：SPI写寄存器
参数：reg:指定寄存器的地址
            value：要写入的值
********************************************/

void Ci24R1_Write_Reg(uint8_t reg, uint8_t value)
{
    Ci24R1_CSN_0;
    SPI1_WriteByte(reg);
    SPI1_WriteByte(value);
    Ci24R1_CSN_1;
}

/********************************************
功能：SPI读寄存器
参数：reg:指定寄存器的地址
********************************************/

uint8_t Ci24R1_Read_Reg(uint8_t reg)
{
    Ci24R1_CSN_0;
    SPI1_WriteByte(reg);
    uint8_t reg_val = SPI1_ReadByte();
    Ci24R1_CSN_1;
    return reg_val;
}

/********************************************
功能：SPI写BUFF
参数：reg:指定寄存器的地址
*pBuf:数据指针
length:数据长度

********************************************/

void Ci24R1_Write_Buf(uint8_t reg, uint8_t *pBuf, uint8_t length)
{
    Ci24R1_CSN_0;
    SPI1_WriteByte(reg);
    for (uint8_t ctr = 0; ctr < length; ctr++) {
        SPI1_WriteByte(*pBuf++);
    }
    Ci24R1_CSN_1;
}

/**********************************
功能：SPI 读Buff
参数：reg:指定寄存器的地址
*pBuf:数据指针
length:数据长度

**********************************/
void Ci24R1_Read_Buf(uint8_t reg, uint8_t *pBuf, uint8_t length)
{
    Ci24R1_CSN_0;
    SPI1_WriteByte(reg); // 写入寄存器的位置
    for (uint8_t ctr = 0; ctr < length; ctr++) {
        pBuf[ctr] = SPI1_ReadByte(); // 读出数据直接写入数组中
    }
    Ci24R1_CSN_1;
}
