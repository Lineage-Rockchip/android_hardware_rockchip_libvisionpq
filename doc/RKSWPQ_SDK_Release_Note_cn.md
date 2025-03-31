# RKSWPQ SDK Release Note

## v0.21.1.4734 Release Note | 2025.07.04
  - [MSSR] RK3576平台调整DFCSR通路CSC系数range解决运动区域拖影残留问题

## v0.21.0.4711 Release Note | 2025.06.26
  - [MSSR] 更新Api的`rkpq_mssr_procflag`：增加`RKPQ_MSSR_PROC_FLAG_SHP`功能选项
  - [MSSR] 更新Api的`rkpq_mssr_cfg`：增加`nSrcFps`和`nDstFps`配置输入和输出帧率
  - [MSSR] RK3562平台MSSR2通路部分处理分支增加可选Sharp功能
  - [MSSR] RK3562平台MSSR2通路`schemeIdx=0`分支修正数据冲突问题

## v0.20.7.4685 Release Note | 2025.06.19
  - [MSSR] RK3576平台更新DFCSR通路，目前已支持`1080pNV12->1080pBGRA/1080pNV24`、`1080pNV12->4kNV12/4kNV24/4kRGB/4kBGRA`、`1080pRGB->4kNV12/4kNV24/4kRGB`等9个处理分支

## v0.20.6.4677 Release Note | 2025.06.18
  - [MSSR] RK3576平台更新DFCSR通路兼容解码输入和HDMI输入，修正bug
  - [MSSR] RK3576平台更新DFCSR通路，目前已支持`1080pNV12->4kNV12/4kNV24`、`1080pRGB->4kNV12/4kNV24/4kRGB`等5个处理分支

## v0.20.5.4672 Release Note | 2025.06.17
  - [MSSR] RK3576平台优化DFCSR通路算法效果（针对解码通路优化效果）

## v0.20.4.4668 Release Note | 2025.06.12
  - [MSSR] RK3576平台调整DFCSR通路时序优化性能和效果

## v0.20.3.4660 Release Note | 2025.06.11
  - [MSSR] RK3562平台支持`rkpq_mssr_cfg::nProcFlag`配置`0`，执行直接拷贝输出
  - [MSSR] RK3562平台增加内部直方图统计优化场景切换过渡
  - [MSSR] RK3576平台DFCSR处理通路新加支持`1080pRGB->4kRGB/4kNV24`处理分支（支持SD+BSR/TSR）
  - [MSSR] 修正`静态横幅文字插帧后闪烁`问题

## v0.20.2.4641 Release Note | 2025.06.05
  - [MSSR] RK3576平台DFCSR处理通路新加支持`1080pRGB->4kRGB`处理分支（只支持SD+BSR）
  - [MSSR] RK3562平台MSSR2通路新加支持`schemeIdx=0`的特殊分支（新加模型）

## v0.20.1.4625 Release Note | 2025.05.29
  - [MSSR] 支持`720pNV12`输入输出的MEMC处理通路
  - [MSSR] RK3562平台新加支持schemeIdx=3的ME模型
  - [MSSR] 修正ME前处理通路分支条件
  - [IO] 修正非对齐输出buffer在计算平均亮度时可能会崩溃的错误以及可能存在的`cache line`未同步错误。

## v0.20.0.4577 Release Note | 2025.05.20
  - [LDC] 新加LDC(Lens Distortion Correction)模块，支持梯形畸变校正、枕形畸变矫正，支持`NV12`/`NV24`/`RGBX`/`BGRX`等格式
  - [MSSR] DFC通路增加支持`1920x1200NV12->1920x1200BGRA`处理分支
  - [MSSR] 修正水印SR开关状态与属性值不匹配的问题

## v0.19.2.4552 Release Note | 2025.05.14
  - [MSSR] 修正Linux平台下内部直方图未初始化导致外部传入直方图数据错误解析的问题

## v0.19.1.4549 Release Note | 2025.05.14
  - [DBL] 更新RK3588平台AIDeblurSR模块，支持单进单出参数配置
  - [MSSR] 更新RK356X平台MSSR模块支持SD和SR功能

## v0.19.0.4538 Release Note | 2025.05.12
  - [ALL] 针对大部分图像分辨率不满足OpenCL NDRange条件的直方图统计行为进行了效率优化。
  - [LD] 模块接口调整 （by LinQiqi）
  - [DBL] RK3588平台新加支持AIDeblurSR模块，支持`1080pBGR->4kNV24`处理通路

