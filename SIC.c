#include "pgrmhead.c"
#include "sic_sicxe_tables.c"
#include "sic_open_sicpgrm.c"
#include "sic_build_itmfile.c"


int main(void){
	
	//open sic program file
	static FILE * sicPgrm;
	sicPgrm = pass1_open_sicpgrm();
	
	pass1_built_itmfile( sicPgrm );
	
	
	
	
	return 0;
}

