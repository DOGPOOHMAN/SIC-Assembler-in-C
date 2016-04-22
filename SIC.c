#include "sic_sicxe_tables.c"
#include "sic_open_sicpgrm.c"


#ifndef TRUE
	#define TRUE 1
#endif

#ifndef FALSE
	#define FALSE 0 
#endif


FILE * open_file(void);//open a sic program


int main(void){
	
	//open sic program file
	static FILE * sicPgrm;
	sicPgrm = pass1_open_sicpgrm();
	
	//starting read file
	unsigned locctr   =  0;
	unsigned lineNum  =  5;
	short lableWide   =  8;
	short opcodeWide  =  8;
	short oprentWide  =  8;
	
	
	
	
	return 0;
}






