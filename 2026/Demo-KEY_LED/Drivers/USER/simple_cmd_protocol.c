#include "simple_cmd_protocol.h"

// 计算校验和：帧头+控制码+速度+角度 取反
uint8_t Calc_Checksum(uint8_t header, uint8_t cmd, uint8_t speed, uint8_t angle)
{
    return ~(header + cmd + speed + angle);
}

// 检查数据包并解析出控制码、速度、角度
// 返回值：1-有效，0-无效
uint8_t Check_Packet(uint8_t *buffer, uint8_t *out_cmd, uint8_t *out_speed, uint8_t *out_angle)
{
    // 检查帧头
    if (buffer[0] != FRAME_HEADER) {
        return 0;
    }
    
    // 验证校验和
    uint8_t calc_checksum = Calc_Checksum(buffer[0], buffer[1], buffer[2], buffer[3]);
    if (calc_checksum != buffer[4]) {
        return 0;
    }
    
    // 验证速度和角度范围
    if (buffer[2] < SPEED_MIN || buffer[2] > SPEED_MAX) return 0;
    if (buffer[3] < ANGLE_MIN || buffer[3] > ANGLE_MAX) return 0;
    
    // 返回解析结果
    if (out_cmd)   *out_cmd   = buffer[1];
    if (out_speed) *out_speed = buffer[2];
    if (out_angle) *out_angle = buffer[3];
    
    return 1;
}
