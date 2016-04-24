void pass1_set_format_wide(Line * l){
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
				/* to advoid long if-express so divided into two part */
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
			else{
				/* let user setting againt */;
			}
		}//end of while
	}//end of if

}//end of pass1_set_format_wide function

