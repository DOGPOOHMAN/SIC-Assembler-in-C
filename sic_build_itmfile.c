/* This function (pass1_built_itmfile()) provide a platform for
   read user's sic program and build itmfile functions, this function also integrate
   variable which used by read and build itmfile, so these variable and functions
   didn't put into main function, let the code looks nice and clean.
*/

#include "sic_build_itmfile_functions.c"

//this define purpose is that let the code looks nice and clean
#define L &lines

#define DEBUG
short pass1_built_itmfile(FILE * sicPgrm){
	//store the character of read line
	Line lines;
	
	//program infor
	char     pgrmName [20];
	unsigned startLoc =  0;
	
	
	//will change in processing
	char temp[10];
	unsigned nowLoc   =  0;


	short errorFlag   =  FALSE;
	short stopReadFlag=  FALSE;
	
	//init variable
	memset(pgrmName,   '\0', sizeof(pgrmName));
	memset(temp,       '\0', sizeof(temp));
	
	/* starting reading program content */
	while(stopReadFlag == FALSE){
		//clean char array
		pass1_init_line(L);
		
		//read a line from program
		if(fgets(lines.all, ALL_LEN, sicPgrm) == NULL){
			stopReadFlag = TRUE;
		}
		else{
			/*if it is comment line drop it,but 
			  fragment this line to three part*/
			if(pass1_isit_comment(L) == TRUE){
				continue;
			}
			else{
				puts(lines.all);
//				printf("%s--\n", lines.all);
//				pass1_divi_in3part(L);
			}
				
		}//end of if(fgets)
		
	}//end of while
	
	
//	
//	
//	//read program name
//	fscanf(sicPgrm, "%s", pgrmName);
//	
//	fscanf(sicPgrm, "%s", temp);
//	//check Pseudo Instrution is "START"
//	if( strcmp(temp, PITABLE[0]) == 0){
//		
//		//read locctr and it maxima is 0x7888
//		fscanf(sicPgrm, "%x", &nowLoc);
//		if(nowLoc > 0x7888){
//			errorFlag = TRUE;
//		}
//		
//	}else{
//		errorFlag = TRUE;
//	}
//	
//	
//	#ifdef DEBUG
//	puts(pgrmName);
//	printf("locctr %#x\n", nowLoc);
//	#endif
//	
//	//out put error information
//	if(errorFlag == TRUE){
//	
//		puts("The program had wrong starting location or another problem!");
//		system("pause");
//		exit(1);
//	}else{
//		
//		errorFlag = FALSE;
//		startLoc  = nowLoc;
//	}
//	
//	
//	
	
	return errorFlag;
}//end of pass1_built_itmfile function

