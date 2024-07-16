//
/////////////////////////////////////////////////////////////////////////
// Copyright(c) 2024 by Rockchip Electronics Co., Ltd. All Rights Reserved.
//
// This file is Rock-chip's property. It contains Rock-chip's trade secret,
// proprietary and confidential information.
// The information and code contained in this file is only for authorized
// Rock-chip employees to design, create, modify, or review.
// DO NOT DISTRIBUTE, DO NOT DUPLICATE OR TRANSMIT IN ANY FORM WITHOUT
// PROPER AUTHORIZATION.
// If you are not an intended recipient of this file, you must not copy,
// distribute, modify, or take any action in reliance on it.
// If you have received this file in error, please immediately notify
// Rock-chip and permanently delete the original and any copy of any file
// and any printout thereof.
//
//////////////////////////////////////////////////////////////////////////
//
// Last update 2024-09-02 for librkswpq.so v0.7.0

#include "rkpq_api.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define USE_HARDWARE_BUFFER 0   /* use DRM like hardware buffers with fd values valid */

void optionalQueryContextInfo(rkpq_context ctx)
{
    rkpq_version_info verInfo;
    rkpq_imgfmt_info srcFmtInfo, dstFmtInfo;
    rkpq_clrspc_info clrSpcInfo;
    rkpq_module_info pqModuleInfo, roiModuleInfo;
    uint32_t isRknnSupport, imgAlignment, bufAlignment;
    rkpq_query(0, RKPQ_QUERY_SDK_VERSION, sizeof(rkpq_version_info), &verInfo);
    rkpq_query(0, RKPQ_QUERY_IMG_FMT_INPUT_SUPPORT, sizeof(rkpq_imgfmt_info), &srcFmtInfo);
    rkpq_query(0, RKPQ_QUERY_IMG_FMT_OUTPUT_SUPPORT, sizeof(rkpq_imgfmt_info), &dstFmtInfo);
    rkpq_query(0, RKPQ_QUERY_IMG_COLOR_SPACE_SUPPORT, sizeof(rkpq_clrspc_info), &clrSpcInfo);
    /* NOTE: call ABOVE querys any time you need */
    /* NOTE: a valid context is needed for BELOW querys */
    rkpq_query(ctx, RKPQ_QUERY_MODULES_SUPPORT, sizeof(rkpq_module_info), &pqModuleInfo);
    rkpq_query(ctx, RKPQ_QUERY_MODULES_ROI_SUPPORT, sizeof(rkpq_module_info), &roiModuleInfo);
    rkpq_query(ctx, RKPQ_QUERY_IMG_ALIGNMENT_OCL, sizeof(uint32_t), &imgAlignment);
    rkpq_query(ctx, RKPQ_QUERY_BUF_ALIGNMENT_OCL, sizeof(uint32_t), &bufAlignment);
    rkpq_query(ctx, RKPQ_QUERY_RKNN_SUPPORT, sizeof(uint32_t), &isRknnSupport);
    printf("SDK version: %d.%d.%d, %s\n", verInfo.nVerMajor, verInfo.nVerMinor, verInfo.nVerRvson, verInfo.sVerInfo);
    printf("Support input/output image format num: %d/%d\n", srcFmtInfo.nValidFmtNum, dstFmtInfo.nValidFmtNum);
    printf("Support color space num: %d\n", clrSpcInfo.nValidSpcNum);
    printf("Support PQ module num: %d\n", pqModuleInfo.nValidModNum);
    printf("OpenCL image alignment: %u\n", imgAlignment);
    printf("OpenCL buffer alignment: %u\n", bufAlignment);
    printf("Is support RKNN: %u\n", isRknnSupport);
}

/**
 * 以下代码展示了混合模块 RKPQ_MIXTURE_MSSR 的集成示例
 * 数据流: [640x480 yuv420sp] =RKPQ_MIXTURE_MSSR=> [1280x960 yuv420sp]
 */
