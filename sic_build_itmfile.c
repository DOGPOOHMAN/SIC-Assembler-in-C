/* This function (pass1_built_itmfile()) provide a platform for
   read user's sic program and build itmfile functions, this function integrate
   variable which used by read and build itmfile, so these variable and functions
   didn't put into main function, let the code looks nice and clean in main().
*/

#define DEBUG
unsigned p130_built_itmfile(FILE * sicPgrm, SYMTABLE * Syms, Line ** Lines){

	//store the malloc struct of Line object
	Line * L;
	
	//store program infor
	char     pgrmName [10];
	unsigned startLoc = 0;
	unsigned pgmLen   = 0;
	
	//will change in processing
	
	//store the temporarily string of read line
	char     tmpLine    [ ALL_LEN + 1 ];
	unsigned nowLoc     =  0;
	unsigned countLines =  0;
	unsigned countSyms  =  0;


	short errorFlag     =  FALSE;
	short stopReadFlag  =  FALSE;
	
	int i = 0;//for loop
	
	//init array as "\0\0\0\0\0\0....."
	memset(pgrmName,  '\0', sizeof(pgrmName));
	

	

	
	
	/* starting reading program content 
	one time only read a line into program from user's SIC program file*/
	
	while(stopReadFlag == FALSE){
		
		//init variable
		memset(tmpLine,'\0', sizeof(tmpLine));
		L = NULL;
		
		
		//read a line from program
		if(fgets(tmpLine, ALL_LEN, sicPgrm) == NULL){
			stopReadFlag = TRUE;
			continue;
		}
		/*if it is comment line drop it,but 
		divided this line to three part*/
		else if(p131_isit_comment(tmpLine) == TRUE){
			continue;
		}
		else{
		
			//init(malloc) struct Line object
			L = p110_init_line(tmpLine);
			
			//divided to three part of lable, code, oprent
			p113_divi_in3part(L);
			
			//store this line object into Line object array
			Lines[countLines] = L;
			countLines++;
			
		}//end of if(fgets)
		
	}//end of while
	
	
	//store the program-name from Line-object
	strcpy(pgrmName,        Lines[0]->lable  );
	
	//store the starting locctr from Line-object
	nowLoc = p000_hex2dec( Lines[0]->oprent );
	
	
	
	/* starting write detail infor into Line-object */		
	

	
	/*First line is title(COPY START 1000), it is spacial case and didn't need
    to find opcode and paseudo-instruction,so for-loop start at 1 not 0
    
    and the last line "END FIRST" is spcial case,
    so for-loop use " i < countLines - 1 "

	This for-loop process use to rocord Symble-Lable and opCode
	*/
	for(i = 1; i < countLines - 1; i++){
		L = Lines[ i ];

		//have error mesag means this line is illegal
		if(L->eroMesg != NULL){
			
			L->locctr = 0xFFFF;
			continue;
			
		}else {
			
			//have lable and insert into Syms(Symble-Table)
			if(L->lable != NULL){
				strcpy(Syms[ countSyms ].lable, L->lable);
				Syms[ countSyms ].locctr = nowLoc;
				countSyms++;
			}
			
			/* find opcode and record subcript
            if this code can not be found in opTable,
            set "tableAdr" value be 99
            */
			p114_find_code_in_table(L);
			
			
			//it is legal line
			if(L->eroMesg == NULL){

                L->locctr = nowLoc;
                //process opCode
                if(L->subscript / OP_BASE == 1){
    				
    				//increse locctr by opcode format
    				nowLoc = nowLoc + OPTABLE[ L->subscript - OP_BASE ].format;
    				
    				
    			//process pseudo-instruction
    			}else if(L->subscript / PI_BASE == 1){
    			
    			    unsigned shiftLoc = 0;
    				
    				shiftLoc = p115_process_picode(L);
    			   
                    nowLoc = nowLoc + shiftLoc;
                }
            	
			}//end of if(L->eroMesg == NULL)
			
		}//end of if(L->eroMesg != NULL)
		
	}//end of for
	
	
	
	//store the program lenth
	pgmLen = nowLoc - p000_hex2dec( Lines[0]->oprent );
	
	
	//store program starting location
	unsigned loc = 0;
	unsigned adr = 0;
	
	//the last line  "END FIRST"
	L = Lines[ countLines - 1 ];
	
	if(L->oprent == NULL){
        
        /* case: START 1000
        use 1000 be start-locctr
        */
        
        startLoc =  p000_hex2dec( Lines[0]->oprent );
    }else{
        
        /* case: END FIRST
        use FIRST be start-locctr
        find FIRST in Symble-Table
        */
        adr = p012_find_sym(Syms, L->oprent);
        
        //successful find the symble-lable
        if(adr != ERROR_VALUE){
            
            startLoc = Syms[ adr ].locctr;
        }else{
            
            p112_write_mesg(L, "-< can not find start Lable >-");
        }
        
    }//end of if(L->oprent == NULL)
    
    
    
    /* start printing the itermidate information */
    
    printf("Program-Name:\t%s\n", pgrmName);
    printf("Start-Loc:\t%x\n", startLoc);
    printf("Program-Length:\t%x\n", pgmLen);


    puts("\n\n>>>>>>>>>>>>>>> Each Line Detail <<<<<<<<<<<<<<<<<");
    puts("\n\n>>>>>>>>>>>>>>> Each Line Detail <<<<<<<<<<<<<<<<<");
	
	for(i = 0; i < countLines; i++){
		L = Lines[ i ];
		
		puts("----------------------------------------------------");
		printf("%10s:%20s", "all", L->all);
		
		printf("%10s:%20s--\n", "lable", L->lable);
		printf("%10s:%20s--\n", "code", L->code);
		printf("%10s:%20s--\n", "oprent", L->oprent);

        printf("\n%10s:%20x--\n", "locctr", L->locctr);
		printf("%10s:%20d--\n\n", "subscript", L->subscript);
		
		
		printf("%10s:%20s--\n", "bytes", L->bytes);
		printf("%10s:%20s--\n\n", "ascii", L->ascii);
		
		printf("%10s:%20s--\n", "eroMesg", L->eroMesg);
		
	}
	printf("countLines:%d\n", countLines);
	
	puts("\n\n>>>>>>>>>>>>>>> Each Line Detail <<<<<<<<<<<<<<<<<");
	
    puts("\n\n>>>>>>>>>>>>>>> Symble-Table <<<<<<<<<<<<<<<<<");
	for(i = 0; i < countSyms - 1 ; i++){
        printf("Symble# %d\n", i);
        printf("   Lable--%s--\n", Syms[ i ].lable);
        printf("   Loc--%x--\n\n", Syms[ i ].locctr);
    }
    puts("\n\n>>>>>>>>>>>>>>> Symble-Table <<<<<<<<<<<<<<<<<");
	
	return(countLines);
}//end of p130_built_itmfile function

