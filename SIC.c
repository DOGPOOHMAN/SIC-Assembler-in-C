#include "sic_sicxe_tables.c"
#include "sic_open_sicpgrm.c"

#ifndef H_STRING
	#include <string.h>
#endif

#ifndef H_STDLIB
	#include <stdlib.h>
#endif

#ifndef TRUE
	#define TRUE 1
#endif

#ifndef FALSE
	#define FALSE 0 
#endif

#define DEBUG


int main(void){
	
	//open sic program file
	static FILE * sicPgrm;
	sicPgrm = pass1_open_sicpgrm();
	
	//init variable
	char pgrmName[20];
	char temp[10];
	
	unsigned locctr   =  0;
	unsigned lineNum  =  5;
	
	short lableWide   =  8;
	short opcodeWide  =  8;
	short oprentWide  =  8;
	
	short errorFlag   =  FALSE;
	
	
	//read program name
	fscanf(sicPgrm, "%s", pgrmName);
	
	
	fscanf(sicPgrm, "%s", temp);
	//check Pseudo Instrution is "START"
	if( strcmp(temp, PITABLE[0]) == 0){
		
		//read locctr and it maxima is 0x7888
		fscanf(sicPgrm, "%x", &locctr);
		if(locctr > 0x7888){
			errorFlag = TRUE;
		}
		
	}else{
		errorFlag = TRUE;
	}
	
	//out put Itmflie or error information
	if(errorFlag == TRUE){
		#ifdef DEBUG
		puts(pgrmName);
		printf("locctr %#x\n", locctr);
		#endif
		
		puts("The program had wrong locctr or name!");
		system("pause");
		exit(1);
	}else{
		
		//output Itmfile
		
		
		errorFlag = FALSE;
		lineNum += 5;
		
		
	}
	
	
	
	return 0;
}






