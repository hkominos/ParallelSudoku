#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "functions.h"





int* SolveSerially(int* board_to_solve, int sudoku_size){
//sudoku_size =9
    CELLINFOSTRUCT** array_of_sudoku_cellstruckts_to_solve=GenerateSudokuStruct(sudoku_size, board_to_solve);
//PrintSET(array_of_sudoku_cellstruckts_to_solve);
    int* SolvedBoard=SolveBoard(array_of_sudoku_cellstruckts_to_solve,board_to_solve,sudoku_size);
//PrintSET(array_of_sudoku_cellstruckts_to_solve);
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

    while(unsolved==true && valid==true&& counter<2 ){
        propagationresult=propagete(array_of_sudoku_cellstruckts_to_solve,board_to_solve,sudoku_size);
        if (propagationresult==MADE_PROGRESS){
            counter++;
            continue;
        }
        else if (propagationresult==DID_NOT_MAKE_PROGRESS){
            counter++;
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

    //constraint1=RemoveAllValuesFromPeers(array_of_sudoku_cellstruckts_to_solve,board_to_solve,sudoku_size);
    constraint2=ForEveryCellDo(array_of_sudoku_cellstruckts_to_solve,board_to_solve,sudoku_size);
    constraint1=DID_NOT_MAKE_PROGRESS;

    if((constraint1==INVALID) || (constraint2==INVALID)){
        propagation_result= INVALID;
    }
    else if((constraint1==DID_NOT_MAKE_PROGRESS) && (constraint2==DID_NOT_MAKE_PROGRESS)){
        propagation_result= DID_NOT_MAKE_PROGRESS;
    }
    else{ propagation_result= MADE_PROGRESS; }

return propagation_result;
}








int ForEveryCellDo(CELLINFOSTRUCT** array_of_sudoku_cellstruckts_to_solve,int * board_to_solve,int sudoku_size){

    int j,grid_size=sudoku_size*sudoku_size-1;
    int removal_result=DID_NOT_MAKE_PROGRESS;
    VALUESTRUCT* value_ptr=NULL;
    int returnValue;

    for(j=0;j<=(grid_size);j++){
        if(removal_result==INVALID){break;}
        if(array_of_sudoku_cellstruckts_to_solve[j]->possible_values!=1){

            value_ptr=array_of_sudoku_cellstruckts_to_solve[j]->values_list;

            while(value_ptr!=NULL){

                if(CheckPeersForValue(value_ptr->possible_value,array_of_sudoku_cellstruckts_to_solve,j)==0){
                    returnValue=SetValueToCurrentcell(array_of_sudoku_cellstruckts_to_solve,value_ptr->possible_value,j);
                    returnValue=MADE_PROGRESS;

                    if(returnValue==INVALID){
                        removal_result=INVALID;
                        break;
                    }
                    else if(returnValue==MADE_PROGRESS){
                        removal_result=MADE_PROGRESS;
                    }
                    else{
                        if(removal_result==MADE_PROGRESS){;}
                        else{removal_result=DID_NOT_MAKE_PROGRESS;}
                    }
                }
                else{;}
                value_ptr=value_ptr->next;
            }
        }
    }
return removal_result;
}


int CheckPeersForValue(int possible_value,CELLINFOSTRUCT** array_of_sudoku_cellstruckts_to_solve,int current_cell){
    int i,position,count=0;
    int* array_of_peers=array_of_sudoku_cellstruckts_to_solve[current_cell]->Peerlist;
    int number_of_peers=array_of_sudoku_cellstruckts_to_solve[current_cell]->number_of_peers;

    for(i=0;i<number_of_peers;i++){
        position=array_of_peers[i];
        count+=checkifpeerhasvalue(possible_value,array_of_sudoku_cellstruckts_to_solve[position]->values_list);
    }




return count;
}

int checkifpeerhasvalue(int possible_value,VALUESTRUCT* head){
    int value_exists=0;
    while(head!=NULL){
        if ((head->possible_value)==possible_value){
            value_exists=1;
            break;
        }
        head=head->next;
    }

return value_exists;
}


int SetValueToCurrentcell(CELLINFOSTRUCT** array_of_sudoku_cellstruckts_to_solve,int final_value,int current_cell){

    int placement_result=DID_NOT_MAKE_PROGRESS;

    VALUESTRUCT* temp;
    VALUESTRUCT* head=array_of_sudoku_cellstruckts_to_solve[current_cell]->values_list;
    array_of_sudoku_cellstruckts_to_solve[current_cell]->possible_values=1;
    head->possible_value=final_value;
    temp=head;
    head->next=NULL;
    head=temp->next;


    while(head!=NULL){
        temp=head;
        head=head->next;
        free(temp);
    }
    placement_result=MADE_PROGRESS;

return placement_result;
}





void PrintSET(CELLINFOSTRUCT** array_of_sudoku_cellstruckts_to_solve){
    int i,count,max=20;
    VALUESTRUCT* head;
    printf("\n");

    int test;
    for(i=0;i<max;i++){
        head=array_of_sudoku_cellstruckts_to_solve[i]->values_list;
        count=CountPossibleValues(head);

        while(head!=NULL){
            test=head->possible_value;
            printf("%d ",test);
            head=head->next;
        }
      printf("\n");
      //printf("the structure thinks%d /n",count);
    }

    printf("end of set\n");

}
