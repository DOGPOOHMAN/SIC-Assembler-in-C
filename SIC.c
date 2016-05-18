#include "pgrmhead.c"

#include "sic_find_tables.c"
#include "sic_hex_to_dec.c"
#include "sic_format3.c"

#include "sic_line.c"



#include "sic_open_sicpgrm.c"

#include "sic_build_itmfile_functions.c"

#include "sic_build_itmfile.c"


int main(void){
	
	int i = 0;
	
	//sotre symble-table
	SYMTABLE Syms[ SYM_LEN ];
	
	//store the intermediate file infor
	Line * Lines[ LINES_LEN ];
	
	
	//init array as NULL, NULL, .....
	memset(Lines,        0, sizeof(Lines));
	
	//init SYMTABLE Syms[ SYM_LEN ];
	for(i = 0; i < SYM_LEN; i++){
		memset(Syms[ i ].lable, '\0', sizeof(Syms[ i ].lable));
		Syms[ i ].locctr = 0;
	}
	
	
	
	//open sic program file
	static FILE * sicPgrm;
//	sicPgrm = p120_open_sicpgrm();
	sicPgrm = fopen("sicpgrm.txt", "r");
	
	
	
	//build and output a intermediate file(itmfile)
	p130_built_itmfile( sicPgrm, Syms, Lines);
	
		
	
//	//unic testing of pass1_process_picode()
//	Line * L;
//	unsigned tableAdr = 0;
//	
//	
//	L = pass1_init_line("OUTPUT	BYTE	X'05'\n");
//	pass1_divi_in3part(L);
//	pass1_find_code_in_table(L);
//	shiftLoc = pass1_process_picode(L, nowLoc, L->subscript);
	
	system("pause");
	
	
	return 0;
}