## v0.18.5.4506 Release Note | 2025.05.06
  - [MSSR] RK3562平台的SR和SD模型改用bin加密文件
  - [SHP] RK3576和RK3562的SHP模块改为Lite模式
  - [ALL] 更新各模块在各平台的参考性能总表

## v0.18.4.4498 Release Note | 2025.04.29
  - [MSSR] 更新RK3588平台MSSR2通路的SD、DC、ME模型
  - [MSSR] 新加RK3562、RK356X平台支持部分分辨率的MEMC、SR功能

## v0.18.3.4433 Release Note | 2025.04.11
  - [MSSR] 更新`1080pNV12->1080pBGRA`的DFC处理通路部分默认参数，优化闪烁问题

## v0.18.2.4431 Release Note | 2025.04.11
  - [MSSR] 新加支持`1080pNV12->1080pNV24`的DFC处理通路，修正黑色区域出现绿色花图问题
  - [MSSR] 更新`1080pNV12->4kNV12`的DFC+SR处理通路，增加切换过渡处理

## v0.18.1.4417 Release Note | 2025.04.08
  - [ALL] OpenCL库增加`/system/lib64/libOpenCL-system.so`搜索选项

## v0.18.0.4415 Release Note | 2025.04.07
  - [MSSR] 新加支持`SD`通路：输入256x256RGB数据，输出场景检测结果数据

## v0.17.6.4403 Release Note | 2025.04.03
  - [MSSR] 更新`1080pNV12->1080pBGRA`的DFC处理通路优化效果

## v0.17.5.4391 Release Note | 2025.04.01
  - [MSSR] 水印支持显示system属性配置的帧率

## v0.17.4.4389 Release Note | 2025.03.31
  - [MSSR] 新加支持`1080pNV12->1080pBGRA`的DFC处理通路

## v0.17.3.4348 Release Note | 2025.03.18
  - [MSSR] 新加支持`1080pNV12->4kNV12`的DFC处理通路
  - [MSSR] 修正RGA拷贝高度非偶数对齐数据失败的问题

## v0.17.2.4330 Release Note | 2025.03.12
  - [MSSR] 修正SR通路非标准4k绿帧问题
  - [MSSR] 更新DFCSR通路：更新模型优化效果

## v0.17.1.4326 Release Note | 2025.03.11
  - [MSSR] 增加DFCSR通路：支持1080pNV12->4kNV12处理通路
  - [MSSR] 修正HDMI通路属性关闭MEMC时出现的闪帧问题

## v0.17.0.4312 Release Note | 2025.03.06
  - [IO] 修正`RGB565`和`BGR565`格式无法使用的错误；修正`RKPQ_IMG_FMT_NV15`到`RKPQ_IMG_FMT_VU24`格式转换的输出错误。
  - [IO/CSC] 增加`RKPQ_IMG_FMT_LEGACY420`格式输入支持，允许转换输出为`RKPQ_IMG_FMT_NV24`/`RKPQ_IMG_FMT_NV16`/`RKPQ_IMG_FMT_NV12`三种格式。

## v0.16.7.4292 Release Note | 2025.03.04
  - [MSSR] 进一步优化4k视频播放卡顿问题

## v0.16.6.4273 Release Note | 2025.02.28
  - [MSSR] 优化4k视频播放卡顿问题

## v0.16.5.4271 Release Note | 2025.02.25
  - [MSSR] 引入`android_dlopen_ext`增强`dlopen`的相关权限
  - [MSSR] 左右边界黑竖线闪现问题优化

## v0.16.4.4256 Release Note | 2025.02.18
  - [MSSR] 修改输出帧数：当关闭MEMC时只输出一帧

## v0.16.3.4233 Release Note | 2025.02.07
  - [MSSR] 更新输出当前算法功能开关状态：改成写出状态信息文件`data/ProcStatus.dat`，可以属性配置写出频次，默认不写出

## v0.16.2.4230 Release Note | 2025.02.06
  - [ALL] OpenCL缓存文件内置写出权限改为664
  - [MSSR] 增加输出当前算法功能开关状态，调用后台线程写出状态值到属性`persist.vendor.rkpq.mssr.proc_status`，属性值含义参考`rkpq_mssr_procflag`，可以属性配置写出频次

## v0.16.1.4220 Release Note | 2025.02.05
  - [BLR] 算法级优化性能
  - [ALL] 更新API接口`rkpq_set_callback()`回调函数提升稳定性

