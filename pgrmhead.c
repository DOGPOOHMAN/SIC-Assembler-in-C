#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE   1
#define FALSE  0

/* sic_tables.c */
#define OPTABLE_LEN      26
#define PSEUDO_INS_LEN   6

/* sic_bulid_itmfile_functions.c */
#define ALL_LEN      60
#define LABLE_LEN    10
#define CODE_LEN     10
#define OPRENT_LEN   10
#define ERROR_LEN    200

/* sic_build_itmfile.c */
#define LINES_LEN  100
#define SYM_LEN    50

/* sic_find_tables*/
#define OP_BASE      100
#define PI_BASE      200
#define ERROR_VALUE  999

/* pseudo-instruction */
#define START  0
#define BYTE   1
#define WORD   2
#define RESB   3
#define RESW   4
#define END    5

/* operation table */
struct opTable{
  	char     name     [LABLE_LEN + 1];
  	
	/*8 bit 0000 0000
	               ni*/
	unsigned opCode     : 8;
	
	/* foramt 1 or 2 or 3*/
	unsigned format     : 2;
};


/* pseudo isntrution table (piTable)*/
const char * PITABLE[ PSEUDO_INS_LEN ]
		= {"START", "BYTE", "WORD", "RESB", "RESW", "END" };


/* symble table */
typedef struct symtable{
	char     lable     [LABLE_LEN + 1];
	unsigned locctr   : 16;
} SYMTABLE;


const struct opTable OPTABLE[ OPTABLE_LEN ] = {
	/* total 26 */
	/* array subscript 0 ~ 19 */
	{ "ADD",0x18,3 },	{ "AND",0x40,3 },	{ "COMP",0x28,3 },	{ "DIV",0x24,3 },
	{ "J",0x3C,3 },		{ "JEQ",0x30,3 },	{ "JGT",0x34,3 },	{ "JLT",0x38,3 },
	{ "JSUB",0x48,3 },	{ "LDA",0x00,3 },	{ "LDCH",0x50,3 },	{ "LDL",0x08,3 },
	{ "LDX",0x04,3 },	{ "MUL",0x20,3 },	{ "OR",0x44,3 },	{ "RD",0xD8,3 },
	{ "RSUB",0x4C,3 },	{ "STA",0x0C,3 },	{ "STCH",0x54,3 },	{ "STL",0x14,3 },
	
	/* array subscript 20 ~  25*/
	{ "STSW",0xE8,3 },	{ "STX",0x10,3 },	{ "SUB",0x1C,3 },	{ "TD",0xE0,3 },
	{ "TIX",0x2C,3 },	{ "WD",0xDC,3 }	
};


typedef struct line{
	//store all line character
	char * all;
	
	char * lable;
	char * code;
	char * oprent;
	

	/*16 bit 0000 0000 0000 0000
	    	  ^^^ ^^^^ ^^^^ ^^^^ */
	unsigned locctr       : 16;
	
	unsigned subscript;
	
	
	/* store BYTE instruction values */
	char *   bytes;
	char *   ascii;
	
	/*store opCode and WORD intructions values*/
	//Format3 format3;
	
	//store error message
	char * eroMesg;
	
} Line;



