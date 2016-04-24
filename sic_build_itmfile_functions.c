#define ALL_LEN      60
#define LABLE_LEN    15
#define CODE_LEN     15
#define OPRENT_LEN   15
#define ERROR_LEN    100

//#define DEBUG
typedef struct line{
	char all   [ ALL_LEN    + 1 ];//pluse one for '\0'
	char lable [ LABLE_LEN  + 1 ];
	char code  [ CODE_LEN   + 1 ];
	char oprent[ OPRENT_LEN + 1 ];
	
	short lableFlag;
	short codeFlag;
	short oprentFlag;
	
	short eroFlag;
	char  eroMesg [ERROR_LEN];
} Line;

void pass1_init_line(Line * l){
	//memset can init all string as "\0\0\0\0\0\0\0...."
	memset(l->all,    '\0', sizeof(l->all));
	memset(l->lable,  '\0', sizeof(l->lable));
	memset(l->code,   '\0', sizeof(l->code));
	memset(l->oprent, '\0', sizeof(l->oprent));
	memset(l->eroMesg,'\0', sizeof(l->eroMesg));

	
	l->lableFlag   = FALSE;
	l->codeFlag    = FALSE;
	l->oprentFlag  = FALSE;
	l->eroFlag     = FALSE;
}//end of pass1_init_line function

short pass1_isit_comment(Line * l){
	short isCommentFalg;

  /* two type of write comment

    RETADR	LDA	THREE
  	<tab>   .
	<tab>	.	COMMENT
	LENGTH	RESW	1
	BUFFER	RESB	4096
	.
	.	COMMENT
	RDREC	LDX	ZERO*/

	if( (l->all[ 0 ] == '.') || (l->all[ 1 ] == '.')){
		isCommentFalg = TRUE;
	}	
	else{
		isCommentFalg = FALSE;
	}
	
	return isCommentFalg;
}//end of pass1_isit_comment function

void pass1_divi_in3part(Line * l){
	unsigned length      = strlen(l->all);
	char * tab1          = NULL;
	char * tab2          = NULL;
	char * newline       = NULL;
	char * front_opcode  = NULL;
	char * front_oprent  = NULL;
	
	
	/*find first tab(ascii 9) in ilne
	  strchr() will find tab in string and return char * ptr */
	tab1 = strchr(l->all,    9);
	
	/*means can't find tab, illegal express
		user maybe write enter in this line*/
	if(tab1 == 0){

		strcat(l->eroMesg, "-< this line is illegal,maybe you only write enter, please delete enter >-");
		l->eroFlag = TRUE;
		return;
	}else if(tab1 == l->all){//means first char is tab, no lable
	
		l->lableFlag  = FALSE;
	}else{
		
		l->lableFlag  = TRUE;
		strncpy(l->lable, l->all, (tab1 - l->all));
	}
	
	
	/*tab1 + 1 means the front of opcode column
	RETADR	LDA	THREE
			^
	*/
	front_opcode = tab1 + 1;
	//find second tab in line
	tab2    = strchr(front_opcode,  9);
	//find newline(ascii 10) in line
	newline = strchr(front_opcode,  10);
	
	if(tab2 == 0){//means this line didn't had oprent
	
		/*the situation of RSUB
		ALPHA	RSUB
				^   ^
					\n
		*/
		strncpy(l->code, front_opcode, (newline - front_opcode));
		l->codeFlag    = TRUE;
		l->oprentFlag  = FALSE;
		
	}
	else{//means this line had opcode and oprent
	
		/*tab2 + 1 means the front of opcode column
		RETADR	LDA	THREE
					^
		*/
		front_oprent = tab2 + 1;
		
		strncpy(l->code,   front_opcode, (tab2 - front_opcode));
		strncpy(l->oprent, front_oprent, (newline - front_oprent));
		l->codeFlag    = TRUE;
		l->oprentFlag  = TRUE;
	}
	
	#ifdef DEBUG
	printf("1:%x\n", tab1);
	printf("2:%x\n", tab2);
	printf("c:%x\n", comma);
	printf("a:%x\n", l->all);
	#endif

}//end of pass1_frag_to3part function









