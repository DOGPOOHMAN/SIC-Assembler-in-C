
void p210_output_objpgrm(SYMTABLE * Syms, Line ** Lines, INFOR * infor){
    
    FILE * output;
    output = fopen("objpgm.txt", "w");
    puts("-------------------------------");
    puts("The output obj-program file name is <objpgm.txt> ");
    puts("-------------------------------");
    
    Line * L  = NULL;
    
    int i = 0;
    int counter = 0;
    
    unsigned ctBytes  = 0;
    unsigned count    = 0;
    unsigned len      = 0;
    unsigned startLoc = 0;
    unsigned nowAdr   = 1;
    unsigned lastAdr  = 0;
    short    stopFlag = FALSE;
    
    
    fprintf(output, 
            "H%-10s%.6x%.6x\n",
            infor->pgmName,
            infor->startLoc,
            infor->pgmLen);
    
    while(nowAdr < infor->countLines){
        
        ctBytes = 0;
        
        stopFlag = FALSE;
        
        
        while(stopFlag == FALSE){
            
            L = Lines[lastAdr + 1];
            count = 0;
            
            if((L != NULL) && (L->eroMesg == NULL)){
                
                if(L->format3 != NULL){
                    
                    //format3 objcode is three byte in memory
                    count = 3;
                }else if(L->bytes != NULL){
                    
                    //two hex words are one byte in memory
                    count = (strlen(L->bytes) / 2);
                }else if(L->ascii != NULL){
                    
                    //one character is one byte in memory
                    count = (strlen(L->ascii) * 2);
                }
            }//end of if(L->eroMesg == NULL)
            
            
            if((ctBytes + count > 0x1E) || (L == NULL)){
                
                stopFlag = TRUE;
            }else{
                
                ctBytes = ctBytes + count;
                
                //move to next line-obj
                lastAdr = lastAdr + 1;
            }
        }//end of while(stopFlag == FALSE)
        
        
        
        
        //printing block
        
        startLoc = Lines[nowAdr]->locctr;
        fprintf(output, "T%.6x%.2x", startLoc, ctBytes);
        for(i = nowAdr; i <= lastAdr; i++){
            
            L = Lines[i];
            if(L->eroMesg == NULL){
                
                if(L->format3 != NULL){
                    
                    fprintf(output, "%.6x", L->format3->objCode);
                }else if(L->bytes != NULL){
                    
                    fprintf(output, "%s", L->bytes);
                }else if(L->ascii != NULL){
                    
                    len = strlen(L->ascii);
                    for(counter = 0; counter < len; counter++){
                        fprintf(output, "%d", L->ascii[counter]);
                    }
                    
                }//end of if(L->format3 != NULL)
            }
            
        }//end of for-loop
        
        fprintf(output, "\n");
        nowAdr = lastAdr + 1;
        
    }//end of while(nowAdr < countLines)
    
    
    fclose(output);
}//end of p210_output_objpgrm function

