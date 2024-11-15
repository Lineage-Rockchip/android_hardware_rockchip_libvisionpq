#pragma once
#ifndef __RKHWPQ_UTILS_AIPQ_MERGE_API_H_
#define __RKHWPQ_UTILS_AIPQ_MERGE_API_H_

#ifdef __cplusplus
extern "C"
{
#endif
/* Run Mode */
#define RK_HWPQ_UTILS_RUN_MODE_AIPQ_CFG_CVT     0x20

/* Process Command */
typedef enum{
    RK_HWPQ_UTILS_AIPQ_MERGE_MIN = 0x100, 
    RK_HWPQ_UTILS_AIPQ_MERGE_LOAD_CFG,
    RK_HWPQ_UTILS_AIPQ_MERGE_GENERATE,
    RK_HWPQ_UTILS_AIPQ_MERGE_UPDATE_ACM,
    RK_HWPQ_UTILS_AIPQ_MERGE_UPDATE_DCI,
    RK_HWPQ_UTILS_AIPQ_MERGE_SET_AIPQ_INFO,
    RK_HWPQ_UTILS_AIPQ_MERGE_MAX, 
} RK_HWPQ_UTILS_AIPQ_MERGE_CMD;


typedef struct RkHwpqAipqMergeCfg_t {
    const char *p_aipq_cfg_file; 
    void* hwpq_cfg_addr; 
    int reserve0[4];
    unsigned char *p_pq_cfg_data;
    unsigned int pq_cfg_bytes;
    int reserve1[3];
} RkHwpqAipqMergeCfg;


#ifdef __cplusplus
}
#endif
#endif //__RKHWPQ_UTILS_AIPQ_MERGE_API_H_