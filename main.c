#include <stdlib.h>
#include <stdio.h>

#include "functions.h"


int sudoku_size=0;
int *ptr_sudoku_size=NULL,*Board=NULL;

int main(){
    ptr_sudoku_size=&sudoku_size;

    printf("\n Sudoku Solver\n");
    printf("\nwhat would you like to do\n\n");
    while(1)
    {
        switch(UserChoice()){
            case 1: {
                    Board=LoadSudoku(ptr_sudoku_size);
                    break;}
            case 2: {
                    PrintSudoku(Board,*ptr_sudoku_size);
                    break;}
            case 3: {
                    SolveSerially(Board,*ptr_sudoku_size);
                    break;}
            case 7: {exit(0);}
            default: {
                     printf("Possible error in input. Exiting");
                     exit(0);}
        }

    }
    return 0;
}

int UserChoice(void){
    int user_chosen_action;
    printf( "1)----   Load the Sudoku    ----\n"
            "2)----   Print Loaded Sudoku    ----\n"
            "3)----   Solve Serialy    ----\n"
            "4)----   Solve in Parallel    ----\n"
            "5)----   Print Solved Sudoku    ----\n"
            "6)----   Validate    ----\n"
            "7)----   Exit    ----\n");

    scanf("%d",&user_chosen_action);
    fflush(stdin);
    return user_chosen_action;
}

