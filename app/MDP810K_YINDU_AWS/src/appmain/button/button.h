#ifndef _BUTTON_H_
#define _BUTTON_H_
typedef enum{
    BUTTON_SHORT_PRESS  = 1, //短按
    BUTTON_LONG_PRESS   = 2, //长按
    BUTTON_DOUBLE_CLICK = 3, //双击
}enumButtonCmd;

typedef struct{
    int bt_key;
    enumButtonCmd bt_cmd;  //长按 短按 双击
}stButtonInfo;

//检查按键，双击或者长按
void get_key_ms(int msec, stButtonInfo* btInfo);
/**
 * @brief 检查按键
 * 
 */
void chk_button_status(void);

#endif //_BUTTON_H_