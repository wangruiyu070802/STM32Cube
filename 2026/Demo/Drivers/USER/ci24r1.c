#include "Ci24R1.h"
#include "main.h"
#include "ci24r1_spi.h"
#include "delay.h"

uint8_t ADDRESS[ADR_WIDTH] = {88, 88, 88, 88};
uint8_t TX_REG18_1M[4] = {0x82, 0x71, 0x82, 0x00};
uint8_t TX_REG18[4] = {0};

extern uint8_t user_data[];
extern uint8_t rf_tx_buffer[];
uint8_t PLL1 = 0;
uint8_t PLL2 = 0;
/********************************
初始化Ci24R1的IO口
********************************/
void Ci24R1_Init(void)
{
    delay_ms(200);//上电延迟100ms等待正常
    Ci24R1_CSN_0;
    Ci24R1_CSN_1;
    CI24R1_SCK_0;

    /*配置data脚为spi*/
    Ci24R1_CSN_0;
    SPI1_WriteByte(SELSPI);
    Ci24R1_CSN_1;
//    HAL_SPI_Transmit(&hspi1,SELSPI,1,1);
//    Ci24R1_Write_Reg(FLUSH_RX,0xff);							//清除TX FIFO的值,防止上次发射异常退出
//    Ci24R1_Write_Reg(FLUSH_TX,0xff);							//清除TX FIFO的值,防止上次发射异常退出
//    Ci24R1_Write_Reg(W_REGISTER + STATUS, 0x7E); // 清除中断标志位

    
    /*模拟电容*/
    //	Ci24R1_Write_Reg(W_REGISTER+0x02,0x01);
    //	Ci24R1_Write_Reg(W_REGISTER+0x01,0x81);
    //	Ci24R1_Write_Reg(W_REGISTER+0x0f,0xA0);     //目前是15pf

}

/********************************
检测Ci24R1是否存在
********************************/

uint8_t Ci24R1_Check(void)
{
    uint8_t Xbuf[5] = {0xA5, 0xA5, 0xA5, 0xA5, 0xA5};
    delay_ms(500); // 延时10ms
    uint8_t i;
    Ci24R1_Write_Reg(CE_OFF, 0xff);
    Ci24R1_Write_Buf(W_REGISTER + TX_ADDR, (uint8_t *)Xbuf, 5);
    Ci24R1_Read_Buf(TX_ADDR, (uint8_t *)Xbuf, 5);
    delay_ms(100);
    for (i = 0; i < 5; i++)
        if (Xbuf[i] != 0xA5)
            break;
    if (i != 5)
        return 1; // 检测Si24R1错误
    return 0;     // 检测到Si24R1
}

/********************************
启动Si24R1发送一次数据
txbuf：待发送数据首地址
返回值：发送完成状况
********************************/
extern  uint8_t RSSI;
uint8_t Ci24R1_TxPacket(uint8_t *buf,uint8_t pload_width)
{
    uint8_t status;
    Ci24R1_Write_Reg(CE_OFF, 0);//待机
    Ci24R1_Write_Reg(FLUSH_TX, 0); // 清除TX FIFO的值，防止上次发射异常推出
    Ci24R1_Write_Buf(W_TX_PAYLOAD_NOACK, buf, pload_width); 
    Ci24R1_Write_Reg(CE_ON, 0);// CE拉高，Si24R1开始发射
    delay_ms(10); //等待数据发送完成
    
    /*中断检测 start*/
    Ci24R1_CSN_0;
    SPI1_WriteByte(SELIRQ);
    Ci24R1_CSN_1;
    Ci24R1_Read_Reg(R_REGISTER + STATUS);
    DATA_IN();
    while (CI24R1_DATA != 0){
//        LL_GPIO_ResetOutputPin(GPIOA,LL_GPIO_PIN_12);
    }; // 一直等待IRQ引脚被拉低（Si24R1的IRQ低电平有效）等待发送完成
    Ci24R1_CSN_0;
    SPI1_WriteByte(SELSPI);
    Ci24R1_CSN_1;
    
    /*查看接收端参数*/
//    RSSI = Ci24R1_Read_Reg(R_REGISTER + RPD); // 查看状态寄存器
    /*查看发送的情况*/
    status = Ci24R1_Read_Reg(R_REGISTER + STATUS); // 查看状态寄存器
    Ci24R1_Write_Reg(W_REGISTER + STATUS, status); // 清楚MAX_TX或TX_OK中断
    if (status & MAX_TX) {
        Ci24R1_Write_Reg(FLUSH_TX, 0x00); // 清除TX FIFO的值
        return MAX_TX;//超次
    }
    if (status & TX_OK) {
        return TX_OK;
    }
    return 0xff; // 其他原因发送失败
}

