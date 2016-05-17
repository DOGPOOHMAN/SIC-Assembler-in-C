


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






/* processing the infor of pseudo instruction */
unsigned pass1_process_picode(Line * L){
	
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
    	    intValue = pass1_hex2dec(strValue);
            
        }else{
            
            intValue = atoi(oprent);
        }//end of if(oprent[0] == 'X')
            
        
        
        //each intrustion had own process way
        switch(L->subscript - PI_BASE){
    	    
            case WORD:
                //format3
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
               pass1_write_mesg(L, "-< Error in  pass1_process_picode(Line * L)>-");
                
        }//end of switch
	
        
    }//end of if(L->subscript - PI_BASE == BYTE)
    
	
	return shiftLoc;
}//end of pass1_itis_picode function