## v0.16.0.4209 Release Note | 2025.01.24
  - [ALL] 新增API接口`rkpq_prefetch_bufs()`，用于异步预导入帧缓存数据，减少主线程等待时间。
  - [ALL] 新增API接口`rkpq_set_callback()`，用于设置回调函数，目前可用于OpenCL缓存文件的自定义读写，以绕过Android相关权限问题。
  - [MSSR] 优化星空画面MEMC效果
  - [MSSR] 解码通路改成与HDMI通路一致：增加Api输出运动状态参数
  - [MSSR] 修复SR通路重置状态Y和UV不同步导致的重影问题

## v0.15.2.4161 Release Note | 2025.01.09
  - [MSSR] 更新ME模型优化效果

## v0.15.1.4150 Release Note | 2025.01.08
  - [MSSR] 更新实际帧率检测功能，防止数据冲突

## v0.15.0.4146 Release Note | 2025.01.07
  - [AUTH] 新增API接口`rkpq_set_auth_info()`，用于直接传递授权相关信息，避免因权限等问题导致授权信息读取失败的困扰。
  - [CSC] 修正`YUV4xxSP => YUV444I`转换执行错误的问题。
  - [MSSR] 更新Api: `rkpq_mssr_procflag`新加`RKPQ_MSSR_PROC_FLAG_FRD`选项用于实际帧率检测，`rkpq_mssr_cfg`增加数组`uint32_t aFrameRateInfo[2]`用于输出帧率信息
  - [MSSR] 新加支持RK356X平台`540pNV12->1080pNV12`的SR处理通路
  - [IO] 增加对**RGBA/BGRA**格式输入输出时**Alpha**通道的拷贝处理（需要通过pipeline最前和最后的两个CSC模块实现）。

## v0.14.4.4090 Release Note | 2024.12.18
  - [ALL] OpenCL库增加`/system/lib/libOpenCL-system.so`搜索路径

## v0.14.3.4088 Release Note | 2024.12.18
  - [MSSR] 更新SR通路支持4kRGB输入时整数帧不输出、非整数帧输出

## v0.14.2.4086 Release Note | 2024.12.17
  - [MSSR] 更新MSSR2通路非标准4kNV12输入分辨率时的帧拷贝性能和效果修正
  - [ALL] OpenCL库增加`/system/lib/libGLES_mali.so`搜索路径

## v0.14.1.4082 Release Note | 2024.12.16
  - [MSSR] 新加RK356X平台支持（暂只支持部分功能）
  - [MSSR] 新加支持非标准分辨率NV12格式输入输出，如`2048x1080`、`2560x1440`、`4096x2160`等

## v0.14.0.4068 Release Note | 2024.12.12
  - [MSSR] 更新Api：`rkpq_mssr_cfg`新加`bEnableHDMI`参数，`rkpq_sr_cfg`新加`nSRStrength`参数，用于区分`codec`和`hdmi`不同输入及相关参数配置
  - [MSSR] 修正CPU绑核失败导致GPU跑挂的问题
  - [ALL] 将OpenCL缓存二进制文件名区分32位和64位，使得同一环境可以切换调用32位和64位算法库

## v0.13.12.4049 Release Note | 2024.12.10
  - [MSSR] 调整MSSR2通路部分log等级

## v0.13.11.4048 Release Note | 2024.12.06
  - [MSSR] 更新SR通路支持1080pNV24输入输出、4kRGB输入输出的50fps或60fps处理通路

## v0.13.10.4045 Release Note | 2024.12.05
  - [MSSR] 更新MSSR2通路增加支持NV24、RGB输入输出
  - [MSSR] 更新MSSR2通路更新ME模型
  - [MSSR] 优化4kRGB处理通路性能，优化大运动场景效果
  - [MSSR] 调整MSSR2-1080p-HDMI通路的DC处理策略，调整DC默认效果参数
  - [MSSR] 更新MSSR2通路调整DC时序优化整体性能

## v0.13.9.4026 Release Note | 2024.11.29
  - [DFC] 新加BlockDFC处理通路，支持ROI配置处理区域、锐化后处理、NV24或RGBA输出
  - [SD/DD/DHW] 修正YUV2RGB的错误转换系数
  - [MSSR] 更新MSSR通路支持属性配置走解码通路还是HDMI通路，HDMI通路增加属性配置效果参数、Api输出运动状态参数
  - [MSSR] 在RK3588平台改用RGA3，解决RGA2内存访问超4G的问题
  - [MSSR] 重新调整MSSR-HDMI通路的DC处理策略、输出SD数据策略

