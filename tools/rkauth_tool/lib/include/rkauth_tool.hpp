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
#ifndef __RKAUTH_TOOL_CXX_H__
#define __RKAUTH_TOOL_CXX_H__

#include <iostream>

/**
 * @brief 授权使用次数
 * 
 */
typedef struct
{
    std::string module;     // 模块名
    int total_num;          // 总次数
    int used_num;           // 已用次数
} RKAuthUsage;

/**
 * @brief 与授权服务器通信进行获取授权
 *
 * @param module 授权模块名称
 * @param user 账号名
 * @param passwd 账号密码
 * @param device_info_file 设备信息文件路径（通过在设备上执行rkdevice_info程序获取）
 * @param with_comment 是否带#开头的注释字符串
 * @param output_license_file 输出licence文件路径
 * @return int 0：成功；-1：失败
 */
int RKAUTH_GetLicense(std::string module, std::string user, std::string passwd, std::string device_info_file,
                           bool with_comment, std::string output_license_file);

/**
 * @brief 与授权服务器通信进行获取授权
 *
 * @param module 授权模块名称
 * @param user 账号名
 * @param passwd 账号密码
 * @param device_info 设备信息字符串
 * @param out_license 输出licence字符串
 * @return int 0：成功；-1：失败
 */
int RKAUTH_GetLicenseStr(std::string module, std::string user, std::string passwd, std::string device_info,
                               std::string& out_license);

/**
 * @brief 获取授权次数
 *
 * @param module 授权模块名称
 * @param user 账号名
 * @param passwd 账号密码
 * @param usages 授权使用情况
 * @return int 0：成功；-1：失败
 */
int RKAUTH_GetUsage(std::string module, std::string user, std::string passwd, RKAuthUsage& usages);

/**
 * @brief 获取授权次数（支持多个模块）
 *
 * @param module 授权模块名称（支持多个模块，每个模块之间使用','间隔）
 * @param user 账号名
 * @param passwd 账号密码
 * @param usages 各模块授权使用情况
 * @param num 模块数量
 * @return int 0：成功；-1：失败
 */
int RKAUTH_GetUsage(std::string module, std::string user, std::string passwd, RKAuthUsage usages[], int num);

/**
 * @brief 获取授权库版本
 *
 * @param version 版本号字符串
 * @return int 0：成功；-1：失败
 */
int RKAUTH_GetVersion(std::string& version);

#endif /* end of #ifndef __RKAUTH_TOOL_CXX_H__ */