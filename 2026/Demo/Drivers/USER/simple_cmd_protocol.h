#ifndef _SIMPLE_CMD_PROTOCOL_H
#define _SIMPLE_CMD_PROTOCOL_H

#include <stdint.h>

// 帧头
#define FRAME_HEADER 0xAA

// 飞行状态控制码
#define CMD_PREPARE    0x01  // 准备
#define CMD_FLY        0x02  // 直线飞行
#define CMD_TURN_LEFT  0x03  // 左转弯
#define CMD_TURN_RIGHT 0x04  // 右转弯
#define CMD_STOP       0x05  // 停止飞行

// 拍翅速度和角度范围
#define SPEED_MIN      1
#define SPEED_MAX      10
#define ANGLE_MIN      90
#define ANGLE_MAX      180

// 函数声明
uint8_t Calc_Checksum(uint8_t header, uint8_t cmd, uint8_t speed, uint8_t angle);
uint8_t Check_Packet(uint8_t *buffer, uint8_t *out_cmd, uint8_t *out_speed, uint8_t *out_angle);

#endif

