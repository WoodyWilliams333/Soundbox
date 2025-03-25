#ifndef _BUTTON_H_
#define _BUTTON_H_
typedef enum{
    BUTTON_SHORT_PRESS  = 1, //�̰�
    BUTTON_LONG_PRESS   = 2, //����
    BUTTON_DOUBLE_CLICK = 3, //˫��
}enumButtonCmd;

typedef struct{
    int bt_key;
    enumButtonCmd bt_cmd;  //���� �̰� ˫��
}stButtonInfo;

//��鰴����˫�����߳���
void get_key_ms(int msec, stButtonInfo* btInfo);
/**
 * @brief ��鰴��
 * 
 */
void chk_button_status(void);

#endif //_BUTTON_H_