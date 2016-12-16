#include <stdlib.h>
#include <stdio.h>

void PrintSudoku(int* Board,int sudoku_size){
	int linenumber=0,i,j;
    for(i=0;i<sudoku_size;i++){
        for(j=0;j<sudoku_size;j++){
    				printf("%d",Board[(linenumber*sudoku_size+j)]);    								
    	}
        linenumber++;
    	printf("\n");		
	}
}