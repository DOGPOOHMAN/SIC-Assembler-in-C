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
} Line;

void pass1_init_line(Line * l){
	strcpy(l->all,    "");
	strcpy(l->lable,  "");
	strcpy(l->code,   "");
	strcpy(l->oprent, "");
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

void pass1_divi_to3part(Line * l){


}//end of pass1_frag_to3part function



