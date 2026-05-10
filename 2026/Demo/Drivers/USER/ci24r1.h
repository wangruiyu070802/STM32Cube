
#ifndef _Ci24R1_H
#define _Ci24R1_H

#include "main.h"
#include "stdio.h"
// #define TX_PLOAD_WIDTH     32
//======================================================================
//========  		Define interface to Si24R1               ========
//======================================================================

#define ADR_WIDTH 4    // 4个字节的发送/接收地址长度
#define PLOAD_WIDTH 11 // PLOAD长度

#define MAX_TX 0x10
#define TX_OK 0x20
#define RX_OK 0x40
#define RX_P_NO 0X0E // 接收FIFO为空标志
//======================================================================
//                      Define SPI pins(Si24R1)
//======================================================================

// #define CSN 	PA6
// #define SCK 	PA5
// #define MOSI	PA1

#define CI24R1_SCK_0 HAL_GPIO_WritePin(GPIOB,GPIO_PIN_13,GPIO_PIN_RESET)
#define CI24R1_SCK_1 HAL_GPIO_WritePin(GPIOB,GPIO_PIN_13,GPIO_PIN_SET)
#define CI24R1_DATA_0 HAL_GPIO_WritePin(GPIOB,GPIO_PIN_15,GPIO_PIN_RESET)
#define CI24R1_DATA_1 HAL_GPIO_WritePin(GPIOB,GPIO_PIN_15,GPIO_PIN_SET)
#define CI24R1_DATA HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_15)
#define Ci24R1_CSN_0    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_RESET)
#define Ci24R1_CSN_1    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_SET)
//======================================================================
//                        SPI commands (Si24R1)
//======================================================================
#define R_REGISTER 0x00         // Define Read command to register
#define W_REGISTER 0x20         // Define Write command to register
#define R_RX_PAYLOAD 0x61       // Define Read RX payload register address
#define W_TX_PAYLOAD 0xA0       // Define Write TX payload register address
#define FLUSH_TX 0xE1           // Define Flush TX register command
#define FLUSH_RX 0xE2           // Define Flush RX register command
#define REUSE_TX_PL 0xE3        // Define Reuse TX payload register command
#define R_RX_PL_WID 0x60        // Define Read RX payload width for the R_RX_PAYLOAD in the RX FIFO
#define W_ACK_PAYLOAD 0xA8      // Define Write Payload to be transmitted together with ACK packet on PIPExxx xxx valid in the range from 000 to 101)
#define W_TX_PAYLOAD_NOACK 0xB0 // Define Write TX Disables AUTOACK on this specific packet
#define NOP 0xFF                // Define No Operation, might be used to read status register

//======================================================================
//                     SPI commands (Ci24R1) (newly increased!!!!)
#define CE_ON 0x70  // 打开CE  CE=1,CE_STATE=1
#define CE_OFF 0x71 // 关闭CE  CE=0,CE_STATE=0
#define SELSPI 0x74 // 选择DATA引脚为SPI功能
#define SELIRQ 0x75 // 选择DATA引脚为输出IRQ值
//======================================================================

