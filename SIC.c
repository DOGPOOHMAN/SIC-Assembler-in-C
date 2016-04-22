#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#ifndef TRUE
	#define TRUE 1
#endif

#ifndef FALSE
	#define FALSE 0 
#endif


FILE * open_file(void);//open a sic program
void pass1_reading(void);


int main(void){
	
	//open sic program file
	static FILE * sicPgrm;
	sicPgrm = open_file();
	
	//starting read file
	unsigned locctr   =  0;
	unsigned lineNum  =  0;
	short lableWide   =  8;
	short opcodeWide  =  8;
	short oprentWide  =  8;
	
	
	
	
	return 0;
}




FILE * open_file(void){
	char fileName[20];
	FILE * fileStream = NULL;
	short openSuccess = FALSE;
	
	
	while(openSuccess == FALSE){
		printf("------------------------------------\n");
		printf("Open SIC program file (.txt):");
		scanf("%s", fileName);
		
		if(NULL == (fileStream = fopen(fileName, "r")) )
		{
			puts("Can't find your file.");
			puts("Please enter exist file name!");
			openSuccess = FALSE;
		} 
		else
		{		
			printf("Open <%s> Success!\n", fileName);
			openSuccess = TRUE;
		}
	}//end of while
	
	return fileStream;
}//end of open_file function

