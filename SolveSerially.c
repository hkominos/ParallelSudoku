#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "functions.h"





int* SolveSerially(int* board_to_solve, int sudoku_size){
//sudoku_size =9
    CELLINFOSTRUCT** array_of_sudoku_cellstruckts_to_solve=GenerateSudokuStruct(sudoku_size, board_to_solve);
    PrintSET(array_of_sudoku_cellstruckts_to_solve);
    int* SolvedBoard=SolveBoard(array_of_sudoku_cellstruckts_to_solve,board_to_solve,sudoku_size);
    PrintSET(array_of_sudoku_cellstruckts_to_solve);
return SolvedBoard;
}



int *SolveBoard(CELLINFOSTRUCT** array_of_sudoku_cellstruckts_to_solve, int* board_to_solve, int sudoku_size){

    bool unsolved=true;
    bool valid=true;
    int* ReturnBoard=NULL;
    int propagationresult=NULL;

    //helper variable to be removed
    int counter=0;
    //end of helper variables

    while(unsolved==true && valid==true&& counter<10 ){
        propagationresult=propagete(array_of_sudoku_cellstruckts_to_solve,board_to_solve,sudoku_size);
        if (propagationresult==MADE_PROGRESS){
            counter++;
            printf("MADE_PROGRESS\n");
            continue;
            
        }
        else if (propagationresult==DID_NOT_MAKE_PROGRESS){
            counter++;
            printf("DID_NOT_MAKE_PROGRESS");
            //PrintSET(array_of_sudoku_cellstruckts_to_solve);
            //Search()
            //CreateNewBoard()
            //ReturnBoard=Solveboard()
            //if(ReturnBoard==NULL){break;}
            //else{unsolved=false;}
        }
        else if(propagationresult==INVALID){valid=false;printf("INVALID");counter++;}
    }

return ReturnBoard;
}



int propagete(CELLINFOSTRUCT** array_of_sudoku_cellstruckts_to_solve,int * board_to_solve,int sudoku_size){

    int propagation_result,constraint1,constraint2;

    constraint1=RemoveAllValuesFromPeers(array_of_sudoku_cellstruckts_to_solve,board_to_solve,sudoku_size);
    constraint2=ForEveryCellDo(array_of_sudoku_cellstruckts_to_solve,board_to_solve,sudoku_size);
    //constraint2=DID_NOT_MAKE_PROGRESS;

    if((constraint1==INVALID) || (constraint2==INVALID)){
        propagation_result= INVALID;
    }
    else if((constraint1==DID_NOT_MAKE_PROGRESS) && (constraint2==DID_NOT_MAKE_PROGRESS)){
        propagation_result= DID_NOT_MAKE_PROGRESS;
    }
    else{ propagation_result= MADE_PROGRESS; }

return propagation_result;
}


void PrintSET(CELLINFOSTRUCT** array_of_sudoku_cellstruckts_to_solve){
    int i,count,max=80;
    VALUESTRUCT* head;
    printf("\n");

    int test;
    for(i=0;i<=max;i++){
        head=array_of_sudoku_cellstruckts_to_solve[i]->values_list;
        count=CountPossibleValues(head);

        while(head!=NULL){
            test=head->possible_value;
            printf("%d ",test);
            head=head->next;
        }
      
      //printf("the structure thinks%d ",count);
      printf("\n");
    }

   // printf("end of set\n");

}
