# Rockchip drm_pq_probe 工具使用指南

发布版本：V1.0.0

日期：2024-09-14

文件密级：□绝密   □秘密   □内部资料   ■公开

**免责声明**

本文档按“现状”提供，瑞芯微电子股份有限公司（“本公司”，下同）不对本文档的任何陈述、信息和内容的准确性、可靠性、完整性、适销性、特定目的性和非侵权性提供任何明示或暗示的声明或保证。本文档仅作为使用指导的参考。

由于产品版本升级或其他原因，本文档将可能在未经任何通知的情况下，不定期进行更新或修改。

**商标声明**

“Rockchip”、“瑞芯微”、“瑞芯”均为本公司的注册商标，归本公司所有。

本文档可能提及的其他所有注册商标或商标，由其各自拥有者所有。

**版权所有 © 2024 瑞芯微电子股份有限公司**

超越合理使用范畴，非经本公司书面许可，任何单位和个人不得擅自摘抄、复制本文档内容的部分或全部，并不得以任何形式传播。

瑞芯微电子股份有限公司

Rockchip Electronics Co., Ltd.

地址：     福建省福州市铜盘路软件园A区18号

网址：     [www.rock-chips.com](http://www.rock-chips.com)

客户服务电话： +86-4007-700-590

客户服务传真： +86-591-83951833

客户服务邮箱： [fae@rock-chips.com](mailto:fae@rock-chips.com)

---

**前言**

**概述**

本文主要介绍 Rockchip drm_pq_probe 工具的使用方法, drm_pq_probe 通过调用 libdrm 接口，获取用户态向内核下发的 hwpq 相关的 blob 属性, 解析后将其打印到控制台, 并支持在控制台中显示曲线。

**产品版本**

| **芯片名称** | **内核版本**     |
| ------------ | ---------------- |
| RK3576       | Linux kernel 6.1 及以上内核 |

**读者对象**

本文档（本指南）主要适用于以下工程师：

PQ 调试工程师

**修订记录**

| **版本号** | **作者** | **修改日期** | **修改说明** |
| ---------- | -------- | ------------ | ------------ |
| V1.0.0     | 王锦耀   | 2024-09-14   | 初始版本     |

---

**目录**

[TOC]

---

## 使用说明

将 drm_pq_probe push 到 /vendor/bin 目录下执行即可，需要注意的是 drm_pq_probe 需要运行在 root 权限下：

> adb root
> adb remount
> adb push drm_pq_probe /vendor/bin/drm_pq_probe
> adb shell -t "drm_pq_probe -h"

此时可以看到如下打印信息：

```
Usage: drm_pq_probe [options]
drm_pq_probe version: DrmPqProbe_v1.0.0
Options:
  -h,        show this help message and exit
  -m,        set curve mode, 0: print info, 1: show curve
  -s,        single run mode, print curve once and exit
  -d,        dump all pq-related info:
        1: get_all_info get all pq-related info
        2: get_drm_summary      get drm summary info
        3: get_drm_state        get drm state info
        4: get_drm_regs get drm regs info
        5: get_pq_props get pq props info
  -i,        set info type:
        0: all info             print all info
        1: dci_common           print dci common info
        2: dci_global           print dci global curve
        3: dci_local            print dci local curve
        4: dci_local_ratio      print dci local curve
        5: hdr_common           print hdr common info
        6: hdr_tone_curve       print hdr tone curve
        7: acm_common           print acm common info
        8: acm_y_delta          print acm y delta curve
        9: acm_h_delta          print acm h delta curve
        10: acm_s_delta         print acm s delta curve
        11: acm_y_gain          print acm y gain info
        12: acm_h_gain          print acm h gain info
        13: acm_s_gain          print acm s gain info
        14: shp_common          print shp common info
        15: csc_common          print csc common info
```

此时可以根据打印出的 help 信息继续输入操作命令，命令的详细说明如下：
- h: 打印 help 信息
- m: 设置曲线显示模式, 0 表示以打印数值的方式显示，1 表示以曲线图的方式显示，只有 dci_global, acm_y_delta, acm_h_delta, acm_s_delta 支持曲线显示，其他模式只会打印数值。
- x: 曲线显示模式，验 Y 轴方向拉伸的比例。
- r: 刷新当前打印信息。
- q: 退出 drm_pq_probe。
- i: 打印的 hwpq 信息类型:

| 输入数值 | 输出信息 |
| :---: | :--- |
0 | all info
1 | dci_common
2 | dci_global
3 | dci_local
4 | dci_local_ratio
5 | hdr_common
6 | hdr_tone_curve
7 | acm_common
8 | acm_y_delta
9 | acm_h_delta
10 | acm_s_delta
11 | acm_y_gain
12 | acm_h_gain
13 | acm_s_gain
14 | shp_common
15 | csc_common

- d: dump 一些常用的 debug 命令的结果:

| 输入数值 | 输出信息 |
| :---: | :--- |
1 | dump all info
2 | dump cmd "cat /d/dri/0/summary" result in drm_pq_probe
3 | dump cmd "cat /d/dri/0/state" result in drm_pq_probe
4 | dump cmd "cat /d/dri/0/regs" result in drm_pq_probe
5 | dump all props which has "pq" in name


也可以在启动 drm_pq_probe 时指定配置参数，参考命令如下:

> adb shell -t "drm_pq_probe -m 0 -i 15"

打印输出信息如下: 

```
set curve mode: 0
set info type: 15
Load /vendor/lib64/libdrm.so successed.
drm probe init success
ws_col=179, ws_row=52
curr_prop_info.cmd = 1280, csc_common      , print csc common info
has_valid_prop = 1
GET_CSC_COMMON
csc_en: 1
brightness: 256
contrast: 256
saturation: 256
hue: 256
r_gain: 256
g_gain: 256
b_gain: 256
r_offset: 256
g_offset: 256
b_offset: 256
```

启动时指定的参数**仅支持 -h, -m, -i, -s, -d 四个参数**，其中 -m, -i, -h, -d 参数含义上述已说明，-s 表示只运行一次的模式，当指定 -s 时，drm_pq_probe 进行一次打印后会自动退出, 不会再继续等待新的命令输入。

## 使用实例

### 打印不同模块common信息

在命令行输入以下命令：

   > adb shell -t "drm_pq_probe -i 15"

打印信息输出如下，显示的是当前 csc 模块的状态信息：

```
set curve mode: 0
set info type: 15
Load /vendor/lib64/libdrm.so successed.
drm probe init success
ws_col=179, ws_row=52
curr_prop_info.cmd = 1280, csc_common      , print csc common info
has_valid_prop = 1
GET_CSC_COMMON
csc_en: 1
brightness: 256
contrast: 256
saturation: 256
hue: 256
r_gain: 256
g_gain: 256
b_gain: 256
r_offset: 256
g_offset: 256
b_offset: 256
```

在命令行中再输入 `i 14`，打印信息如下，显示的是当前 sharp 模块的状态信息：

```
i 14
input_str = i 14

set info type: 14
curr_prop_info.cmd = 1024, shp_common      , print shp common info
has_valid_prop = 1
GET_SHP_COMMON
shp_en: 0x000005d9
peaking_gain: 96
```

在命令行输入 `q` 退出程序。

```
set info type: 14
curr_prop_info.cmd = 1024, shp_common      , print shp common info
has_valid_prop = 1
GET_SHP_COMMON
shp_en: 0x000005d9
peaking_gain: 96
q
input_str = q
```

### 打印不同模块曲线信息

在命令行输入以下命令：

   > adb shell -t "drm_pq_probe -m 0 -i 9"

打印信息如下，显示的是以数值打印形式显示的 acm_h_delta 信息：

```
set curve mode: 0
set info type: 9
Load /vendor/lib64/libdrm.so successed.
drm probe init success
ws_col=179, ws_row=52
curr_prop_info.cmd = 770, acm_h_delta     , print acm h delta curve
has_valid_prop = 1
GET_ACM_H_DELTA
ACM_h_delta:
1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 1, 3, 3, 3, 2, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
1,
```

在命令行中再输入 `m 1`, 此时显示信息如下，显示的是以曲线图形式显示的 acm_h_delta 信息：

```
⢀
⢸
⢸
⢸
⢸
⢸
⢸
⢸
⢸
⢸
⢸
⢸
⢸                             ⣀⣀⣀⡀
⣼⣤⣤⣤⣤⣤⣤⣤⣄⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣤⣊⣀⣀⣀⣈⣒⣤⣄⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣠⡄
⢸
⢸
⢸
⢸
⢸
⢸
⢸
⢸
⢸
⢸
⢸
⢸
⢸
```

在命令行中在输入 `i 2`, 此时显示信息如下，显示的是以曲线图形式显示的 dci_global 信息：

```




⢀                                                                                       ⢀⡀
⢸                                                                                    ⣀⠴⠚⠁
⢸                                                                                ⢀⡠⠖⠋
⢸                                                                             ⡠⠴⠚⠁
⢸                                                                         ⣀⠤⠖⠉
⢸                                                                     ⢀⡤⠔⠉
⢸                                                                 ⢀⣠⠔⠊⠁
⢸                                                              ⣀⡤⠒⠉
⢸                                                          ⢀⡠⠔⠉⠁
⢸                                                       ⣀⠤⠊⠉
⢸                                                   ⢀⣠⠔⠉⠁
⢸                                                ⢀⡤⠒⠁
⢸                                             ⣀⠴⠊⠁
⣼                                          ⣀⣔⣋
⢸                                       ⣠⠔⠉⠁
⢸                                    ⡠⠖⠉
⢸                                ⢀⡠⠒⠋
⢸                             ⢀⡤⠖⠉
⢸                          ⢀⠤⠒⠁
⢸                       ⣀⠤⠚⠁
⢸                   ⢀⣠⠔⠊⠁
⢸                ⣀⠤⠒⠉
⢸            ⣀⠤⠒⠉⠁
⢸        ⣀⡤⠖⠉
⢸    ⣀⡠⠔⠊
⢸⢀⣀⠔⠊⠁
⣼⣉⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⡀


```

在命令行输入 `m 0` 切换回数值打印模式，下图显示的是以数值打印形式显示的 dci_global 信息：

```
m 0
input_str = m 0

set curve mode: 1
curr_prop_info.cmd = 257, dci_global      , print dci global curve
has_valid_prop = 1
GET_DCI_GLOBAL_LUT
Get global lut finished 0x7fd5044150
DCI_global_lut:
0, 4, 8, 12, 17, 21, 25, 29, 33, 37, 41, 45, 49, 53, 57, 61,
65, 69, 72, 76, 80, 83, 87, 91, 94, 97, 102, 105, 109, 112, 115, 119,
122, 125, 130, 133, 136, 140, 143, 147, 150, 153, 158, 161, 164, 167, 171, 175,
178, 181, 185, 189, 192, 196, 199, 203, 206, 210, 214, 218, 222, 225, 230, 233,
237, 241, 246, 250, 255, 258, 262, 267, 271, 275, 280, 284, 288, 293, 298, 302,
306, 311, 315, 319, 324, 328, 333, 337, 342, 346, 351, 355, 360, 364, 369, 374,
378, 383, 387, 392, 397, 401, 405, 410, 414, 419, 424, 428, 433, 437, 441, 446,
450, 455, 460, 464, 469, 473, 477, 482, 486, 491, 495, 500, 505, 509, 513, 518,
522, 527, 531, 536, 540, 544, 548, 553, 557, 561, 566, 570, 574, 578, 583, 587,
591, 595, 600, 604, 608, 612, 616, 621, 625, 629, 633, 637, 641, 644, 649, 653,
657, 661, 665, 669, 673, 677, 681, 685, 689, 693, 696, 700, 705, 708, 712, 715,
719, 723, 727, 731, 735, 739, 743, 746, 750, 754, 758, 762, 766, 769, 773, 776,
780, 784, 788, 792, 795, 799, 803, 807, 810, 814, 818, 822, 825, 829, 832, 836,
840, 844, 847, 851, 855, 858, 862, 865, 869, 873, 877, 881, 885, 888, 892, 895,
899, 903, 907, 910, 914, 918, 922, 925, 929, 933, 937, 941, 945, 949, 953, 956,
960, 964, 968, 972, 976, 980, 984, 988, 992, 996, 1000, 1004, 1008, 1012, 1016, 1020,
```

在命令行输入 `q` 退出程序。

### 命令行直接以曲线图形式显示信息

在命令行输入以下命令：

   > adb shell -t "drm_pq_probe -m 1 -i 9"

打印信息如下，显示的是以曲线图形式显示的 acm_h_delta 信息：

```
⢀
⢸
⢸
⢸
⢸
⢸
⢸
⢸
⢸
⢸
⢸
⢸
⢸                             ⣀⣀⣀⡀
⣼⣤⣤⣤⣤⣤⣤⣤⣄⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣤⣊⣀⣀⣀⣈⣒⣤⣄⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣠⡄
⢸
⢸
⢸
⢸
⢸
⢸
⢸
⢸
⢸
⢸
⢸
⢸
⢸

```

在命令行输入 `q` 退出程序。

### 曲线缩放功能

在命令行输入以下命令来显示 acm_h_delta 信息：

   > adb shell -t "drm_pq_probe -m 1 -i 9"

```
⢀
⢸
⢸
⢸
⢸
⢸
⢸
⢸
⢸
⢸
⢸
⢸
⢸
⣸⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣤⣒⣒⣒⣒⣤⣤⣄⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⡀
⢸
⢸
⢸
⢸
⢸
⢸
⢸
⢸
⢸
⢸
⢸
⢸
⢸

```

此时显示的是以曲线图形式显示的 acm_h_delta 信息，此时可以输入 `x 2` 进行曲线缩放：

```
⢀
⢸
⢸
⢸
⢸
⢸
⢸
⢸
⢸
⢸
⢸
⢸
⢸                            ⢀⠤⠤⠤⢄
⣼⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣠⣤⣤⣤⣧⣒⣒⣒⣒⣭⣭⣖⣤⣤⣤⣤⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣠⡄
⢸
⢸
⢸
⢸
⢸
⢸
⢸
⢸
⢸
⢸
⢸
⢸
⢸

```

此时输入 `x 1` 进行曲线缩放回原大小：

```
⢀
⢸
⢸
⢸
⢸
⢸
⢸
⢸
⢸
⢸
⢸
⢸
⢸
⣼⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣠⣤⣤⣤⣧⣒⣒⣒⣒⣭⣭⣖⣤⣤⣤⣤⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣠⡄
⢸
⢸
⢸
⢸
⢸
⢸
⢸
⢸
⢸
⢸
⢸
⢸
⢸

```

在命令行输入 `q` 退出程序。

### 单次运行dump全部信息并保存到文件中

在命令行输入以下命令：
   
   > adb shell -t "drm_pq_probe -s -m 0 -i 0 -d 1 > /data/pq_info.txt"
   > adb pull /data/pq_info.txt ./

此时 drm_pq_probe 会打印全部信息并保存到文件中，并将文件从板子上拉取到本地。

## 注意事项

- drm_pq_probe 仅支持 RK3576  Android14 平台。
- drm_pq_probe 仅支持在 root 权限下运行。
