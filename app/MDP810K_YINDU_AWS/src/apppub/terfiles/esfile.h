#ifndef _ES_FILE_H_
#define _ES_FILE_H_

#define JBG_TOTAL_NUM		500		// �ɴ��ͼƬ����

enum{
	WR_JPGDAT_DONE = 0,
	WR_JPGDAT_ING = 1
};

typedef struct st_jbg_dat{
	int num;	// jbg ͼƬ����
	int offset; // jbg���ݵ��ļ���ʼƫ�Ƶ�ַ
}ST_JBG_HEAD, *LP_JBG_HEAD;
#define ST_JBG_HEAD_SIZE sizeof(ST_JBG_HEAD)

typedef struct st_jbg_info{
	int offset;
	int preoffset; // ǰһ�ʵ�ַ
	int nextoffset; //��һ�ʵ�ַ
	int index;	// jbg������,�����׺�
	int no;
	int size;	// jbg��С
	void *pjbgdata;	//jbg����
}ST_JBG_INFO;
#define ST_JBG_INFO_SIZE sizeof(ST_JBG_INFO)


int find_jbg_dat(int index, char *psImageBuffer,int *len);
void Add_JbgToFile(void *arg, appbool bThreadProc);

#endif

