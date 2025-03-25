/*
 * @Description: seos库头文件
 * @Author: YangJing
 * @Date: 2020-04-03 09:04:00
 * @LastEditors: YangJing
 * @LastEditTime: 2020-04-14 09:29:25
 */

#ifndef __SEOS_H__
#define __SEOS_H__

#ifdef __cplusplus
extern "C" {
#endif /* end of __cplusplus */


#ifndef MAYBE_UNUSE
#define MAYBE_UNUSE(x)              (void)(x)
#endif

#ifndef UNUSE
#define UNUSE(x)                    (void)(x)
#endif

#ifndef __attribute_used__
#define __attribute_used__          __attribute__((__used__))
#endif

#ifndef __attribute_maybe_unused__
#define __attribute_maybe_unused__  __attribute__((__unused__)) 
#endif


/**
* @brief 设置wnet库的日志开关，默认情况是日志关闭的
* @param[in] on     欲设置的日志开关状态，非0表示打开，为0表示关闭，见 LOGGER_MODULE_ON 枚举定义
* @return 设置后的日志开关状态
*	-<em> != 0 </em>  logger on
*	-<em> == 0 </em>  logger off
*/
extern int seos_logger_on(int on);


/**
* @brief 获取libseos库的版本信息
* @param[out] version，libwnet库的版本信息输出   
* @param[in]  size，version执行的buffer长度，建议至少64字节    
* @return 获取的结果
*	-<em> == 0  </em>  成功
*	-<em> == -1 </em>  失败
*/
extern int seos_get_version(char *version, int size);

#ifdef __cplusplus
}
#endif /* end of __cplusplus */

#endif /* end of __SEOS_H__ */

