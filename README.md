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
| [1]	| CLOOP   	| JSUB    	| RDREC  	(lable, opcode, oprent三種都有)	|
| [2] | LDA	| LENGTH	| (opcode, oprent沒有lable)	|
[3]	         LDA    BUFFER,X(可以處理X-relative)  
[4]	         RSUB			(opcode 只有opcode)  
[5]	         BYTE   C'IECS'	(BYTE可以處理字串)  
[6]	         BYTE   X'FF25AA'(BYTE可以處理hex 兩個字一個BYTE)  
[7]	         WORD  3		(WORD可以處理dec)  
[8]	         WORD  X'FF'	(WORD可以處理hex)  
[9]	RETADR   RESW  1		(RESW RESB可以處理dec)  
[10]	RETADR   RESW  X'FF'		(RESW RESB可以處理hex)  
[11]	         . COMMENT		(可以輸入註解行)  


| Type | Lable  | Opcode   | Oprent   | Detail |
| :----: | -------- | -------- | ------- | ------- |
| [1] | CLOOP | JSUB | RDREC | lable, opcode, oprent三種都有 |
| [1] | CLOOP | JSUB | RDREC | lable, opcode, oprent三種都有 |
| [1] | CLOOP | JSUB | RDREC | lable, opcode, oprent三種都有 |
| [1] | CLOOP | JSUB | RDREC | lable, opcode, oprent三種都有 |
| [1] | CLOOP | JSUB | RDREC | lable, opcode, oprent三種都有 |
| [1] | CLOOP | JSUB | RDREC | lable, opcode, oprent三種都有 |
| [1] | CLOOP | JSUB | RDREC | lable, opcode, oprent三種都有 |
| [1] | CLOOP | JSUB | RDREC | lable, opcode, oprent三種都有 |
| [1] | CLOOP | JSUB | RDREC | lable, opcode, oprent三種都有 |
| [1] | CLOOP | JSUB | RDREC | lable, opcode, oprent三種都有 |
| [1] | CLOOP | JSUB | RDREC | lable, opcode, oprent三種都有 |
| [1] | CLOOP | JSUB | RDREC | lable, opcode, oprent三種都有 |
| col 2 is      | centered      |   $12 |
| zebra stripes | are neat      |    $1 |

