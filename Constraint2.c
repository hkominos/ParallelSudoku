#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "functions.h"


int ForEveryCellDo(CELLINFOSTRUCT** array_of_sudoku_cellstruckts_to_solve,int * board_to_solve,int sudoku_size){

    int j,grid_size=sudoku_size*sudoku_size-1;    
    int removal_result=DID_NOT_MAKE_PROGRESS;
    VALUESTRUCT* value_ptr=NULL;
    int returnValue;
    bool valid=true;

    

    for(j=0;j<=(grid_size)&&valid==true;j++){
        if(removal_result==INVALID){break;}
        if(array_of_sudoku_cellstruckts_to_solve[j]->possible_values<1){
            removal_result=INVALID;
            break;
        }
        else if(array_of_sudoku_cellstruckts_to_solve[j]->possible_values>1 && valid==true){      
            value_ptr=array_of_sudoku_cellstruckts_to_solve[j]->values_list;
            while(value_ptr!=NULL){

                if(CheckPeersForValue(value_ptr->possible_value,array_of_sudoku_cellstruckts_to_solve,j)==0){
                    returnValue=SetValueToCurrentcell(array_of_sudoku_cellstruckts_to_solve,value_ptr->possible_value,j);                   
                    if(returnValue==INVALID){
                        removal_result=INVALID;
                        valid=false;
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

    if(array_of_sudoku_cellstruckts_to_solve[current_cell]->possible_values==1){
        placement_result=INVALID;
    }
    else{
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
    }
return placement_result;
}



