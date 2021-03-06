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
        ptrtable[current_cell]->number_of_peers = (2*sudoku_size -2 ) + (sudoku_size -(2 *((int)sqrt(sudoku_size)))+1);        
        ptrtable[current_cell]->values_list = GeneratePossibleValues(sudoku_size,Board,current_cell);
        ptrtable[current_cell]->cardinality= CountPossibleValues(ptrtable[current_cell]->values_list);        
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



int** GenerateUnitsArray(int sudoku_size){

    int grid_size=sudoku_size*sudoku_size-1;
    int number_of_possible_units=sudoku_size*3;
    int ** array_of_units=(int **)malloc(number_of_possible_units*sizeof(int *));
    int i,j;

    for(i=0;i<sudoku_size;i++){
        int* row=malloc(sudoku_size*sizeof(int));
        int set=i*sudoku_size;
        for(j=0;j<sudoku_size;j++){
            row[j]=set+j;
        }
        array_of_units[i]=row;
    } 

    for(i=0;i<sudoku_size;i++){
        int* column=malloc(sudoku_size*sizeof(int));        
        for(j=0;j<sudoku_size;j++){
            column[j]=i+j*sudoku_size;            
        }        
        array_of_units[sudoku_size+i]=column;
        
    }
    
    int temp=0;
    int BoxSize=sqrt(sudoku_size);
    int current_cell=-BoxSize;    


    for(i=0;i<sudoku_size;i++){
        
        int cell2;     
        if(i%BoxSize==0&&i!=0){
            current_cell=current_cell+(BoxSize-1)*sudoku_size; //jump lines
        }
        current_cell=current_cell+BoxSize;        
                
        int* box=malloc(sudoku_size*sizeof(int));
        int j=0;
        for(cell2 = 0 ; cell2<= grid_size; cell2++){
            if  (current_cell / sudoku_size / BoxSize == cell2 / sudoku_size / BoxSize && current_cell % sudoku_size / BoxSize == cell2 % sudoku_size / BoxSize){  //if cells in box
                    box[j++]=cell2;
            }
        }

        array_of_units[2*sudoku_size+temp]=box;
        temp++;        
    }    

return array_of_units ;
}


void Validate(int* Board,int sudoku_size ){

    int i,current_block;    
    int** array_of_units=GenerateUnitsArray(sudoku_size);

    for(current_block=0;current_block<3*sudoku_size;current_block++){
        int sum=0;
        int *array_to_check=array_of_units[current_block];
        for(i=0;i<sudoku_size;i++){
            sum+=Board[array_to_check[i]];
        }
        printf("Set contains sum of %d\n",sum );
    }

    FreeArrayOfUnits(array_of_units,sudoku_size);
    printf("If every set contains the same sum of values and that is equal to arithmetic \n");
    printf("progression sum then the sudoku must be correct. \n");
    printf("Validation is also taken into consideration during constraint propagation \n\n");
}