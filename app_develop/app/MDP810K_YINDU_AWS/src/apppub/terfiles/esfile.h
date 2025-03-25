#ifndef _ES_FILE_H_
#define _ES_FILE_H_

#define JBG_TOTAL_NUM		500		// 可存的图片数量

enum{
	WR_JPGDAT_DONE = 0,
	WR_JPGDAT_ING = 1
};

typedef struct st_jbg_dat{
	int num;	// jbg 图片数量
	int offset; // jbg数据的文件起始偏移地址
}ST_JBG_HEAD, *LP_JBG_HEAD;
#define ST_JBG_HEAD_SIZE sizeof(ST_JBG_HEAD)

typedef struct st_jbg_info{
	int offset;
	int preoffset; // 前一笔地址
	int nextoffset; //后一笔地址
	int index;	// jbg索引号,即交易号
	int no;
	int size;	// jbg大小
	void *pjbgdata;	//jbg数据
}ST_JBG_INFO;
#define ST_JBG_INFO_SIZE sizeof(ST_JBG_INFO)


int find_jbg_dat(int index, char *psImageBuffer,int *len);
void Add_JbgToFile(void *arg, appbool bThreadProc);

#endif

