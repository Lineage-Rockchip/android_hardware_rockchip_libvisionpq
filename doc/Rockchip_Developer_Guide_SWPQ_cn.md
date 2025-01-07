# RK SW(SoftWare) PQ SDK 使用指南

发布版本：v1.2.5

发布日期：2025-03-07

文件密级：□绝密   □秘密   ■内部资料   □公开

---

**免责声明**

本文档按“现状”提供，瑞芯微电子股份有限公司（“本公司”，下同）不对本文档的任何陈述、信息和内容的准确性、可靠性、完整性、适销性、特定目的性和非侵权性提供任何明示或暗示的声明或保证。本文档仅作为使用指导的参考。

由于产品版本升级或其他原因，本文档将可能在未经任何通知的情况下，不定期进行更新或修改。

**商标声明**

“Rockchip”、“瑞芯微”、“瑞芯”均为本公司的注册商标，归本公司所有。

本文档可能提及的其他所有注册商标或商标，由其各自拥有者所有。

**版权所有** **© 2022 瑞芯微电子股份有限公司**

超越合理使用范畴，非经本公司书面许可，任何单位和个人不得擅自摘抄、复制本文档内容的部分或全部，并不得以任何形式传播。

瑞芯微电子股份有限公司

Rockchip Electronics Co., Ltd.

地址：     福建省福州市铜盘路软件园A区18号

