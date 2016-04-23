#define ALL_LEN      61
#define LABLE_LEN    16
#define CODE_LEN     16
#define OPRENT_LEN   16

typedef struct line{
	//sic program format
	unsigned labWide;//column wide of lable
	unsigned codWide;//column wide of opcode
	
	char all   [ ALL_LEN    ];
	char lable [ LABLE_LEN  ];
	char code  [ CODE_LEN   ];
	char oprent[ OPRENT_LEN ];
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

void pass1_frag_to3part(Line * l){


}//end of pass1_frag_to3part function

void pass1_set_pgrmformat(Line * l){
	char choice;
	
	printf("------------------------------------\n");
	printf("Column wide of character of lable  :%d\n", l->labWide);
	printf("Column wide of character of opcode :%d\n", l->codWide);
	printf("SIC> Do you want to use default setting? (y/n):");
	scanf(" %c", &choice);
	
	if(choice != 'y'){
		
		short setSuccess = FALSE;
		unsigned tempLabWide;
		unsigned tempCodWide;
		
		
		
		while(setSuccess == FALSE){
			
			//init choice
			choice = ' ';
		
			printf("------------------------------------\n");
			printf("lable  :");
			scanf(" %u", &tempLabWide);
			
			printf("opcode :");
			scanf(" %u", &tempCodWide);
			
			printf("SIC> Do you want to use this setting? (y/n):");
			scanf(" %c", &choice);
			
			if(choice == 'y')
			{
				if( (tempLabWide <= 15) && (tempCodWide <= 15) ){
					if( (tempLabWide >= 8) && (tempCodWide >= 8) ){
						
						setSuccess = TRUE;
						l->labWide = tempLabWide;
						l->codWide = tempCodWide;
					}
					else{
						puts("Maximum wide of Lable and Opcode is [15]");
						puts("Minimum wide of Lable and Opcode is [08]");
					}
				}
				else{
					puts("Maximum wide of Lable and Opcode is [15]");
					puts("Minimum wide of Lable and Opcode is [08]");
				}
			} 
		}//end of while
	}//end of if

}//end of pass1_set_pgrmformat function





//short pass1_is_comment()
//
//short pass1_pitable_start()

