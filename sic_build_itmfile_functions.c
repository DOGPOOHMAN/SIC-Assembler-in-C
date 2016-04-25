#define ALL_LEN      60
#define LABLE_LEN    10
#define CODE_LEN     10
#define OPRENT_LEN   10
#define ERROR_LEN    100

//#define DEBUG
typedef struct line{
	//store all line character
	char * all;
	
	char * lable;
	char * code;
	char * oprent;
	
	//store error message
	char * eroMesg;
	
} Line;

Line * pass1_init_line(char * allLine){
	Line * temp =  NULL;
	
	temp = malloc( sizeof(Line) * (ALL_LEN  + 1) ); 
	
	//init Line variable
	temp->all = malloc( sizeof(char) * (ALL_LEN  + 1) );
	strcpy(temp->all, allLine);
	
	temp->lable    = NULL;
	temp->code     = NULL;
	temp->oprent   = NULL;
	temp->eroMesg  = NULL;
	
	return temp;
}//end of pass1_init_line function

void pass1_delete_line(Line * l){
	if(l->all != NULL)
		free(l->all);

	if(l->lable != NULL)
		free(l->lable);
		
	if(l->code != NULL)
		free(l->code);
		
	if(l->oprent != NULL)
		free(l->oprent);
		
	if(l->eroMesg != NULL)
		free(l->eroMesg);
		
	free(l);	

}//end of pass1_init_line function

short pass1_isit_comment(char * allLine){
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

	if( (allLine[ 0 ] == '.') || (allLine[ 1 ] == '.')){
		isCommentFalg = TRUE;
	}	
	else{
		isCommentFalg = FALSE;
	}
	
	return isCommentFalg;
}//end of pass1_isit_comment function

void pass1_divi_in3part(Line * l){

	//to record the char address in 
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

		if(l->eroMesg == NULL){
			l->eroMesg = malloc( sizeof(char) * (ERROR_LEN  + 1) );
			memset(l->eroMesg, '\0', sizeof(l->eroMesg));
		}
		
		strcat(l->eroMesg, "-< this line is illegal >-");

		return;
	}else if(tab1 == l->all){//means first char is tab, no lable
	
		l->lable = NULL;
	}else{
		
		l->lable = malloc( sizeof(char) * (LABLE_LEN  + 1) );
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
		l->code = malloc( sizeof(char) * (CODE_LEN   + 1) );
		strncpy(l->code, front_opcode, (newline - front_opcode));	
	}
	else{//means this line had opcode and oprent
	
		/*tab2 + 1 means the front of opcode column
		RETADR	LDA	THREE
					^
		*/
		front_oprent = tab2 + 1;
		
		l->code   = malloc( sizeof(char) * (CODE_LEN   + 1) );
		l->oprent = malloc( sizeof(char) * (OPRENT_LEN + 1) );
		
		strncpy(l->code,   front_opcode, (tab2    - front_opcode));
		strncpy(l->oprent, front_oprent, (newline - front_oprent));
	
	}
	
	#ifdef DEBUG
	printf("1:%x\n", tab1);
	printf("2:%x\n", tab2);
	printf("c:%x\n", comma);
	printf("a:%x\n", l->all);
	#endif

}//end of pass1_frag_to3part function