int main(int argc, const char *argv[])
{
    int ret = 0;

    /* 创建相关结构体对象，有条件可以做一层封装 */
    rkpq_context context = NULL;
    rkpq_init_params initParams = {0};
    rkpq_proc_params procParams = {0};

    /* 在初始化`rkpq_context`之前可以设置日志等级、缓存路径等非必须操作 */
    int logLevel = 4;
    ret |= rkpq_set_loglevel(nullptr, logLevel);             /* 日志等级说明请看api文件 */
    ret |= rkpq_set_cache_path(nullptr, "/data/rkalgo/", 1); /* 参数说明请看api文件 */
    // ret |= rkpq_set_target_platform("rk3588");               /* reserved */
    if (ret)
    {
        printf("Failed to set loglevel or cache_path or target_platform! %d\n", ret);
        // return ret;
    }

    /* 步骤1: 填写初始化参数'rkpq_init_params'然后通过接口`rkpq_init()`初始化`rkpq_context`上下文实例 */
    initParams.nInitFlag = RKPQ_FLAG_DEFAULT;
    initParams.nInitFlag |= RKPQ_FLAG_ASYNC_MODE;       // 某些模块支持异步模式，请指明这个flag
    initParams.nInitFlag |= RKPQ_FLAG_CIRCULAR_BUF_IN | RKPQ_FLAG_CIRCULAR_BUF_OUT; /* 如果输入/输出是环形缓冲区，请显示指定此flag，可节省buffer映射时间 */
    initParams.aModPipeOrder[0] = RKPQ_MIXTURE_MSSR;    // 这里pipeline中只包含`MSSR`这一个模块
    initParams.nModNumInPipe = 1;                       // 这里pipeline中模块数量为1
    ret = rkpq_init(&context, &initParams);             // 注意这里参数是两个指针!
    if (ret)
    {
        printf("Failed to call rkpq_init() %d, Please check the API parameters!\n", ret);
        return ret;
    }

    /**
     * 步骤2: 准备输入输出的图像和缓冲区信息，填写`rkpq_imgbuf_info`结构体，
     * 一般模块仅支持"单输入-单输出"模式，图像和缓存信息位于`rkpq_proc_params::stSrcImgInfo`和`rkpq_proc_params::stDstImgInfo`结构体中，
     * 注: `MSSR`模块是一个支持多输入多输出的模块，需要通过`rkpq_set_inputs()`和`rkpq_set_outputs()`接口设置输入输出的图像和缓冲区信息。
     * `rkpq_proc_params::stSrcImgInfo`和`rkpq_proc_params::stDstImgInfo`结构体内的数据将会被忽略！
     */
    rkpq_imgbuf_info stSrcImgInfos[5] = {0}; // 创建新的`rkpq_imgbuf_info`对象，本例中输入和输出的数量均为1
    rkpq_imgbuf_info stDstImgInfos[3] = {0}; // 请注意这里变量的生命周期

    /* 步骤2.1: 设置输入输出图像信息 */
    // NV24[n]
    stSrcImgInfos[0].nColorSpace    = RKPQ_CLR_SPC_YUV_601_FULL;// see rkpq_clr_spc
    stSrcImgInfos[0].nPixFmt        = RKPQ_IMG_FMT_NV24;        // see rkpq_img_fmt
    stSrcImgInfos[0].nPixWid        = 960;                      // set the input image width
    stSrcImgInfos[0].nPixHgt        = 544;                      // set the input image height
    stSrcImgInfos[0].nEleDepth      = 8;                        // set the first component(Y or R) depth [bit]
    stSrcImgInfos[0].nAlignment     = 128;                      // set the pitch alignment [byte], better equal to 'imgAlignment' queried before
    stSrcImgInfos[0].aWidStrides[0] = 1024;                     // in this case, no padding in the width dimension
    stSrcImgInfos[0].aHgtStrides[0] = 544;                      // in this case, there are 8 lines padding after the first (luma) plane
    // NV24[n-1]
    memcpy(&stSrcImgInfos[1], &stSrcImgInfos[0], sizeof(rkpq_imgbuf_info));
    // NV24[n-2]
    memcpy(&stSrcImgInfos[2], &stSrcImgInfos[0], sizeof(rkpq_imgbuf_info));
    // RGB2[n]
    stSrcImgInfos[3].nColorSpace    = RKPQ_CLR_SPC_RGB_FULL;    // see rkpq_clr_spc
    stSrcImgInfos[3].nPixFmt        = RKPQ_IMG_FMT_RGB;         // see rkpq_img_fmt
    stSrcImgInfos[3].nPixWid        = 960;                      // set the input image width
    stSrcImgInfos[3].nPixHgt        = 544;                      // set the input image height
    stSrcImgInfos[3].nEleDepth      = 8;                        // set the first component(Y or R) depth [bit]
    stSrcImgInfos[3].nAlignment     = 64;                       // set the pitch alignment [byte], better equal to 'imgAlignment' queried before
    stSrcImgInfos[3].aWidStrides[0] = 2880;                     // in this case, no padding in the width dimension
    stSrcImgInfos[3].aHgtStrides[0] = 544;                      // in this case, there are 8 lines padding after the first (luma) plane
    // RGB1[n]
    stSrcImgInfos[4].nColorSpace    = RKPQ_CLR_SPC_RGB_FULL;    // see rkpq_clr_spc
    stSrcImgInfos[4].nPixFmt        = RKPQ_IMG_FMT_RGB;         // see rkpq_img_fmt
    stSrcImgInfos[4].nPixWid        = 480;                      // set the input image width
    stSrcImgInfos[4].nPixHgt        = 272;                      // set the input image height
    stSrcImgInfos[4].nEleDepth      = 8;                        // set the first component(Y or R) depth [bit]
    stSrcImgInfos[4].nAlignment     = 64;                       // set the pitch alignment [byte], better equal to 'imgAlignment' queried before
    stSrcImgInfos[4].aWidStrides[0] = 1536;                     // in this case, no padding in the width dimension
    stSrcImgInfos[4].aHgtStrides[0] = 272;                      // in this case, there are 8 lines padding after the first (luma) plane

    // NV12 dst#0
    stDstImgInfos[0].nColorSpace    = RKPQ_CLR_SPC_YUV_601_FULL;// see rkpq_clr_spc
    stDstImgInfos[0].nPixFmt        = RKPQ_IMG_FMT_NV12;        // see rkpq_img_fmt
    stDstImgInfos[0].nPixWid        = 1920;                     // set the input image width
    stDstImgInfos[0].nPixHgt        = 1080;                     // set the input image height
    stDstImgInfos[0].nEleDepth      = 8;                        // set the first component(Y or R) depth [bit]
    stDstImgInfos[0].nAlignment     = 128;                      // set the pitch alignment [byte], better equal to 'imgAlignment' queried before
    stDstImgInfos[0].aWidStrides[0] = 1920;                     // in this case, no padding in the width dimension
    stDstImgInfos[0].aHgtStrides[0] = 1080;                     // in this case, there are 8 lines padding after the first (luma) plane
    // NV12 dst#1
    memcpy(&stDstImgInfos[1], &stDstImgInfos[0], sizeof(rkpq_imgbuf_info));
    // NV12 dst#2
    memcpy(&stDstImgInfos[2], &stDstImgInfos[0], sizeof(rkpq_imgbuf_info));


    /* 步骤2.2: 调用`rkpq_query()`接口填充剩下的图像信息，如果`rkpq_imgbuf_info`内所有属性你都填好了，这一步可以省略 */
#if 1 /* not necessary */
    for (int i=0; i<5; i++)
    {
        ret |= rkpq_query(NULL, RKPQ_QUERY_IMG_BUF_INFO, sizeof(rkpq_imgbuf_info), &stSrcImgInfos[i]);
    }
    for (int i=0; i<2; i++)
    {
        ret |= rkpq_query(NULL, RKPQ_QUERY_IMG_BUF_INFO, sizeof(rkpq_imgbuf_info), &stDstImgInfos[i]);
    }
    if (ret)
    {
        printf("Failed to call rkpq_query() %d, Please check the API parameters!\n", ret);
        return ret;
    }
#endif

    /* 步骤3: 设置模块的调校参数以及其他配置；通过`rkpq_get_default_cfg`接口获取到的配置参数值均是默认值，可以根据具体需求进行修改。*/
    rkpq_mssr_cfg *pConfig = (rkpq_mssr_cfg *)rkpq_get_default_cfg(context, 0, RKPQ_MIXTURE_MSSR);   // order 0 is the MSSR module in the pipeline
    if (!pConfig || !pConfig->pSRConfig || !pConfig->pSDConfig)
    {
        printf("Get an invalid config! \n");
        return -1;
    }
    pConfig->bEnableMEMC = 1;
    pConfig->nModelIdx  = 0; // 插帧模型序号
    pConfig->nMemcScale = 4; // 插帧倍率
    pConfig->aDstIdx[0] = 0; // 选择输出帧0的MC序号
    pConfig->aDstIdx[1] = 2; // 选择输出帧1的MC序号
    pConfig->nDstNum    = 2; // 每次输出帧数
    pConfig->nMEMCStrength = 100; // MEMC强度，范围0-100，越大越强

    /* 步骤4: 调用`rkpq_proc()`执行算法 */
    int frameIdx = 0;
    int exitFlag = 0;
    while (exitFlag != 1)   /* break condition */
    {
        procParams.nFrameIdx = frameIdx; // 设置帧号，每帧更新，建议填写

        /* 步骤4.1: 申请缓冲区并将信息填入`rkpq_imgbuf_info`内 */
    #if USE_HARDWARE_BUFFER
        // 使用带fd的硬件缓冲区，算法内部会对其进行映射使用，该方案可以实现零拷贝，推荐使用（ARM下一般需要至少64byte对齐）
        int fdSrc = 0, fdDst = 0;           // create hardware buffer then import through fd value
        int fdSrcIdx = 0, fdDstIdx = 0;     // create hardware buffer then import through fd value
        /* create hardware buffers to make 'fdSrc' & 'fdDst' valid... */
        /* ... */
        /**
         * 填入有效的fd属性，有fd的话，虚地址可以不用填
         * 注意: 一个buffer被释放后再次申请，fd值可能保持不变，但实际buffer对象已经是另一个新的了，这种现象经常出现在如播放器片源切换、HDMI信号切换等场景。
         *      由于算法内部会对buffer创建映射缓存列表，防止重复映射，提高性能，在这种情况下，缓存对应的buffer实际已经失效，这会导致使用了非法的脏数据。
         *      使用`nFdIndex`属性可以对缓存的有效性做一次双重检验，避免出现上诉问题。 如果你的fd-buffer有对应的唯一标识符，可以使用此唯一标识符作为`nFdIndex`；
         *      如果没有唯一标识符，可以使用一个初始数值作为（当前这一组所有）buffer的`nFdIndex`，在（当前这一组所有）buffer被释放后将此数值递增。
         */
        for (int i=0; i<5; i++)
        {
            // create hardware buffer then import through fd value
            stSrcImgInfos[i].nFdValue = fdSrc;      // different fd value for each buffer
            stSrcImgInfos[i].nFdIndex = fdSrcIdx;   // unique identifier of the device buffer
        }
        for (int i=0; i<2; i++)
        {
            // create hardware buffer then import through fd value
            stDstImgInfos[i].nFdValue = fdDst;      // different fd value for each buffer
            stDstImgInfos[i].nFdIndex = fdDstIdx;   // unique identifier of the device buffer
        }
    #else
        // 直接使用`malloc`申请内存，这种情况下不具有零拷贝功能，算法会显示地对输入和输出做一次拷贝操作
        for (int i=0; i<5; i++)
        {
            stSrcImgInfos[i].aPlaneAddrs[0] = (unsigned char*)malloc(stSrcImgInfos[0].nFrameSize);
        }
        for (int i=0; i<2; i++)
        {
            stDstImgInfos[i].aPlaneAddrs[0] = (unsigned char*)malloc(stDstImgInfos[0].nFrameSize);
        }
    #endif
        for (int i=0; i<5; i++)
        {
            stSrcImgInfos[i].nBufferSize = stSrcImgInfos[i].nFrameSize; /* real buffer sieze, should be >= nFrameSize! unit: byte */
        }
        for (int i=0; i<2; i++)
        {
            stDstImgInfos[i].nBufferSize = stDstImgInfos[i].nFrameSize; /* real buffer sieze, should be >= nFrameSize! unit: byte */
        }

        /* 步骤4.2: 帧级参数更新 */
        // 本模块MSSR的分辨率变换信息`stPipeResInfo`需要填写
        pConfig->stPipeResInfo.nSrcImgWid = stSrcImgInfos[0].nPixWid;
        pConfig->stPipeResInfo.nSrcImgHgt = stSrcImgInfos[0].nPixHgt;
        pConfig->stPipeResInfo.nDstImgWid = stDstImgInfos[0].nPixWid;
        pConfig->stPipeResInfo.nDstImgHgt = stDstImgInfos[0].nPixHgt;
        // 内部SR子模块如果打开，其格式变换信息`stPipeFmtInfo`和分辨率变换信息`stPipeResInfo`需要填写
        pConfig->pSRConfig->bEnableSR = 1;  // enable SR sub-module here
        pConfig->pSRConfig->stPipeFmtInfo.nSrcClrSpc = stSrcImgInfos[0].nColorSpace;
        pConfig->pSRConfig->stPipeFmtInfo.nSrcPixFmt = stSrcImgInfos[0].nPixFmt;
        pConfig->pSRConfig->stPipeFmtInfo.nDstClrSpc = stDstImgInfos[0].nColorSpace;
        pConfig->pSRConfig->stPipeFmtInfo.nDstPixFmt = stDstImgInfos[0].nPixFmt;
        memcpy(&pConfig->pSRConfig->stPipeResInfo, &pConfig->stPipeResInfo, sizeof(rkpq_pipe_res_info));
        pConfig->bEnableMEMC = 1;           // 这里关闭了 MEMC 子模块
        pConfig->pSDConfig->bEnableSD = 0;  // 这里开启了 SD 子模块

        int inputFPS = 20;
        int outputFPS = 30;
        int kk = frameIdx;
        if (inputFPS == 15 && outputFPS == 30) // 15->30
        {
            // 0 - 0.5
            pConfig->nModelIdx = 0;
            pConfig->nMemcScale = 4;
            pConfig->aDstIdx[0] = 0;
            pConfig->aDstIdx[1] = 2;
            pConfig->nDstNum = 2;
        }
        else if (inputFPS == 20 && outputFPS == 30) // 20->30
        {
            if (kk%2==0)
            {
                // 0 - 0.6
                pConfig->nModelIdx = 1;
                pConfig->nMemcScale = 5;
                pConfig->aDstIdx[0] = 0;
                pConfig->aDstIdx[1] = 3;
                pConfig->nDstNum = 2;
            }
            else if (kk%2==1)
            {
                // 1.4
                pConfig->nModelIdx = 1;
                pConfig->nMemcScale = 5;
                pConfig->aDstIdx[0] = 2;
                pConfig->nDstNum = 1;
            }
        }
        else if (inputFPS == 25 && outputFPS == 30) // 25->30
        {
            if (kk%2==0)
            {
                // 0 - 0.8
                pConfig->nModelIdx = 1;
                pConfig->nMemcScale = 5;
                pConfig->aDstIdx[0] = 0;
                pConfig->aDstIdx[1] = 4;
                pConfig->nDstNum = 2;
            }
            else if (kk%2==1)
            {
                // 1.6
                pConfig->nModelIdx = 1;
                pConfig->nMemcScale = 5;
                pConfig->aDstIdx[0] = 3;
                pConfig->nDstNum = 1;
            }
            else if (kk%2==2)
            {
                // 2.5
                pConfig->nModelIdx = 0;
                pConfig->nMemcScale = 4;
                pConfig->aDstIdx[0] = 2;
                pConfig->nDstNum = 1;
            }
            else if (kk%2==3)
            {
                // 3.4
                pConfig->nModelIdx = 1;
                pConfig->nMemcScale = 5;
                pConfig->aDstIdx[0] = 2;
                pConfig->nDstNum = 1;
            }
            else if (kk%2==4)
            {
                // 3.4
                pConfig->nModelIdx = 1;
                pConfig->nMemcScale = 5;
                pConfig->aDstIdx[0] = 1;
                pConfig->nDstNum = 1;
            }
        }
        else if (inputFPS == 25 && outputFPS == 60) // 25->60
        {
            if (kk%5==0)
            {
                // 0 - 0.4 - 0.8
                pConfig->nModelIdx = 1;
                pConfig->nMemcScale = 5;
                pConfig->aDstIdx[0] = 0;
                pConfig->aDstIdx[1] = 2;
                pConfig->aDstIdx[2] = 4;
                pConfig->nDstNum = 3;
            }
            else if (kk%5==1)
            {
                // 1.25 - 1.75
                pConfig->nModelIdx = 0;
                pConfig->nMemcScale = 4;
                pConfig->aDstIdx[0] = 1;
                pConfig->aDstIdx[1] = 3;
                pConfig->nDstNum = 2;
            }
            else if (kk%5==2)
            {
                // 2.2 - 2.6
                pConfig->nModelIdx = 1;
                pConfig->nMemcScale = 5;
                pConfig->aDstIdx[0] = 1;
                pConfig->aDstIdx[1] = 3;
                pConfig->nDstNum = 2;
            }
            else if (kk%5==3)
            {
                // 3.0 - 3.4 - 3.8
                pConfig->nModelIdx = 1;
                pConfig->nMemcScale = 5;
                pConfig->aDstIdx[0] = 0;
                pConfig->aDstIdx[1] = 2;
                pConfig->aDstIdx[2] = 4;
                pConfig->nDstNum = 3;
            }
            else if (kk%5==4)
            {
                // 4.2 - 4.6
                pConfig->nModelIdx = 1;
                pConfig->nMemcScale = 5;
                pConfig->aDstIdx[0] = 1;
                pConfig->aDstIdx[1] = 3;
                pConfig->nDstNum = 2;
            }
        }

        /* 步骤4.3: 设置输入和输出 */
        // 设置输入输出图像和缓冲区信息；一般每帧的缓冲区不同，每帧都要设置一次
        rkpq_set_inputs(context, stSrcImgInfos, 5);
        rkpq_set_outputs(context, stDstImgInfos, 2);

        /* 步骤4.4: 执行算法 */
        ret = rkpq_proc(context, &procParams); // 算法阻塞执行
        if (ret)
        {
            printf("Fail to rkpq_proc() %d\n", ret);
            break;
        }
        else
        {
            // output yuv
            printf("Writing frame data ...\n");
            for (int i=0; i < pConfig->nDstNumPrev; i++)
            {
                // TODO...
            }
        }

        /* 步骤4.5: 释放帧级资源 */
    #if USE_HARDWARE_BUFFER
        /* free hardware buffer here */
        /* ... */
    #else
        // free the buffers that you allocated
        for (int i = 0; i < 5; i++) // 本例有5个输入
        {
            if (stSrcImgInfos[i].aPlaneAddrs[0] != NULL)
            {
                free(stSrcImgInfos[i].aPlaneAddrs[0]);
                stSrcImgInfos[i].aPlaneAddrs[0] = NULL;
            }
        }
        for (int i = 0; i < 2; i++) // 本例有2个输出
        {
            if (stDstImgInfos[i].aPlaneAddrs[0] != NULL)
            {
                free(stDstImgInfos[i].aPlaneAddrs[0]);
                stDstImgInfos[i].aPlaneAddrs[0] = NULL;
            }
        }
    #endif

        frameIdx++;              // 更新帧号，切换信号和片源后，建议重置
        exitFlag = frameIdx > 1; // 这里跑2帧就退出，实际业务中可以根据实际情况设置退出条件
    }

    /* 步骤5: 回收资源 */
    ret = rkpq_deinit(context);
    if (ret)
    {
        printf("Failed to call rkpq_deinit() %d\n", ret);
    }

    return ret;
}