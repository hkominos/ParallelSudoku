#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "functions.h"




int CHECKALL(CELLINFOSTRUCT** array_of_sudoku_cellstruckts_to_solve,int * board_to_solve,int sudoku_size,int** array_of_units){

    int current_block;    
    int removal_result=DID_NOT_MAKE_PROGRESS;
    
    int returnValue,value_to_check_for,singlurar_cell=-1;
   

    int MAX_POSSIBLE_VALUE=sudoku_size;

    for(current_block=0;current_block<3*sudoku_size;current_block++){
        for(value_to_check_for=1;value_to_check_for<=MAX_POSSIBLE_VALUE;value_to_check_for++){
            int *array_of_peers=array_of_units[current_block];
            int *ptr_tocell=&singlurar_cell;
            int count=PeersHaveValue2(value_to_check_for,array_of_sudoku_cellstruckts_to_solve,array_of_peers,sudoku_size,ptr_tocell);
            if(count==0){
                removal_result=INVALID;                
                break;
            }
            else if(count==1 && array_of_sudoku_cellstruckts_to_solve[singlurar_cell]->cardinality!=1){
               // printf("I want to change %s\n", );
                returnValue=SetValueToCurrentcell(array_of_sudoku_cellstruckts_to_solve,value_to_check_for,singlurar_cell);
                if(returnValue==INVALID){
                        removal_result=INVALID;                        
                        break;
                    }
                else if(returnValue==MADE_PROGRESS){
                        removal_result=MADE_PROGRESS;
                        break; 
                }
                else{
                        if(removal_result==MADE_PROGRESS){;}
                        else{removal_result=DID_NOT_MAKE_PROGRESS;}
                    }

            }
            else{;}
        }
    }
       
        
return removal_result;
}








int PeersHaveValue2(int possible_value,CELLINFOSTRUCT** array_of_sudoku_cellstruckts_to_solve,int* array_of_peers,int sudoku_size,int* ptr_tocell){
    int i,temp,position,count=0;
    int number_of_peers=sudoku_size;

    for(i=0;i<number_of_peers;i++){
        position=array_of_peers[i];   
        temp=CheckIfPeerContainsValue(possible_value,array_of_sudoku_cellstruckts_to_solve[position]->values_list);
        if (temp==1){
            *ptr_tocell=position;
        }     
        count+=temp;
        if(count>2)break;
    }    
    
return count;
}

int CheckIfPeerContainsValue2(int possible_value,VALUESTRUCT* head){
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