
/* used to initialize the Line-object */
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
	
	//for record Itmfile Result
	temp->locctr    = 0;
	temp->opCode    = 0;
	temp->subscript = 0;
	temp->objcode   = NULL;
	
	return temp;
}//end of pass1_init_line function



/* used to free the Line-object in memory*/
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
		
	if(l->objcode != NULL)
		free(l->objcode);
		
	free(l);	

}//end of pass1_init_line function



/* used to writing erroMesg into Line-object */
void pass1_write_mesg(Line * l, char * mesg){
	
	if(l->eroMesg == NULL){
		l->eroMesg = malloc( sizeof(char) * (ERROR_LEN  + 1) );
		memset(l->eroMesg, '\0', sizeof(l->eroMesg));
	}
	
	strcat(l->eroMesg, mesg);
}//end of pass1_write_mesg function


/* used to identify the pgm-line is comment or not */
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



/* used to divied the pgm-line into 3 part, 1.lable 2.code 3.oprent */
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

		pass1_write_mesg(l, "-< this line is illegal >-");
		return;
		
	}else if(tab1 == l->all){//means first char is tab, no lable
	
		l->lable = NULL;
	}else{
		
		l->lable = malloc( sizeof(char) * (LABLE_LEN  + 1) );
		memset(l->lable,  '\0', sizeof(l->lable));
		strncpy(l->lable, l->all, (tab1 - l->all));
	}
	
	
	/*tab1 + 1 means the front of opcode column
	RETADR <tab1> LDA   THREE
			      ^
	*/
	front_opcode = tab1 + 1;
	//find second tab in line
	tab2    = strchr(front_opcode,  9);
	//find newline(ascii 10) in line
	newline = strchr(front_opcode,  10);
	
	
	//means this line didn't had oprent
	if(tab2 == 0){
	
		/*the situation is RSUB
			      
		ALPHA <tab1> RSUB <NO tab2> 
				     ^        ^
					\n
		*/
		l->code = malloc( sizeof(char) * (CODE_LEN   + 1) );
		memset(l->code,  '\0', sizeof(l->code));
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
		
		memset(l->code,    '\0', sizeof(l->code  ));
		memset(l->oprent,  '\0', sizeof(l->oprent));
		
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


/* processing the infor of pseudo instruction */
unsigned pass1_process_picode(Line * l, unsigned loc, unsigned adr){
	
	unsigned shiftLoc = 3;
	
	switch(adr){
		
	}//end of switch
	
	
	l->subscript = 999;
	l->locctr    = loc;
	
	return shiftLoc;
}//end of pass1_itis_picode function






