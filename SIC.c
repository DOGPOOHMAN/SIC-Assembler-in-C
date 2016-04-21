#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define TRUE   1
#define FALSE  0


FILE * open_file(void);

int main(void){
	
	FILE * sicFile;
	sicFile = open_file();
	
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

