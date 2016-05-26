1.在我的程式碼，以及這份文件中
----------------------------
* Oprent		等同於 Operand
* Itmfile		等同於 intermediate file
* PI		    等同於 pseudo instruction

2.開發語言及平台
--------------
開發語言 C  
開發平台 dev-C++  

3.程式可以處理的格式
--------------------
| Type | Lable  | Opcode   | Oprent   | Detail |
| :----: | -------- | -------- | ------- | ------- |
| [1] | CLOOP | JSUB | RDREC     | lable, opcode, oprent三種都有 |
| [2] |       | LDA  | LENGTH    | opcode, oprent沒有lable |
| [3] |       | LDA  | BUFFER,X  | 可以處理X-relative |
| [4] |       | RSUB |           | 只有opcode |
| [5] |       | BYTE | C'IECS'   | BYTE可以處理字串 |
| [6] |       | BYTE | X'FF25AA' | BYTE可以處理hex 兩個字一個BYTE |
| [7] |       | WORD | 3         | WORD可以處理dec |
| [8] |       | WORD | X'FF'     | WORD可以處理hex |
| [9]  | RETADR | RESW | 1 | RESW RESB可以處理dec |
| [10] | RETADR | RESW | X'FF' | RESW RESB可以處理hex |
| [11] |        | . COMMENT |   | 可以輸入註解行 |

4.	目的
------
這一支程式不只能編譯objcode，當使用者的sic-program不能編譯時，   
程式會指出哪一行出現語法錯誤，指示使用者修改，   
使的使用者能改進自己的sic-program。

5.程式結構
---------
* A.	Assembler 共用function( sic_hex_to_dec.c   sic_find_tables.c )
    * p000_hex2dec(char * math) : unsigned
    * p010_find_opcode(char * temp) : unsigned
    * p011_find_pi(char * temp) : unsigned
    * p012_find_sym(SYMTABLE *Syms, char * temp) : unsigned

* B.	用來記錄以及產生Format3的objcode  
(屬於結構Format3底下的function) ( sic_format3.c )
  * p010_init_format3(unsigned value) : Format3 *
  * p011_delete_format3(Format3 * c) : void
  * p012_calcu_format3(Format3 * c) : void

* C.	用來記錄sic-program的每一行以及更進一步的處理
(屬於結構Line底下的function) ( sic_line.c )
	* p110_init_line(char * allLine) : Line *
	* p111_delete_line(Line * L) : void
	* p113_divi_in3part(Line * L) : void
	* p114_find_code_in_table(Line * L) : void
	* p115_process_picode(Line * L) : unsigned

* D.	用來開啟sic-program file( sic_open_sicpgrm.c )
  * p120_open_sicpgrm(void) : FILE *

* E.	建立以及產生中介資料( sic_build_itmfile.c )
  * p130_built_itmfile(FILE * sicPgrm, SYMTABLE * Syms, Line ** Lines, INFOR * infor) : void

* F.	檢查是否是註解行( sic_build_itmfile_functions.c )
  * p131_isit_comment(char * allLine) : short

* G.	產生以及輸出object-program( sic_gener_f3.c   sic_output_objpgm.c )
  * p200_gener_f3_objcode(SYMTABLE * Syms, Line ** Lines, unsigned countLines) : void
  * p210_output_objpgrm(SYMTABLE * Syms, Line ** Lines, INFOR * infor) : void