## v0.13.8.3999 Release Note | 2024.11.21
  - [MSSR] 更新parseME降低带宽优化性能的激活条件
  - [MSSR] SR通路增加DC的激活条件

## v0.13.7.3994 Release Note | 2024.11.19
  - [MSSR] 修改SR、MEMC部分默认参数

## v0.13.6.3992 Release Note | 2024.11.18
  - [MSSR] 更新parseME降低带宽优化性能
  - [MSSR] 修复MSSR4K通路RGB输入输出dump功能

## v0.13.5.3972 Release Note | 2024.11.12
  - [AUTH] 增加对`rkauth_config.json`授权配置文件的授权支持；`rkpq_set_cache_path()`接口增加对该文件的路径指定功能。

## v0.13.4.3966 Release Note | 2024.11.12
  - [MSSR] 修正NV24输入输出时UV通道出现错位的问题

## v0.13.3.3958 Release Note | 2024.11.08
  - [MSSR] MSSR4K通路支持NV12、NV24、RGB格式输入时不传RGB2和RGB1，关闭外部RGA相应处理，改由内部GPU生成
  - [DCI_ACM] 修正 DCI_ACM 模块对 DCI/ACM 模块的相关继承用法，解决崩溃问题
  - [MSSR] 更新schemeIdx={0,1}的X4的ME模型，优化个别视频运动画面破图问题
  - [MSSR] MSSR和MSSR4K通路小运动闪烁问题进一步优化。
  - [MSSR] 修正DC+HWPQ效果异常问题
  - [MSSR] 更新场景切换检测
  - [MSSR] 更新部分ME模型
  - [RKNN] RKNN SDK支持版本提升至 v2.2.0

## v0.13.2.3917 Release Note | 2024.10.31
  - [MSSR] SR通路支持1080pNV24输入输出

## v0.13.1.3915 Release Note | 2024.10.30
  - [MSSR] 修正DC效果问题，简化parseDC计算优化性能

## v0.13.0.3910 Release Note | 2024.10.29
  - [MSSR] MSSR4K通路增加支持RGB输入输出，此时输入只需要配3帧RGB数据，不再需要配RGB2和RGB1两帧小分辨率数据
  - [MSSR] MSSR通路增加支持1080p输入时可选DC模型
  - [MSSR] SR通路支持4kNV24输入输出
  - [LD] 新增`RKPQ_MODULE_LD`模块，支持Local Dimming相关处理

## v0.12.6.3901 Release Note | 2024.10.23
  - [MSSR] 更新DC支持自动处理不同的输入range
  - [IO] 进一步增强对非对齐内存的自适应支持

## v0.12.5.3898 Release Note | 2024.10.22
  - [MSSR] HDMI通路DC优化（range改成Full2Full，优化随机噪声逻辑），小运动闪烁问题优化

## v0.12.4.3896 Release Note | 2024.10.22
  - [MSSR] MSSR、MSSR2通路增加支持1080pNV24输入输出
  - [MSSR] NV24输出通路增加动静判决的MC优化性能
  - [MSSR] MSSR4K通路增加支持4k输入时可选DC模型

## v0.12.3.3888 Release Note | 2024.10.18
  - [IO] 修正IO buffer缓存数量超过上限后的会将所有缓存都清除的错误行为（该错误会导致输入数据异常并可能造成程序退出）

## v0.12.2.3885 Release Note | 2024.10.17
  - [MSSR] MSSR4K通路增加属性控制MSSR4K整数帧输出方式
  - [MSSR] MSSR4K通路增加属性控制4kDC使用的模型
  - [MSSR] MSSR2通路增加支持1080p输入时可选DC模型
  - [DFC] NV12->RGBA输出通路增加演示功能，可通过属性配置各种演示模式
  - [MSSR] 修正MSSR4K通路DC结果异常问题
  - [MSSR] MSSR4K通路增加支持NV24输入输出

## v0.12.1.3873 Release Note | 2024.10.11
  - [MSSR] 调整MSSR4K通路处理时序，优化处理性能
  - [MSSR] 调整MSSR4K通路的DC处理，减少带宽使用
  - [DFC] 修改默认走通路sendFrmN1：默认使用model11，支持Sharp后处理，结果送n-1帧

