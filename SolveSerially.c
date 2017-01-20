#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "functions.h"
#include <string.h>




int* SolveSerially(int* board_to_solve, int sudoku_size){
    clock_t begin = clock();    
    CELLINFOSTRUCT** array_of_sudoku_cellstruckts_to_solve=GenerateSudokuStruct(sudoku_size, board_to_solve); 
    int** array_of_units=GenerateUnitsArray(sudoku_size);
    //PrintSET(array_of_sudoku_cellstruckts_to_solve);
    int* SolvedBoard=SolveBoard(array_of_sudoku_cellstruckts_to_solve,board_to_solve,sudoku_size,array_of_units);
    //PrintSET(array_of_sudoku_cellstruckts_to_solve);

    FreeArrayOfUnits(array_of_units,sudoku_size);
    FreeOldBoard(array_of_sudoku_cellstruckts_to_solve,sudoku_size);
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Elapsed: %f seconds\n",time_spent );
    
return SolvedBoard;
}



int *SolveBoard(CELLINFOSTRUCT** array_of_sudoku_cellstruckts_to_solve, int* board_to_solve, int sudoku_size,int** array_of_units){

    bool valid=true;
    int* ReturnBoard=NULL;
    int propagationresult=-1;
    int cell=0;
    int run_again=NO;
    int *ptr_to_run_again=&run_again;


    while(ReturnBoard==NULL && valid==true  ){
        propagationresult=propagete(array_of_sudoku_cellstruckts_to_solve,board_to_solve,sudoku_size,ptr_to_run_again,array_of_units);
        if (propagationresult==MADE_PROGRESS){
            if(run_again==YES)continue;
            else propagationresult=DID_NOT_MAKE_PROGRESS;
        }
        
        if (propagationresult==DID_NOT_MAKE_PROGRESS){
            if(IfSudokuIsSolved(array_of_sudoku_cellstruckts_to_solve,sudoku_size)){
                printf("SOLVED\n");
                ReturnBoard=PutStrucktInBoard(array_of_sudoku_cellstruckts_to_solve,sudoku_size);                
                break;
            }
            else{
                cell=FindCellToBranch(array_of_sudoku_cellstruckts_to_solve, sudoku_size);                           
                VALUESTRUCT* temp=array_of_sudoku_cellstruckts_to_solve[cell]->values_list;
                int max_tries=CountPossibleValues(temp);
                int backtrack_counter=0;
                do{
                    CELLINFOSTRUCT** new_board=CreateNewBoard(array_of_sudoku_cellstruckts_to_solve,sudoku_size,temp->possible_value,cell);
                    ReturnBoard=SolveBoard(new_board,board_to_solve,sudoku_size,array_of_units);
                    if(ReturnBoard==NULL){backtrack_counter++;}                    
                    FreeOldBoard(new_board,sudoku_size);
                    if(backtrack_counter==max_tries ){                          
                        valid=false;
                        ReturnBoard=NULL;
                        backtrack_counter++;                        
                        break; 
                    }
                    temp=temp->next;
                }while(temp!=NULL && ReturnBoard==NULL );
            }
        }
        else if(propagationresult==INVALID){
            valid=false;
            ReturnBoard=NULL;
            break;  }
    }

return ReturnBoard;
}


int propagete(CELLINFOSTRUCT** array_of_sudoku_cellstruckts_to_solve,int * board_to_solve,int sudoku_size,int* run_again,int** array_of_units){

    int propagation_result,constraint1,constraint2;
    *run_again=NO;

    constraint1=RemoveAllValuesFromPeers(array_of_sudoku_cellstruckts_to_solve,board_to_solve,sudoku_size);
    //constraint2=ForEveryCellDo(array_of_sudoku_cellstruckts_to_solve,board_to_solve,sudoku_size);
    constraint2=CHECKALL(array_of_sudoku_cellstruckts_to_solve,board_to_solve,sudoku_size,array_of_units);
    
    if((constraint1==INVALID) || (constraint2==INVALID)){
        propagation_result= INVALID;
    }
    else if((constraint1==DID_NOT_MAKE_PROGRESS) && (constraint2==DID_NOT_MAKE_PROGRESS)){
        propagation_result= DID_NOT_MAKE_PROGRESS;
    }
    else{ propagation_result= MADE_PROGRESS; }

    if (constraint2==MADE_PROGRESS) {
        *run_again=YES;}

return propagation_result;
}