网址：     [www.rock-chips.com](http://www.rock-chips.com)

客户服务电话： +86-4007-700-590

客户服务传真： +86-591-83951833

客户服务邮箱： [fae@rock-chips.com](mailto:fae@rock-chips.com)

---

**读者对象**

本文档主要适用于以下工程师：

- **Rockchip内部**技术支持工程师
- **Rockchip内部**软件开发工程师

**修订记录**

| **日期**   | **版本** | **适配SDK版本** |  **作者** | **审核**           | **修改说明**                    |
|:----------:|:--------:|:--------------:|:----------:|:-------:|:---------------------------------------- |
| 2022/08/18 | 1.0.0    | librkswpq_v6.0.0 (pre) | 吴方熠 | 夏海军 | 初始版本                                 |
| 2022/11/28 | 1.0.1    | librkswpq_v8.0.0 (pre) | 吴方熠 | 夏海军 | 增加支持图像格式和ZME模块，增加计算精度和性能 |
| 2023/04/11 | 1.1.0    | librkswpq v0.1.0 | 吴方熠 |   \  | 基于 pipeline 框架修改为通用版本              |
| 2024/06/27 | 1.2.0    | librkswpq v0.5.0 | 吴方熠 |   \  | 开发指南全面更新，增加新的模块说明和性能数据等 |
| 2024/07/15 | 1.2.1    | librkswpq v0.5.0 | 吴方熠 |   \  | 更新平台支持情况等数据 |
| 2024/08/01 | 1.2.2    | librkswpq v0.6.0 | 吴方熠 |   \  | 新增 `AI_DHW` 模块说明 |
| 2024/09/18 | 1.2.3    | librkswpq v0.10.0| 吴方熠 |   \  | API修改，对应内容补充；新增 `DCI_ACM` 模块相关说明；Android属性名称调整 |
| 2024/09/24 | 1.2.4    | librkswpq v0.11.0| 吴方熠 |   \  | API flag调整，信息更新 |
| 2025/02/24 | 1.2.5    | librkswpq v0.11.0| 周祥云 |   \  | 信息更新 |
| 2025/03/07 | 1.2.6    | librkswpq v0.17.0| 周祥云 |   \  | `CSC`模块数据更新 |

## 目 录

[TOC]

## 1. SDK介绍
### 1.1. 概述
SWPQ (SoftWare Picture Quality) 主要功能是利用软件对输出画质进行进一步改善，是现有各平台图像处理硬件 (RGA、IEP、VOP) 的补充。

目前 SWPQ 中大部分模块主要运行于在**GPU**设备上，部分AI模块（如：AIDM, AISD, AISR, MIXFE）还需要通过RKNN在**NPU**设备上运行。

### 1.2. Feature支持
- **数据格式**
  - 输入格式支持：
    - RGBA8888 / BGRA8888 / RGB888 / BGR888 / RGB565 / BGR565
    - YUV444SP_NV24 / YUV422SP_NV16 / YUV420SP_NV12 / YUV420SP_NV30 / YUV420SP_NV20 / YUV420SP_NV15 / YUV444I_VU24
    - Y8 / UV88
  - 输出格式支持：
    - RGBA8888 / BGRA8888 / RGB888 / BGR888 / RGB565 / BGR565
    - YUV444SP_NV24 / YUV422SP_NV16 / YUV420SP_NV12 / YUV420SP_NV30 / YUV420SP_NV20 / YUV420SP_NV15 / YUV444I_VU24
  - 分辨率支持：
    - 理论最低: 128x128
    - 理论最高: 16384x16384, 高于 8K(7680x4320) 分辨率暂未经过验证
  - 当前版本**只支持Non-FBC格式**，FBC格式目前不支持
<br>

- **色域变换模块(Corlor Space Convert, CSC)**
  - 支持 Y2R, Y2Y, R2Y, R2R
  - 支持 YCbCr BT.601 / BT.709 完整特性
  - 支持 Full-Range / Limited-Range 相互转换
  - 支持调整亮度、色调、对比度、饱和度、色温和颜色增益
<br>

<!-- - 图像格式转换模块(Format Convert, CVT)
  - 主要用于同类图像格式下不同通道间的转换(Y2Y/R2R)，如NV12到NV24, RGBA到RGB等
  - 内部模块，无需特别指定参数 -->

- **动态对比度模块(Dynamic Contrast Improvement, DCI)**
  - 支持全局动态对比度调整
  - 支持调整亮区/暗区对比度增益
<br>

- **自动色彩管理模块(Auto Color Management, ACM)**
  - 支持自动调整亮度、色调、饱和度
  - 支持特定亮度、色调、饱和度改变
<br>

- **缩放管理引擎模块(Zoom Manage Engine, ZME)**
  - 支持任意倍率缩放
  - 支持deringing功能
<br>

- **锐化(Sharpen, SHP)**
  - 支持全局清晰度调整
  - 支持调整 coring / gain / limit 等相关配置
<br>

- **CGC**
  - 色域转换功能和类纸模式
  - 支持配置3x3色域转换矩阵
  - 支持配置色温校正的Rgain 和 Bgain
  - 支持类纸纹理效果，纹理样式和纹理强度可配，可与色域转换功能同时开启
<br>

<br>

- **AI超分辨率模块(AI Super Resolution, AI-SR)**
  - 超分辨率放大，**仅支持2倍率放大**
  - ~~方向滤波 + 双三次插值, 支持任意分辨率输入~~ （暂不支持）
  - **RK3588**平台仅支持分辨率 1080P => 4K (RKNN版本需大于等于1.4)
  - **RK356X**平台仅支持分辨率 540P => 1080P (RKNN版本需大于等于1.4)
<br>

- **AI场景检测模块(AI Scene Detection, AI-SD)**
  - 用于场景检测，目前支持场景分类: 自然 / 文字
  - 目前主要用于辅助其他模块(AISR)搭配使用
  - 支持**RK3588**平台(RKNN版本需大于等于1.4), **RK3576**(RKNN版本需大于等于2.0)
<br>

- **AI去噪模块(AI DeMosquito, AI-DM)**
  - 去蚊虫噪声, 主要用于处理压缩率比较高的图像，或码率较低的视频
  - 应用项目：云办公场景等
  - 仅支持分辨率为**1080P**的**YUV**图像输入输出
  - 仅支持**RK356X**平台(RKNN版本需大于等于1.4)
<br>

- **AI去伪色模块(AI DeFalseColor, AI-DFC)**
  - 用于从YUV420转换至YUV444场景，还原YUV420丢失的颜色信息
  - 支持**RK3588**(RKNN版本需大于等于1.5), **RK3576**(RKNN版本需大于等于2.0)
<br>

- **AI文档检测模块(AI Document Detection, AI-DD)**
  - 检测图像内的文档区域，得到四个顶点
  - 支持**RK3588**(RKNN版本需大于等于1.5), **RK3576**(RKNN版本需大于等于2.0)
<br>

- **AI文档增强模块(AI Document Enhancement, AI-DE)**
  - 将带有四个顶点信息的文档图像变换为正投影，并进行AI文档增强
  - 支持**RK3588**(RKNN版本需大于等于1.5), **RK3576**(RKNN版本需大于等于2.0)
<br>

- **AI文档手写擦除模块(AI DeHandWriting, AI-DHW)**
  - 将文档增强后的图像进行手写文字擦除，还原文档/试卷的原貌
  - 支持**RK3576**(RKNN版本需大于等于2.0)
<br>

- **AI人脸增强混合模块(Mixture Face Enhancement, Mix-FE)**
  - 人脸检测+增强+4x放大
  - 仅支持**RK3588**(RKNN版本需大于等于1.5)
<br>

- **AI视频插帧混合模块(Mix-MSSR)**
  - 支持MEMC,SD,SR,DC等，24/25/30/50/60 fps => 60fps
  - 支持**RK3588**(RKNN版本需大于等于2.0)，支持**RK3576**(RKNN版本需大于等于2.0)
<br>

### 1.3. 平台支持情况和特殊硬件需求
| **平台支持情况** | RK3588 | RK3576 | RK356X | RK3399 | ... |
|:----------------|:------:|:------:|:------:|:------:|:---:|
| Android         | ✔️     | ✔️    | ✔️     | ✔️    | ... |
| Linux           | ✔️     | ✔️    | ✔️     | TBD   | ... |

| **特殊硬件需求**   | **说明**                  |
| --- | ------------------------------------ |
| GPU | 绝大部分模块运行于GPU，需求OpenCL 2.0及以上 |
| NPU | AISR/AISD等模块需NPU硬件，RKNN 1.4及以上版本，部分AI模块需要2.0以上版本 |

注：
1. 部分非AI模块在RK356X和RK3399平台上不支持
2. 因为RKNN模型与平台强相关，所以AI模块的支持与否也与平台强相关
3. 每个模块对所支持的平台上实测数据记录在对应模块的**支持平台及性能数据参考**小节内容中，若表中标注`N/A`则表示对应的平台或对应图像分辨率通路不支持。


## 2. 模块数据汇总
### 2.1. 各模块理论数据汇总
| 模块 | GPU算力[FLOPS] | NPU算力[FLOPS] |  GPU带宽[MB/帧] | NPU带宽[MB/帧] | 总带宽[MB/帧] | 总带宽备注 |
|:----:|----------------| ---------------|:-----------------|:---------------|:-------------|:----------|
| CSC  | 3.0G | \ | 3+3=6 | \      | 6   | 1080P NV12 => 1080P NV12 |
| DCI  | 0.6G | \ | 4+2=6 | \      | 6   | 1080P NV12 => 1080P NV12, 仅计算Y通道 |
| ACM  | 6.0G | \ | 3+3=6 | \      | 6   | 1080P NV12 => 1080P NV12 |
| SHP  | 9.5G | \ | 2+2=4 | \      | 4   | 1080P NV12 => 1080P NV12, 仅计算Y通道 |
| CGC  | 5.5G | \ | 6+6=12 |  \    | 12  | 1080P RGB => 1080P RGB |
| ZME  | 40.7G | \ | 9+18=27 | \    | 27  | 1080P NV12 => 4K NV12 |
| AISR | 16G | TBD | 27+28=55 | 180 | 205 | 1080P NV12 => 4K NV12 |
| AISD | 0.1G | TBD | 3+0=3 | 2      |  5  | 1080P NV12 input |
| AIDM | 22.5G | TBD | 4+2=6 | 15     | 21  | 1080P NV12 => 1080P NV12, 仅计算Y通道 |
| AIDFC| TBD | TBD | 3+6=9 | 24 | 33 | 1080P NV12 => 1080P NV24或RGBA |
| AIDE | TBD | TBD | TBD | TBD | TBD | TBD |
| AIDD | TBD | TBD | TBD | TBD | TBD | TBD |
| AIDHW | TBD | TBD | TBD | TBD | TBD | TBD |
| MixFE | TBD | TBD |   TBD   | ~430 |   TBD    | 540P  NV12 => 4K NV12; 异步模式，延迟1帧 |
| MixMSSR | TBD | TBD | 5+6=11 <br><br> 6+6=12 <br><br> 9+6=15 <br><br> 9+12=21 <br><br> 36+24=60 <br><br> 71+47=118 <br><br> 71+47=118 | 21 <br><br> 21 <br><br> 23 <br><br> 35 <br><br> 18 <br><br> 18 <br><br> 18 | 32 <br><br> 43 <br><br> 38 <br><br> 56 <br><br> 78 <br><br> 136 <br><br> 136 | 3x540P NV24 => 2x1080P NV12;异步延迟2帧 <br> 3x720P Y+C => 2x1080P NV12;异步延迟2帧 <br> 3x1080P NV12 => 2x1080P NV12;异步延迟2帧 <br> 3x1080P NV12 => 1x4K NV12;异步延迟2帧 <br> 3x4K NV12 => 2x4K NV12;异步延迟2帧  <br> 3x4K NV24 => 2x4K NV24;异步延迟2帧 <br> 3x4K RGB => 2x4K RGB;异步延迟2帧  |

注：
1. 算力（以60pfs计）和带宽数据根据右侧备注中输入输出图像和格式计算得到
2. GPU带宽数据格式为"**输入带宽 + 输出带宽 = 总带宽**"
3. 以上理论数值跟实际测量情况可能存在差异

### 2.2. 各模块支持的输入/输出图像格式
| 模块 | 是否支持ROI | 支持的输入/输出格式 | 备注 |
|:----:|:-----------:|:------------------|:------|
| CSC  | 否 | 输入: YUV4xxSP_8bit, YUV4xxSP_10bit, YUV444I_VU24, API中所有RGB系列 <br> 输出: YUV4xxSP_8bit, YUV4xxSP_10bit, YUV444I_VU24, API中所有RGB系列 | 一般情况下输出格式或色彩空间和输入不同 |
| DCI  | 是 | 输入: YUV4xxSP_8bit, YUV444I_VU24, Y8 <br> 输出: YUV4xxSP_8bit, YUV444I_VU24, Y8 | 输出格式和输入相同，只处理Y通道 |
| ACM  | 否 | 输入: YUV4xxSP_8bit, YUV444I_VU24 <br> 输出: YUV4xxSP_8bit, YUV444I_VU24 | 输出格式和输入相同 |
| SHP  | 否 | 输入: YUV4xxSP_8bit, YUV444I_VU24, Y8 <br> 输出: YUV4xxSP_8bit, YUV444I_VU24, Y8 | 输出格式和输入相同，只处理Y通道，full-range |
| CGC  | 否 | 输入: RGB(A)888(8) <br> 输出:  RGB(A)888(8) | 一般情况下输出格式或色彩空间和输入相同 |
| ZME  | 否 | 输入: YUV4xxSP_8bit, YUV444I_VU24, API中所有RGB系列, Y8, UV8 <br> 输出: YUV4xxSP_8bit, YUV444I_VU24, API中所有RGB系列, Y8, UV8 | 一般不改变输入格式，注5 |
| AISR | 是 | 输入: YUV4xxSP_8bit, YUV444I_VU24, Y8 <br> 输出: YUV4xxSP_8bit, YUV444I_VU24, Y8 | 一般不改变输入格式，注5 |
| AISD | 否 | 输入: YUV4xxSP_8bit, YUV444I_VU24, API中所有RGB系列 <br> 输出: 各场景和类别得分 | 无图像对象输出 |
| AIDM | 是 | 输入: YUV4xxSP_8bit, Y8 <br> 输出: YUV4xxSP_8bit, Y8 | 输出格式和输入相同，只处理Y通道 |
| AIDFC| 是 | 输入: YUV420SP_NV12 <br> 输出: YUV444SP_NV24, RGBA8888 | \ |
| AIDE | 否 | 输入: YUV420SP_NV12, RGB[A8]888 <br> 输出: YUV420SP_NV12 | \ |
| AIDD | 否 | 输入: YUV4xxSP_8bit, RGB[A8]888, Y8 <br> 输出: YUV4xxSP_8bit, RGB[A8]888, Y8 | 输出格式和输入相同 |
| AIDHW| 否 | 输入: YUV4xxSP_8bit, RGB[A8]888, Y8 <br> 输出: YUV4xxSP_8bit, RGB[A8]888, Y8 | 输出格式和输入相同 |
| MixSHPACM | 否 | 输入: YUV420SP_NV12, RGBA8888 <br> 输出: YUV420SP_NV12 | \ |
| MixFE | 否 | 输入: 540p YUV420SP_NV12 <br> 输出: 4k YUV420SP_NV12 | 只支持指定的分辨率和指定的输入输出格式 |
| MixMSSR | 否 | 输入 $\xrightarrow{主要算法处理}$ 输出： <br> 540pNV24 $\xrightarrow{SD+DC+SR+MEMC}$ 1080pNV12 <br> 720pY8+UV88 $\xrightarrow{SD+DC+SR+MEMC}$ 1080pNV12 <br> 1080pNV12 $\xrightarrow{SD+DC+SR+MEMC}$ 1080pNV12 <br> 1080pNV24 $\xrightarrow{SD+DC+SR+MEMC}$ 1080pNV24 <br> 1080pRGB $\xrightarrow{SD+MEMC}$ 1080pRGB <br> 1080pNV12 $\xrightarrow{SD+DC+SR}$ 4kNV12 <br> 540pNV24 $\xrightarrow{SR+MEMC+FE}$ 1080pNV12 <br> 4kNV12 $\xrightarrow{SD+MEMC}$ 4kNV12 <br> 4kNV24 $\xrightarrow{SD+MEMC}$ 4kNV24 <br> 4kRGB $\xrightarrow{SD+MEMC}$  4kRGB| 只支持指定的分辨率和指定的输入输出格式 |

注：
1. `YUV4xxSP_8bit`表示`YUV420SP_NV12, YUV422SP_NV16, YUV444SP_NV24`均支持。
2. `API中所有RGB系列`表示`RGBA8888, RGB888, RGB565`以及对应BGR通道顺序的格式。
3. 以上表中所有`RGB`系列格式均包含了其对应的`BGR`通道顺序的格式。
4. `RGB565`等`packed`格式的图像格式，通道排列顺序遵循`Most Significant Byte(MSB)`优先原则。
5. 由于`ZME`/`AISR`模块对亮度和色度模块的缩放是分离执行的，故在做缩放的同时也支持`YUV4xxSP_8bit`表示的格式之间相互转换，但不能转变色彩空间。
6. 除`CSC`模块是明确转换色彩空间的功能，输出无论是**Full-Range**还是**Limited-Range**，都可以保证其取值范围是正确的。但其他模块默认输入输出的色彩空间是**Full-Range**，故强烈建议对**Limited-Range**的输入图像过一次`CSC`模块先转到**Full-Range**，再进行后续模块的处理; **Limited-Range**的输出对这些模块来说不能保证还是**Limited-Range**。
7. 大部分**非AI模块**基本只支持**YUV Full-Range**输入，大部分**AI模块**还支持**RGB Full-Range**输入。


### 2.3. 各模块详细性能数据

注：
1. 以下表中符号`N/A`表示该模块在对应平台或对应分辨率情况下不支持；
2. 以下表中符号`TBD`表示该模块在对应平台或对应分辨率情况下未经过测试，数据缺失；
3. 如果AI模块的性能不符合预期，大概率和`librknnrt.so`的版本有关系，可以将板上`librknnrt.so`版本切换到模块对应模型编译的版本再次测试。（比如低版本的多核模型在高版本`librknnrt.so`环境中运行时，可能无法跑多核）

#### CSC 模块
##### CSC 色彩空间转换支持说明
- `RKPQ_CLR_SPC_YUV_601_LIMITED`
- `RKPQ_CLR_SPC_YUV_601_FULL`
- `RKPQ_CLR_SPC_YUV_709_LIMITED`
- `RKPQ_CLR_SPC_YUV_709_FULL`
- ~~`RKPQ_CLR_SPC_YUV_2020_LIMITED`~~
- ~~`RKPQ_CLR_SPC_YUV_2020_FULL`~~
- `RKPQ_CLR_SPC_RGB_LIMITED`
- `RKPQ_CLR_SPC_RGB_FULL`

注：以上8个色彩空间中，除 `RKPQ_CLR_SPC_YUV_2020_LIMITED` 和 `RKPQ_CLR_SPC_YUV_2020_FULL`两种色彩空间暂不支持外，其他的色彩空间之间可以任意互相转换。

##### CSC 输入输出格式支持
| 输入\输出格式 | NV24 | NV16 | NV12 | NV30 | NV20 | NV15 | VU24 | VU30 | Y8 | UV88 | VU88 | LEGACY420 | RGBA | BGRA | RGB | BGR | RGB565 | BGR565 |
| ------------ |:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:--:|:----:|:----:|:---------:|:----:|:----:|:---:|:---:|:------:|:------:|
| (0) NV24     |  ✔️ |  ✔️  |  ✔️ |  ✔️ |  ✔️  |  ✔️  |  ✔️ |  ✔️ | ❌ |  ❌  |  ❌  |    ❌    |  ✔️  |  ✔️ | ✔️ | ✔️  |  ✔️   |  ✔️   |
| (1) NV16     |  ✔️ |  ✔️  |  ✔️ |  ✔️ |  ✔️  |  ✔️  |  ✔️ |  ✔️ | ❌ |  ❌  |  ❌  |    ❌    |  ✔️  |  ✔️ | ✔️ | ✔️  |  ✔️   |  ✔️   |
| (2) NV12     |  ✔️ |  ✔️  |  ✔️ |  ✔️ |  ✔️  |  ✔️  |  ✔️ |  ✔️ | ❌ |  ❌  |  ❌  |    ❌    |  ✔️  |  ✔️ | ✔️ | ✔️  |  ✔️   |  ✔️   |
| (3) NV30     |  ✔️ |  ❌  |  ❌ |  ❌ |  ❌  |  ❌  |  ✔️ |  ✔️ | ❌ |  ❌  |  ❌  |    ❌    |  ❌  |  ❌ | ❌ | ❌  |  ❌   |  ❌   |
| (4) NV20     |  ✔️ |  ❌  |  ❌ |  ❌ |  ❌  |  ❌  |  ✔️ |  ✔️ | ❌ |  ❌  |  ❌  |    ❌    |  ❌  |  ❌ | ❌ | ❌  |  ❌   |  ❌   |
| (5) NV15     |  ✔️ |  ❌  |  ❌ |  ❌ |  ❌  |  ❌  |  ✔️ |  ✔️ | ❌ |  ❌  |  ❌  |    ❌    |  ❌  |  ❌ | ❌ | ❌  |  ❌   |  ❌   |
| (10) VU24    |  ✔️ |  ✔️  |  ✔️ |  ✔️ |  ✔️  |  ✔️  |  ✔️ |  ✔️ | ❌ |  ❌  |  ❌  |    ❌    |  ✔️  |  ✔️ | ✔️ | ✔️  |  ✔️   |  ✔️   |
| (11) VU30    |  ✔️ |  ✔️  |  ✔️ |  ✔️ |  ✔️  |  ✔️  |  ✔️ |  ✔️ | ❌ |  ❌  |  ❌  |    ❌    |  ✔️  |  ✔️ | ✔️ | ✔️  |  ✔️   |  ✔️   |
| (12) Y8      |  ❌ |  ❌  |  ❌ |  ❌ |  ❌  |  ❌  |  ❌ |  ❌ | ❌ |  ❌  |  ❌  |    ❌    |  ❌  |  ❌ | ❌ | ❌  |  ❌   |  ❌   |
| (13) UV88    |  ❌ |  ❌  |  ❌ |  ❌ |  ❌  |  ❌  |  ❌ |  ❌ | ❌ |  ❌  |  ❌  |    ❌    |  ❌  |  ❌ | ❌ | ❌  |  ❌   |  ❌   |
| (14) VU88    |  ❌ |  ❌  |  ❌ |  ❌ |  ❌  |  ❌  |  ❌ |  ❌ | ❌ |  ❌  |  ❌  |    ❌    |  ❌  |  ❌ | ❌ | ❌  |  ❌   |  ❌   |
| (15) LEGACY420| ✔️ |  ✔️  |  ✔️ |  ❌ |  ❌  |  ❌  |  ❌ |  ❌ | ❌ |  ❌  |  ❌  |    ❌    |  ❌  |  ❌ | ❌ | ❌  |  ❌   |  ❌   |
| (1000) RGBA   | ✔️ |  ✔️  |  ✔️ |  ❌ |  ❌  |  ❌  |  ✔️ |  ✔️ | ❌ |  ❌  |  ❌  |    ❌    |  ✔️  |  ✔️ | ✔️ | ✔️  |  ✔️   |  ✔️   |
| (1001) BGRA   | ✔️ |  ✔️  |  ✔️ |  ❌ |  ❌  |  ❌  |  ✔️ |  ✔️ | ❌ |  ❌  |  ❌  |    ❌    |  ✔️  |  ✔️ | ✔️ | ✔️  |  ✔️   |  ✔️   |
| (1002) RGB    | ✔️ |  ✔️  |  ✔️ |  ❌ |  ❌  |  ❌  |  ✔️ |  ✔️ | ❌ |  ❌  |  ❌  |    ❌    |  ✔️  |  ✔️ | ✔️ | ✔️  |  ✔️   |  ✔️   |
| (1003) BGR    | ✔️ |  ✔️  |  ✔️ |  ❌ |  ❌  |  ❌  |  ✔️ |  ✔️ | ❌ |  ❌  |  ❌  |    ❌    |  ✔️  |  ✔️ | ✔️ | ✔️  |  ✔️   |  ✔️   |
| (1004) RGB565 | ✔️ |  ✔️  |  ✔️ |  ❌ |  ❌  |  ❌  |  ✔️ |  ✔️ | ❌ |  ❌  |  ❌  |    ❌    |  ✔️  |  ✔️ | ✔️ | ✔️  |  ✔️   |  ✔️   |
| (1005) BGR565 | ✔️ |  ✔️  |  ✔️ |  ❌ |  ❌  |  ❌  |  ✔️ |  ✔️ | ❌ |  ❌  |  ❌  |    ❌    |  ✔️  |  ✔️ | ✔️ | ✔️  |  ✔️   |  ✔️   |

:warning:注：
- `YU24、YU16、YU12、YUYV`等格式暂不支持

##### CSC 支持平台及性能数据参考
| 平台 | GPU型号与频率 | 输入图像分辨率和格式 | 固定帧率[fps] | GPU占用率[%] | 带宽占用[MB/s] | 耗时[ms] |
|:---- |:------------ |:------------------- |:-------------:|:-----------:|:-------------:|:--------:|
|RK3399| Mali-T860 MP4 @800MHz | 1920x1080 NV12 => RGB | 60 | 27 | cpu-200, gpu-280 | 6.5 |
|RK3568| Mali-G52 2EE @800MHz  | 960x540 NV16 => NV24  | 60 | 11 | cpu-240, gpu-105 | 3.5 |
| ^    | ^                     | 1920x1080 NV12 => RGB | 60 | 30 | cpu-240, gpu-370 | 7.0 |
| ^    | ^                     | 1920x1080 RGB => NV24 | 60 | 40 | cpu-240, gpu-500 | 8.5 |
|RK3588| Mali-G610 MC4 @1000MHz| 1920x1080 NV12 => RGB | 60 | 5  | gpu-560  | 2.0 |
| ^    | ^                     | 3840x2160 RGB => NV12 | 60 | 15 | gpu-2250 | 3.5 |
| ^    | ^                     | 3840x2160 Legacy420 => NV12 | 60 | 16 | TBD | 3.0 |
| ^    | ^                     | 3840x2160 Legacy420 => NV24 | 60 | 25 | TBD | 4.5 |
|RK3576|Mali-G52 MC4EE2 @800MHz| 最大4K, IP support<br>(online display) | IP support | IP support | IP support | IP support |
| ^    | ^                     | 3840x2160 Legacy420 => NV12 | 60 | 33 | TBD | 6.5 |
| ^    | ^                     | 3840x2160 Legacy420 => NV24 | 60 | 45 | TBD | 8.5 |

#### DCI 模块
##### DCI 支持平台及性能数据参考
(`html`表格。如显示异常，请更换支持`html`的`Markdown`渲染器)
<table>
  <tr align="center">
    <td rowspan="2"><b>平台</b></td>
    <td rowspan="2"><b>GPU型号与频率</b></td>
    <td rowspan="2"><b>输入图像分辨率和格式</b></td>
    <td rowspan="2"><b>固定帧率[fps]</b></td>
    <td rowspan="1" colspan="3"><b>性能数据<b> (performance mode)</td>
    <tr align="center">
      <td><b>GPU占用率[%]</b></td>
      <td><b>带宽占用[MB/s]</b></td>
      <td><b>耗时[ms]</b></td>
    </tr>
  </tr>
  <!-- RK3399 -->
  <tr align="center">
    <td>RK3399</td>
    <td>Mali-T860 MP4 @800MHz</td>
    <td>1920x1080, NV12</td>
    <td>60</td>
    <td>32</td>
    <td>cci-300, gpu-190</td>
    <td>4.5 + 4.5</td>
  </tr>
  <!-- RK3568 -->
  <tr align="center">
    <td rowspan="2">RK3568</td>
    <td rowspan="2">Mali-G52 2EE @800MHz</td>
    <td>960x540, NV16</td>
    <td>30</td>
    <td>45</td>
    <td>cpu-200, gpu-30</td>
    <td>16.5 + 2.5</td>
      <tr align="center">
        <td>1920x1080, NV12</td>
        <td>60</td>
        <td>55</td>
        <td>cpu-400, gpu-250</td>
        <td>8.0 + 5.0</td>
      </tr>
  </tr>
  <!-- RK3588 -->
  <tr align="center">
    <td rowspan="2">RK3588</td>
    <td rowspan="2">Mali-G610 MC4 @1000MHz</td>
    <td>1920x1080, NV12</td>
    <td>60</td>
    <td>7</td>
    <td>gpu-370</td>
    <td>1.5 + 1.0</td>
      <tr align="center">
        <td>3840x2160, NV24</td>
        <td>60</td>
        <td>23</td>
        <td>gpu-1480</td>
        <td>2.5 + 2.0</td>
      </tr>
  </tr>
  <!-- RK3576 -->
  <tr align="center">
    <td>RK3576</td>
    <td>Mali-G52 MC4EE2 @800MHz</td>
    <td>最大4K, IP support <br> (online display) </td>
    <td>IP support</td>
    <td>IP support</td>
    <td>IP support</td>
    <td>IP support</td>
  </tr>
</table>

注：
1. DCI 的耗时部分由 $a + b$ 两部分组成，其中 $a$ 表示单独进行前处理直方图统计的耗时，$b$ 表示实际 DCI 查表操作的耗时;
2. DCI 前面有 CSC 模块的话，在常见格式输入的情况下，$a$ 部分耗时可以省略;

#### ACM 模块
##### ACM 支持平台及性能数据参考
(`html`表格。如显示异常，请更换支持`html`的`Markdown`渲染器)
<table>
  <tr align="center">
    <td rowspan="2"><b>平台</b></td>
    <td rowspan="2"><b>GPU型号与频率</b></td>
    <td rowspan="2"><b>输入图像分辨率和格式</b></td>
    <td rowspan="2"><b>固定帧率[fps]</b></td>
    <td rowspan="1" colspan="3"><b>性能数据<b> (performance mode)</td>
    <tr align="center">
      <td><b>GPU占用率[%]</b></td>
      <td><b>带宽占用[MB/s]</b></td>
      <td><b>耗时[ms]</b></td>
    </tr>
  </tr>
  <!-- RK3399 -->
  <tr align="center">
    <td>RK3399</td>
    <td>Mali-T860 MP4 @800MHz</td>
    <td>N/A</td>
    <td>N/A</td>
    <td>N/A</td>
    <td>N/A</td>
    <td>N/A</td>
  </tr>
  <!-- RK3568 -->
  <tr align="center">
    <td rowspan="2">RK3568</td>
    <td rowspan="2">Mali-G52 2EE @800MHz</td>
    <td>960x540, NV16</td>
    <td>60</td>
    <td>11</td>
    <td>cpu-180, gpu-85</td>
    <td>3.5</td>
      <tr align="center">
        <td>1920x1080, NV12</td>
        <td>60</td>
        <td>31</td>
        <td>cpu-180, gpu-250</td>
        <td>7.0</td>
      </tr>
  </tr>
  <!-- RK3588 -->
  <tr align="center">
    <td rowspan="2">RK3588</td>
    <td rowspan="2">Mali-G610 MC4 @1000MHz</td>
    <td>1920x1080, NV12</td>
    <td>60</td>
    <td>4</td>
    <td>gpu-380</td>
    <td>1.5</td>
      <tr align="center">
        <td>3840x2160, NV24</td>
        <td>60</td>
        <td>21</td>
        <td>gpu-3000</td>
        <td>4.0</td>
      </tr>
  </tr>
  <!-- RK3576 -->
  <tr align="center">
    <td>RK3576</td>
    <td>Mali-G52 MC4EE2 @800MHz</td>
    <td>最大4K, IP support <br> (online display) </td>
    <td>IP support</td>
    <td>IP support</td>
    <td>IP support</td>
    <td>IP support</td>
  </tr>
</table>

#### ZME 模块
##### ZME 支持平台及性能数据参考
(`html`表格。如显示异常，请更换支持`html`的`Markdown`渲染器)
<table>
  <tr align="center">
    <td rowspan="2"><b>平台</b></td>
    <td rowspan="2"><b>GPU型号与频率</b></td>
    <td rowspan="2"><b>输入（输出）图像分辨率和格式</b></td>
    <td rowspan="2"><b>固定帧率[fps]</b></td>
    <td rowspan="1" colspan="3"><b>性能数据<b> (performance mode)</td>
    <tr align="center">
      <td><b>GPU占用率[%]</b></td>
      <td><b>带宽占用[MB/s]</b></td>
      <td><b>耗时[ms]</b></td>
    </tr>
  </tr>
  <!-- RK3399 -->
  <tr align="center">
    <td>RK3399</td>
    <td>Mali-T860 MP4 @800MHz</td>
    <td>1920x1080 => 3840x2160, Y8</td>
    <td>20</td>
    <td>79</td>
    <td>cci-150, gpu-1200</td>
    <td>46.0</td>
  </tr>
  <!-- RK3568 -->
  <tr align="center">
    <td rowspan="2">RK3568</td>
    <td rowspan="2">Mali-G52 2EE @800MHz </td>
    <td>960x540 => 1920x1080, NV16</td>
    <td>30</td>
    <td>53</td>
    <td>cpu-320, gpu-190</td>
    <td>24.0</td>
      <tr align="center">
        <td>1920x1080 => 3840x2160, NV12</td>
        <td>15</td>
        <td>86</td>
        <td>cpu-160, gpu-285</td>
        <td>64.0</td>
      </tr>
  </tr>
  <!-- RK3588 -->
  <tr align="center">
    <td rowspan="2">RK3588</td>
    <td rowspan="2">Mali-G610 MC4 @1000MHz</td>
    <td>960x540 => 1920x1080, NV16</td>
    <td>60</td>
    <td>10</td>
    <td>gpu-570</td>
    <td>3.5</td>
    <tr align="center">
      <td>1920x1080 => 3840x2160, NV12</td>
      <td>60</td>
      <td>28</td>
      <td>gpu-1680</td>
      <td>6.5</td>
    </tr>
  </tr>
  <!-- RK3576 -->
  <tr align="center">
    <td>RK3576</td>
    <td>Mali-G52 MC4EE2 @800MHz</td>
    <td>最大1080P,IP support <br> (Y/UV separated, online display)</td>
    <td>IP support</td>
    <td>IP support</td>
    <td>IP support</td>
    <td>IP support</td>
  </tr>
</table>

#### SHP 模块
##### SHP 支持平台及性能数据参考
(`html`表格。如显示异常，请更换支持`html`的`Markdown`渲染器)
<table>
  <tr align="center">
    <td rowspan="2"><b>平台</b></td>
    <td rowspan="2"><b>GPU型号与频率</b></td>
    <td rowspan="2"><b>输入图像分辨率和格式</b></td>
    <td rowspan="2"><b>固定帧率[fps]</b></td>
    <td rowspan="1" colspan="3"><b>性能数据<b> (performance mode)</td>
    <tr align="center">
      <td><b>GPU占用率[%]</b></td>
      <td><b>带宽占用[MB/s]</b></td>
      <td><b>耗时[ms]</b></td>
    </tr>
  </tr>
  <!-- RK3399 -->
  <tr align="center">
    <td>RK3399</td>
    <td>Mali-T860 MP4 @800MHz</td>
    <td>N/A</td>
    <td>N/A</td>
    <td>N/A</td>
    <td>N/A</td>
    <td>N/A</td>
  </tr>
  <!-- RK3568 -->
  <tr align="center">
    <td rowspan="2">RK3568</td>
    <td rowspan="2">Mali-G52 2EE @800MHz</td>
    <td>960x540, NV16 (Lite版本)</td>
    <td>60</td>
    <td>12</td>
    <td>cp-180, gpu-40</td>
    <td>3.5</td>
      <tr align="center">
        <td>1920x1080, NV12 (Lite版本)</td>
        <td>60</td>
        <td>50</td>
        <td>cp-180, gpu-170</td>
        <td>10.0</td>
      </tr>
  </tr>
  <!-- RK3588 -->
  <tr align="center">
    <td rowspan="2">RK3588</td>
    <td rowspan="2">Mali-G610 MC4 @1000MHz</td>
    <td>1920x1080, NV12</td>
    <td>60</td>
    <td>7</td>
    <td>gpu-280</td>
    <td>2.0</td>
    <tr align="center">
      <td>3840x2160, NV24</td>
      <td>60</td>
      <td>23</td>
      <td>gpu-1000</td>
      <td>4.5</td>
    </tr>
  </tr>
  <!-- RK3576 -->
  <tr align="center">
    <td rowspan="2">RK3576</td>
    <td rowspan="2">Mali-G52 MC4EE2 @800MHz</td>
    <td>最大4K, IP support <br> (online display) </td>
    <td>IP support</td>
    <td>IP support</td>
    <td>IP support</td>
    <td>IP support</td>
  </tr>
</table>

#### CGC 模块
(`html`表格。如显示异常，请更换支持`html`的`Markdown`渲染器)
以下为只开启色域转换功能测试的性能数据
<table>
  <tr align="center">
    <td rowspan="2"><b>平台</b></td>
    <td rowspan="2"><b>GPU型号与频率</b></td>
    <td rowspan="2"><b>输入图像分辨率和格式</b></td>
    <td rowspan="2"><b>固定帧率[fps]</b></td>
    <td rowspan="1" colspan="3"><b>性能数据<b> (performance mode)</td>
    <tr align="center">
      <td><b>GPU占用率[%]</b></td>
      <td><b>带宽占用[MB/s]</b></td>
      <td><b>耗时[ms]</b></td>
    </tr>
  </tr>
  <!-- RK3588 -->
  <tr align="center">
    <td rowspan="2">RK3588</td>
    <td rowspan="2">Mali-G610 MC4 @1000MHz</td>
    <td>3840x2160, rgba8bit</td>
    <td>60</td>
    <td>60</td>
    <td>gpu-7300</td>
    <td>4.5</td>
    <tr align="center">
      <td>1920x1080, rgba8bit</td>
      <td>60</td>
      <td>24</td>
      <td>gpu-3000</td>
      <td>2</td>

    </tr>
  </tr>
  <!-- RK3576 -->
  <tr align="center">
    <td rowspan="2">RK3576</td>
    <td rowspan="2">Mali-G52 MC4EE2 @800MHz</td>
    <td>TBD</td>
    <td>TBD</td>
    <td>TBD</td>
    <td>TBD</td>
    <td>TBD</td>
  </tr>
</table>


TODO

#### AI-SR 模块
##### AI-SR 支持平台及性能数据参考
(`html`表格。如显示异常，请更换支持`html`的`Markdown`渲染器)
<table>
  <tr align="center">
    <td rowspan="2"><b>平台</b></td>
    <td rowspan="2"><b>GPU型号与频率</b></td>
    <td rowspan="2"><b>输入（输出）图像分辨率和格式</b></td>
    <td rowspan="2"><b>固定帧率[fps]</b></td>
    <td rowspan="1" colspan="3"><b>性能数据<b> (performance mode)</td>
    <tr align="center">
      <td><b>GPU占用率[%]</b></td>
      <td><b>带宽占用[MB/s]</b></td>
      <td><b>耗时[ms]</b></td>
    </tr>
  </tr>
  <!-- RK3568 -->
  <tr align="center">
    <td rowspan="2">RK3568</td>
    <td rowspan="2">Mali-G52 2EE @800MHz</td>
    <td>960x540 => 1920x1080, NV16</td>
    <td>30</td>
    <td>22</td>
    <td>cpu-300<br>gpu-240<br>npu-780</td>
    <td>25.0</td>
    <tr align="center">
        <td>1920x1080 => 3840x2160, N/A</td>
        <td>N/A</td>
        <td>N/A</td>
        <td>N/A</td>
        <td>N/A</td>
    </tr>
  </tr>
  <!-- RK3588 -->
  <tr align="center">
    <td rowspan="2">RK3588</td>
    <td>Mali-G610 MC4 @1000MHz (Android)</td>
    <td>1920x1080 => 3840x2160, NV12 </td>
    <td>60</td>
    <td>18</td>
    <td>cpu-400<br>gpu-3000<br>npu-10000</td>
    <td>16.0</td>
    <tr align="center">
      <td>Mali-G610 MC4 @900MHz (Linux)</td>
      <td>1920x1080 => 3840x2160, NV12 </td>
      <td>60</td>
      <td>20</td>
      <td>gpu-3050<br>npu-10000</td>
      <td>15.0</td>
    </tr>
  </tr>
  <!-- RK3576 -->
  <tr align="center">
    <td>RK3576</td>
    <td>Mali-G52 MC4EE2 @800MHz</td>
    <td>TBD</td>
    <td>TBD</td>
    <td>TBD</td>
    <td>TBD</td>
    <td>TBD</td>
  </tr>
</table>

#### AI-SD 模块
##### AI-SD 支持平台及性能数据参考
(`html`表格。如显示异常，请更换支持`html`的`Markdown`渲染器)
<table>
  <tr align="center">
    <td rowspan="2"><b>平台</b></td>
    <td rowspan="2"><b>GPU型号与频率</b></td>
    <td rowspan="2"><b>输入图像分辨率和格式</b></td>
    <td rowspan="2"><b>固定帧率[fps]</b></td>
    <td rowspan="1" colspan="3"><b>性能数据<b> (performance mode)</td>
    <tr align="center">
      <td><b>GPU占用率[%]</b></td>
      <td><b>带宽占用[MB/s]</b></td>
      <td><b>耗时[ms]</b></td>
    </tr>
  </tr>
  <!-- RK3568 -->
  <tr align="center">
    <td>RK3568</td>
    <td>Mali-G52 2EE @800MHz</td>
    <td>N/A</td>
    <td>N/A</td>
    <td>N/A</td>
    <td>N/A</td>
    <td>N/A</td>
  </tr>
  <!-- RK3588 -->
  <tr align="center">
    <td>RK3588</td>
    <td>Mali-G610 MC4 @1000MHz</td>
    <td>1920x1080, NV12</td>
    <td>60</td>
    <td>2</td>
    <td>cpu-200, gpu-200, npu-720</td>
    <td>4.0</td>
  </tr>
  <!-- RK3576 -->
  <tr align="center">
    <td>RK3576</td>
    <td>Mali-G52 MC4EE2 @800MHz</td>
    <td>TBD</td>
    <td>TBD</td>
    <td>TBD</td>
    <td>TBD</td>
    <td>TBD</td>
  </tr>
</table>

#### AI-DM 模块
##### AI-DM 支持平台及性能数据参考
(`html`表格。如显示异常，请更换支持`html`的`Markdown`渲染器)
<table>
  <tr align="center">
    <td rowspan="2"><b>平台</b></td>
    <td rowspan="2"><b>GPU型号与频率</b></td>
    <td rowspan="2"><b>输入图像分辨率和格式</b></td>
    <td rowspan="2"><b>固定帧率[fps]</b></td>
    <td rowspan="1" colspan="3"><b>性能数据<b> (performance mode)</td>
    <tr align="center">
      <td><b>GPU占用率[%]</b></td>
      <td><b>带宽占用[MB/s]</b></td>
      <td><b>耗时[ms]</b></td>
    </tr>
  </tr>
  <!-- RK3568 -->
  <tr align="center">
    <td>RK3568</td>
    <td>Mali-G52 2EE @800MHz</td>
    <td>1920x1080, NV12</td>
    <td>60</td>
    <td>35</td>
    <td>cpu-400, gpu-350, npu-640</td>
    <td>15.5</td>
  </tr>
  <!-- RK3588 -->
  <tr align="center">
    <td>RK3588</td>
    <td>Mali-G610 MC4 @1000MHz</td>
    <td>N/A</td>
    <td>N/A</td>
    <td>N/A</td>
    <td>N/A</td>
    <td>N/A</td>
  </tr>
  <!-- RK3576 -->
  <tr align="center">
    <td>RK3576</td>
    <td>Mali-G52 MC4EE2 @800MHz</td>
    <td>N/A</td>
    <td>N/A</td>
    <td>N/A</td>
    <td>N/A</td>
    <td>N/A</td>
  </tr>
</table>

#### AI-DFC 模块
##### AI-DFC 支持平台及性能数据参考
(`html`表格。如显示异常，请更换支持`html`的`Markdown`渲染器)
<table>
  <tr align="center">
    <td rowspan="2"><b>平台</b></td>
    <td rowspan="2"><b>GPU型号与频率</b></td>
    <td rowspan="2"><b>输入图像分辨率和格式</b></td>
    <td rowspan="2"><b>固定帧率[fps]</b></td>
    <td rowspan="1" colspan="3"><b>性能数据<b> (performance mode)</td>
    <tr align="center">
      <td><b>GPU占用率[%]</b></td>
      <td><b>带宽占用[MB/s]</b></td>
      <td><b>耗时[ms]</b></td>
    </tr>
  </tr>
  <!-- RK3568 -->
  <tr align="center">
    <td>RK3568</td>
    <td>Mali-G52 2EE @800MHz</td>
    <td>N/A</td>
    <td>N/A</td>
    <td>N/A</td>
    <td>N/A</td>
    <td>N/A</td>
  </tr>
  <!-- RK3588 -->
  <tr align="center">
    <td>RK3588</td>
    <td>Mali-G610 MC4 @1000MHz</td>
    <td>1920x1080 NV12</td>
    <td>TBD</td>
    <td>TBD</td>
    <td>TBD</td>
    <td>TBD</td>
  </tr>
  <!-- RK3576 -->
  <tr align="center">
    <td>RK3576</td>
    <td>Mali-G52 MC4EE2 @800MHz</td>
    <td>1920x1080 NV12</td>
    <td>30</td>
    <td>30</td>
    <td>N/A</td>
    <td>28</td>
  </tr>
</table>

#### AI-DE 模块
##### AI-DE 支持平台及性能数据参考
(`html`表格。如显示异常，请更换支持`html`的`Markdown`渲染器)
<table>
  <tr align="center">
    <td rowspan="2"><b>平台</b></td>
    <td rowspan="2"><b>GPU型号与频率</b></td>
    <td rowspan="2"><b>输入图像分辨率和格式</b></td>
    <td rowspan="2"><b>固定帧率[fps]</b></td>
    <td rowspan="1" colspan="3"><b>性能数据<b> (performance mode)</td>
    <tr align="center">
      <td><b>GPU占用率[%]</b></td>
      <td><b>带宽占用[MB/s]</b></td>
      <td><b>耗时[ms]</b></td>
    </tr>
  </tr>
  <!-- RK3568 -->
  <tr align="center">
    <td>RK3568</td>
    <td>Mali-G52 2EE @800MHz</td>
    <td>N/A</td>
    <td>N/A</td>
    <td>N/A</td>
    <td>N/A</td>
    <td>N/A</td>
  </tr>
  <!-- RK3588 -->
  <tr align="center">
    <td>RK3588</td>
    <td>Mali-G610 MC4 @1000MHz</td>
    <td>TBD</td>
    <td>TBD</td>
    <td>TBD</td>
    <td>TBD</td>
    <td>TBD</td>
  </tr>
  <!-- RK3576 -->
  <tr align="center">
    <td>RK3576</td>
    <td>Mali-G52 MC4EE2 @800MHz</td>
    <td>TBD</td>
    <td>TBD</td>
    <td>TBD</td>
    <td>TBD</td>
    <td>TBD</td>
  </tr>
</table>

#### AI-DD 模块
##### AI-DD 支持平台及性能数据参考
(`html`表格。如显示异常，请更换支持`html`的`Markdown`渲染器)
<table>
  <tr align="center">
    <td rowspan="2"><b>平台</b></td>
    <td rowspan="2"><b>GPU型号与频率</b></td>
    <td rowspan="2"><b>输入图像分辨率和格式</b></td>
    <td rowspan="2"><b>固定帧率[fps]</b></td>
    <td rowspan="1" colspan="3"><b>性能数据<b> (performance mode)</td>
    <tr align="center">
      <td><b>GPU占用率[%]</b></td>
      <td><b>带宽占用[MB/s]</b></td>
      <td><b>耗时[ms]</b></td>
    </tr>
  </tr>
  <!-- RK3568 -->
  <tr align="center">
    <td>RK3568</td>
    <td>Mali-G52 2EE @800MHz</td>
    <td>N/A</td>
    <td>N/A</td>
    <td>N/A</td>
    <td>N/A</td>
    <td>N/A</td>
  </tr>
  <!-- RK3588 -->
  <tr align="center">
    <td>RK3588</td>
    <td>Mali-G610 MC4 @1000MHz</td>
    <td>1920x1080, RGB</td>
    <td>60</td>
    <td>4</td>
    <td>cpu-850, gpu-750, npu-3920</td>
    <td>31.0</td>
  </tr>
  <!-- RK3576 -->
  <tr align="center">
    <td>RK3576</td>
    <td>Mali-G52 MC4EE2 @800MHz</td>
    <td>TBD</td>
    <td>TBD</td>
    <td>TBD</td>
    <td>TBD</td>
    <td>TBD</td>
  </tr>
</table>

#### AI-DHW 模块
##### AI-DHW 支持平台及性能数据参考
TODO

#### MIX-FE 模块
##### MIX-FE 支持平台及性能数据参考
(`html`表格。如显示异常，请更换支持`html`的`Markdown`渲染器)
<table>
  <tr align="center">
    <td rowspan="2"><b>平台</b></td>
    <td rowspan="2"><b>GPU型号与频率</b></td>
    <td rowspan="2"><b>输入图像分辨率和格式</b></td>
    <td rowspan="2"><b>固定帧率[fps]</b></td>
    <td rowspan="1" colspan="3"><b>性能数据<b> (performance mode)</td>
    <tr align="center">
      <td><b>GPU占用率[%]</b></td>
      <td><b>带宽占用[MB/s]</b></td>
      <td><b>耗时[ms]</b></td>
    </tr>
  </tr>
  <!-- RK3568 -->
  <tr align="center">
    <td>RK3568</td>
    <td>Mali-G52 2EE @800MHz</td>
    <td>N/A</td>
    <td>N/A</td>
    <td>N/A</td>
    <td>N/A</td>
    <td>N/A</td>
  </tr>
  <!-- RK3588 -->
  <tr align="center">
    <td>RK3588</td>
    <td>Mali-G610 MC4 @1000MHz</td>
    <td>TBD</td>
    <td>TBD</td>
    <td>TBD</td>
    <td>TBD</td>
    <td>TBD</td>
  </tr>
  <!-- RK3576 -->
  <tr align="center">
    <td>RK3576</td>
    <td>Mali-G52 MC4EE2 @800MHz</td>
    <td>960x540,NV24</td>
    <td>30</td>
    <td>N/A</td>
    <td>N/A</td>
    <td>30</td>
  </tr>
</table>

#### MIX-MSSR 模块
##### MIX-MSSR 支持平台及性能数据参考
(`html`表格。如显示异常，请更换支持`html`的`Markdown`渲染器)
<table>
  <tr align="center">
    <td rowspan="2"><b>平台</b></td>
    <td rowspan="2"><b>GPU型号与频率</b></td>
    <td rowspan="2"><b>输入图像分辨率和格式</b></td>
    <td rowspan="2"><b>固定帧率[fps]</b></td>
    <td rowspan="1" colspan="3"><b>性能数据<b> (performance mode)</td>
    <tr align="center">
      <td><b>GPU占用率[%]</b></td>
      <td><b>带宽占用[MB/s]</b></td>
      <td><b>耗时[ms]</b></td>
    </tr>
  </tr>
  <!-- RK3568 -->
  <tr align="center">
    <td>RK3568</td>
    <td>Mali-G52 2EE @800MHz</td>
    <td>N/A</td>
    <td>N/A</td>
    <td>N/A</td>
    <td>N/A</td>
    <td>N/A</td>
  </tr>
  <!-- RK3588 -->
  <tr align="center">
    <td>RK3588</td>
    <td>Mali-G610 MC4 @1000MHz</td>
    <td>TBD</td>
    <td>TBD</td>
    <td>TBD</td>
    <td>TBD</td>
    <td>TBD</td>
  </tr>
  <!-- RK3576 -->
  <tr align="center">
    <td>RK3576</td>
    <td>Mali-G52 MC4EE2 @900MHz</td>
    <td>540pNV24 <br> 720pY8+UV88 <br> 1080pNV12 <br> 1080pNV24 <br> 1080pRGB <br> 4kNV12 <br> 4kNV24 <br> 4kRGB </td>
    <td>15/20/24/25/30 ⟶ 30 <br> 15/20/24/25/30/50/60 ⟶ 60</td>
    <td>N/A</td>
    <td>N/A</td>
    <td>N/A</td>
  </tr>
</table>


### 2.4. AI 模块运行所需模型文件列表
| 模块 | 发布模型文件 | 内部文件md5值（仅供内部开发人员审核使用，与发布模型文件无关） |
|:----|:-------|:----|
| AISR  | rkaipq_sr_model_540p_rknn140_rk356x.bin <br> rkaipq_sr_model0_1080p_rknn140_rk3588.bin <br> rkaipq_sr_model1_1080p_rknn140_rk3588.bin | 080d8cc840f38a7ed3602bdc0a9acc6a <br> e0bd9da45fd5c598b11d46731308c0eb <br> ba3b4a372ef72cd365bf377f80016d52 |
| AISD  | rkaipq_sd_model_rknn140_rk3588.bin <br> rkaipq_mssr_model0_sd_rknn200_rk3576.bin | abfd6d291e0cb017c2306b565e432c8f <br> \ |
| AIDM  | rkaipq_dm_model_rknn140_rk356x.bin | afcfdc7b24f88390b24eb5ba57061b82 |
| AIDFC | rkaipq_dfc_model_rknn150_rk3588.bin <br> rkaipq_dfc_model[~10]_rknn200_rk3576.bin | 3cb6e9905915af4965693e84f16ec973 <br> \ |
| AIDE  | rkaipq_de_model_rknn150_rk3588.bin <br> rkaipq_de_model_rknn162_rk3576.bin |b6a1dd05b0df34b788f55cc968bbd71f <br> 416afaa26c159809a5475d5f43f98e6e |
| AIDD  | rkaipq_dd_model0_rknn150_rk3588.bin <br> rkaipq_dd_model1_rknn150_rk3588.bin <br> rkaipq_dd_model0_rknn200_rk3576.bin <br> rkaipq_dd_model1_rknn200_rk3576.bin | 5d33642ab5cd2346eb4aa7b782c16977 <br> 257945db4dc3197e188ed0e9e69f7598 <br> \ <br> \ |
| AIDHW | rkaipq_dhw_model0_rknn200_rk3576.bin <br> rkaipq_dhw_model1_rknn200_rk3576.bin | TBD |
| MixFE |  TBD | TBD |
| MixFE2 | TBD | TBD |
| MixFE3 | TBD | TBD |
| MixFE4 | TBD | TBD |
| MixFE4 | TBD | TBD |
| MixMSSR | rkaipq_mssr_model0_EbookSR1920to1920_rknn200_rk3576.bin <br> rkaipq_mssr_model0_EbookSR480to960_rknn200_rk3576.bin <br> rkaipq_mssr_model0_NaturalSR540to1080_rknn200_rk3576.bin <br> rkaipq_mssr_model0_NaturalSR720to4K_rknn200_rk3576.bin <br> rkaipq_mssr_model0_fd_rknn200_rk3576.bin <br> rkaipq_mssr_model0_fe_rknn200_rk3576.bin <br> rkaipq_mssr_model0_fs_rknn200_rk3576.bin <br> rkaipq_mssr_model0_fsr_rknn200_rk3576.bin <br> rkaipq_mssr_model0_sd_rknn200_rk3576.bin <br> rkaipq_mssr_model0_std_rknn200_rk3576.bin <br> rkaipq_mssr_model1_DC1080p_rknn200_rk3576.bin <br> rkaipq_mssr_model1_DC540p_rknn200_rk3576.bin <br> rkaipq_mssr_model1_DC720p_rknn200_rk3576.bin <br> rkaipq_mssr_model1_IFBlockX5Stage0_rknn200_rk3576.bin <br> rkaipq_mssr_model1_IFBlockX5Stage1_rknn200_rk3576.bin <br> rkaipq_mssr_model1_IFBlockX5Stage2_rknn200_rk3576.bin <br> rkaipq_mssr_model1_NaturalSR1080to4K_rknn200_rk3576.bin <br> rkaipq_mssr_model1_fe_rknn200_rk3576.bin <br> rkaipq_mssr_model2_DC1080p_rknn200_rk3576.bin <br> rkaipq_mssr_model2_IFBlockX4Stage0_rknn200_rk3576.bin <br> rkaipq_mssr_model2_IFBlockX4Stage1_rknn200_rk3576.bin <br> rkaipq_mssr_model2_IFBlockX4Stage2_rknn200_rk3576.bin <br> rkaipq_mssr_model2_IFBlockX5Stage0_rknn200_rk3576.bin <br> rkaipq_mssr_model2_IFBlockX5Stage1_rknn200_rk3576.bin <br> rkaipq_mssr_model2_IFBlockX5Stage2_rknn200_rk3576.bin <br> rkaipq_mssr_model2_NaturalSR1080to4K_rknn200_rk3576.bin <br> rkaipq_mssr_model3_IFBlockX4Stage0_rknn200_rk3576.bin <br> rkaipq_mssr_model3_IFBlockX4Stage1_rknn200_rk3576.bin <br> rkaipq_mssr_model3_IFBlockX4Stage2_rknn200_rk3576.bin <br> rkaipq_mssr_model3_IFBlockX5Stage0_rknn200_rk3576.bin <br> rkaipq_mssr_model3_IFBlockX5Stage1_rknn200_rk3576.bin <br> rkaipq_mssr_model3_IFBlockX5Stage2_rknn200_rk3576.bin <br> rkaipq_mssr_model3_NaturalSR1080to4K_rknn200_rk3576.bin <br> rkaipq_mssr_model3_NaturalSR720to1080_rknn200_rk3576.bin <br> rkaipq_mssr_model4_IFBlockX4Stage0_rknn200_rk3576.bin <br> rkaipq_mssr_model4_IFBlockX4Stage1_rknn200_rk3576.bin <br> rkaipq_mssr_model4_IFBlockX4Stage2_rknn200_rk3576.bin <br> rkaipq_mssr_model4_IFBlockX5Stage0_rknn200_rk3576.bin <br> rkaipq_mssr_model4_IFBlockX5Stage1_rknn200_rk3576.bin <br> rkaipq_mssr_model4_IFBlockX5Stage2_rknn200_rk3576.bin <br> rkaipq_mssr_model4_IFBlockX5TxtSeg_rknn200_rk3576.bin <br> rkaipq_mssr_model4_NaturalSR1080to4K_rknn200_rk3576.bin <br> rkaipq_mssr_model4_NaturalSR720to1080_rknn200_rk3576.bin <br> rkaipq_mssr_model5_IFBlockX4Stage0_rknn200_rk3576.bin <br> rkaipq_mssr_model5_IFBlockX4Stage1_rknn200_rk3576.bin <br> rkaipq_mssr_model5_IFBlockX4Stage2_rknn200_rk3576.bin <br> rkaipq_mssr_model5_IFBlockX4TxtSeg_rknn200_rk3576.bin <br> rkaipq_mssr_model5_NaturalSR1080to4K_rknn200_rk3576.bin <br> rkaipq_mssr_model5_NaturalSR720to1080_rknn200_rk3576.bin <br>  | 4e6b01313838892bd821c7f7ccf7d45e <br> 6981f230a71dd942fa92b084f80855a5 <br> 9a997ba1c86760fce48f2e9cbad05161 <br> 626bf59c6ebb2be5f0ac0c16f4c9b355 <br> fd6ade66c0320d05f0916d10a738e624 <br> d99d5a9392c2450c29e8f9220bcc6170 <br> 261f1cba4b3ce02b8172543c7c443b23 <br> 2aaa8d32419b38c7cb19fe4be6678651 <br> 1f5187c937e87c364d378ab3ee950c2c <br> 1aba8c6b8f18db81e0cea2db35e847b8 <br> 75f176ca8befde487bc6832fa28c7091 <br> eb0009e4d4c59ff60069692b14502c41 <br> cfd4f9b58c58fda49cd53638ee113a78 <br> 42281ce98a209cd98f2f76d311dfc3a8 <br> 25f9d68111c0d0bf4a2810ede2a56bbc <br> 9cba025bb4291c38acc1ba1af702e53a <br> 2404c1fdb8ec5b0b22914c788b11bf6c <br> 1a3f2b897459f3bd6f2bd9edbff56800 <br> a750145fc97d1325e18fc93d544364f2 <br> 57ccfd4d429066a96af1fb54f2e4bef0 <br> af07923efbf0fd4be8a64f5b628630fa <br> 118498ba79da16aaf9ee05ad42b16b84 <br> 9fcbe23608f870f5a41f4d3e6c9121fe <br> 488bb9d3ad7563b5fd498f2e67976d91 <br> bbe1b39076db24413c08b45b16b90737 <br> d4aaf0b4f0918a7dffa1ea618888ab9f <br> 86aee47434e195c073bcffc58c6df59a <br> dd383c03a8d4fb97c90327416a5ff370 <br> dc3f5a1a9c9cc30d3e8559dc6f3c9c9b <br> 56c5d8731d5f43e5d1423e86ea142645 <br> 6232501c182cc789421c9d63a7e2466c <br> 5f779a55329d228e051c0e7adabd991a <br> 003e6ce6e973ae71c8b0ec6798a97bc2 <br> 295d7d7b08f0d9f96058d58c5161385c <br> e1740ff387ca2d54254dad2a77873d7e <br> 64abb0f5c47093def15bd11614cf3e37 <br> f463be62f318a2e98b16c28f702285ed <br> dae6f7fcf962caaa8f2f94fb0c7030b0 <br> 4ee9b467b7fdae7942949bbf27d278aa <br> 3bdf51f778722f83307ffb6cee75d308 <br> 82d5f1a63a7692cb031d547aa8d45bb3 <br> aca859650d5c53d8bbf3886c634c06eb <br> 6957daeaeb732efed97091294bd8760d <br> 0390823176f79df482bae99b0cdf2426 <br> 02e7843bbfd69dd5ded5170906334f9e <br> f265647cdce1a11381b1e1da8f4cbf22 <br> 16676f0a4f0af3eea4c615eb3c98bcbf <br> a626977fcedabd30cd240aa4fe4b51bc <br> 2cee5c3dee2b6971aafca651a6036ca3 <br> |

注：
1. 随库提供的模型文件默认加载路径为: Android: `/vendor/etc/`, Linux: `/etc/`;
2. `rkpq_set_cache_path()`接口结合`target=4`参数可以修改RKNN模型的加载路径，需要在`rkpq_init()`前调用。


## 3. 关键数据结构与应用接口说明

### 3.1. SDK版本说明
#### SDK版本号格式与递增规则

版本号格式:
```
RKSWPQ_major.minor.revision.build.time
```

版本号递增规则:

| 名称     | 规则                                            | 备注 |
| -------- | ----------------------------------------------- | ---- |
| major    | 主版本号，当提交不向下兼容的API修改。             | - |
| minor    | 次版本号，当向下兼容的功能性新增或删除。          | major更新后重置 |
| revision | 修订版本号，当向下兼容的功能补充或致命的问题修正。 | major/minor更新后重置 |
| build    | 编译版本号，当向下兼容的问题修正。                | 一直递增，不重置 |
| time     | 编译时间。                                      | - |


#### 版本号查询

##### strings命令查询

以Android R 64位为例：

```shell
:/# strings /vendor/lib64/librkswpq.so | grep RKSWPQ_
RKSWPQ_0.0.4.2986.202401171019
```

##### Android系统属性/Linux系统环境变量查询

由于程序对系统属性的设置可能存在权限问题，所以该方法可能无法查询到版本信息。

```shell
# Android 系统查询属性信息
adb shell getprop persist.vendor.rkpq.version

# Linux 系统查询环境变量
echo $rkpq_version
```

##### 日志打印

当调用`rkpq_init()`时，会打印版本号。

```txt
--s-- rkpq_init()
--------------------------------
        Version: RKSWPQ_0.0.4.2986.202401171019 (CPU-64bit)
```

当调用`rkpq_proc()`时，也会打印版本号。
```txt
--s-- rkpq_proc() #0 ---- RKSWPQ_0.0.4.2986.202401171019
```

##### 函数接口查询

调用`rkpq_query()`接口查询版本号，版本信息位于结构体`rkpq_version_info`中。具体使用说明可以查看 **应用接口说明** 章节。
```c
rkpq_version_info version_info;
rkpq_query(context, RKPQ_QUERY_SDK_VERSION, sizeof(rkpq_version_info), &version_info);
printf("SDK version: %d.%d.%d, %s\n", verInfo.nVerMajor, verInfo.nVerMinor, verInfo.nVerRvson, verInfo.sVerInfo);
// 输出内容: SDK version: 0.0.4, RKSWPQ_0.0.4.2986.202401171019
```


### 3.2. 数据结构说明

下面罗列出的数据结构较为重要或复杂，文中未罗列出的数据结构请查看`rkpq_api.h`头文件相关注释。

注：头文件中带有`reserved`备注字样的属性or条目暂未支持。

#### rkpq_query_cmd
```c
/* rkpq_query() 接口所支持的相关信息查询条目列表 */
typedef enum _rkpq_query_cmd
{
    RKPQ_QUERY_SDK_VERSION = 0,         /* 用于查询 SDK 版本信息 */
    RKPQ_QUERY_PERF_INFO,               /* 用于查询运行耗时信息 */
    RKPQ_QUERY_MODULES_SUPPORT,         /* 用于查询 SDK 在该版本下支持的模块 */
    RKPQ_QUERY_MODULES_ROI_SUPPORT,     /* 用于查询支持ROI操作的模块 */
    RKPQ_QUERY_IMG_RES_CHANGE_SUPPORT,  /* 用于查询是否支持运行时改变图像分辨率 */
    RKPQ_QUERY_IMG_FMT_CHANGE_SUPPORT,  /* 用于查询是否支持运行时改变图像格式 */
    RKPQ_QUERY_IMG_FMT_INPUT_SUPPORT,   /* 用于查询支持的输入图像格式 */
    RKPQ_QUERY_IMG_FMT_OUTPUT_SUPPORT,  /* 用于查询支持的输出图像格式 */
    RKPQ_QUERY_IMG_COLOR_SPACE_SUPPORT, /* 用于查询支持的图像色彩空间 */
    RKPQ_QUERY_IMG_BUF_INFO,            /* 用于查询图像的内存对象信息，查询前必须要先指定图像格式和尺寸等信息，具体见 rkpq_imgbuf_info */
    RKPQ_QUERY_IMG_ALIGNMENT_OCL,       /* 用于查询OpenCL图像在宽度上的对齐量，单位：pixel */
    RKPQ_QUERY_BUF_ALIGNMENT_OCL,       /* 用于查询OpenCL子图像需要的偏移(offset)的对齐量，单位：byte */
    RKPQ_QUERY_RKNN_SUPPORT,            /* 用于查询是否支持RKNN模型在NPU上运行 */
    RKPQ_QUERY_MEAN_LUMA_OUTPUT,        /* 用于查询输出帧图像的平均亮度(需要指定`RKPQ_FLAG_CALC_MEAN_LUMA`) */
    RKPQ_QUERY_MAX,                     /* 条目数量标志，无实际意义 */
} rkpq_query_cmd;
```

#### rkpq_imgbuf_info
```c
/**
 * 定义了输入/输出图像的格式与尺寸等相关信息，非常重要！
 *  - 该结构体指定了输入/输出图像的基本格式信息内存信息
 *  - 可使用'RKPQ_QUERY_IMG_BUF_INFO'条目自动计算结构体成员变量的取值
 *  - 需保证该结构体的取值与实际输入/输出的图像buffer的虚宽、虚高、大小、排列方式等保持一致！
 */
typedef struct _rkpq_imgbuf_info
{
    uint32_t    nColorSpace;                        /* [i] 色彩空间，见 rkpq_clr_spc */
    uint32_t    nPixFmt;                            /* [i] 图像格式，见 rkpq_img_fmt */
    uint32_t    nDrmFmt;                            /* [i/o] reserved */
    uint32_t    nPixWid;                            /* [i] 图像宽度，单位：pixel，建议以4对齐 */
    uint32_t    nPixHgt;                            /* [i] 图像高度，单位：pixel，建议以2对齐 */
    uint32_t    nEleDepth;                          /* [i] 像素第一个元素（YUV的Y，RGB的R）的深度(bpc), 单位：bit */
    uint32_t    nAlignment;                         /* [i] buffer的行对齐量, 单位：byte */
    uint32_t    aWidStrides[RKPQ_MAX_PLANE_NUM];    /* [i/o] 每个平面的虚宽, 单位：byte，建议以64 byte对齐 */
    uint32_t    aHgtStrides[RKPQ_MAX_PLANE_NUM];    /* [i/o] 每个平面的虚高, 单位：pixel */
    size_t      aPlaneSizes[RKPQ_MAX_PLANE_NUM];    /* [o] 每个平面的buffer占用大小, 单位：byte */
    uint32_t    aPlaneElems[RKPQ_MAX_PLANE_NUM];    /* [o] 每个平面的元素数量 */
    uint32_t    nPlaneNum;                          /* [o] 图像的平面数量，由其格式决定 */
    size_t      nFrameSize;                         /* [o] 整幅图像对应的buffer占用大小, 等于所有平面的占用大小之和，单位：byte */

    uint8_t    *aPlaneAddrs[RKPQ_MAX_PLANE_NUM];    /* [i] 每个平面数据的起始虚地址，如果在零拷贝时buffer被映射过，则虚地址需要被正确设置！ */
    int32_t     nFdValue;                           /* [i] buffer的硬件描述符，用于实现零拷贝 */
    uint32_t    nFdIndex;                           /* [i] fd的索引，必须是fd的唯一标识符，用于缓存映射的检验，解决缓存失效问题，详见下文中的`rkpq_clear_caches()`接口说明 */
    size_t      nBufferSize;                        /* [i] buffer的总大小, 应 >= nFrameSize，单位：byte */
} rkpq_imgbuf_info;
```

##### 基本概念

SWPQ SDK 支持 `YUV` 和 `RGB` 两种大系列的图像格式，另外部分模块支持`Y8`单通道灰度格式和`UV88`双通道格式。

**YUV 采样方式**最常见的有`YUV444`，`YUV422`，`YUV420`三种，每种采样方式的区别如下：
  - `YUV444`：在2行4列像素中，每行保留4个Y，第一行保留4个UV, 第二行保留4个UV，即每个Y像素都有对应的UV值；
  - `YUV422`：在2行4列像素中，每行保留4个Y，第一行保留2个UV, 第二行保留2个UV，即1x2个Y像素共用一组UV；
  - `YUV420`：在2行4列像素中，每行保留4个Y，第一行保留2个UV, 第二行不保留UV，即2x2个Y像素共用一组UV。

**YUV 存储方式**根据其平面数量可分为：
  - `Planar`：Y，U，V分别存储于3个平面, 即: `YYYY...UUUU...VVVV...`
  - `Semi-Plane`：Y存储于1个平面，UV交织存储于1个平面，总计2个平面，即: `YYYYYYYY...UVUVUVUV...`
  - `Packed/Interleaved`：Y，U，V交织存储，总计1个平面, 即: `YUVYUVYUVYUV...`

**RGB 存储方式**一般为**多通道交织**，所以一般都只有单个平面。
  - 对于 `RGBA8888` 的像素排列为`LSB order`，即: [31:0]=[A8:B8:G8:R8]
  - 对于 `RGB565` 这种**紧凑型**的像素排列为`MSB order`，即: [15:0]=[R5:G6:B5]

##### 辅助接口的使用 - rkpq_query() with RKPQ_QUERY_IMG_BUF_INFO

1. `rkpq_imgbuf_info`结构体定义了图像的格式、图像尺寸、像素位宽、元素排列方式、所处的色彩空间等基础信息。
2. 在`rkpq_proc_params`结构体中包含了输入/输出图像的这些基础信息，故必须在`rkpq_proc()`接口调用前指定这些信息。
3. 由于`rkpq_imgbuf_info`结构体定义的信息非常详细且复杂，故在`rkpq_query_cmd`中特意增加了`RKPQ_QUERY_IMG_BUF_INFO`条目供`rkpq_query()`接口来自动计算和填充。
4. 工程师可以在设置带有`'[i]'`备注的属性值后，调用`rkpq_query()`接口并配`RKPQ_QUERY_IMG_BUF_INFO`参数以获取剩下的属性值。
5. 由于实际图像buffer往往存在对齐量，**自动计算的结果未必和实际情况相符**，所以工程师必须在`rkpq_query()`接口调用后认真检查其属性结果和实际情况是否一致。
6. 当相关属性值与buffer的存储结构不一致时，**应当在`rkpq_query()`调用后，`rkpq_proc()`调用前**，手动修改相关属性值，使其与实际情况保持一致。
7. 若工程师对`rkpq_imgbuf_info`中所有属性值都了然于胸，在`rkpq_proc()`调用前可直接手动设置各属性，不必调用`rkpq_query()`接口来自动填充。

##### 其他说明

1. 带`[i]`注释部分的内容，**必须**在调用`rkpq_query()`接口前设定，即图像色彩空间、格式、尺寸、元素长度和对齐量等。
2. 带`[i/o]`注释部分的内容，如若值已知**可以**在调用`rkpq_query()`接口前设定，调用后值会被更新。
3. 带`[o]`注释部分的内容，**无须**设定，调用`rkpq_query()`接口后值会被更新。（如果不调用该接口更新，这部分属性仍然需要被指定）
4. 此结构体指定了输入/输出图像的基本信息，需在调用`rkpq_proc()`之前**确认其值与对应buffer的实际存储结构保持一致**。
5. 当**调用`rkpq_query()`接口后**，相关属性值与buffer的存储结构不一致时，**应当在`rkpq_query()`调用后，`rkpq_proc()`调用前**，手动修改相关属性值（**包括虚宽 aWidStrides、虚高 aHgtStrides、平面大小 aPlaneSizes、总大小 nFrameSize 等**），使其保持一致。
6. 对齐量`nAlignment`详解：
   - 用于计算图像的虚宽，取值为以2为底的次幂数，如：0, 2, 4, 8, 16, 32, 64, 128等，**ARM上常见为64**；
   - **默认为第一个平面的对齐量，YUV格式中其他平面的虚宽以第一个平面的虚宽为标准即对应格式的采样率计算，而不是独立计算！**
   > 举例：`720x480 NV24(YUV444SP)`格式，64位对齐，虚宽计算结果对比：
   > 1) 按SDK中的计算结果：第一个平面的虚宽为 `align(720,64)=768`, 第二个平面的虚宽为`768*2=1536`;
   > 2) 若按每个平面**独立计算**，第一个平面虚宽相同为`768`，第二个平面虚宽为`align(720*2,64)=1472`，注意这里的不同！

