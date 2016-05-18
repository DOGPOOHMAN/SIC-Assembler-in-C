
FILE * p120_open_sicpgrm(void){
	char fileName[20];
	FILE * fileStream = NULL;
	short openSuccess = FALSE;
	
	
	while(openSuccess == FALSE){
		printf("------------------------------------\n");
		printf("SIC> Open SIC program file (.txt):");
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
}//end of p120_open_file function

