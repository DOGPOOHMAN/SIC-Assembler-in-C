
/* used to identify the pgm-line is comment or not */
short p131_isit_comment(char * allLine){
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
}//end of p131_isit_comment function