7. 虚宽属性`aWidStrides[RKPQ_MAX_PLANE_NUM]`详解：
   - 调用`rkpq_query()`后的输出值`aWidStrides[0]`总是大于等于`nPixWid`；
   - 如果已知虚宽为`W'`，可只设置`aWidStrides[0]=W'`，`aWidStrides[1:2]`将根据图像格式对应的采样率自动计算；
   - 如果已知对齐量`nAlignment`，可以设置`aWidStrides[0]=0`，`aWidStrides[0:2]`将根据图像格式自动计算；
   - 如果buffer的对齐量如第6点所诉每个平面独立计算，或其他的实际属性与接口返回值不一致的情况下，需要对相关属性进行**手动修改**。
   > 举例：`720x480 NV24(YUV444SP)`格式，64位对齐，且虚宽按每个平面独立计算时：
   > 1) 第一个平面的虚宽为`align(720,64)=768`，将与`rkpq_query()`接口返回值一致，无需修改;
   > 2) 第二个平面的虚宽为`align(720*2,64)=1472`，将与`rkpq_query()`接口返回值`768*2=1536`不一致，则需手动设置`aWidStrides[1]=1472`，使其与实际情况一致.
   > 3) 虚宽数据被手动修改后，要修改对应平面的buffer大小和图像的帧buffer大小数据，即：
   > ```c
   >   size_t oldSize = bufInfo.aPlaneSizes[1]; // 记录旧的UV平面buffer大小
   >   bufInfo.aWidStrides[1] = 1472;  // 修改uv平面虚宽至实际值
   >   bufInfo.aPlaneSizes[1] = 1472 * bufInfo.aHgtStrides[1]; // 更新uv平面buffer大小
   >   bufInfo.nFrameSize = bufInfo.nFrameSize - oldSize + bufInfo.aPlaneSizes[1]; // 更新图像帧buffer大小
   > ```
