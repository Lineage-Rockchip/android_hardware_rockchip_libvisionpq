# RK AIPQ SDK License 生成指南

本文介绍如何由RK提供的激活码和工具生成AIPQ SDK所需的license文件方法和命令。

[toc]

## 更新日志
- 2024.07.03 by Vance.wu: 更新了`vendor_storage`工具的使用说明
- 2024.06.04 by Vance.wu: 更新了授权工具日志返回的错误码对照表
- 2024.05.23 by Vance.wu: 更新了授权工具的使用命令；增加一条常见错误的解决提示
- 2024.04.11 by Vance.wu: 上传AIPQ SDK的初版授权工具使用指南


## 条件准备
在开始之前，需要确认以下条件满足：
1. 获得RK提供的权限激活账户或者激活码；
2. 获得RK提供的license生成工具`rkauth_tool`;
3. 获得RK提供的AIPQ算法库SDK;
4. 如果在**RK内网**进行授权，需要在执行激活程序的系统上设置一下授权服务器的IP：
	```shell
	# Android
	setprop persist.sys.rk.auth.ip 10.10.10.16
	# Linux
	export RKAUTH_IP=10.10.10.16
	# Windows
	set RKAUTH_IP=10.10.10.16
	```

## 执行流程和命令

以**PC宿主机为Window x64**，**设备为RK3588**为例，程序执行命令如下：

- 如果设备可以联网:
```shell
# 1. 宿主机进入到设备使用的程序路径
cd tools/rkauth_tool/bin/Android/arm64-v8a/
# 2. 将激活程序推到设备上
adb push rkauth_tool_bin /vendor/bin
adb push rkdevice_info /vendor/bin
# 3. 执行设备信息获取程，获取设备信息
adb shell "mkdir -p /data/vendor/rkalgo"
adb shell rkdevice_info /data/vendor/rkalgo/device.inf
# 3. 执行激活程序生成license, --user的参数填写RK提供的激活码
adb shell rkauth_tool_bin --type=1 --user="xxxx-active-code-xxxx" --module=pq --device_info="/data/vendor/rkalgo/device.inf" --output="/data/vendor/rkalgo/rk_aipq.lic"
```

- 如果设备不可以联网，要确PC保宿主机联网
```shell
# 1. 进入到PC宿主机使用的程序路径
cd tools/rkauth_tool/bin/Windows/x64/
# 2. 将设备信息获取程序推到设备上
adb push tools/rkauth_tool/bin/Android/arm64-v8a/rkdevice_info /vendor/bin
# 3. 执行设备信息获取程，获取设备信息
adb shell rkdevice_info /data/device.inf
# 4. 将设备信息拉出到PC宿主机当前路径
adb pull /data/device.inf ./
# 5. 使用PC宿主机的激活程序生成license， --user的参数填写RK提供的激活码
rkauth_tool_bin.exe --type=1 --user="xxxx-active-code-xxxx" --module=pq --output="./rk_aipq.lic" --device_info="./device.inf"
# 6. 将license文件推到设备上
adb shell "mkdir -p /data/vendor/rkalgo"
adb push ./rk_aipq.lic /data/vendor/rkalgo
```

## 使用`vendor_storage_tool`为量产设备写入激活码
使用`vendor_storage_tool`可以为 RK 平台的量产设备批量写入激活码。
注意：使用时可能需要获取设备的`root`权限。

```shell
# 将工具的可执行文件推到板端
cd tools/vendor_storage_tool/bin/Android/arm64-v8a/
adb push rk_vendor_storage_tool /vendor/bin
# 使用'-h'参数查看使用方法
adb shell rk_vendor_storage_tool -h
```

## 问题解决
### 常见授权失败问题
| 返回值 | 错误码 | 错误描述 | 解决方案 |
| --- | --- | --- | --- |
| -1 | RKAUTH_FAIL | 授权失败 | 未知 |
| -2 | RKAUTH_LICENSE_INVALID | 授权文件无效 | 检查授权文件(如`/data/vendor/rkalgo/rk_aipq.lic`)是否存在或有效 |
| -3 | RKAUTH_ACTIVATE_CODE_INVALID | 激活码无效 | 通过log检查读取到的激活码是否与RK提供的激活码一致 |
| -4 | RKAUTH_DEVICE_ACTIVATED | 设备已授权 | 无需其他操作 |
| -5 | RKAUTH_LICENSE_OUTDATE | 授权已过期 | 联系RK延长授权期限 |
| -6 | RKAUTH_ACCESS_FILE_ERROR | 授权文件访问失败 | 检查程序对授权文件是否有读写权限 |
| -7 | RKAUTH_GET_DEVICE_INFO_ERROR | 设备信息获取失败 | 可能与SELinux有关，尝试关闭SELinux |
| -8 | RKAUTH_NETWORK_ERROR | 网络相关错误 | 未联网；或处于RK内网时未设置授权服务器的IP；或非RK内网环境下却设置了RK内网的授权服务器的IP |
| -9 | RKAUTH_ACTIVATE_CODE_EXPIRED | 激活码失效 | 通过log检查读取到的激活码是否与RK提供的激活码一致，检查激活码对应的授权是否过期 |
| -10| RKAUTH_LICENSE_PARSE_ERROR | 授权文件解析错误 | 检查授权文件是否被修改或破坏，尝试删除授权文件并重新生成 |
| -11| RKAUTH_READ_VENDOR_STORAGE_ERROR | 读取`vendor_storage`错误 | 检查程序是否有对`vendor_storage`对应端口的读取权限 |

### 其他错误
1. 如果碰到类似于 `license_path can't write ./tmp.lic` 之类的错误提示，请优先检查输出文件和设备信息文件的路径是否正确，上级目录是否存在，相对于授权程序的路径需要使用`./`开头。