#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "functions.h"




int CHECKALL(CELLINFOSTRUCT** array_of_sudoku_cellstruckts_to_solve,int * board_to_solve,int sudoku_size){

    int i,grid_size=sudoku_size*sudoku_size-1;    
    int removal_result=DID_NOT_MAKE_PROGRESS;
    VALUESTRUCT* value_ptr=NULL;
    int returnValue;
    bool valid=true;

    

    for(i=0;((i<=grid_size)&&(valid==true));i++){
        if(removal_result==INVALID){break;}
        else{
            int current_cell=i;
            int* current_array=array_of_sudoku_cellstruckts_to_solve[i]->Peerlist;
            returnValue=CheckIfAllValuesExistInPeers(array_of_sudoku_cellstruckts_to_solve,current_cell,current_array,sudoku_size);
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
    }
        
return removal_result;
}




int CheckIfAllValuesExistInPeers(CELLINFOSTRUCT** array_of_sudoku_cellstruckts_to_solve,int current_cell,int current_array,int sudoku_size){

    int j,numbertofind,grid_size=sudoku_size*sudoku_size-1; 
    int dotheyexist=0;   

    for(j=0;array_of_sudoku_cellstruckts_to_solve[j]->number_of_peers;j++){
        for(numbertofind=1;numbertofind<=sudoku_size;numbertofind++){
            return_value+=PeersHaveValue(numbertofind,array_of_sudoku_cellstruckts_to_solve,current_cell);
            }

        if return_value==sudoku_size{
            dotheyexist=YES;

        }
        else{
            dotheyexist=NO;
        }

    return dotheyexist;

    }


int PeersHaveValue2(int possible_value,CELLINFOSTRUCT** array_of_sudoku_cellstruckts_to_solve,int current_cell){
    int i,position,count=0;
    int* array_of_peers=array_of_sudoku_cellstruckts_to_solve[current_cell]->Peerlist;
    int number_of_peers=array_of_sudoku_cellstruckts_to_solve[current_cell]->number_of_peers;

    for(i=0;i<number_of_peers;i++){
        position=array_of_peers[i];        
        count+=CheckIfPeerContainsValue(possible_value,array_of_sudoku_cellstruckts_to_solve[position]->values_list);
        if(count>0)break;
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