## v0.12.0.3870 Release Note | 2024.10.09
  - [MSSR] Api修改：`rkpq_mssr_initflag`增加`RKPQ_MSSR_INIT_FLAG_MSSR4K`参数，用于初始化MSSR4K通路
  - [MSSR] 增加初版MSSR4K通路支持
  - [RKNN] RKNN符号的动态加载由即时加载改为延迟加载，未调用AI模块时不会主动加载`librknnrt.so`文件的符号
  - [IO] 修正在某些情况下计算输出图像平均亮度会失败的问题
  - [DFC] 支持model11的异步并行处理，RK3576平台性能模式`1080pNV12->RGBA`处理耗时约30ms，算法处理接口约15ms内提前返回

## v0.11.2.3856 Release Note | 2024.09.29
  - [MSSR] MSSR4K通路部分RGA处理改成GPU处理，优化带宽分布
  - [MSSR] 修正SR解析结果写出到输出虚宽大于实宽时出现的花图问题
  - [MSSR] 修正调用`rkpq_deinit`报错问题

## v0.11.1.3843 Release Note | 2024.09.25
  - [MSSR] 重新调整输出SD数据：只有场景发生切换时输出场景类型及相关数据才能变化
  - [MSSR] 修改异步线程wait机制，避免wait启动失败的线程
  - [MSSR] 更新`watermark_type=4`的定制水印
  - [MSSR] 修正`v0.10.3.3828`引入的720p打开logD会闪退的问题

## v0.11.0.3836 Release Note | 2024.09.24
  - [ALL] 恢复并修改`RKPQ_FLAG_CALC_MEAN_LUMA`的值使其重新生效，结合新增的`RKPQ_QUERY_MEAN_LUMA_OUTPUT`可以获取输出图像的平均亮度值
  - [MSSR] 优化AIPQ处理效果：只有在场景发生切换时场景类型才能发生变化，保持同一场景的AIPQ处理效果时域一致，避免在同一场景时出现效果跳变

## v0.10.3.3828 Release Note | 2024.09.23
  - [MSSR] 重新支持接口'nSchemeIdx=2'的配置降低NPU-ME耗时，优化GPU-MC性能

## v0.10.2.3824 Release Note | 2024.09.20
  - [BLR] 修正`nBlurChannel`和`nBlurMode`从api传参失败的问题

## v0.10.1.3819 Release Note | 2024.09.19
  - [MSSR] 修改MSSR通路：支持4k输入、4k输出的MEMC处理通路
  - [MSSR] 修正输出虚宽大于实宽时出现的花图问题
  - [BLR] BLR模块配置参数`rkpq_blr_cfg`新加参数：`nBlurChannel`用于配置指定模糊的通道，`nBlurMode`用于配置模糊处理是在指定区域内还是指定区域外，详见`rkpq_blr_cfg`

## v0.10.0.3812 Release Note | 2024.09.18
  - [IO] 增加了`rkpq_init_params::nMaxIoBufCacheNum`用于设置 IO buffer cache 的上限数量(对应Android属性为`persist.vendor.rkpq.io.cache.limit`)，并将默认上限数还原为32个
  - [DCI_ACM] 新增`RKPQ_MIXTURE_DCI_ACM`混合模块，支持DCI+ACM合并处理减少耗时，新增对应的集成示例(rkpq_demo_dci_acm.cpp)
  - [ALL] 取消`SHP_ACM`和`DCI_ACM`两个模块的授权要求
  - [ALL] 优化了pipeline最后一级是单通道处理模块（如`SHP`/`DCI`）时的copy操作，该情况下性能和带宽略有优化
  - [ALL] 部分Android属性名称变更，由`test.vendor.rkpq`开头的属性名称去掉`test.`前缀，避免因SELinux权限问题导致属性读取失败而频繁报错 (最新的属性名称见开发文档 Rockchip_Developer_Guide_SWPQ_cn.md)
  - [DHW] 模型文件更新，解决出图结果有多块大面积团状黑斑的问题
  - [MSSR] 增加针对文字区域的ME优化：新加支持X5模型，支持帧率x2、x2.4、x2.5、x4等倍数
  - [MSSR] 调整算法处理步骤时序优化SR通路性能

## v0.9.1.3784 Release Note | 2024.09.10
  - [MSSR] 修改CMCC定制水印`AI-SR`与`AI_DC`关联一个水印`AI-SR`
  - [IO] 修改FD映射表上限64改成256

