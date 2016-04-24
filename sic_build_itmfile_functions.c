#define ALL_LEN      60
#define LABLE_LEN    15
#define CODE_LEN     15
#define OPRENT_LEN   15

typedef struct line{
	//sic program format
	unsigned labWide;//column wide of lable
	unsigned codWide;//column wide of opcode
	
	char all   [ ALL_LEN    + 1 ];//pluse one for '\0'
	char lable [ LABLE_LEN  + 1 ];
	char code  [ CODE_LEN   + 1 ];
	char oprent[ OPRENT_LEN + 1 ];
	
	short lableFlag;
	short codeFlag;
	short oprentlag;
} Line;

void pass1_init_line(Line * l){
	memset(l->all,   '\0', sizeof(l->all));
	memset(l->lable, '\0', sizeof(l->lable));
	memset(l->code,  '\0', sizeof(l->code));
	memset(l->oprent,'\0', sizeof(l->oprent));
	
	l->lableFlag  = FALSE;
	l->codeFlag   = FALSE;
	l->oprentlag  = FALSE;
}//end of pass1_init_line function

short pass1_isit_comment(Line * l){
	short isCommentFalg;
	unsigned wide = l->labWide;

  /* two type of write comment

    RETADR	LDA	THREE
  			.
			.	COMMENT
	LENGTH	RESW	1
	BUFFER	RESB	4096
	.
	.	COMMENT
	RDREC	LDX	ZERO*/

	if( (l->all[ 0 ] == '.') || (l->all[ wide + 1 ] == '.')){
		isCommentFalg = TRUE;
	}	
	else{
		isCommentFalg = FALSE;
	}
	
	return isCommentFalg;
}//end of pass1_isit_comment function

void pass1_divi_in3part(Line * l){
	unsigned length = strlen(l->all);
	
	printf("len:%u\n", length);

}//end of pass1_frag_to3part function



