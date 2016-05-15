
unsigned pass1_find_opcode(char * temp){
	unsigned count = 0;
	
	for(; count < OPTABLE_LEN; count++){
		if(strcmp(temp, OPTABLE[ count ].name) == 0){
			break;
		}
	}
	
	//if not found
	if(count >= OPTABLE_LEN){
		count = 99;
	}
	
	return count;
}//end of pass1_find_opcode function


unsigned pass1_find_pi(char * temp){
	unsigned count = 0;
	
	for(; count < PSEUDO_INS_LEN; count++){
		if(strcmp(temp, PITABLE[ count ]) == 0){
			break;
		}
	}
	
	//if not found
	if(count >= PSEUDO_INS_LEN){
		count = 99;
	}
	
	return count;
}//end of pass1_find_opcode function

//SYMTABLE * pass1_init_symtable(char * lable, unsigned locctr){
//	SYMTABLE * temp;
//	temp = malloc( sizeof(SYMTABLE) );
//	
//	strcpy(temp->lable, lable);
//	temp->locctr = locctr;
//	
//	return temp;
//}//end of pass1_init_symtable function

