unsigned pass1_htoi(char * math){
	
	int hex2dec(unsigned expon, int hex){
		int dec = 0;
		
		/* transform hex to dec */
		
		//0 ~ 9 ascii 48 ~ 57  transform into 0 ~ 9
		if(hex >= 48 && hex <= 57){
			dec = hex - 48;
		}
		
		//A ~ F ascii 65 ~ 70  transform into 10 ~ 15
		else if(hex >= 65 && hex <= 70){
			dec = hex - 55;
		}
		
		else{//a ~ f ascii 97 ~ 102  transform into 10 ~ 15
			dec = hex - 87;
		}
	
		/* dec Multiply 16^expon */
		int i;
		int base = 1;
		
		for(i = expon; i > 0; i--){
			base = base * 16;
		}
		
		return (unsigned)dec * base;
		
	}//end of hex2dec sub function
	
	
	int hex;
	
	//init for loop
	unsigned sum   = 0;
	unsigned expon = 0;
	int      len   = strlen(math);
	int      adr   = len - 1;
	
	for(; adr >= 0; adr--, expon++ ){
		hex = (int)math[adr];
		
		//0x32 = (2 * 16^0) + (3 * 16^1)
		sum = sum + hex2dec(expon, hex);
	}
	
	return sum;
	
}//end of pass1_htoi function

