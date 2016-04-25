/* This function (pass1_built_itmfile()) provide a platform for
   read user's sic program and build itmfile functions, this function also integrate
   variable which used by read and build itmfile, so these variable and functions
   didn't put into main function, let the code looks nice and clean.
*/

#include "sic_build_itmfile_functions.c"

#define LINES_LEN 100

#define DEBUG
void pass1_built_itmfile(FILE * sicPgrm){
	//store the intermediate file infor
	Line * Lines[ LINES_LEN ];
	
	//store the malloc struct of line
	Line * L;
	
	//program infor
	char     pgrmName [20];
	unsigned startLoc =  0;
	
	
	//will change in processing
	
	//store the character of read line
	char     allLine  [ ALL_LEN + 1 ];
	unsigned nowLoc   =  0;
	unsigned count    =  0;


	short errorFlag   =  FALSE;
	short stopReadFlag=  FALSE;
	
	//init array as "\0\0\0\0\0\0....."
	memset(pgrmName,  '\0', sizeof(pgrmName));
	//init array as NULL, NULL, .....
	memset(Lines,        0, sizeof(Lines));
	
	/* starting reading program content */
	while(stopReadFlag == FALSE){
		
		//init variable
		memset(allLine,'\0', sizeof(allLine));
		L = NULL;
		
		
		/* if pass checking then start init*/
		
		//read a line from program
		if(fgets(allLine, ALL_LEN, sicPgrm) == NULL){
			stopReadFlag = TRUE;
			continue;
		}
		/*if it is comment line drop it,but 
		divided this line to three part*/
		else if(pass1_isit_comment(allLine) == TRUE){
			continue;
		}
		else{
			#ifdef DEBUG
			puts(allLine);
			#endif
			
			//init struct line object
			L = pass1_init_line(allLine);
			//store this line object
			Lines[count] = L;
			count++;
			
			pass1_divi_in3part(L);
			
			#ifdef DEBUG
			if(L->eroMesg != NULL){
				puts(L->eroMesg);
			}
			else{
				printf("lable:%s\n", L->lable);
				printf("code:%s\n", L->code);
				printf("oprent:%s\n\n", L->oprent);
			}
			#endif
			
		}//end of if(fgets)
		
	}//end of while
	
	
	
	#ifdef DEBUG
	printf("count:%d\n", count);
	#endif
	
	int i = 0;
	for(; i < LINES_LEN; i++){
		L = Lines[i];
		if(L != NULL){
			
			#ifdef DEBUG
			printf("free:%d\n", i);
			#endif
			
			pass1_delete_line(L);
		}
	}
	
}//end of pass1_built_itmfile function

