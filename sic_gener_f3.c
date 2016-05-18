
void p200_gener_f3_objcode(SYMTABLE * Syms, Line ** Lines, unsigned countLines){
    
    //store the malloc struct of Line object
	Line    * L  = NULL;
	Format3 * F3 = NULL;
	
	
	int i = 0;
	unsigned opTableAdr  = 0;
	unsigned symTableAdr = 0;
	unsigned len         = 0;
	
	char lable [LABLE_LEN + 1];
	//init lable
	memset(lable,'\0', sizeof(lable));
	
	
	
	for(i = 1; i < countLines - 1; i++){
	    
		L = Lines[ i ];
		
		//if this Line-object is opCode
		if(L->subscript / OP_BASE == 1){
		    
		    opTableAdr = L->subscript - OP_BASE;
		    
		    //init F3
            F3 = p010_init_format3(0);
            F3->opCode = OPTABLE[ opTableAdr ].opCode;
            
		    //set disp and xFlag
		    if(opTableAdr == 16){
		        //special case: RSUB    
		        F3->disp   = 0x0;
            }else{
                
      
		        len = strlen(L->oprent);
		        /* if it is x relative
                   BUFFER,X
                          ^  len-1 
               */
		        if(L->oprent[len - 1] == 'X'){
		            
		            F3->xFlag = TRUE;
		            
		            /*  oprent = BUFFER,X
                    lable = BUFFER
                   */
		            strncpy(lable, (char *)(&L->oprent[0]), len -2 );
		            symTableAdr = p012_find_sym(Syms, lable);
                }else{
                    
                    symTableAdr = p012_find_sym(Syms, L->oprent);
                }
		        
		        
                //set the disp via symble-table locctr
                F3->disp = Syms[ symTableAdr ].locctr;
		        
            }//end of if(opTableAdr == 16)
            
            
            //generate objcode
            p012_calcu_format3(F3);
            
            //store the result into line-obj
            L->format3 = F3;
            
        }//end of if(L->subscript / OP_BASE == 1)
	}//end of for-loop
	
}//end of p200_gener_f3_objcode function

