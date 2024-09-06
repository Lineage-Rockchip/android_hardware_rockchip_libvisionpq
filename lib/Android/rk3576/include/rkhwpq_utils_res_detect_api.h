#pragma once
#ifndef __RKHWPQ_UTILS_RES_DETECT_API_H_
#define __RKHWPQ_UTILS_RES_DETECT_API_H_

#ifdef __cplusplus
extern "C"
{
#endif
/* Run Mode */
#define RK_HWPQ_UTILS_RUN_MODE_RES_DETECT     0x50

/* Process Command */
typedef enum{
    RK_HWPQ_UTILS_RES_DETECT_MIN = 0x100, 
    RK_HWPQ_UTILS_RES_DETECT_GET_RES_INFO,
    RK_HWPQ_UTILS_RES_DETECT_GET_HWPQ_CFG,
    RK_HWPQ_UTILS_RES_DETECT_MAX, 
} RK_HWPQ_UTILS_RES_DETECT_CMD;

/* Type Definition */
typedef enum{
    RK_HWPQ_UTILS_RES_DETECT_SCALE_RATIO_1X = 0,
    RK_HWPQ_UTILS_RES_DETECT_SCALE_RATIO_2X,
    RK_HWPQ_UTILS_RES_DETECT_SCALE_RATIO_4X,
    RK_HWPQ_UTILS_RES_DETECT_SCALE_RATIO_MAX
} RK_HWPQ_UTILS_RES_DETECT_SCALE_RATIO;

/* Hwpq base config structure */
typedef struct RkHwpqResDetectCfg_t {
    int src_fd;
    void *p_src_buf;
    int img_w;
    int img_h;
    int img_s;
    int img_fmt; // only support bgr888 now
    char reserve0[128];

    /* output info */
    int do_update_cfg;
    void* hwpq_cfg_addr;
    int scaler_ratio; 
    char reserve1[128];
} RkHwpqResDetectCfg;


#ifdef __cplusplus
}
#endif
#endif //__RKHWPQ_UTILS_RES_DETECT_API_H_