//======================================================================
//                    SPI registers address(Si24R1)
//======================================================================
#define CONFIG 0x00      // 'Config' register address
#define EN_AA 0x01       // 'Enable Auto Acknowledgment' register address
#define EN_RXADDR 0x02   // 'Enabled RX addresses' register address
#define SETUP_AW 0x03    // 'Setup address width' register address
#define SETUP_RETR 0x04  // 'Setup Auto. Retrans' register address
#define RF_CH 0x05       // 'RF channel' register address
#define RF_SETUP 0x06    // 'RF setup' register address
#define STATUS 0x07      // 'Status' register address
#define OBSERVE_TX 0x08  // 'Observe TX' register address
#define RPD 0x09         // 'Received Power Detector' register address  equal to Si24R1 is "CD"(Carrier Detecotr)
#define RX_ADDR_P0 0x0A  // 'RX address pipe0' register address
#define RX_ADDR_P1 0x0B  // 'RX address pipe1' register address
#define RX_ADDR_P2 0x0C  // 'RX address pipe2' register address
#define RX_ADDR_P3 0x0D  // 'RX address pipe3' register address
#define RX_ADDR_P4 0x0E  // 'RX address pipe4' register address
#define RX_ADDR_P5 0x0F  // 'RX address pipe5' register address
#define TX_ADDR 0x10     // 'TX address' register address
#define RX_PW_P0 0x11    // 'RX payload width, pipe0' register address
#define RX_PW_P1 0x12    // 'RX payload width, pipe1' register address
#define RX_PW_P2 0x13    // 'RX payload width, pipe2' register address
#define RX_PW_P3 0x14    // 'RX payload width, pipe3' register address
#define RX_PW_P4 0x15    // 'RX payload width, pipe4' register address
#define RX_PW_P5 0x16    // 'RX payload width, pipe5' register address
#define FIFO_STATUS 0x17 // 'FIFO Status Register' register address
#define BandWidth_TX 0x18
#define DYNPD 0x1C   // 'Enable dynamic paload length' register address
#define FEATURE 0x1D //  Feature Register address

//////////llhao//////////////
#define RF_POWER_F9     0x00
#define RF_POWER_F4     0x01
#define RF_POWER_F1     0x02
#define RF_POWER_3      0x03
#define RF_POWER_7      0x04
#define RF_POWER_9      0x05

#define RF_FREQ_250K    0x20
#define RF_FREQ_1M      0x00
#define RF_FREQ_2M      0x08

#define RF_CH_2525      0x7D//125  
#define RF_CH_2500      0x64//100 
#define RF_CH_2482      0x52//82   
#define RF_CH_2480      0x50//80  2480MHz
#define RF_CH_2463      0x3F//63   
#define RF_CH_2462      0x3E//62   
#define RF_CH_2442      0x2A//42   
#define RF_CH_2440      0x28//40  2440MHz
#define RF_CH_2402      0x02//02  2402MHz
#define RF_CH_2400      0x00//00
// 干扰较少的推荐频点（Wi-Fi信道间隙）
#define RF_CH_2404      0x04    // 2404MHz (Wi-Fi信道1与2之间)
#define RF_CH_2406      0x06    // 2406MHz (Wi-Fi信道1间隙)
#define RF_CH_2414      0x0E    // 2414MHz
#define RF_CH_2424      0x18    // 2424MHz (Wi-Fi信道5与6之间)
#define RF_CH_2434      0x22    // 2434MHz
#define RF_CH_2448      0x30    // 2448MHz (Wi-Fi信道7与8之间)
#define RF_CH_2456      0x38    // 2456MHz
#define RF_CH_2468      0x44    // 2468MHz (Wi-Fi信道10与11之间)
#define RF_CH_2472      0x48    // 2472MHz
#define RF_CH_2476      0x4C    // 2476MHz (Wi-Fi信道12与13之间)
#define RF_CH_2486      0x56    // 2486MHz
#define RF_CH_2498      0x62    // 2498MHz
#define RF_CH_2510      0x6E    // 2510MHz
#define RF_CH_2518      0x76    // 2518MHz
#define RF_CH_2522      0x7A    // 2522MHz

#define Single_Carrier_MODE  1    //单载波模式
#define Modulated_Wave_MODE  0    //调制波模式
#define ADV_INTERVAL_MS      50   //广播间隔


// 函数声明
uint8_t Ci24R1_Check(void);
uint8_t Ci24R1_TxPacket(uint8_t *buf,uint8_t pload_width);
uint8_t Ci24R1_RxPacket(uint8_t *rxbuf);
void Ci24R1_RX_Mode(void);
void Ci24R1_TX_Mode(void);
void rf_mainloop(void);
void Ci24R1_Init(void);
void Ci24R1_Reg18_change(void);
uint8_t Check_Sum(uint8_t *_pbuff, uint16_t _cmdLen);
uint8_t Check_Sum(uint8_t *_pbuff, uint16_t _cmdLen);
#endif
