#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "functions.h"



int RemoveAllValuesFromPeers(CELLINFOSTRUCT** array_of_sudoku_cellstruckts_to_solve,int * board_to_solve,int sudoku_size){

    int i,j,grid_size=sudoku_size*sudoku_size-1;
    int removal_result=DID_NOT_MAKE_PROGRESS;
    int  from_peer,value_to_remove,returnValue;


    for(j=0;j<=(grid_size);j++){        
        if(removal_result==INVALID){break;}
        if(array_of_sudoku_cellstruckts_to_solve[j]->cardinality==0){
            removal_result=INVALID;
            break;
        }
        if(array_of_sudoku_cellstruckts_to_solve[j]->cardinality==1){

            for(i=0;i<array_of_sudoku_cellstruckts_to_solve[j]->number_of_peers;i++){
                from_peer=array_of_sudoku_cellstruckts_to_solve[j]->Peerlist[i];

                if(board_to_solve[j]!=0){value_to_remove=board_to_solve[j];}
                else{value_to_remove=array_of_sudoku_cellstruckts_to_solve[j]->values_list->possible_value;}


                returnValue=RemoveValue(from_peer,value_to_remove,array_of_sudoku_cellstruckts_to_solve);
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

    }


return removal_result;
}


int RemoveValue(int from_peer,int value_to_remove,CELLINFOSTRUCT** array_of_sudoku_cellstruckts_to_solve){

    VALUESTRUCT* head=array_of_sudoku_cellstruckts_to_solve[from_peer]->values_list;
    VALUESTRUCT* previous=NULL;
    int returnValue=DID_NOT_MAKE_PROGRESS;

    do{
        if(head->possible_value==value_to_remove){
            if(array_of_sudoku_cellstruckts_to_solve[from_peer]->cardinality==1){
               returnValue=INVALID;               
               break;
            }
            else{
                if(head==array_of_sudoku_cellstruckts_to_solve[from_peer]->values_list){
                    VALUESTRUCT* temp=head;
                    array_of_sudoku_cellstruckts_to_solve[from_peer]->values_list=(head->next);
                    free(temp);
                }else{
                    previous->next=head->next;
                    free(head);
                    head=previous->next;
                }

                (array_of_sudoku_cellstruckts_to_solve[from_peer]->cardinality)--;
                returnValue=MADE_PROGRESS;
                break;
            }
        }
        else{   previous=head;
                head=head->next;}
    }while(head!=NULL);


return returnValue;
}


