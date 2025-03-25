
#ifndef POS_PARAMS_H
#define POS_PARAMS_H

#define KEYESC			1
#define KEY_1			2
#define KEY_2			3
#define KEY_3			4
#define KEY_4			5
#define KEY_5			6
#define KEY_6			7
#define KEY_7			8
#define KEY_8			9
#define KEY_9			10
#define KEY_0			11
#define KEYMINUS		12
#define KEYEQUAL		13
#define KEYCLEAR		14
#define KEY_Q			16
#define KEY_W			17
#define KEY_E			18
#define KEY_R			19
#define KEY_T			20
#define KEY_Y			21
#define KEY_U			22
#define KEY_I			23
#define KEY_O			24
#define KEY_P			25
#define KEYLEFTBRACE		26
#define KEYRIGHTBRACE		27
#define KEYENTER		28
#define KEY_A			30
#define KEY_S			31
#define KEY_D			32
#define KEY_F			33
#define KEY_G			34
#define KEY_H			35
#define KEY_J			36
#define KEY_K			37
#define KEY_L			38
#define KEYSEMICOLON		39
#define KEYAPOSTROPHE		40
#define KEYGRAVE		41
#define KEYLEFTSHIFT		42
#define KEYBACKSLASH		43
#define KEY_Z			44
#define KEY_X			45
#define KEY_C			46
#define KEY_V			47
#define KEY_B			48
#define KEY_N			49
#define KEY_M			50
#define KEY_COMMA		51
#define KEY_DOT			52
#define KEY_SLASH		53
#define KEY_KPASTERISK		55
#define KEY_KPMINUS		74
#define KEY_KPPLUS		78
#define KEYDOWN		108

#define  STR_PARAMS(A)  (uint8_t*)A,	sizeof(A)
#define  CHAR_PARAMS(A) (uint8_t*)&A,	sizeof(char)
#define  INT_PARAMS(A)	(uint8_t*)&A,	sizeof(int)
#define  LONG_PARAMS(A)	(uint8_t*)&A,	sizeof(int)

#define STRING_ITEM	0x00	//保证最后一位为0x00;
#define ASSCII_ITEM 0x01	
#define HEX_ITEM	0x02	
#define BIN_ITEM	0x03
#define BCD_ITEM	0x04


typedef struct
{
	uint8_t name[40];
	void *ini_ptr;
	uint8_t len;
	uint8_t type;
}PARAMS;

#endif
