#include "pgrmhead.c"

#include "sic_sicxe_tables.c"

#include "sic_open_sicpgrm.c"

#include "sic_build_itmfile_functions.c"
#include "sic_hex_to_dec.c"
#include "sic_build_itmfile.c"


int main(void){
	
	
	//open sic program file
	static FILE * sicPgrm;
//	sicPgrm = pass1_open_sicpgrm();
	sicPgrm = fopen("sicpgrm.txt", "r");
	
	
	
	//build and output a intermediate file(itmfile)
	pass1_built_itmfile( sicPgrm );
	
	system("pause");
	
	
	return 0;
}

