/* This function (pass1_built_itmfile()) provide a platform for
   read user's sic program and build itmfile functions, this function also integrate
   variable which used by read and build itmfile, so these variable and functions
   didn't put into main function, let the code looks nice and clean.
*/

#include "sic_build_itmfile_functions.c"

//this define purpose is that let the code looks nice and clean
#define L &lines

//#define DEBUG
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
				pass1_divi_in3part(L);
				
				if(lines.eroFlag == TRUE){
					puts(lines.eroMesg);
				}
				else{
					
					#ifdef DEBUG
					printf("lable:%s\n", lines.lable);
					printf("code:%s\n", lines.code);
					printf("oprent:%s\n", lines.oprent);
					#endif
				}
				
				
				
			}
				
		}//end of if(fgets)
		
	}//end of while
}

