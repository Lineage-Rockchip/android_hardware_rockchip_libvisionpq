/****************************************************************************
 *
 *    Copyright (c) 2018 - 2021 by Rockchip Corp.  All rights reserved.
 *
 *    The material in this file is confidential and contains trade secrets
 *    of Rockchip Corporation. This is proprietary information owned by
 *    Rockchip Corporation. No part of this work may be disclosed,
 *    reproduced, copied, transmitted, or used in any way for any purpose,
 *    without the express written permission of Rockchip Corporation.
 *
 *****************************************************************************/

#ifndef __RKAUTH_TOOL_H__
#define __RKAUTH_TOOL_H__

#ifdef __cplusplus
extern "C" {
#endif

#define RKAUTH_MODULE_NAME_MAX_SIZE 32
#define RKAUTH_LICENSE_MAX_SIZE 1024

/**
 * @brief 授权使用次数
 * 
 */
typedef struct
{
    int total_num;  // 总次数
    int used_num;   // 已使用次数
} rkauth_usage_t;

/**
 * @brief 与授权服务器通信进行获取授权
 *
 * @param module 授权模块名称
 * @param user 账号名
 * @param passwd 账号密码
 * @param device_info_file 设备信息文件路径（通过在设备上执行rkdevice_info程序获取）
 * @param with_comment 是否带#开头的注释字符串
 * @param output_file 输出licence文件路径
 * @return int 0：成功；-1：失败
 */
int rkauth_tool_get_licence(const char* module, const char* user, const char* passwd, const char* device_info_file,
                       int with_comment, const char* output_file);

/**
 * @brief 与授权服务器通信进行获取授权
 *
 * @param module 授权模块名称
 * @param user 账号名
 * @param passwd 账号密码
 * @param device_info 设备信息字符串
 * @param out_license_str 输出licence字符串buffer(需要外面分配，buffer分配大小参考RKAUTH_LICENSE_MAX_SIZE定义)
 * @param size 输出license字符串buffer大小
 * @return int 0：成功；-1：失败
 */
int rkauth_tool_get_licence_str(const char* module, const char* user, const char* passwd, const char* device_info,
                           char* out_license_str, int max_size);

/**
 * @brief 获取授权次数
 *
 * @param module 授权模块名称
 * @param user 账号名
 * @param passwd 账号密码
 * @param usages 已使用授权次数
 * @return int 0：成功；-1：失败
 */
int rkauth_tool_get_usage(const char* module, const char* user, const char* passwd, rkauth_usage_t* usages);

/**
 * @brief 获取授权库版本
 *
 * @param version 版本号字符串buffer
 * @param max_size 版本字符串bffer size
 * @return int 0：成功；-1：失败
 */
int rkauth_tool_get_version(char* version, int max_size);

#ifdef __cplusplus
}
#endif /* end of __cplusplus */

#endif /* end of #ifndef __RKAUTH_TOOL_H__ */