#include "sic_build_itmfile_functions.c"
#define DEBUG
short pass1_built_itmfile(FILE * sicPgrm){
	//sic program format
	short lableWide   =  8;
	short opcodeWide  =  8;
	short oprentWide  =  8;
	
	//starting reading
	char pgrmName[20];
	char temp[10];
	
	unsigned startLoc =  0;
	unsigned nowLoc   =  0;

	short errorFlag   =  FALSE;
	short stopReadFlag=  FALSE;
	
	//init variable
	strcpy(pgrmName, "");
	strcpy(temp, "");
	
	
	/* user setting program format */
	pass1_set_pgrmformat(&lableWide, &opcodeWide, &oprentWide);
//	
	/* starting reading program*/
	//read program name
	fscanf(sicPgrm, "%s", pgrmName);
	
	fscanf(sicPgrm, "%s", temp);
	//check Pseudo Instrution is "START"
	if( strcmp(temp, PITABLE[0]) == 0){
		
		//read locctr and it maxima is 0x7888
		fscanf(sicPgrm, "%x", &nowLoc);
		if(nowLoc > 0x7888){
			errorFlag = TRUE;
		}
		
	}else{
		errorFlag = TRUE;
	}
	
	
	#ifdef DEBUG
	puts(pgrmName);
	printf("locctr %#x\n", nowLoc);
	#endif
	
	//out put error information
	if(errorFlag == TRUE){
	
		puts("The program had wrong starting location or another problem!");
		system("pause");
		exit(1);
	}else{
		
		errorFlag = FALSE;
		startLoc  = nowLoc;
	}
	
	
	/* read program content */
	while(stopReadFlag == FALSE){
		stopReadFlag = TRUE;
	}//end of while
	
	return errorFlag;
}//end of pass1_built_itmfile function

