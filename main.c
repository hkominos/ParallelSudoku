#include <stdlib.h>
#include <stdio.h>

#include "functions.h"
#include <pthread.h>

int sudoku_size=0;
int *ptr_sudoku_size=NULL,*Board=NULL;
int *solved_board=NULL;


int main(){
    ptr_sudoku_size=&sudoku_size;

    printf("\n Sudoku Solver\n");
    printf("\nwhat would you like to do\n\n");
    while(1)
    {
        switch(UserChoice()){
            case 1: {                  
                    Board=LoadSudoku(ptr_sudoku_size);
                    printf("Sudoku size is %d * %d\n",*ptr_sudoku_size,*ptr_sudoku_size );  

                    break;}
            case 2: {                
                    PrintSudoku(Board,*ptr_sudoku_size);
                    break;}
            case 3: {
                    solved_board=SolveSerially(Board,*ptr_sudoku_size);
                    break;}
            case 4:{
                    solved_board=SolveInParallelManual(Board,*ptr_sudoku_size);
                    break;
            }
            case 5: {
                    PrintSudoku(solved_board,*ptr_sudoku_size);
                    break;}
            case 6: {
                    Validate(solved_board,*ptr_sudoku_size);
                    break;
                    }
            case 7: {free(Board);
                    free(solved_board);
                     exit(0);
                    }
            default: {
                     free(Board);
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
            "4)----   Solve in Parallel Manually   ----\n"
            "5)----   Print Solved Sudoku    ----\n"
            "6)----   Validate    ----\n"
            "7)----   Exit    ----\n");

    scanf("%d",&user_chosen_action);
    fflush(stdin);
    return user_chosen_action;
}