/********************************
启动Si24R1接收一次数据
txbuf：待接收数据首地址
返回值：0,接收完成；  1：其他错误代码
********************************/

uint8_t Ci24R1_RxPacket(uint8_t *rxbuf)
{
    uint8_t status;
    /*中断判断 可选*/
    Ci24R1_CSN_0;
    SPI1_WriteByte(SELIRQ);
    Ci24R1_CSN_1;
    DATA_IN();
    while (CI24R1_DATA != 0){
//        LL_GPIO_ResetOutputPin(GPIOA,LL_GPIO_PIN_12);
    }; // 一直等待IRQ引脚被拉低（Si24R1的IRQ低电平有效）等待发送完成
    Ci24R1_CSN_0;
    SPI1_WriteByte(SELSPI);
    Ci24R1_CSN_1;
    
    status = Ci24R1_Read_Reg(R_REGISTER + STATUS);
    Ci24R1_Write_Reg(W_REGISTER + STATUS, status); 
    if (status & RX_OK) {
        while ((status & RX_P_NO) != 0x0e) // 判断RX_FIFO是否为空，不为空继续读
        {
            Ci24R1_Read_Buf(R_RX_PAYLOAD, rxbuf, PLOAD_WIDTH);
            status = Ci24R1_Read_Reg(R_REGISTER + STATUS); // 继续读状态寄存器判断RX_FIFO标志位
        }
        Ci24R1_Write_Reg(FLUSH_RX, 0x00); // 清空RX_FIFO
        return 0;
    }
    return 1;
}

uint8_t buf[10]={0};
/********************************
初始化Si24R1到RX模式
设置RX地址，RX数据宽度，选择RF频道，波特率
当CE变高后，即进入RX模式，并可以接收数据了
********************************/
void Ci24R1_RX_Mode(void)
{
    Ci24R1_Write_Reg(CE_OFF, 0);
    Ci24R1_Write_Reg(W_REGISTER + SETUP_AW, 0x02); // 设置接收地址宽度为4个字节；
    Ci24R1_Write_Buf(W_REGISTER + RX_ADDR_P0, ADDRESS, ADR_WIDTH); // 写入RX节点地址
    Ci24R1_Write_Reg(W_REGISTER + EN_AA, 0);              // 使能通道0的自动应答（如果需要使用Shockburst协议，设为0）
    Ci24R1_Write_Reg(W_REGISTER + EN_RXADDR, 0x01);          // 使能通道0的接收地址
    Ci24R1_Write_Reg(W_REGISTER + RX_PW_P0, PLOAD_WIDTH); // 选择通道0的有效数据宽度
    
    Ci24R1_Write_Reg(0x50, 0x73);//解锁？
    Ci24R1_Write_Reg(W_REGISTER + FEATURE, 0x01);
//    Ci24R1_Write_Reg(W_REGISTER + DYNPD, 0x00);//动态载荷
    
    Ci24R1_Write_Reg(W_REGISTER + RF_CH, RF_CH_2440);                // 设置RF频率
    Ci24R1_Write_Reg(W_REGISTER + RF_SETUP, RF_POWER_9|RF_FREQ_250K);           // 设置RX接收参数，7dBm增益，1Mbps，低噪声增益开启
    Ci24R1_Write_Reg(W_REGISTER + CONFIG, 0x0F);             // 配置基本工作模式的参数，PWR_UP,EN_CRC,16BIT,接收模式
    Ci24R1_Write_Reg(CE_ON, 0);// CE拉高，进入接收模式
    
//    uint8_t rfch = Ci24R1_Read_Reg(R_REGISTER + RF_CH);
//    uint8_t status = Ci24R1_Read_Reg(R_REGISTER + STATUS);
//    uint8_t width = Ci24R1_Read_Reg(R_REGISTER + RX_PW_P0);
//    uint8_t donfig = Ci24R1_Read_Reg(R_REGISTER + CONFIG);
//    uint8_t featrue = Ci24R1_Read_Reg(R_REGISTER + FEATURE);
//    Ci24R1_Read_Buf(R_REGISTER + RX_ADDR_P0, (uint8_t *)buf, ADR_WIDTH);
}