void FreeOldBoard(CELLINFOSTRUCT** board_to_free,int sudoku_size){

    int current_cell,grid_size=sudoku_size*sudoku_size-1;

    for (current_cell = 0 ;  current_cell<= grid_size; current_cell++){
        VALUESTRUCT* temp= NULL;
        VALUESTRUCT* head = board_to_free[current_cell]->values_list;
        while(head!=NULL){
            temp=head;
            head=head->next;
            free(temp);
        }        
        free(board_to_free[current_cell]->Peerlist);
        free(board_to_free[current_cell]);
    }

    free(board_to_free);
}


CELLINFOSTRUCT** CreateNewBoard(CELLINFOSTRUCT** old_board,int sudoku_size,int possible_value,int celltoedit){
    struct CELLINFO **ptrtable=NULL;
    int current_cell,grid_size=sudoku_size*sudoku_size-1;
    
    ptrtable=(struct CELLINFO **)malloc((grid_size+1)*sizeof(CELLINFOSTRUCT * ));
    
    for (current_cell = 0 ;  current_cell<= (grid_size); current_cell++){
        
        ptrtable[current_cell]=malloc(sizeof(CELLINFOSTRUCT));        
        ptrtable[current_cell]->number_of_peers = old_board[current_cell]->number_of_peers;
        ptrtable[current_cell]->cardinality= old_board[current_cell]->cardinality;

        if(current_cell==celltoedit){
            ptrtable[current_cell]->cardinality=1;
            struct VALUE*  head=malloc(sizeof(VALUESTRUCT));            
            head->next=NULL;  
            head->possible_value=possible_value;          
            ptrtable[current_cell]->values_list=head;
            
        }           
        else{
            ptrtable[current_cell]->values_list = CopyValuesStruckt(old_board[current_cell]->values_list);
        }
        
        int *peer_table=malloc(sizeof(int)*ptrtable[current_cell]->number_of_peers);
        ptrtable[current_cell]->Peerlist = memcpy(peer_table, old_board[current_cell]->Peerlist, ptrtable[current_cell]->number_of_peers*sizeof(int));        

        }

    
return ptrtable;

}


VALUESTRUCT* CopyValuesStruckt(VALUESTRUCT* old_values_head){
    struct VALUE*  head=NULL;
    struct VALUE*  newnode=NULL;

    do{
        newnode=malloc(sizeof(VALUESTRUCT));
        newnode->possible_value=old_values_head->possible_value;
        newnode->next=head;
        head=newnode;
        old_values_head=old_values_head->next;
    }while(old_values_head!=NULL);

return head;
}




int FindCellToBranch(CELLINFOSTRUCT** array_of_sudoku_cellstruckts_to_solve,int sudoku_size){

    int min_branching_value=2;
    int cell_with_min_value,min_value_found=300;
    int i,temp, grid_size=sudoku_size*sudoku_size-1;


    for(i=0;i<=grid_size;i++){
        temp=array_of_sudoku_cellstruckts_to_solve[i]->cardinality;
        if (temp>1){

            if(temp<min_value_found){
                cell_with_min_value=i;
            }
            if(temp==min_branching_value){
                cell_with_min_value=i;
                break;
            }
        }
    }

return cell_with_min_value;
}

int * PutStrucktInBoard(CELLINFOSTRUCT** array_of_sudoku_cellstruckts_to_solve,int sudoku_size){

    int* final_board=(int *) malloc(sudoku_size*sudoku_size*sizeof(int));
    int i,grid_size=sudoku_size*sudoku_size-1;
   
    for(i=0;i<=grid_size;i++){
        final_board[i]=array_of_sudoku_cellstruckts_to_solve[i]->values_list->possible_value;
    }

    return final_board;
}


bool IfSudokuIsSolved(CELLINFOSTRUCT** array_of_sudoku_cellstruckts_to_solve,int sudoku_size){
    int i,count=0;
    int grid_size=sudoku_size*sudoku_size-1;

    for(i=0;i<=grid_size;i++){
        count+=array_of_sudoku_cellstruckts_to_solve[i]->cardinality;
        if(array_of_sudoku_cellstruckts_to_solve[i]->cardinality!=1){break;}
    }

    if (count==(sudoku_size*sudoku_size)){return true;}
    else {return false;}
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
      printf("the structure thinks%d ",count);
      printf("\n");
    }
   // printf("end of set\n");
}


void FreeArrayOfUnits(int ** array_of_units,int sudoku_size){
    
    int i;

    for(i=0;i<3*sudoku_size;i++){
        free(array_of_units[i]);
    }

    free(array_of_units);

}