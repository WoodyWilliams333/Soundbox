#ifndef _SYS_UPDATE_H_
#define _SYS_UPDATE_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    SYS_UPDATE_OK               = 0, 	/* Update success */
	SYS_UPDATE_ERR_OTHER		= -1,	/* Other error */
    SYS_UPDATE_ERR_SIGN			= -2,	/* Sinature error */
    SYS_UPDATE_NO_SPACE			= -3,	/* FLASH space not enough*/
    SYS_UPDATE_ERR_FID			= -4,	/* FID error*/
} SYS_UPDATE_CODE_RET;


typedef void *fw_node_t;

/**
 * This function will update the application from a pkg file.
 * @param[in] path   pkg file path.
 * @return           Please refer to #SYS_UPDATE_CODE_RET.
 */
extern int sys_update_pkg(const char *path);

/**
 * This function will open a fw update node. 
 * The previous node will be deleted.
 * @return           instance of fw_node_t - success
 * @return           NULL - fail
 */
extern fw_node_t sys_open_fw_node(void);

/**
 * This function will write data to the node file.
 * @param[in] node   instance of the node.
 * @param[in] data   data to write
 * @return           Please refer to #SYS_UPDATE_CODE_RET.
 */
extern int sys_write_fw_node(fw_node_t node, void *data, int len);

/**
 * This function will close the node file.
 * @param[in] node   instance of the node.
 * @return           Please refer to #SYS_UPDATE_CODE_RET.
 */
extern int sys_close_fw_node(fw_node_t node);

/**
 * This function will delete the current node file.
 * @return           Please refer to #SYS_UPDATE_CODE_RET.
 */
extern int sys_delete_fw_node(void);

/**
 * This function will install the current node file.
 * @return           Please refer to #SYS_UPDATE_CODE_RET.
 */
extern int sys_install_fw_node(void);

/**
 * get sysupdate version information
 * @param[out]	version			-	version information
 * @param[in]	size			-	the version length
 * @return		0				-	success
 * @return		other			-	fail
 */
extern int sys_update_get_version(char *version, int size);

#ifdef __cplusplus
}
#endif

#endif

