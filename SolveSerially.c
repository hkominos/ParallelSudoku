#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "functions.h"


#define INVALID                 0
#define MADE_PROGRESS           1
#define DID_NOT_MAKE_PROGRESS   2


int* SolveSerially(int* board_to_solve, int sudoku_size){
//sudoku_size =9
CELLINFOSTRUCT** array_of_sudoku_cellstruckts_to_solve=GenerateSudokuStruct(sudoku_size, board_to_solve);
int* SolvedBoard=SolveBoard(array_of_sudoku_cellstruckts_to_solve,board_to_solve,sudoku_size);
return SolvedBoard;

}



CELLINFOSTRUCT** GenerateSudokuStruct(int sudoku_size, int* Board ){

    struct CELLINFO **ptrtable=NULL;
    int current_cell,grid_size=sudoku_size*sudoku_size-1;
    int i,j;

    ptrtable=(struct CELLINFO **)malloc(grid_size*sizeof(CELLINFOSTRUCT * ));    
    for (current_cell = 0 ;  current_cell<= (grid_size); current_cell++){
        ptrtable[current_cell]=malloc(sizeof(CELLINFOSTRUCT)); 
        ptrtable[current_cell]->cellid = current_cell;        
        ptrtable[current_cell]->number_of_peers = (2*sudoku_size -2 ) + (sudoku_size -(2 *((int)sqrt(sudoku_size)))+1);
        ptrtable[current_cell]->values_list = GeneratePossibleValues(sudoku_size,Board,current_cell);
        ptrtable[current_cell]->possible_values= CountPossibleValues(ptrtable[current_cell]->values_list);
        ptrtable[current_cell]->Peerlist = GeneratePeers(current_cell,ptrtable[current_cell]->number_of_peers, grid_size, sudoku_size );

        }  
    return ptrtable;
}

int* GeneratePeers(int current_cell,int number_of_peers,int grid_size,int sudoku_size){

    int *peer_table=malloc(sizeof(int)*number_of_peers);
    int i,cell2,BoxSize=sqrt(sudoku_size),j=0;    
    
    for(cell2 = 0 ; cell2<= grid_size; cell2++){ 
            if (((current_cell/sudoku_size==cell2/sudoku_size) ||   //if cells in row
                (current_cell%sudoku_size==cell2%sudoku_size) ||   //if cells in column
                (current_cell / sudoku_size / BoxSize == cell2 / sudoku_size / BoxSize && current_cell % sudoku_size / BoxSize == cell2 % sudoku_size / BoxSize)) && //if cells in box
                (current_cell != cell2)){
                    peer_table[j++]=cell2;                  
            }
    }    
return peer_table;
}

VALUESTRUCT* GeneratePossibleValues(int sudoku_size, int* Board,int current_cell){

    int i;
    struct VALUE*  head=NULL;
    struct VALUE*  newnode=NULL;   
    

    if(Board[current_cell]!=0) {
        head=malloc(sizeof(VALUESTRUCT));
        head->possible_value=Board[current_cell];        
        head->next=NULL;
    }
    else{  
        head=malloc(sizeof(VALUESTRUCT));
        head->possible_value=1;        
        head->next=NULL;
        for (i = 2 ; i <= sudoku_size; i++){            
            newnode=malloc(sizeof(VALUESTRUCT));
            newnode->possible_value=i;            
            newnode->next=head;            
            head = newnode;                            
        } 
    }          
return head;
}


int CountPossibleValues(VALUESTRUCT* head){
    int counter=0;
    do{
        counter++;
        head=head->next;
    }while(head!=NULL);
return counter;
}



int *SolveBoard(CELLINFOSTRUCT** array_of_sudoku_cellstruckts_to_solve, int* board_to_solve, int sudoku_size){
    bool unsolved=true; 
    bool valid=true;
    int* ReturnBoard=NULL;
    int propagationresult=NULL;

    while(unsolved==true && valid==true){
        propagationresult=propagete(array_of_sudoku_cellstruckts_to_solve,board_to_solve,sudoku_size);
        if (propagationresult==MADE_PROGRESS){
            continue;            
        }
        else if (propagationresult==DID_NOT_MAKE_PROGRESS){
            //Search()
            //CreateNewBoard()
            //ReturnBoard=Solveboard()
            //if(ReturnBoard==NULL){break;}
            //else{unsolved=false;}
        }        
        
        else if(propagationresult==INVALID){valid=false;}            
    }

return ReturnBoard;
}



int propagete(CELLINFOSTRUCT** array_of_sudoku_cellstruckts_to_solve,int * board_to_solve,int sudoku_size){

    int propagation_result,constraint1,constraint2;

    constraint1=RemoveAllValuesFromPeers(array_of_sudoku_cellstruckts_to_solve,board_to_solve,sudoku_size);
    //constraint2=ForEveryCellDo(array_of_sudoku_cellstruckts_to_solve,board_to_solve,sudoku_size);
    constraint2==DID_NOT_MAKE_PROGRESS;

    if((constraint1==INVALID) || (constraint2==INVALID)){
        propagation_result= INVALID;
    }
    else if((constraint1==DID_NOT_MAKE_PROGRESS) && (constraint2==DID_NOT_MAKE_PROGRESS)){
        propagation_result= DID_NOT_MAKE_PROGRESS;
    }
    else{ propagation_result= MADE_PROGRESS; }

return propagation_result;
}



int RemoveAllValuesFromPeers(CELLINFOSTRUCT** array_of_sudoku_cellstruckts_to_solve,int * board_to_solve,int sudoku_size){
    int i,j,grid_size=sudoku_size*sudoku_size-1;
    int removal_result=DID_NOT_MAKE_PROGRESS;
    int  from_peer,value_to_remove,returnValue;

    for(j=0;j<(grid_size);j++){
        if(removal_result==INVALID){break;}
        if(array_of_sudoku_cellstruckts_to_solve[j]->possible_values==1){
            for(i=0;i<array_of_sudoku_cellstruckts_to_solve[j]->number_of_peers;i++){

                from_peer=array_of_sudoku_cellstruckts_to_solve[j]->Peerlist[i];
                value_to_remove=board_to_solve[j];

                returnValue=RemoveValue(from_peer,value_to_remove,array_of_sudoku_cellstruckts_to_solve);
                if(returnValue==INVALID){
                    removal_result=INVALID;

                }
                else if(returnValue==MADE_PROGRESS){
                    removal_result=MADE_PROGRESS;

                }
                else{removal_result==DID_NOT_MAKE_PROGRESS;}

            }
        }
    }



return removal_result;
}


int RemoveValue(int from_peer,int value_to_remove,CELLINFOSTRUCT** array_of_sudoku_cellstruckts_to_solve){

    VALUESTRUCT* head=array_of_sudoku_cellstruckts_to_solve[from_peer]->values_list;
    VALUESTRUCT* copy;
    int returnValue=DID_NOT_MAKE_PROGRESS;

    while(head!=NULL){
        if(head->possible_value==value_to_remove){
            if(array_of_sudoku_cellstruckts_to_solve[from_peer]->possible_values){
               returnValue=INVALID;
               break; 
            }
            copy=head;
            head=head->next;
            (array_of_sudoku_cellstruckts_to_solve[from_peer]->possible_values)-1;
            free(copy);
            returnValue=MADE_PROGRESS;
            break;
        }
        else{head=head->next;}
    }

return returnValue;

}





int ForEveryCellDo(CELLINFOSTRUCT** array_of_sudoku_cellstruckts_to_solve,int * board_to_solve,int sudoku_size){
;
}