## v0.9.0.3782 Release Note | 2024.09.10
  - [ALL] 初始化参数`rkpq_init_params`增加参数`aModSetupFlags[]`用于配置配置对应算法模块的初始化处理，当前支持`CSC`与`MSSR`模块，`MSSR`模块的配置详见`rkpq_mssr_initflag`
  - [ALL] 性能优化：当pipeline中最后几级的模块只处理Y通道或UV通道时，在一定条件下可以省去未处理通道的拷贝过程
  - [ALL] `rkpq_set_cache_path()`接口加入`pPath`参数的空指针检验，防止传入空指针导致程序崩溃
  - [RKNN] RKNN自定义模型路径的访问权限由读写改为只读
  - [CGC] 支持纹理不重复的 full resolution 的类纸纹理叠加的算法实现
  - [DHW] 上传正式的模型文件；支持开关文档外观增强功能；取消输出格式必须和输入一致的限制
  - [MSSR] 修正SD数据与输出帧序不一致问题
  - [MSSR] 配置参数`rkpq_mssr_cfg`增加参数`nProcFlag`，用于`rkpq_proc()`调用时配置算法模块各步骤的开关，具体配置详见`rkpq_mssr_procflag`，各算法步骤开关属性配置仍沿用旧版
  - [MSSR] 增加CMCC定制水印`persist.vendor.rkpq.watermark_type 4`
  - [MSSR] 修正切换到FE通路出现人脸跳闪问题

## v0.8.0.3756 Release Note | 2024.09.03
  - [MSSR] 修正场景切换结果数据冲突问题
  - [MSSR] 增加针对文字区域的ME优化：暂只支持X4模型，支持帧率x2或x4倍数。
  - [MSSR] 增加一个API参数`aDstHistIdx[16]`用于输出对应帧的直方图序号，`aDstHistIdx[k]=x`表示输出的第`k`帧使用输入的`n-x`帧对应的直方图数据

## v0.7.4.3732 Release Note | 2024.08.23
  - [DHW] 修正对 YUV4xxSP 和 Y8 格式的输入输出支持运行错误
  - [RKNN] RKNN符号动态加载的预设路径扩充，增加对`/system`路径下的`librknnrt.so`文件符号加载尝试

## v0.7.3.3724 Release Note | 2024.08.21
  - [MSSR] 修改部分效果调试参数默认值与属性配置建议值一致
  - [RKNN] RKNN符号动态加载的预设路径扩充，库加载后将尝试从`/vendor`、`/usr`等路径下寻找`librknnrt.so`文件的符号;

## v0.7.2.3719 Release Note | 2024.08.20
  - [MSSR] 优化Decontour处理之后PQ处理会把色带阶梯再次强化的问题（需要配合PQ的修改）

## v0.7.1.3714 Release Note | 2024.08.17
  - [DD]  在 RGB系列格式基础上增加了对 YUV4xxSP 和 Y8 格式的输入输出支持
  - [DHW] 在 RGB系列格式基础上增加了对 YUV4xxSP 和 Y8 格式的输入输出支持；去手写模型由RGB输入改为黑白图像输入，输出的RGB图像会丢失颜色信息
  - [MSSR] RK3576-Linux-NVR修正概率跑挂问题
  - [MSSR] 增加输出`DC_Score`到接口数组中`rkpq_mssr_cfg::pSDConfig->aSDResult`，场景数涨到9，每帧前8个数据与旧版一致，最后1个数据存储每帧的`DC_Score`值，用于后端PQ优化效果

## v0.7.0.3703 Release Note | 2024.08.14
  - [MSSR] 增加支持属性配置选择SR模型：`persist.vendor.rkpq.iptv_sr_enable`，`0`表示投影SR模型，`1`表示盒子SR模型
  - [Auth] 授权文件夹创建权限由700提升至755;
  - [RKNN] 将RKNN符号改用动态加载，使算法库脱离对`librknnrt.so`文件的依赖;
  - [DD] 文档检测后处理操作升级，增强鲁棒性
  - [DHW] 增加文档增强的前处理，提升擦除效果（非正式版本）; 增加 `rkpq_dhw_cfg::nDocEnhanceLevel` 属性参数（暂不生效）
  - [ALL] API修改：
    - `RKPQ_FLAG_HIGH_PERFORM` flag 生效，建议在CPU负载比较低时开启使程序效率增加。
    - `RKPQ_FLAG_CIRCULAR_BUF_IN` 和 `RKPQ_FLAG_CIRCULAR_BUF_OUT` flag 生效，仅在输入/输出缓冲区显示指定为 **ring-buffer** 机制时才开启内部的 buffer-cache 功能，节省零拷贝的映射耗时;
    - 增加 `rkpq_init_params::bLazyInit` 属性参数，用于指明 pipeline 内各模块执行延迟初始化操作，默认为0;
    - 增加 `rkpq_proc_params::bEnableIncreaseCpuUtl` 属性参数，用于开关子线程以控制CPU利用率，仅在`RKPQ_FLAG_HIGH_PERFORM` flag 指定时生效。

