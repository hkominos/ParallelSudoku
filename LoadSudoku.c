#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "functions.h"



int* LoadSudoku(int *ptr_sudoku_size){

    int len,i,firstreadflag=0,linenumber=0;
    int *Board;
    char ch;
    char *buffer;
    size_t bufsize = 32;

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
            printf("sudoku_size is %d\n",len);
            if (firstreadflag==0){
                Board=(int *) malloc(len*len*sizeof(int));
                firstreadflag=1;
            }
            for(i=0;i<len;i++){
                    if(isspace(buffer[i])){continue;}
                    else{
                        if(buffer[i]<58)
                        Board[linenumber*len+i]=(int)(buffer[i]-'0');
                        else{                            
                            Board[linenumber*len+i]=(int)((int)(buffer[i]-'7'));
                        }
                    }
            }
            linenumber++;
        }
    printf("File loaded succesfully \n\n ");
    }
    fclose(fp);
    free(buffer);
    
    return Board;
}

