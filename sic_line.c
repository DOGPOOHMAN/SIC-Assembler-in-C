/* used to initialize the Line-object */
Line * p110_init_line(char * allLine){
	Line * L =  NULL;
	
	L = (Line *)malloc( sizeof(Line) ); 
	
	//init Line variable
	L->all = malloc( sizeof(char) * (ALL_LEN  + 1) );
	strcpy(L->all, allLine);
	
	
	L->lable    = NULL;
	L->code     = NULL;
	L->oprent   = NULL;
	
	
	L->locctr    = 0;
	L->subscript = 0;
	
	
	L->format3 = NULL;
	
	L->bytes   = NULL;
	L->ascii   = NULL;
	
	
	L->eroMesg  = NULL;
	return L;
}//end of p110_init_line function



/* used to free the Line-object in memory*/
void p111_delete_line(Line * L){
    
    //all
	if(L->all != NULL)
		free(L->all);
    
    //lable
	if(L->lable != NULL)
		free(L->lable);
		
	//code
    if(L->code != NULL)
		free(L->code);

    //oprent		
	if(L->oprent != NULL)
		free(L->oprent);
	
	//bytes
    if(L->bytes != NULL)
		free(L->bytes);
		
	//format3
    if(L->format3 != NULL)
		free(L->format3);
	
    //ascii	
	if(L->ascii != NULL)
		free(L->ascii);
    
    //eroMesg
	if(L->eroMesg != NULL)
		free(L->eroMesg);
		
	free(L);	

}//end of p111_init_line function



/* used to writing erroMesg into Line-object */
void p112_write_mesg(Line * L, char * mesg){
	
	if(L->eroMesg == NULL){
		L->eroMesg = malloc( sizeof(char) * (ERROR_LEN  + 1) );
		memset(L->eroMesg, '\0', sizeof(L->eroMesg));
	}
	
	strcat(L->eroMesg, mesg);
}//end of p112_write_mesg function



/* used to divied the pgm-line into 3 part, 1.lable 2.code 3.oprent */
void p113_divi_in3part(Line * L){

	//to record the char address in 
	char * tab1          = NULL;
	char * tab2          = NULL;
	char * newline       = NULL;
	char * front_opcode  = NULL;
	char * front_oprent  = NULL;
	
	
	/*find first tab(ascii 9) in ilne
	  strchr() will find tab in string and return char * ptr */
	tab1 = strchr(L->all,    9);
	
	/*means can't find tab, illegal express
		user maybe write enter in this line*/
	if(tab1 == 0){

		p112_write_mesg(L, "-< this line is illegal >-");
		return;
		
	}else if(tab1 == L->all){//means first char is tab, no lable
	
		L->lable = NULL;
	}else{
		
		L->lable = malloc( sizeof(char) * (LABLE_LEN  + 1) );
		memset(L->lable,  '\0', sizeof(L->lable));
		strncpy(L->lable, L->all, (tab1 - L->all));
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
		L->code = malloc( sizeof(char) * (CODE_LEN   + 1) );
		memset(L->code,  '\0', sizeof(L->code));
		strncpy(L->code, front_opcode, (newline - front_opcode));	
	}
	else{//means this line had opcode and oprent
	
		/*tab2 + 1 means the front of opcode column
		RETADR	LDA	THREE
					^
		*/
		front_oprent = tab2 + 1;
		
		L->code   = malloc( sizeof(char) * (CODE_LEN   + 1) );
		L->oprent = malloc( sizeof(char) * (OPRENT_LEN + 1) );
		
		memset(L->code,    '\0', sizeof(L->code  ));
		memset(L->oprent,  '\0', sizeof(L->oprent));
		
		strncpy(L->code,   front_opcode, (tab2    - front_opcode));
		strncpy(L->oprent, front_oprent, (newline - front_oprent));
	
	}
	
	#ifdef DEBUG
	printf("1:%x\n", tab1);
	printf("2:%x\n", tab2);
	printf("c:%x\n", comma);
	printf("a:%x\n", L->all);
	#endif

}//end of p113_frag_to3part function








