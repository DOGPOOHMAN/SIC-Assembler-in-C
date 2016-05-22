#include "pgrmhead.c"

#include "sic_find_tables.c"
#include "sic_hex_to_dec.c"
#include "sic_format3.c"

#include "sic_line.c"



#include "sic_open_sicpgrm.c"

#include "sic_build_itmfile_functions.c"

#include "sic_build_itmfile.c"

#include "sic_gener_f3.c"

#include "sic_output_objpgm.c"

int main(void){
	
	int i = 0;
	unsigned countLines = 0;
	
	//store symble-table
	SYMTABLE Syms[ SYM_LEN ];
	
	//store the intermediate file infor
	Line * Lines[ LINES_LEN ];
	
	//store the program information
	INFOR infor;
	
	
	
	//init array as NULL, NULL, .....
	memset(Lines,        0, sizeof(Lines));
	
	//init SYMTABLE Syms[ SYM_LEN ];
	for(i = 0; i < SYM_LEN; i++){
		memset(Syms[ i ].lable, '\0', sizeof(Syms[ i ].lable));
		Syms[ i ].locctr = 0;
	}
	
	//init infor
	memset(infor.pgmName, '\0', sizeof(infor.pgmName));
	infor.countLines  = 0;
	infor.pgmLen      = 0;
	infor.startLoc    = 0;
	
	
	
	//open sic program file
	static FILE * sicPgrm;
//	sicPgrm = p120_open_sicpgrm();
	sicPgrm = fopen("sicpgrm.txt", "r");
	
	
	
	//build and output a intermediate file(itmfile)
	p130_built_itmfile( sicPgrm, Syms, Lines, &infor);
	
	//close the sic program file-stream
	fclose(sicPgrm);
	
	p200_gener_f3_objcode(Syms, Lines, infor.countLines);
    p210_output_objpgrm(Syms, Lines, &infor);
	
	
	//free the Line-Obj
	Line * L;
	for(i = 0; i < LINES_LEN; i++){
		L = Lines[i];
		if(L != NULL){
			p111_delete_line(L);
		}
	}
	
	system("pause");
	
	
	return 0;
}