## v0.6.2.3680 Release Note | 2024.08.06
  - [MSSR] RK3576-Android平台更新540p/720p/1080p->1080p通路增加Decontour算法处理

## v0.6.1.3666 Release Note | 2024.08.02
  - [MSSR] RK3576-Linux-NVR增加支持水印定制

## v0.6.0.3663 Release Note | 2024.08.01
  - [MSSR] RK3576-Android-IPTV更新1080p-4k的SR通路增加Decontour算法处理
  - [DFC] 使用新的训练模型优化算法效果
  - [DHW] 增加**AI-DHW**模块，用于文档增强应用中的手写擦除场景
  - [DD] 增加一个API参数用于表明当前帧输出是否有效
  - [SD] 修正水印开启后读取无效SD模块信息导致的程序闪退问题
  - [ALL] 修正当输入帧号无效时会存在dump无限帧数的问题
  - [ZME] 修正对RGB系列图像任意倍率缩放结果偏差一个像素的错误
  - [CSC] 修正`YUV601L_TO_YUV601L`, `YUV601L_TO_YUV709L`, `YUV709L_TO_YUV709L`三种色彩空间转换的系数错误

## v0.5.9.3625 Release Note | 2024.07.19
  - [MSSR] RK3576-Linux-NVR初版串联集成库

## v0.5.8.3618 Release Note | 2024.07.15
  - [SD] 增加RK3576平台支持（需要RKNN 2.0版本）
  - [SD] 增加AIPQ通路（请参考`rkpq_demo_aipq.cpp`），修正PQTool调试不生效的问题

## v0.5.7.3596 Release Note | 2024.07.10
  - [MSSR] RK3576-Android-IPTV增加支持1080p-4k的SR通路
  - [MSSR] RK3576-Android-IPTV增加支持客户配置水印标题
  - [CGC] 新增RGBA格式输入和输出，支持在模块中配置`nR(G/B)gain`参数以进行色温调整

## v0.5.6.3519 Release Note | 2024.06.20
  - [MSSR] RK3576-Android-IPTV更新SR模型

## v0.5.5.3507 Release Note | 2024.06.19
  - [MSSR] 修复FE通路下人脸边界跳变明显问题
  - [MSSR] 修正FE通路帧序跳变时跑挂问题
  - [MSSR] 修复部分变量未初始化问题

## v0.5.4.3493 Release Note | 2024.06.17
  - [MSSR] 修正RK3576人脸增强处理的bug

## v0.5.3.3490 Release Note | 2024.06.17
  - [MSSR] 修改演示水印：显示输入输出的分辨率、帧率，各种开关状态
  - [CGC] 新增类纸功能，使用`bEnablePaperMode`进行功能开关，`nTextureStrength`进行纹理强度模配置；强度越大纹理越明显

## v0.5.2.3476 Release Note | 2024.06.11
  - [MSSR] SR模型修改，默认用USM效果，修复文字边缘瑕疵
  - [MSSR] 新加支持1080pNV12输入输出的SR通路
  - [MSSR] 人脸增强通路改为异步，默认走384x384通路

## v0.5.1.3453 Release Note | 2024.06.05
  - [MSSR] Linux平台人脸增强通路集成跑通
  - [MSSR] ProjectorSR通路颜色拖影问题修正

## v0.5.0.3445 Release Note | 2024.06.03
  - [MSSR] MEMC性能优化
  - [MSSR] 增加支持人脸增强通路，接口增加`bEnableFE`参数控制是否打开人脸增强功能

## v0.4.0.3437 Release Note | 2024.05.30
  - [MSSR] 关闭MEMC的SR通路输出场景检测结果数据。
  - [MSSR] 优化720pSR的效果
  - [MSSR] 接口增加MEMC强度参数`nMEMCStrength`
  - [CGC] 增加CGC模块

## v0.3.0.3378 Release Note | 2024.05.17
  - [MSSR] 增加支持三套ME金字塔分辨率方案，由api新增参数`nSchemeIdx`指定并传入相应数据
  - [MSSR] 优化540p和720p的SR处理性能，满足30fps输入的SR+MEMC性能要求