8. 虚高属性`aHgtStrides[RKPQ_MAX_PLANE_NUM]`详解：
    - 如果高度方向**没有**对齐填充，设置`aHgtStrides[0]=0`, 调用接口后将会自动更新为`nPixHgt`的值；
    - 如果高度方向**有**对齐填充，设置`aHgtStrides[0]`的值即可，`aHgtStrides[1:2]`将根据图像格式对应的采样率自动计算;
    - 如果只有第1、2个平面之间有对齐填充，第2、3个平面之间没有或者填充量与采样率不一致，则也需要在接口返回后对其进行**手动修改**。
9. 虚宽属性`aWidStrides[RKPQ_MAX_PLANE_NUM]`和虚高属性`aHgtStrides[RKPQ_MAX_PLANE_NUM]`经过手动修改后，对应每个平面的占用大小`aPlaneSizes[RKPQ_MAX_PLANE_NUM]`和总占用大小`nFrameSize`也需要对应手动修改！

#### rkpq_init_params
```c
/* 初始化参数结构体 */
typedef struct _rkpq_init_params
{
    uint32_t    nInitFlag;          /* 初始化标志位 */
    uint32_t    nExtenFlag;         /* reserved */

    uint32_t    nModNumInPipe;                              /* [i] 自定义 pipeline 中模块的数量 */
    uint32_t    aModPipeOrder[RKPQ_MAX_PIPE_MODULE_NUM];    /* [i] 自定义 pipeline 中模块的顺序，值为rkpq_module枚举值 */

    uint32_t    bLazyInit;                                  /* [i] 延迟初始化开关: 开启后提升 rkpq_context 的初始化速度(即降低 rkpq_init() 接口的返回时间)，
                                                             但内部各模块的初始化会到运行时才进行，首帧的处理速度会下降；关闭后内部所有模块的初始化操作在
                                                             rkpq_init() 接口调用期间完成，该情况下初始化返回时间与模块数量正相关，后续各帧处理时间保持稳定。 */
    uint32_t    aModSetupFlags[RKPQ_MAX_PIPE_MODULE_NUM];   /* [i] 每个模块的初始化标志位，用于节省内存占用以及初始化耗时。默认值应全为0 */
    int32_t     nMaxIoBufCacheNum;                          /* [i] 最大IO buffer缓存数量, 取值范围:[(0), 256] (=0时将使用默认值32, <0时关闭缓存功能) */

} rkpq_init_params;

/* 初始化标志位取值说明 */
#define RKPQ_FLAG_PERF_DETAIL           (1 << 0)    /* 保留标志位，暂无作用 */
#define RKPQ_FLAG_HIGH_PERFORM          (1 << 1)    /* 提升CPU利用率以提升性能，在CPU无法定频的情况下使用，开启后允许通过`bEnableIncreaseCpuUtl`参数开关 */
#define RKPQ_FLAG_HIGH_PRECISION        (1 << 2)    /* 保留标志位，暂无作用 */
#define RKPQ_FLAG_ASYNC_MODE            (1 << 3)    /* 异步开关标志位，部分模块支持异步处理，开启后增加送显延迟 */
#define RKPQ_FLAG_FIX_RES_IMG_IO        (1 << 4)    /* 保留标志位，暂无作用 */
#define RKPQ_FLAG_CIRCULAR_BUF_IN       (1 << 5)    /* 输入缓冲区采用ring-buffer机制，开启后可以降低零拷贝的映射开销（分辨率与格式需保持一致） */
#define RKPQ_FLAG_CIRCULAR_BUF_OUT      (1 << 6)    /* 输出缓冲区采用ring-buffer机制，开启后可以降低零拷贝的映射开销（分辨率与格式需保持一致） */
#define RKPQ_FLAG_CALC_MEAN_LUMA        (1 << 7)    /* 允许计算输出帧图像的平均亮度，开启后会略微增加处理时间 */
#define RKPQ_FLAG_CVT_RANGE_ONLY        (1 << 4)    /* 已废弃 */
```

