typedef struct line{
	//sic program format
	unsigned labWide;//column wide of lable
	unsigned codWide;//column wide of opcode
	
	char all   [60];
	char lable [16];
	char code  [16];
	char oprent[16];
} Line;


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



void pass1_init_line(Line * l){
	strcpy(l->all,    "");
	strcpy(l->lable,  "");
	strcpy(l->code,   "");
	strcpy(l->oprent, "");
}

//short pass1_is_comment()
//
//short pass1_pitable_start()