/* used to find code in opTable and piTable 
if this code can not be found in Tables
set "subscript" value be ERROR_VALUE
*/
void p114_find_code_in_table(Line * L){
    char     * temp      = NULL;       
	unsigned   subscript = 0;
	
	temp = L->code;
	//find in opTable
	subscript = p010_find_opcode(temp);
	
	if(subscript != ERROR_VALUE){
	    
	    subscript = subscript + OP_BASE;
	    L->subscript = subscript;
	    
    }else{
        
        //find in pseudoTable
        subscript = p011_find_pi(temp);
        if(subscript != ERROR_VALUE){
	    
	       subscript = subscript + PI_BASE;
	       L->subscript = subscript;
     	}else{
     	    
     	    L->subscript  = ERROR_VALUE;
 	        L->locctr     = 0xFFFF;
	        p112_write_mesg(L, "-< opcode or picode is illegal >-");
       }
        
    }//if(subscript != ERROR_VALUE)
	
	
	
}//end of p114_find_in_table function






/* processing the infor of pseudo instruction */
unsigned p115_process_picode(Line * L){
	
	unsigned  shiftLoc = 0;
	unsigned  objLen   = 0;
	char      oprent   [OPRENT_LEN + 1 ];
	
	//init oprent
	memset(oprent,      '\0', sizeof(oprent  ));
    strcpy(oprent, L->oprent);
    
    
    //process BYTE instruction
    if(L->subscript - PI_BASE == BYTE){
        
        objLen = strlen(oprent);
        char *temp = NULL;
 
        //init temp
        temp = malloc( sizeof(char) * ( (objLen - 3)+ 1) );
        memset(temp,  '\0', sizeof(temp));
        
        /* EOF    BYTE    C'EOF'
            oprent = C'EOF'
            temp = EOF
            
            INPUT    BYTE    X'F1'
            oprent = X'F1'
            temp = F1
        */
        strncpy(temp, (char *)(&oprent[2]), objLen -3 );
        
        
        if(oprent[0] == 'C'){
            
            L->ascii = temp;
            //one character is one byte in memory
            shiftLoc = strlen(temp) * 2;
            
        }else if(oprent[0] == 'X'){
            
            L->bytes = temp;
            //two hex words are one byte in memory
            shiftLoc = strlen(temp) / 2;
        }//end of if(oprent[0] == 'C')
       
   
   
   
    //process the other three instruction WORD RESB RESW
    }else{
        
        unsigned  intValue = 0;
	    char      strValue [OPRENT_LEN + 1 ];
        
        //init strValue
	    memset(strValue,    '\0', sizeof(strValue));
        
        //turn the hex-value into dec-value
        if(oprent[0] == 'X'){
    	    
    	    objLen = strlen(oprent);
    	    
    	    //copy the hex words into strValue
    	    strncpy(strValue, (char *)(&L->oprent[2]), objLen -3 );
    	    
    	    //turn the hex-value into dec-value
    	    intValue = p000_hex2dec(strValue);
            
        }else{
            
            intValue = (unsigned)atoi(oprent);
        }//end of if(oprent[0] == 'X')
            
        
        
        //each intrustion had own process way
        switch(L->subscript - PI_BASE){
    	    
            case WORD:
                //WORD generate a 3-bytes objCode 
                L->format3 = p010_init_format3(intValue);
                shiftLoc = 3;
                break;
    	        
            case RESB:
                
                shiftLoc = intValue;
                break;
                
            case RESW:
                
                shiftLoc = intValue * 3;
                break;
           
           case END:
                
                shiftLoc = 0;
                break;
                
           default:
               p112_write_mesg(L, "-< Error in  pass1_process_picode(Line * L)>-");
                
        }//end of switch
	
        
    }//end of if(L->subscript - PI_BASE == BYTE)
    
	
	return shiftLoc;
}//end of p115_process_picode function



