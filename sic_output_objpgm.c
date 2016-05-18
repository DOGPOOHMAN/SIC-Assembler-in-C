
void p210_output_objpgrm(SYMTABLE * Syms, Line ** Lines, unsigned countLines){
    
    FILE * output;
    output = fopen("objpgm.txt", "w");
    
    Line * L  = NULL;
    
    int i = 0;
    
    unsigned ctBytes  = 0x1E;
    unsigned len      = 0;
    unsigned startLoc = 0x123456;
    unsigned nowAdr   = 1;
    unsigned lastAdr  = 7;
    
    
    fprintf(output, "H%-10s%.6x%.6x\n","AA", 0x000100, 0x001000);
    
    
    
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
                
                fprintf(output, "%s", L->ascii);
            }
        }
        
    }

    
    
    fclose(output);
}//end of p210_output_objpgrm function