注：
1. 只有指定了`RKPQ_FLAG_CIRCULAR_BUF_IN`或`RKPQ_FLAG_CIRCULAR_BUF_OUT`的情况下，IO buffer缓存功能才会生效。
2. 不建议开启`RKPQ_FLAG_HIGH_PERFORM`，请在开发人员指导下使用。

#### rkpq_proc_params
```c
/* 执行参数结构体 */
typedef struct _rkpq_proc_params
{
    // 图像和缓冲区信息
    rkpq_imgbuf_info    stSrcImgInfo;         /* [i] 输入图像和缓冲区信息 */
    rkpq_imgbuf_info    stDstImgInfo;         /* [i] 输出图像和缓冲区信息 */
    rkpq_roi            stImgRoi;             /* [i] ROI信息，基于输出图像坐标系 */

    // Extension config
    uint32_t            nExtenType;           /* [i] reserved */
    void               *pExtenConfig;         /* [i] reserved */

    // Parameter info
    uint32_t            nFrameIdx;            /* [i] 帧序号 */
    uint32_t            bEnablePropControl;   /* [i] 属性tuning开关，与`bEnableSliderControl`互斥 */
    uint32_t            bEnableSliderControl; /* [i] PQTool tuning开关 */
    uint32_t            bEnableIncreaseCpuUtl;/* [i] 提升CPU利用率开关，仅在`RKPQ_FLAG_HIGH_PERFORM`指定后生效（不建议开启） */

    uint32_t            aReservedData[1];     /* reserved, for future use */
} rkpq_proc_params;
```
注：
1. 对于大部分PQ模块来说都是“**单输入-单输出**”的模式，其输入和输出图像信息目前必须由`rkpq_proc_params`参数传入；
2. 对于少数“**多输入-多输出**”模式的PQ模块（目前仅`AI-MSSR`模块）来说，其输入和输出的图像信息由`rkpq_set_inputs()`和`rkpq_set_outputs()`接口传入。