/********************************
初始化Si24R1到TX模式
设置TX地址，TX数据宽度，选择RF频道，波特率
当CE变高后，10us后启动发射数据
********************************/
void Ci24R1_TX_Mode(void)
{
    Ci24R1_Write_Reg(CE_OFF, 0xff); //待机
    Ci24R1_Write_Reg(W_REGISTER + SETUP_AW, 0x02); // 设置接收地址宽度为4个字节；
    Ci24R1_Write_Buf(W_REGISTER + TX_ADDR, ADDRESS, ADR_WIDTH); // 写入TX节点地址
    Ci24R1_Write_Reg(W_REGISTER + EN_AA, 0);     // 使能通道0的自动应答（如果需要使用Shockburst协议，设为0）
    Ci24R1_Write_Reg(W_REGISTER + EN_RXADDR, 0x01); // 使能通道0的接收地址
    
    Ci24R1_Write_Reg(0x50, 0x73);//解锁？
    Ci24R1_Write_Reg(W_REGISTER + FEATURE, 0x01);//_noACK 防止撞包
    Ci24R1_Write_Reg(W_REGISTER + DYNPD, 0x00);//动态载荷
    Ci24R1_Write_Reg(W_REGISTER + SETUP_RETR, 0); // 关闭自动重发 

    /*Ci24R1 与 Xordic 或者 Si24R1 进行 ACK 通信*/
////    //////////写 0F_12,0F_13寄存器（锁相环）///////
//    Ci24R1_Write_Reg(W_REGISTER + 0x02, 0X01); 
//    Ci24R1_Write_Reg(W_REGISTER + 0x01, 0xC1);
//    Ci24R1_Write_Reg(W_REGISTER + 0x0f, 0x60); // 修改0F_12寄存器
//    Ci24R1_Write_Reg(W_REGISTER + 0x02, 0X41); 
//    Ci24R1_Write_Reg(W_REGISTER + 0x01, 0xC1);
//    Ci24R1_Write_Reg(W_REGISTER + 0x0f, 0xa0); // 修改0F_13寄存器

    
    Ci24R1_Write_Reg(W_REGISTER + RF_CH, RF_CH_2440); // 设置RF频率
    Ci24R1_Write_Reg(W_REGISTER + RF_SETUP, RF_POWER_9|RF_FREQ_250K); // 设置TX发射功率11dbm，1Mbps发射速率
    Ci24R1_Write_Reg(W_REGISTER + CONFIG, 0x0e); // 配置基本工作模式的参数，PWR_UP,EN_CRC,16BIT,发射模式
}

/*
    增加调制带宽，提升发射距离（注意，增加调制带宽会导致 FCC/CE 认证无法通过，请谨慎使用）
*/
void Ci24R1_Reg18_change()
{
    Ci24R1_Write_Reg(CE_OFF, 0xff);
    Ci24R1_Write_Reg(0x50, 0xa5);
    Ci24R1_Read_Buf(W_REGISTER + BandWidth_TX, (uint8_t *)TX_REG18, 4);
    Ci24R1_Write_Buf(W_REGISTER + BandWidth_TX, (uint8_t *)TX_REG18_1M, 4);
    Ci24R1_Write_Reg(CE_OFF, 0xff);
    Ci24R1_Write_Reg(0x50, 0xa5);
}

uint8_t Check_Sum(uint8_t *_pbuff, uint16_t _cmdLen)
{
    uint32_t cmd_sum = 0;  // 使用32位防止任何溢出
    uint16_t i;
    
    for (i = 0; i < _cmdLen; i++) {
        cmd_sum += _pbuff[i];
    }
    cmd_sum = (~cmd_sum) & 0xFF;
    
    return (uint8_t)cmd_sum;
}