## v0.2.1.3349 Release Note | 2024.05.11
  - [MSSR] 输出场景检测结果
  - [MSSR] 优化720pSR性能

## v0.2.0.3333 Release Note | 2024.05.09
  - [ALL] 增加新的接口`rkpq_clear_caches()`，用于清除旧的输入输出缓存buffer
  - [MSSR] 重新打开授权功能
  - [MSSR] 支持前后两帧输入不同的分辨率

## v0.1.2.3280 Release Note | 2024.04.24
  - [ALL] 取消对 vendor_storage 端口的写权限要求，改为只读权限;
  - [ALL] RKNN模型和授权文件的默认读取路径在Android下统一设为: `/vendor/etc/`, 在Linux下统一设为`/etc/`
  - [MSSR] 性能优化; RKNN模型升级到2.0.0b

## v0.1.1.3264 Release Note | 2024.04.22
  - [ALL] 授权功能增加 vendor_storage 验证，授权验证全面开启
  - [ALL] pipeline实时开关模块的功能支持，通过api_config的`bEnableXXX`参数可控制子模块实时开关
  - [ACM] 修正ACM子模块的api_config参数传递不生效问题

## v0.1.0.3210 Release Note | 2024.04.11
  - [DD] 文档检测子模块完成fp16零拷贝适配，性能优化至35fps(on RK3588)
  - [ALL] OpenCL缓存加入版本信息，防止Mali库版本变化后缓存失效造成程序无法正常运行
  - [ALL] **（重要）API大调整，**
    - **增加新的模块，`rkpq_module`枚举名称和对应数值调整**，并划分为3个子类别，每个类别对应的模块如下：
      1. 通用的非AI模块: CVT(暂不支持)/CSC/DCI/ACM/ZME/SHP/MLC(新增，暂不支持)
      2. 通用的AI模块: AI_SR/AI_SD/AI_DM/AI_DFC(新增)/AI_DD(新增)/AI_DE(新增)
      3. 特定优化的混合模块: SHP_ACM/FE(新增)/MSSR(新增)
    - **增加新的图像格式**
      1. 单通道格式: `Y8`；
      2. 双通道格式: `UV88`,`VU88`(暂不支持)；
      3. 三通道紧凑RGB格式`RGB565`/`BGR565`(MSB顺序，即对于`RGB565`来说，高5位为R，低5位为B)
    - **接口调整**
      1. 增加`rkpq_set_inputs()`,`rkpq_set_outputs()`接口，用于支持多输入多输出的模块(MSSR)
      2. 增加`rkpq_set_cache_path()`接口，用于用户自定义缓存路径，具体包含3种：OpenCL缓存文件路径、RKNN模型文件路径、许可文件路径
      3. 增加`rkpq_set_target_platform()`接口(暂不支持)

## v0.0.8.3074_alpha Release Note | 2024.03.04
  - [DD] 增加文档检测(DocDetection, DD)子模块

## v0.0.7.3057 Release Note | 2024.02.28
  - [CSC] CSC子模块增加 R2R 通路，并支持色温调节功能

## v0.0.6.3040 Release Note | 2024.02.23
  - [ALL] 增加非对齐数据导致零拷贝失效情况下的程序鲁棒性
  - [ALL] 增加对不同平台不同版本的OpenCL对齐条件不一致的适配
  - [SR] AISR子模块文字模型效果修正

## v0.0.5.3012 Release Note | 2024.02.04
  - 修正Linux系统下零拷贝功能不支持的问题
  - 增加Linux系统环境变量的读取功能以修改日志等级等一系列属性

## v0.0.4.2986 Release Note | 2024.01.17
  - `rkpq_set_loglevel()`日志等级设置可以不用指定特定的`pq_context`, 支持在调用`pq_init()`之前设置

## v0.0.3.2865 Release Note | 2023.12.01
  - 增加非零拷贝即不带 fd buffer 的支持

## v0.0.2.2829 Release Note | 2023.11.16
  - 恢复 DCI/ACM/DM 模块的支持
  - SR/DM 模块增加了对 ROI 支持
  - ZME 模块增加了对 RGBA 格式图像的缩放支持
  - SR 模块增加了在 RK356X 平台上分辨率从 960x540 -> 1920x1080 的通路支持
  - RKNN 依赖版本提升到 v1.5.2

## v0.0.0.2534 Release Note | 2023.07.21
  - 新的处理框架，支持用户自定义的 pipeline 形式
  - 支持模块: CSC/SD/SR/DM/ZME/SHP