#### rkpq_pipe_fmt_info 和 rkpq_pipe_res_info
```c
/* 格式变换信息，记录在某些会改变输入格式/色彩空间的模块（如CSC/CVT/ZME/SR）配置内 */
typedef struct _rkpq_pipe_fmt_info
{
    uint32_t    nSrcClrSpc;     /* [i] 输入图像色彩空间 */
    uint32_t    nSrcPixFmt;     /* [i] 输入图像格式 */
    uint32_t    nSrcDrmFmt;     /* reserved */

    uint32_t    nDstClrSpc;     /* [i] 输出图像色彩空间，如果不是最后一个模块，不可以指定为 Limited-Range ! */
    uint32_t    nDstPixFmt;     /* [i] 输出图像格式 */
    uint32_t    nDstDrmFmt;     /* reserved */
} rkpq_pipe_fmt_info;

/* 分辨率变换信息，记录在某些会改变输入分辨率的模块（如ZME/SR/FE/MSSR）配置内 */
typedef struct _rkpq_pipe_res_info
{
    uint32_t    nSrcImgWid;   /* [i] 输入图像宽度，单位: pixel */
    uint32_t    nSrcImgHgt;   /* [i] 输入图像高度，单位: pixel */
    uint32_t    nDstImgWid;   /* [i] 输出图像宽度，单位: pixel */
    uint32_t    nDstImgHgt;   /* [i] 输出图像高度，单位: pixel */
} rkpq_pipe_res_info;
```
注：
- 所有输出格式或色彩空间会发生改变的模块（如`CSC/CVT/ZME/SR`）都需要记录当前模块的输入/输出的格式以及色彩空间信息，以便在pipeline之后的模块确认自己的输入格式。
- 所有输出分辨率会发生改变的模块（如`ZME/SR/FE`等）都需要记录当模块的输入/输出的分辨率信息，以便在pipeline之后的模块确认自己的输入分辨率。


### 3.3. 应用接口说明
#### rkpq_init()
接口作用:
用于初始化一个有效的`rkpq_context`上下文对象，用于后续的处理。

接口定义：
```c
int rkpq_init(rkpq_context *pCtxPtr, rkpq_init_params *pInitParam);
```

参数说明：
- `rkpq_context *pCtxPtr`: `rkpq_context`对象**指针**
- `rkpq_init_params *pInitParam`: `rkpq_init_params`结构体对象指针

注：
- 如果没有OpenCL程序缓存文件，第一次调用`rkpq_init()`进行初始化耗时会比较长（秒级）;
- 初始化成功后OpenCL程序会**自动写出缓存文件**，之后的初始化耗时将大幅度降低（毫秒级）;
- 自动写出缓存文件可能会因为程序权限等问题失败;
- 缓存文件与OpenCL驱动版本强相关，OTA升级后如若更新了驱动，缓存文件会重新生成，造成单次初始化耗时增加;
- OpenCL程序默认缓存路径: `/data/rkalgo/` 或 `/data/vendor/rkalgo/`;
- `rkpq_set_cache_path()`接口结合`target=1`参数可以修改OpenCL缓存的保存和加载路径，需要在`rkpq_init()`前调用。

#### rkpq_proc()
接口作用:
根据传入的`rkpq_proc_params`参数，调用`rkpq_context`上下文对象执行PQ处理，处理过程会**阻塞调用线程**，直到接口程序返回。

接口定义：
```c
int rkpq_proc(rkpq_context ctx, rkpq_proc_params *pProcParam);
```

参数说明：
- `rkpq_context ctx`: `rkpq_context`对象
- `rkpq_proc_params *pProcParam`: `rkpq_proc_params`结构体对象指针

#### rkpq_deinit()
接口作用:
析构`rkpq_context`上下文对象，回收相关资源。

接口定义：
```c
int rkpq_deinit(rkpq_context ctx);
```

参数说明：
- `rkpq_context ctx`: 待析构的`rkpq_context`对象

注:
- 调用`rkpq_init()`后若返回一个无效值，仍需要退出程序前调用`rkpq_deinit()`以释放相关资源。

#### rkpq_query()
接口作用:
根据`rkpq_query_cmd`条目查询SDK相关信息

接口定义：
```c
int rkpq_query(rkpq_context ctx, rkpq_query_cmd cmd, size_t size, void* info);
```

参数说明：
- `rkpq_context ctx`: `rkpq_context`对象，对于不需要传入`rkpq_context`的条目，可直接传入`NULL`
- `rkpq_query_cmd cmd`: 查询条目
- `size_t size`: 返回值变量对象的占用大小
- `void* info`: 返回值变量的指针

说明：

|       查询条目                     |  是否需要Context  |   返回值类型       |
| --------------------------------- |:-----------------:| ----------------- |
| RKPQ_QUERY_SDK_VERSION            |       no          | rkpq_version_info |
| RKPQ_QUERY_PERF_INFO              |       YES         | rkpq_perf_info    |
| RKPQ_QUERY_MODULES_SUPPORT        |       YES         | rkpq_module_info  |
| RKPQ_QUERY_MODULES_ROI_SUPPORT    |       YES         | rkpq_module_info  |
| RKPQ_QUERY_IMG_RES_CHANGE_SUPPORT |       no          | uint32_t          |
| RKPQ_QUERY_IMG_FMT_CHANGE_SUPPORT |       no          | uint32_t          |
| RKPQ_QUERY_IMG_FMT_INPUT_SUPPORT  |       no          | rkpq_imgfmt_info  |
| RKPQ_QUERY_IMG_FMT_OUTPUT_SUPPORT |       no          | rkpq_imgfmt_info  |
| RKPQ_QUERY_IMG_COLOR_SPACE_SUPPORT|       no          | rkpq_clrspc_info  |
| RKPQ_QUERY_IMG_BUF_INFO           |       no          | rkpq_imgbuf_info  |
| RKPQ_QUERY_IMG_ALIGNMENT_OCL      |       YES         | uint32_t          |
| RKPQ_QUERY_BUF_ALIGNMENT_OCL      |       YES         | uint32_t          |
| RKPQ_QUERY_RKNN_SUPPORT           |       YES         | uint32_t          |
| RKPQ_QUERY_MEAN_LUMA_OUTPUT       |       YES         | int32_t           |


#### rkpq_set_loglevel()
接口作用:
用于设置SWPQ库的输出log等级，有效值范围[0, 4]，信息量从少到多。

接口定义：
```c
int rkpq_set_loglevel(rkpq_context ctx, int logLevel);
```

参数说明：
- `rkpq_context ctx`: `rkpq_context`对象，将此参数设为`NULL`使日志等级全局生效。（目前暂不支持按实例设置日志等级）
- `int logLevel`: 表示log等级，有效值范围[0, 4]

#### rkpq_set_cache_path()
接口作用:
用于设置算法库缓存文件路径，包括：（存放OpenCL程序缓存，用于程序初始化加速）。
默认路径为`/data/rkalgo/`

接口定义：
```c
int rkpq_set_cache_path(rkpq_context ctx, const char *pPath, int target);
```

参数说明：
- `rkpq_context ctx`: `rkpq_context`对象，将此参数设为`NULL`使缓存路径全局生效。（目前暂不支持按实例设置缓存路径）
- `const char *pPath`: 缓存路径字符串，请以'/'结尾
- `int target`: 缓存目标类型，二进制位域取值/所需权限/对应功能说明如下:
  - 0x0 / rw- / 表示对所有类型都是用同一个缓存路径
  - 0x1 / rw- / 表示设置OpenCL的缓存文件路径
  - 0x2 / r-- / 表示设置RKNN模型文件路径
  - 0x4 / rw- / 表示存放license授权文件路径
  - 0x8 / r-- / 表示指定`librga.so`库文件的路径

