/* This function (pass1_built_itmfile()) provide a platform for
   read user's sic program and build itmfile functions, this function integrate
   variable which used by read and build itmfile, so these variable and functions
   didn't put into main function, let the code looks nice and clean in main().
*/

#define DEBUG
void pass1_built_itmfile(FILE * sicPgrm){
	SYMTABLE Syms[ SYM_LEN ];
	
	//store the intermediate file infor
	Line * Lines[ LINES_LEN ];
	
	//store the malloc struct of Line object
	Line * L;
	
	//store program infor
	char     pgrmName [10];
	unsigned startLoc =  0;
	
	
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
	
	//init array as NULL, NULL, .....
	memset(Lines,        0, sizeof(Lines));
	
	//init SYMTABLE Syms[ SYM_LEN ];
	for(i = 0; i < SYM_LEN; i++){
		memset(Syms[ i ].lable, '\0', sizeof(Syms[ i ].lable));
		Syms[ i ].locctr = 0;
	}
	

	
	
	/* starting reading program content 
	one time read only a line into program from user's SIC program file*/
	
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
		else if(pass1_isit_comment(tmpLine) == TRUE){
			continue;
		}
		else{
		
			//init(malloc) struct Line object
			L = pass1_init_line(tmpLine);
			
			//divided to three part of lable, code, oprent
			pass1_divi_in3part(L);
			
			//store this line object into Line object array
			Lines[countLines] = L;
			countLines++;
			
		}//end of if(fgets)
		
	}//end of while
	
	
	//store the program-name and starting locctr from Line-object
	strcpy(pgrmName,        Lines[0]->lable  );
	nowLoc = pass1_hex2dec( Lines[0]->oprent );
	
	
	
	/* starting write detail infor into Line-object */		
	
	
	
	unsigned tableAdr = 0;
	
	/*First line is title(COPY START 1000), it is spacial case and didn't need
    to find opcode and paseudo-instruction,so for-loop start at 1 not 0
    
	This for-loop process the infor to intermediate file from previous while loop
	*/
	for(i = 1; i < countLines; i++){
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
			tableAdr = pass1_find_opcode(L->code);
			
			//if foud code in optable, 
			if(tableAdr != 99){
				L->locctr    = nowLoc;
				L->opCode    = OPTABLE[ tableAdr ].opCode;
				L->subscript = tableAdr;
				
				//increse locctr by opcode format
				nowLoc = nowLoc + OPTABLE[ tableAdr ].format;
				
			}else if(tableAdr = pass1_find_pi(L->code) != 99){// if found in pitable
			
				
				
			}else{
				L->locctr = 0xFFFF;
				pass1_write_mesg(L, "-< opcode or picode is illegal >-");
			}
		}//end of if(L->eroMesg != NULL)
		
	}//end of for
	
	#ifdef DEBUG
	for(i = 0; i < countLines; i++){
		L = Lines[ i ];
		
		puts("----------------------------------------------------");
		printf("%10s:%20s", "all", L->all);
		
		printf("%10s:%20s--\n", "lable", L->lable);
		printf("%10s:%20s--\n", "code", L->code);
		printf("%10s:%20s--\n", "oprent", L->oprent);

		printf("\n%10s:%20d--\n\n", "subscript", L->subscript);
		
		printf("%10s:%20x--\n", "locctr", L->locctr);
		printf("%10s:%20x--\n", "opCode", L->opCode);
		printf("%10s:%20s--\n\n", "objcode", L->objcode);
		
		printf("%10s:%20s--\n", "eroMesg", L->eroMesg);
		
	}
	printf("countLines:%d\n", countLines);
	#endif
	
	
	for(i = 0; i < LINES_LEN; i++){
		L = Lines[i];
		if(L != NULL){
			
			#ifdef DEBUG
			printf("free:%d\n", i);
			#endif
			
			pass1_delete_line(L);
		}
	}
	
}//end of pass1_built_itmfile function

