#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "functions.h"


CELLINFOSTRUCT** GenerateSudokuStruct(int sudoku_size, int* Board ){

    struct CELLINFO **ptrtable=NULL;
    int current_cell,grid_size=sudoku_size*sudoku_size-1;

    ptrtable=(struct CELLINFO **)malloc((grid_size+1)*sizeof(CELLINFOSTRUCT * ));
    for (current_cell = 0 ;  current_cell<=(grid_size); current_cell++){
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
    int cell2,BoxSize=sqrt(sudoku_size),j=0;

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
    while(head!=NULL){
        counter++;
        head=head->next;
    }
return counter;
}