#### rkpq_clear_caches()
接口作用:
清除在SDK内部输入输出fd-buffer对象的缓存，清除老旧的buffer缓存条目，避免占用过多的虚拟内存。

接口定义：
```c
int rkpq_clear_caches(rkpq_context ctx, int flag);
```

参数说明：
- `rkpq_context ctx`: `rkpq_context`对象，不可为`NULL`。
- `int flag`: 目前只能为1

使用说明：
- 要使用零拷贝功能必须要完成从`fd-buffer`到`OpenCL-buffer`的映射，为了提高性能，避免重复映射，SDK内部会缓存映射后的`fd-buffer`对象（目前上限32个），对外部采用**ring-buffer**的场景十分有效。
- SDK内部根据`nFdValue`值作为`key`来缓存映射后的`OpenCL-buffer`，由`nFdIndex`和`nBufferSize`作为缓存的一致性检验参数。
- 在`rkpq_context`正常调用`rkpq_deinit()`回收资源的情况下，所有`OpenCL-buffer`的缓存也会被清除，避免持续占用虚拟内存，避免造成内存泄漏。
- 但是`rkpq_context`未析构的情况下，当`fd-buffer`对象**存在释放和重新申请的操作时**（比如切换片源，或是切换码流，解码器会释放旧的一批次`fd-buffers`, 再申请一批次新的`fd-buffers`），**新申请的`fd-buffer`的`nFdValue`数值和大小可能会与之前释放的一致**，导致算法内部缓存的`OpenCL-buffer`对象无法和实际的`fd-buffer`不是对应关系，导致错误发生。具体表现为：
    - 存在一帧或多帧历史帧闪烁显示（输入`fd-buffer`与缓存不对应）
    - 存在一帧或多帧绿屏画面帧闪烁显示（输出`fd-buffer`与缓存不对应）
- 若出现上诉问题，可以调用此接口对失效的缓存进行清除。另外也可以：
    - 使用`setprop vendor.rkpq.io.cache.clear`命令进行临时手动缓存清除，强制`fd-buffer`重新映射；
    - 使用`setprop persist.vendor.rkpq.io.cache.enbale`命令进行临时禁用缓存功能，强制`fd-buffer`每帧都进行一次映射操作；
    - 最佳方式是获取`fd-buffer`的**唯一标识符**，并将其填至`rkpq_imgbuf_info::nFdIndex`属性上，由SDK进行一致性检验；
    - 次佳方式是为同一批次的`fd-buffers`设置同一个`nFdIndex`值，在批次变化时将此值自增。

#### rkpq_set_default_cfg()
接口作用:
用于还原指定模块的配置参数到默认值。

接口定义：
```c
int rkpq_set_default_cfg(void *pModuleConfig, rkpq_module module);
```

参数说明：
- `void *pModuleConfig`: SWPQ模块结构体对象指针（指针获取见`rkpq_get_default_cfg()`接口）
- `rkpq_module module`: SWPQ模块枚举值

#### rkpq_get_default_cfg()
接口作用:
用于获取pipeline中指定模块的配置参数指针，以便用户修改相关参数调整该模块的效果。

接口定义：
```c
void *rkpq_get_default_cfg(rkpq_context ctx, int pipeOrder, int module);
```

参数说明：
- `rkpq_context ctx`: `rkpq_context`对象
- `int pipeOrder`: 需要设置的模块在pipeline中的顺序索引，需要与`rkpq_init_params`里设定的一致
- `int module`: `rkpq_module`枚举值

#### rkpq_set_inputs() & rkpq_set_outputs()
接口作用:
用于设定pipeline的所有输入图像，主要用于支持多输入或多输出的模块（如`MSSR`模块）。
**支持多帧输入/输出、多种分辨率、多种图像格式**，每帧图像的详细完整信息记录在`rkpq_imgbuf_info`结构体内。

接口定义：
```c
int rkpq_set_inputs(rkpq_context ctx, rkpq_imgbuf_info *pInputBufs, int num);
int rkpq_set_outputs(rkpq_context ctx, rkpq_imgbuf_info *pOutputBufs, int num);
```

参数说明：
- `rkpq_context ctx`: `rkpq_context`对象
- `rkpq_imgbuf_info *pInputBufs`: 待输入的多帧图像结构体信息数组
- `rkpq_imgbuf_info *pOutputBufs`: 待输出的多帧图像结构体信息数组
- `int num`: 输入/输出图像帧数


## 4. 快速部署和集成
### 4.1. 集成调用示例
随SDK提供的几个详细的调用示例如下：
- 通用SWPQ处理流程调用示例：[rkpq_demo_common_pipeline.cpp](../demo/rkpq_demo_common_pipeline.cpp)
- `MIX-SSMR`模块使用调用示例：[rkpq_demo_mssr.cpp](../demo/rkpq_demo_mssr.cpp)
- 其他多个应用场景的调用示例：[rkpq_demo.cpp](../demo/rkpq_demo.cpp)

### 4.2 仿真程序使用
使用可执行程序进行仿真前先使用`update_32bit.bat`或`update_64bit.bat`脚本先将可执行程序`rk_swpq_exe`与库文件`librkswpq.so`推送到`/vendor`对应目录下，且添加对应可执行权限。

在板端执行`adb shell rk_swpq_exe -h` 获取可执行程序执行说明，这里对命令行参数说一下说明：

执行命令: `adb shell rk_swpq_exe -f=sim` 可对当前swpq算法库编译时指定的流程进行仿真（主要供内部测试使用）；
执行命令: `adb shell rk_swpq_exe -f=unpack` 可对输入的紧凑型YUV文件（如NV15、NV30、RGB565等格式）进行解码，转成非紧凑的图像以便在看图软件上可视化图像；

其中仿真部分的执行命令为: `adb shell rk_swpq_exe -f=sim <input_options> <output_options> <proc_flags>`，其中

`input_options`有:
  - -i=<input_file>, <font color=Red>必填</font>，指定输入文件路径。
  - -sw=<src_width>, <font color=Red>必填</font>，指定输入图像像素宽度。
  - -sh=<src_height>, <font color=Red>必填</font>，指定输入图像像素高度。
  - -sf=<src_format>, <font color=Red>必填</font>，指定输入图像的像素格式，取值为`enum rkpq_img_fmt`。
  - -sc=<src_color_space>, 选填，指定输入图像色彩空间，取值为`enum rkpq_clr_spc`，默认值为1（即`RKPQ_CLR_SPC_YUV_601_FULL`）。
  - -sa=<src_align>, 选填，指定输入图像行方向的对齐量，单位为byte.
  - -sd0=<src_stride0>, 选填，指定输入图像第1个平面虚宽，单位为byte; 未指定情况下会自动计算。
  - -sd1=<src_stride1>, 选填，指定输入图像第2个平面虚宽，单位为byte; 未指定情况下会自动计算。
  - -sd2=<src_stride2>, 选填，指定输入图像第3个平面虚宽，单位为byte; 未指定情况下会自动计算。

`output_options`有:
- -o=<output_file> , 选填，指定输出文件路径，未指定的情况下输出文件将会被设置成`"/data/dump/rkpq_result_WxH.fmt"`。
  可通过log查看输出文件路径。（**请确保输出文件所在路径存在！**）
- -dw=<dst_width>, 选填，指定输出图像像素宽度。若未指定，则与输入一致（会自动64像素对齐）。
- -dh=<dst_height>, 选填，指定输出图像像素高度。若未指定，则与输入一致。
- -df=<dst_format>, 选填，指定输出图像像素格式。若未指定，则与输入一致。
- -dc=<dst_color_space>, 选填，指定输出图像色彩空间。若未指定，则与输入一致。
- -da=<src_align>, 选填，指定输出图像行方向的对齐量，单位为byte.
- -dd0=<dst_stride0>, 选填，指定输出图像第1个平面虚宽，单位为byte；若未指定，则与输入一致。
- -dd1=<dst_stride0>, 选填，指定输出图像第2个平面虚宽，单位为byte；未指定情况下会自动计算。
- -dd2=<dst_stride0>, 选填，指定输出图像第3个平面虚宽，单位为byte；未指定情况下会自动计算。

`proc_flags`有:
  - -csc=0/1, 开关CSC模块。
  - -dci=0/1, 开关DCI模块。
  - -acm=0/1, 开关ACM模块。
  - -zme=0/1, 开关ZME模块。
  - -shp=0/1, 开关SHP模块。
  - -sr=0/1, 开关SR模块。
  - -n=<num_frames>, 指定处理帧数，默认为1

**注：允许adb属性控制时，以上模块开关和某些参数可能会被adb属性强制覆盖！**
程序执行完毕后，依照log提示，将输出文件导出，检查结果。


## 5. 调试和调校工具
### 5.1 通过PQTool进行参数调校
见《Rockchip_PQTool_Guide》。

### 5.2 通过Andoird属性或Linux环境变量进行参数调校
在Android系统下可以通过 `adb properties` 来 debug 和 tuning

在Linux系统下可以通过环境变量完成同样的功能

支持的 `adb properties` 有:

| Android属性名称 | Linux环境变量名称 |  取值范围 | 控制行为 | 备注 |
| --------------- | ----------------- | ------- | -------- | ---- |
| persist.vendor.rkpq.watermark | rkpq_watermark | [0, 1, 2] | 是否显示水印 | 开启后在零拷贝模式且没有虚地址传入的情况下，会做mmap，影响帧率 |
| persist.vendor.rkpq.loglevel  | rkpq_loglevel | {[0, 4], 603892, 603893} | 控制log等级 | log等级超过INFO，会影响帧率 |
| persist.vendor.rkpq.logstep   | rkpq_logstep | [0, 512] | 控制log显示频率 | 目前仅少部分log受此属性影响，推荐通过设置log等级来控制日志输出量 |
| vendor.rkpq.dump              | rkpq_dump | [0, 15] | 控制dump行为 | 见后文详解 |
| persist.vendor.rkpq.init_flag | rkpq_init_flag | bitfield | 覆盖`rkpq_init_params::nInitFlag`的值 | 需要在`rkpq_init()`接口调用前才会生效 |
| vendor.rkpq.roi.enable        | rkpq_roi_enable | {0, 1} | 控制ROI行为开关 | 目前仅支持DCI/ACM/AI-SR/AI-DM/AI-DFC模块 |
| ~~persist.vendor.rkpq.all.prop_cover~~ | \ | {0, 1} | **强行覆盖设置标志** | 设1后由adb properties设定的参数会强制覆盖输入参数 |
| persist.vendor.rkpq.io.cache.enable | rkpq_io_cache_enable | {0, 1} | 控制IO缓存行为 | 设0后强制关闭buffer缓存功能 |
| persist.vendor.rkpq.io.cache.limit  | rkpq_io_cache_limit  | \      | 控制IO缓存上限 | 0表示默认值(32)，负数等效于关闭buffer缓存功能 |
| vendor.rkpq.io.cache.clear          | rkpq_io_cache_clear  | {0, 1} | 控制IO缓存行为 | 每次设一个不同的数字，对缓存buffer做一次清除操作 |
| persist.vendor.rkpq.io.alignUnitPixel | rkpq_io_alignUnitPixel | {0, 1} | 改变buffer对齐单位 | 设1后强制将对齐单位由Byte改为Pixel，在一些低版本的设备上可能需要 |

注：
1. ~~所有可设的属性以文档《pq_tuning.bat》为准。~~
2. Android属性中以'test'开头的字段，需要关闭SELinux才可以生效。 (`adb shell setenforce 0`)

### 5.3 通过dump输入输出文件进行效果验证
```shell
adb shell setprop persist.vendor.rkpq.dump <X>
```
\<X\> 为二进制数`0bxxxx`， **从低到高位**分别表示 dump 所有输入, 所有输出, 单帧输入, 单帧输出。

**有效数值列表**

| X取值 | 十六进制值 | dump行为解释        | 生效条件 |
|:-----:|:-------:|:--------------------|:---------|
| 1     | 0x01    | dump所有输入        | 在`rkpq_init()`调用前设置此属性才能生效 (**deprecated**) |
| 2     | 0x02    | dump所有输出        | 在`rkpq_init()`调用前设置此属性才能生效 (**deprecated**) |
| 4     | 0x04    | 按帧dump即时输入    | `/data/dump/rkpq.dump.src.cfg`内指定帧数后生效 |
| 8     | 0x08    | 按帧dump即时输出    | `/data/dump/rkpq.dump.dst.cfg`内指定帧数后生效 |
| 16    | 0x10    | \                  | \ |
| 32    | 0x20    | dump每个子模块的输出| 程序对`/data/dump/`有写入权限时生效 |
| 12(4+8)| 0x0c   | 按帧dump即时输入+输出| 同4,8 |
| 44(4+8+32)| 0x2c| 按帧dump即时输入+输出和每个子模块输出 | 对应条件生效后其对应dump功能开启 |

**举例**
```shell
# dump所有输入
adb shell setprop persist.vendor.rkpq.dump 1
# dump所有输出
adb shell setprop persist.vendor.rkpq.dump 2
# 按帧dump输入，从命令生效后开始的连续独立3帧
adb shell setprop persist.vendor.rkpq.dump 4
adb shell "echo 3 >> /data/dump/rkpq.dump.src.cfg"
# 按帧dump输出，从命令生效后开始的连续独立1帧
adb shell setprop persist.vendor.rkpq.dump 8
adb shell "echo 1 >> /data/dump/rkpq.dump.dst.cfg"
```

若要按帧即时dump 5帧输入和输出，则X的值为`0b1100 = 12`
按照一下顺序执行
```shell
# 先执行echo设置帧数
echo 5 >> /data/dump/rkpq.dump.src.cfg          # 命令1
echo 5 >> /data/dump/rkpq.dump.dst.cfg          # 命令2
# 再执行dump行为值设定命令
adb shell setprop persist.vendor.rkpq.dump 12   # 命令3
```
按照以上的顺序执行，可以保证dump下来的输入和输出是相互对应的。
如果先执行命令3，在执行命令1和2，**大概率会造成输入输出不对应的情况**。因为在命令1执行后且命令2执行前，命令1的行为已经生效。

**检查dump是否有效**
在/data/dump目录下检查是否有`rkpq_<W>x<H>_dump_<src/dst>_#<frame_id>_<image_format>.bin`文件生成。
可通过检查log信息来确认dump行为是否有效：
```bash
# dump成功时，log提示示例
: Dump src frame #1566 (size:8294400+4147200+0=12441600), use cmd to pull this file:
:    adb pull <dump_file>

# dump失败时，log提示示例
: Failed to dump src frame #63298, Permission denied
```


## 6. 错误和异常分析
### 6.1. OpenCL相关错误码说明

OpenCL错误码请见其头文件定义`cl.h`，常见于`rkpq_init()`初始化调用错误中。
这里总结了一些**OpenCL使用中常见的错误码**如下，以便自查错误原因并快速定位错误位置:

