#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "functions.h"



int* LoadSudoku(int *ptr_sudoku_size){
   
    int len,i,firstreadflag=0,linenumber=0;
    int *Board;
    char ch;
    char *buffer,test;
    size_t bufsize = 32;
    long number;
    buffer = (char *)malloc(bufsize * sizeof(char));
    printf("Type the name of the sudoku file ");
    while ((ch = getchar()) != '\n' && ch != EOF);  
    getline(&buffer,&bufsize,stdin);    
    
    //strip newline character
    char *pos;
    if ((pos=strchr(buffer, '\n')) != NULL)*pos = '\0';
    FILE *fp ;	
    
    if((fp=fopen(buffer,"r"))==NULL) {
        fprintf(stderr,"Error opening file %s",buffer);
        getchar();
        }
    else{
       	while (fgets(buffer,256, fp) != NULL){   				
    	    if ((pos=strchr(buffer, '\n')) != NULL)*pos = '\0';
    	    len = strlen(buffer);
            *ptr_sudoku_size=len;
            if (firstreadflag==0){
	            Board=(int *) malloc(len*len*sizeof(int));
    		    firstreadflag=1;
    		}    			
    		for(i=0;i<len;i++){
    			Board[linenumber*len+i]=(int)(buffer[i]-'0');    				
    	 	}
    	 	linenumber++;		
		}
	printf("File loaded succesfully ");			
	}
	fclose(fp);
	return Board;
}

