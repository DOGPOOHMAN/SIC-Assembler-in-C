#include <stdio.h>

#define TRUE   1
#define FALSE  0


typedef struct code {
	/*8 bit 0000 0000
	               ni*/
	unsigned opCode     : 8;
	
	/*16 bit 0000 0000 0000 0000
	    	 x                */
	unsigned disp       : 16;
	
	/*16 bit 1000 0000 0000 0000
	    	 x                */
	unsigned xMask      : 16;
	
	unsigned format3    : 24;
	
	short xFlag;
	unsigned lineNum;

} Code;

void pass2_init_code(Code * c){
	c->xMask = 0x8000;
	c->xFlag = FALSE;
}//end pass2_init_code function

void pass2_calcu_code(Code * c){
	
	//use x-relative addressing
	if(c->xFlag == TRUE){
		
		//insert x-bit into disp
		c->disp = c->disp | c->xMask;
	}
	
	/*generate object code*/
	
	/*opCode = STCH = 0x54
	c->format3 0000 0000  0000 0000  0101 0100
	
	left shift 16-bits
	c->format3 0101 0100 0000 0000  0000 0000  
	
	write disp into object code(OR as disp)
	c->format3 0101 0100 0000 0000  0000 0000  
	disp                 XXXX XXXX  XXXX XXXX
	
	*/
	c->format3   =   c->opCode;
	c->format3   <<= 16;
	c->format3   =   c->format3 | c->disp;
	
}//end pass2_calcu_code



int main(void){
	Code line_0;
	pass2_init_code(&line_0);


	/*°²³] STCH	BUFFER,X 
	   BUFFER 1039*/
	line_0.opCode   = 0x54;
	line_0.disp     = 0x1039;
	line_0.xFlag    = TRUE;
	
	pass2_calcu_code(&line_0);
	
	printf( "STCH = 0x54 , BUFFER 1039\n"
			"STCH	BUFFER,X = %x\n",
			line_0.format3);
			
			
	return 0;
}


//
//void displayBits(unsigned value){
//	unsigned counter;
//	
//	unsigned mask = 1 << 31;
//	
//	printf("%10u = ", value);
//}

//struct bit {
//	/*8 bit 0000 0000
//	               ni*/
//	unsigned opCode      : 8;
//	unsigned ni       
//	unsigned xbpe
//	
//	
//	/*16 bit 0000 0000 0000 0000
//	    	 x                */
//	unsigned disp       : 12;
//	
//	union Format {
//		unsigned one    : 8;
//		unsigned two    : 16;
//		unsigned three  : 24;
//		unsigned four   : 32;
//	} format;
//	short x;
//};


