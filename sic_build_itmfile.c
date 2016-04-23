#include "sic_build_itmfile_functions.c"
#define DEBUG
short pass1_built_itmfile(FILE * sicPgrm){
	//store the character of read line
	Line lines;
	
	//sic program format
	lines.labWide   =  8;//column wide of lable
	lines.codWide   =  8;//column wide of opcode

	
	//program infor
	char     pgrmName [20];
	unsigned startLoc =  0;
	
	
	//will change in processing
	char temp[10];
	unsigned nowLoc   =  0;


	short errorFlag   =  FALSE;
	short stopReadFlag=  FALSE;
	
	//init variable
	strcpy(pgrmName, "");
	strcpy(temp, "");
	
	
	/* user setting program format */
	pass1_set_pgrmformat(&lines);

	#ifdef DEBUG
	printf("labWide %u\n", lines.labWide);
	printf("codWide %u\n", lines.codWide);
	#endif

//	/* starting reading program*/
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
//	/* read program content */
//	while(stopReadFlag == FALSE){
//		stopReadFlag = TRUE;
//	}//end of while
	
	return errorFlag;
}//end of pass1_built_itmfile function

