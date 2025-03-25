/*
 * @Description: 
 * @Author: YangJing
 * @Date: 2021-03-15 11:32:58
 * @LastEditors: YangJing
 * @LastEditTime: 2021-04-15 17:26:12
 */
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>

#include "appthread.h"
//#include "nptmsdef.h"

#include "appmalloc.h"

#include "logger.h"



#ifdef _USE_MEM_MONITOR_

typedef struct {
    void *pnext;
    size_t size;
}tms_mem_t;

tms_mem_t* glpTmsmemls = NULL;
static size_t cursize = 0, maxsizeused = 0;
#define TMS_FALSE 0
#define TMS_TRUE 1
static pthread_mutex_t glMemmutex;
static int glMemMutexInited = TMS_FALSE;

void app_printftmsmem(void)
{
    tms_mem_t *ppos = glpTmsmemls;
    int icnt = 0;
    size_t total = 0;

    if (glMemMutexInited == TMS_FALSE) {
        glMemMutexInited = TMS_TRUE;
        app_mutex_creat(&glMemmutex);
    }

    app_mutex_safe_lock(&glMemmutex);
    
    if (!ppos) {
        logger_debug("tms mem is empty, total = %d\n", total);
        app_mutex_safe_unlock(&glMemmutex);
        return;
    }

    
    while (ppos) {
        logger_debug("<%d> [%p(%u)] %p->%p\n", ++icnt, (uint8_t*)ppos + sizeof(tms_mem_t), ppos->size, ppos, ppos->pnext);
        total += ppos->size;
        ppos = ppos->pnext;
    }

    logger_debug("tms memory prt total cnt = %d, total size = %d; cursize = %d, maxsize = %d\n", icnt, total, cursize, maxsizeused); 
    app_mutex_safe_unlock(&glMemmutex);
}

size_t tmsmem_calc_size(void)
{
    tms_mem_t *ppos = glpTmsmemls;
    size_t total = 0;

    if (!ppos) {
        // logger_debug("tms mem is empty, total = %d\n", total);
        return total;
    }

    while (ppos) {
        // logger_debug("<%d> [%p(%u)] %p->%p\n", ++icnt, (uint8_t*)ppos + sizeof(tms_mem_t), ppos->size, ppos, ppos->pnext);
        total += ppos->size;
        ppos = ppos->pnext;
    }

    // logger_debug("tms memory prt total cnt = %d, total size = %d\n", icnt, total);
    return total;  
}

static tms_mem_t* tmsmem_new(size_t size)
{
    tms_mem_t *ptmm = malloc(sizeof(tms_mem_t) + size);

    // logger_debug("%s ptmm = %p\n", __func__, ptmm);
    if (ptmm) {
        ptmm->pnext = NULL;
        ptmm->size = size;
    }

    return ptmm;
}

static void tmsmem_delete(tms_mem_t* ptmm)
{
    // logger_debug("%s ptm = %p\n", __func__, ptmm);
    if (ptmm) {
        free(ptmm);
    }
}

static void tsm_mem_ls_append(tms_mem_t* ptmm)
{
    tms_mem_t *ppos = NULL;

    // logger_debug("%s ptm = %p, glpTmsmemls = %p\n", __func__, ptmm, glpTmsmemls);

    if (!glpTmsmemls) {
        glpTmsmemls = ptmm;   
        // logger_debug("new list\n");
        return;
    }    

    ppos = glpTmsmemls;
    while (ppos->pnext) {
        ppos = ppos->pnext;
    }
    ppos->pnext = ptmm;

    // logger_debug("new node\n");
}

static void tsm_mem_ls_remove(tms_mem_t* ptmm)
{
    tms_mem_t *ppos = NULL, *ppre = NULL;

    // logger_debug("%s ptm = %p, glpTmsmemls = %p\n", __func__, ptmm, glpTmsmemls);

    if (!glpTmsmemls || !ptmm) {
        // logger_debug("%s list empty or ptmm is wrong\n");
        return;  
    }
    
    ppre = ppos = glpTmsmemls;
    do {
        if (ptmm == ppos) {
            break;
        }

        ppre = ppos;
        ppos = ppos->pnext;        
    } while(ppos);

    // logger_debug("%s ppre = %p, ppos = %p\n", __func__, ppre, ppos);
    if (ppos) {
        if (ppos == glpTmsmemls) {
            glpTmsmemls = glpTmsmemls->pnext;        
        }
        else {
            ppre->pnext = ppos->pnext;
        }
    }      
}

void *app_malloc(size_t size)
{
    tms_mem_t *ptmm = NULL;
    void* pret = NULL;

    // logger_debug("%s pmm = %p\n", __func__, ptmm);
    if (glMemMutexInited == TMS_FALSE) {
        glMemMutexInited = TMS_TRUE;
        app_mutex_creat(&glMemmutex);
    }

    app_mutex_safe_lock(&glMemmutex);
    ptmm = tmsmem_new(size);
    if (ptmm) {
        tsm_mem_ls_append(ptmm);  

        pret = (uint8_t *)ptmm + sizeof(tms_mem_t);
        
        cursize += ptmm->size; 
        if (maxsizeused < cursize) {
            maxsizeused = cursize;
        }
    }
    
    logger_debug("%s pret(%d) = %p\n", __func__, size, pret);
    // app_printftmsmem();

    app_mutex_safe_unlock(&glMemmutex);
    return pret;
}

void app_free(void *ptr)
{
    tms_mem_t *ptmm = NULL;
    void *ptmp = NULL;

    logger_debug("%s ptr = %p\n", __func__, ptr);
    if (!ptr) {
        return;
    }

    ptmp = (uint8_t*)ptr - sizeof(tms_mem_t);
    ptmm = (tms_mem_t *)ptmp;
    // logger_debug("%s ptmm = %p\n", __func__, ptmm);
    if (!ptmm) {
        return;
    }

    if (glMemMutexInited == TMS_FALSE) {
        glMemMutexInited = TMS_TRUE;
        app_mutex_creat(&glMemmutex);
    }

    app_mutex_safe_lock(&glMemmutex);
    
    tsm_mem_ls_remove(ptmm);
    cursize -= ptmm->size;
    tmsmem_delete(ptmm);

    // app_printftmsmem();
    app_mutex_safe_unlock(&glMemmutex);
}

#else

void app_printftmsmem(void)
{
    logger_debug("no use tms memory monitor\n");
}

#endif