(`html`表格。如显示异常，请更换支持`html`的`Markdown`渲染器)
<table>
  <tr align="left">
    <td> 错误类型 </td>
    <td> 错误码 </td>
    <td> 宏名称 </td>
    <td> 错误解读 </td>
    <td> 解决思路 </td>
  </tr>

  <tr align="left">
    <td rowspan="3"> 设备特性支持错误 </td>
    <td> -10 / -39 </td>
    <td> CL_IMAGE_FORMAT_NOT_SUPPORTED / CL_INVALID_IMAGE_FORMAT_DESCRIPTOR </td>
    <td> 图像格式不支持 </td>
    <td rowspan="3"> 往往是OpenCL版本过低或设备不支持某些特性导致，请升级OpenCL版本或更换设备 </td>
    <tr>
      <td> -1 </td>
      <td> CL_DEVICE_NOT_FOUND </td>
      <td> 无法找到(GPU)设备 </td>
    </tr>
    <tr>
      <td> -2 / -33 </td>
      <td> CL_DEVICE_NOT_AVAILABLE / CL_INVALID_DEVICE </td>
      <td> (GPU)设备无法使用 </td>
    </tr>
  </tr>

  <tr align="left">
    <td rowspan="5"> 内存相关错误 </td>
    <td> -6 </td>
    <td> CL_OUT_OF_HOST_MEMORY </td>
    <td> 内存越界 </td>
    <td rowspan="5"> 未对齐，越界，buffer大小不匹配等因素导致 </td>
    <tr>
      <td> -12 </td>
      <td> CL_MAP_FAILURE </td>
      <td> buffer映射失败 </td>
    </tr>
    <tr>
      <td> -13 </td>
      <td> CL_MISALIGNED_SUB_BUFFER_OFFSET </td>
      <td> buffer对齐量不符要求 </td>
    </tr>
    <tr>
      <td> -61 </td>
      <td> CL_INVALID_BUFFER_SIZE </td>
      <td> buffer大小不对 </td>
    </tr>
  </tr>
</table>

遇到除表上所诉外的其他错误码，请联系算法库维护同事分析解决。

### 6.2. PQ程序错误码说明

PQ程序错误码如下：

| 返回值 | 返回值宏名称 | 错误解读 |
| ------ | ---------- | -------- |
| 0  | RK_SUCCESS | 无错误 |
| -1 | RK_ERR_FAILURE | 未知错误 |
| -2 | RK_ERR_TIMEOUT | 超时错误 |
| -3 | RK_ERR_INIT_FAILURE | 初始化错误 |
| -4 | RK_ERR_INVALID_PROCESSOR | 无效的执行对象 |
| -5 | RK_ERR_NULL_POINTER | 空指针错误 |
| -6 | RK_ERR_MALLOC_FAILURE | malloc错误 |
| -7 | RK_ERR_INVALID_VIR_ADDR | 无效的虚地址 |
| -8 | RK_ERR_INVALID_ARGS | 无效的函数实参 |
| -9 | RK_ERR_INVALID_CFGS | 无效的配置参数 |
| -10 | RK_ERR_UNSUPPORTED_DEVICE | 不支持的设备 |
| -11 | RK_ERR_UNSUPPORTED_CASE | 不支持的选项 |
| -12 | RK_ERR_UNSUPPORTED_FEATURE | 不支持的特性 |
| -13 | RK_ERR_UNKNOWN_DEVICE | 未知设备 |
| -14 | RK_ERR_UNKNOWN_CASE | 未知选项 |
| -15 | RK_ERR_UNKNOWN_FEATURE | 未知特性 |
| -16 | RK_ERR_CANCELED | 取消操作 |
| -17 | RK_ERR_DIVISION_BY_ZERO | 除零操作 |
| -20 | RK_ERR_FILE_OPEN_FAIL | 打开文件失败 |
| -21 | RK_ERR_FILE_NOT_EXIST | 文件不存在 |
| -22 | RK_ERR_FILE_NO_PERMISSION | 无权限操作文件 |
| -25 | RK_ERR_DIR_ACCESS_FAIL | 访问目录失败 |
| -26 | RK_ERR_DIR_NOT_EXIST | 目录不存在 |
| -27 | RK_ERR_DIR_NO_PERMISSION | 无权限操作目录 |
| -30 | RK_ERR_LACK_OF_MEMORY | 缺少内存空间 |
| -31 | RK_ERR_OUT_OF_MEMORY | 访问超出内存范围 |
| -32 | RK_ERR_OUT_OF_RANGE | 访问超出有效范围 |
| -33 | RK_ERR_INVALID_MEM_OBJECT | 无效的内存对象 |
| -50 | RK_ERR_NO_INPUT_IMAGE | 未指定输入图像 |
| -51 | RK_ERR_NO_OUTPUT_IMAGE | 未指定输出图像 |
| -52 | RK_ERR_INVALID_IMAGE_FORMAT | 无效的图像格式 |
| -53 | RK_ERR_INVALID_IMAGE_DEPTH | 无效的图像深度 |
| -54 | RK_ERR_INVALID_IMAGE_SIZE | 无效的图像尺寸 |
| -60 | RK_ERR_INVALID_BUFFER_SIZE | 无效的缓冲区大小 |
| ... | ... | ... |

### 6.3. 常见异常现象分析解答
1. 输出图像明显被放大且只显示了约原图左上角1/4左右的区域，或仅左上角1/4区域有内容
    - 存在分辨率放大的模块(如ZME/AISR等)没有正确地开启或关闭，或者输出图像的分辨率大小设置不正确。

2. 输出图像亮度/对比度/色调/饱和度怪异
    - 检查每个开启模块的配置参数是否有初始化，以及取值是否在合理的范围。
    - 可调用`rkpq_set_default_cfg`接口将配置的配置参数设为默认值，再对对应的参数进行修改。
    - 可能造成这些影响的模块有：CSC, DCI, ACM 等。

3. 输出图像全黑，开启水印后有水印显示
    - 若CSC模块开启，请检查`rkpq_csc_cfg`参数是否正确，`nBrightness/nR[/G/B]Gain = 0`时图像会变黑。

4. 输出图像有重影或者花屏，水印显示不正确
    - 一般是虚宽配置不对造成。可以打开dump功能，dump输入与输出。根据dump出来的图像分析输入和输出的虚宽是否正确。
    - 在3.2小节对`rkpq_imgbuf_info`结构体的介绍中，有提到虚宽计算容易出错的地方，可参考内容进行分析。

5. 输出图像绿屏
    - LOG没有错误：可能是该版本SDK未支持的某些模块被开启，可查询`RKPQ_QUERY_MODULES_SUPPORT`条目获取当前版本支持的模块。
    - LOG里有错误`CL_MISALIGNED_SUB_BUFFER_OFFSET`: 可能是输入输出图像buffer没有对齐量，造成OpenCL映射buffer错误，建议修改图像buffer的对齐量。
    - LOG里有错误`No enough src(or dst) buffer size (xxxx) < frame size (xxxx)`, buffer的大小参数传入错误，应该不小于图像的大小。

6. 输出图像Y通道正常，UV通道有重复性条纹
    - 可能是Y和UV的像素对齐量不一致导致，可以dump输入输出确认Y通道和UV通道的虚宽是否正确。
    - 分辨率较小时往往存在对齐虚宽，图像的对齐量可能与预期不符。
    - UV通道交织于第二个平面时（有2个元素）与Y平面（1个元素）的对齐量计算方法一致，但不符合图像的默认排列方式。
    - 可参考3.2小节`rkpq_imgbuf_info`结构体的介绍中对对齐要求的说明

7. 调用`rkpq_init()`错误，初始化失败，可能有如下log输出：
    ```
    --e-- rkpq_init() failed! -46
    Failed to call rk_vop_init()! Exitng...
    ```
    错误码-46为OpenCL相关元素初始化失败报错，请检查以下内容：
    - OpenCL库文件是否存在或有读取权限；
    - OpenCL版本是否大于1.2；
    - 检查OpenCL错误代码（"OpenCL error with code xxxx"）：
      - `CL_INVALID_KERNEL_NAME`，可能是旧版本SDK未规避不支持的模块，请更新使用的SDK版本；也有可能是本地的OpenCL程序文件被破坏或与SDK版本不符，可使用命令`rm /data/rkalgo/*_cl.bin`删除这些文件文件后重新让程序执行初始化；
      - `CL_OUT_OF_HOST_MEMORY`，一般是`rkpq_proc_params::nSrcBufSize`或`rkpq_proc_params::nDstBufSize`设置过大，超出了实际的buffer大小，请检查buffer的实际大小并修正此参数；
      - `CL_INVALID_WORK_GROUP_SIZE`，可能是图像分辨率和大小等信息与实际不符，请检查传入的图像信息参数；
      - `CL_MISALIGNED_SUB_BUFFER_OFFSET`，图像分辨率可能太小，或者对齐量不足，导致OpenCL使用错误，请调大对齐量或者图像分辨率

8. 水印显示有误
    - 检查水印属性是否开启，可通过LOG关键字`watermark`确保水印flag开启，且输出**图像宽度大于等于720**.
    - 水印和图像均显示错位，大概率是输出图像虚宽配置不正确。
    - 水印显示错位，输出图像显示正常，有可能混淆了图像的宽和高两个参数。

9. 显示画面每隔几帧会发生闪烁，闪烁内容是之前的画面
    - 执行命令`adb shell setprop vendor.rkpq.io.cache.clear 1`，查看是否解决问题，如果解决问题，则原因如下：
      - fd-buffer存在释放和重新申请的操作，新申请的buffer的fd数值与之前释放的一致，导致算法内部缓存的buffer数据无法和实际buffer对应上，往往在输入信号源变化时发生；
      - `setprop vendor.rkpq.io.cache.clear`命令清除了算法内的缓存，强制fd-buffer重新映射，故能解决该问题；
      - 最佳方式是获取fd-buffer的**唯一标识符**，并将其填至`rkpq_imgbuf_info::nFdIndex`属性上。

### 模块输入输出及平台性能总表

| 模块名称 | 输入格式 | 输出格式 | 支持ROI | 平台    | GPU占用率 (%) | 带宽占用 (Gbps) | 耗时 (ms) | 备注 |
|----------|----------|----------|---------|---------|---------------|-----------------|-----------|------|
| **CSC**  | YUV4xxSP_8/10bit, VU24, RGB系列 | YUV4xxSP_8/10bit, VU24, RGB系列 | 否 | RK3588 | 5%@(1080P→RGB) | GPU-0.560 | 2.0 | **Color Space Conversion** 模块，支持Full/LimitedRange色彩空间转换[YUV2RGB,RGB2YUV] |
|          |          |          |         | RK3568 | 30%@(1080P→RGB) | GPU-0.5370 | 7.0 |  |
|          |          |          |         | RK3399 | 27%@(1080P→RGB) | GPU-0.5280 | 6.5 |  |
| **DCI**  | YUV4xxSP_8bit, VU24, Y8 | 同输入格式 | 是 | RK3588 | 7%@(1080P NV12) | GPU-0.5370 | 2.5 (统计+处理) | **Dynamic Contrast lmprovement**模块,根据图像直方图信息智能动态调整画面的对比度和层次感仅处理Y通道 |
|          |          |          |         | RK3568 | 55%@(1080P NV12) | GPU-0.5250 | 8.0+5.0 |  |
|          |          |          |         | RK3399 | 32%@(1080P NV12) | GPU-0.5190 | 4.5+4.5 |  |
| **ACM**  | YUV4xxSP_8bit, VU24 | 同输入格式 | 否 | RK3588 | 4%@(1080P NV12) | GPU-0.5380 | 1.5 | **Auto Color Management**模块，基于HSV色彩空间调节用户感兴趣的色相，比如天空蓝色人像肤色、植物绿色等 |
|          |          |          |         | RK3568 | 31%@(1080P NV12) | GPU-0.5250 | 7.0 |  |
| **SHP**  | YUV4xxSP_8bit, VU24, Y8 | 同输入格式 | 否 | RK3588 | 7%@(1080P NV12) | GPU-0.5280 | 2.0 | **Sharpnees**模块，根据图像的高频信息，选择性增强不同频段能量，提高清晰度.仅处理Y通 |
|          |          |          |         | RK3568 | 50%@(1080P NV12) | GPU-0.5170 | 10.0 |  |
| **ZME**  | YUV4xxSP, VU24, RGB系列, Y8/UV88 | 同输入格式（支持缩放） | 否 | RK3588 | 10%@(540P→1080P) | GPU-0.5570 | 3.5 | **Zoom Management Engine**模块，支持任意倍率缩放 |
|          |          |          |         | RK3568 | 53%@(540P→1080P) | GPU-0.5190 | 24.0 |  |
| **AISR** | YUV4xxSP_8bit, VU24, Y8 | 2x放大（如1080P→4K） | 是 | RK3588 | 18%@(1080P→4K) | NPU-10 | 16.0 | **Al super-resolution**模块，支持任意倍率放大 |
|          |          |          |         | RK3568 | 22%@(540P→1080P) | NPU-0.780 | 25.0 |  |
| **AISD** | YUV/RGB系列 | 场景得分 | 否 | RK3588 | 2%@(1080P NV12) | NPU-0.720 | 4.0 | **Al  scene detection**场景分类(建筑，人像，植物，天空，食物)识别不同场景智能动态调整参数，使得蓝天场景更蓝，绿色植物更绿，肤色更加自然等 |
| **AIDM** | YUV420SP_NV12, Y8 | 同输入格式 | 是 | RK3568 | 35%@(1080P NV12) | NPU-0.640 | 15.5 | **Al De mosquito noise** 去压缩蚊虫噪声，仅RK356X平台 |
| **AIDFC** | YUV420SP_NV12 | YUV444SP_NV24/RGBA | 是 | RK3576 | 30%@(1080P NV12) | N/A | 28 | **Al De false color** 对比RGB或者YUV444信号针对YUV420丢失的高频色彩伪色还原，特别是excel表格中的彩色文字等 |
| **MixMSSR** | 多种分辨率组合（如540P NV24） | 目标分辨率（如1080P NV12） | 否 | RK3576 | 5%~45%(720p->4k & 24/25/30fps->60fps) | 复杂多模型(maxup to 11) | 可变 | 支持**插帧(MEMC)**，**超分(SR)** 混合处理,由于3576平台集成了硬件PQ处理模块，因此只在RK3576平台支持MixMSSR模块 |

### 关键说明：
1. **输入输出格式**
   - **YUV4xxSP**: 包含NV12/YUV420SP、NV16/YUV422SP、NV24/YUV444SP等格式
   - **RGB系列**: 包含RGBA8888、RGB888、RGB565等格式（含BGR排列）
   - **Y8/UV88**: 单通道或双通道灰度格式

2. **性能数据**
   - 表中数据基于文档实测值，实际性能可能因系统负载、频率配置等略有波动
   - **NPU带宽**: AI模块涉及NPU计算时需额外考虑模型推理带宽（如AISR在RK3588上NPU带宽约10GB/s）

3. **平台限制**
   - **RK3399**: 仅支持部分基础模块（CSC/DCI/ZME）
   - **RK3576**: 新增支持AIDFC/AIDD/AIDHW等AI模块
   - **AI模块依赖RKNN版本**（如AISR需≥1.4，AIDFC需≥1.5）

4. **特殊场景**
   - **零拷贝模式**: 需正确配置`rkpq_imgbuf_info`中的`nFdValue`和`nFdIndex`
   - **异步处理**: MixMSSR等模块支持异步模式，会增加1-2帧延迟
