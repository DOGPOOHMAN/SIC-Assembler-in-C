
/* used to find code in opTable
if this code can not be found in Table
set "subscript" value be 99
*/
unsigned pass1_find_opcode(char * temp){
	unsigned subscript = 0;
	
	for(; subscript < OPTABLE_LEN; subscript++){
		if(strcmp(temp, OPTABLE[ subscript ].name) == 0){
			break;
		}
	}
	
	//if not found
	if(subscript >= OPTABLE_LEN){
		subscript = 99;
	}
	
	return subscript;
}//end of pass1_find_opcode function



/* used to find code in piTable(pseudoTable)
if this code can not be found in Table
set "subscipt" value be 99
*/
unsigned pass1_find_pi(char * temp){
	unsigned subscript = 0;
	
	for(; subscript < PSEUDO_INS_LEN; subscript++){
		if(strcmp(temp, PITABLE[ subscript ]) == 0){
			break;
		}
	}
	
	//if not found
	if(subscript >= PSEUDO_INS_LEN){
		subscript = 99;
	}
	
	return subscript;
}//end of pass1_find_opcode function



/* used to find code in opTable and piTable 
if this code can not be found in Tables
set "subscript" value be 99
*/
unsigned pass1_find_in_table(char * temp){
	unsigned subscript = 0;
	
	//find in opTable
	subscript = pass1_find_opcode(temp);
	
	//find in pseudoTable
	if(subscript == 99){
	    subscript = pass1_find_pi(temp);
    }
	
	return subscript;
}//end of pass1_find_in_table function

//SYMTABLE * pass1_init_symtable(char * lable, unsigned locctr){
//	SYMTABLE * temp;
//	temp = malloc( sizeof(SYMTABLE) );
//	
//	strcpy(temp->lable, lable);
//	temp->locctr = locctr;
//	
//	return temp;
//}//end of pass1_init_symtable function

