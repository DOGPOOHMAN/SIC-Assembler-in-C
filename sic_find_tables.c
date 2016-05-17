
/* used to find code in opTable
if this code can not be found in Table
set "subscript" value be ERROR_VALUE
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
		subscript = ERROR_VALUE;
	}
	
	return subscript;
}//end of pass1_find_opcode function



/* used to find code in piTable(pseudoTable)
if this code can not be found in Table
set "subscipt" value be ERROR_VALUE
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
		subscript = ERROR_VALUE;
	}
	
	return subscript;
}//end of pass1_find_opcode function


unsigned pass1_find_sym(SYMTABLE *Syms, char * temp){
	unsigned subscript = 0;
	
	for(; subscript < SYM_LEN; subscript++){
		if(strcmp(temp, Syms[ subscript ].lable) == 0 ){
			break;
		}
	}
	
	//if not found
	if(subscript >= SYM_LEN){
		subscript = ERROR_VALUE;
	}
	
	return subscript;
}//end of pass1_find_opcode function


