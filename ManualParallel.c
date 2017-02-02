#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <pthread.h>

#include "functions.h"
#include <string.h>

int* ReturnBoard=NULL;
int Public_thread_count;


int* SolveInParallelManual(int* board_to_solve, int sudoku_size ){
    Public_thread_count=GetThreadsFromUser();

    struct timespec start, finish;
    double elapsed;
    clock_gettime(CLOCK_MONOTONIC, &start);

    clock_t begin = clock();
    CELLINFOSTRUCT** array_of_sudoku_cellstruckts_to_solve=GenerateSudokuStruct(sudoku_size, board_to_solve);
    int** array_of_units=GenerateUnitsArray(sudoku_size);
    int is_solved_Parallel=NO;
    int* ptr_is_solved_Parallel=&is_solved_Parallel; 

    bool valid=true;
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
                *ptr_is_solved_Parallel=YES;
                clock_gettime(CLOCK_MONOTONIC, &finish);
                elapsed = (finish.tv_sec - start.tv_sec);
                clock_t end = clock();
                double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
                FreeArrayOfUnits(array_of_units,sudoku_size);   
                FreeOldBoard(array_of_sudoku_cellstruckts_to_solve,sudoku_size);
                printf("Cpu time Elapsed: %f seconds\n",time_spent );   
                printf("Wall time Elapsed: %f seconds\n",elapsed );       
                break;
            }
            else{

                cell=FindExplicitCellToBranch(array_of_sudoku_cellstruckts_to_solve, sudoku_size,Public_thread_count);
                Public_thread_count=array_of_sudoku_cellstruckts_to_solve[cell]->cardinality;

                printf("the best possible cell to branch is %d has %d values \n",cell,array_of_sudoku_cellstruckts_to_solve[cell]->cardinality);

                pthread_t* thread_handles=malloc(Public_thread_count*sizeof(pthread_t));
                long thread;

                THREADHELPERSTRUCT** Helper_Array=malloc(Public_thread_count*sizeof(THREADHELPERSTRUCT*));
                VALUESTRUCT* temp=array_of_sudoku_cellstruckts_to_solve[cell]->values_list;


                for(thread=0;thread<Public_thread_count;thread++){

                    Helper_Array[thread]=malloc(sizeof(THREADHELPERSTRUCT));
                    Helper_Array[thread]->possible_value=temp->possible_value;
                    Helper_Array[thread]->my_cell=cell;
                    Helper_Array[thread]->sudoku_size=sudoku_size;
                    Helper_Array[thread]->board_to_solve=board_to_solve;
                    Helper_Array[thread]->array_of_units=GenerateUnitsArray(sudoku_size);
                    Helper_Array[thread]->Solved_Board=NULL;              
                    Helper_Array[thread]->Array_of_structs=CreateNewBoard(array_of_sudoku_cellstruckts_to_solve,sudoku_size,temp->possible_value,cell);
                    Helper_Array[thread]->ptr_is_solved=ptr_is_solved_Parallel;
                    pthread_create(&thread_handles[thread],NULL,ThreadedSolver,(void*)Helper_Array[thread]);               

                    temp=temp->next;
                }

                for(thread=0;thread<Public_thread_count;thread++){                    
                    pthread_join(thread_handles[thread],NULL);
                    if (Helper_Array[thread]->Solved_Board!=NULL)             
                        ReturnBoard=Helper_Array[thread]->Solved_Board;                        
                   }
                  
                free(thread_handles); 

                for(thread=0;thread<Public_thread_count;thread++){
                    FreeArrayOfUnits(Helper_Array[thread]->array_of_units,sudoku_size);                    
                    FreeOldBoard(Helper_Array[thread]->Array_of_structs,sudoku_size);                    
                    free(Helper_Array[thread]);
                }

                free(Helper_Array);

            }
        }

        clock_gettime(CLOCK_MONOTONIC, &finish);
        elapsed = (finish.tv_sec - start.tv_sec);
        clock_t end = clock();
        double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
        FreeArrayOfUnits(array_of_units,sudoku_size);   
        FreeOldBoard(array_of_sudoku_cellstruckts_to_solve,sudoku_size);
        printf("Cpu time Elapsed: %f seconds\n",time_spent );   
        printf("Wall time Elapsed: %f seconds\n",elapsed );      

    
    }    
    return ReturnBoard;
}





void* ThreadedSolver(void* Helper){

    int LEVEL=-1;

    struct Thread_Data *my_helper;
    my_helper=(struct Thread_Data *) Helper;
    my_helper->Solved_Board=SolveBoard(my_helper->Array_of_structs,my_helper->board_to_solve,my_helper->sudoku_size,my_helper->array_of_units,my_helper->ptr_is_solved,LEVEL);

    return NULL;
}





int GetThreadsFromUser(void){
    int c;
        while ((c = getchar()) != '\n' && c != EOF);
    int count=-1;

    printf("Please give number of threads");

    count = getchar();
    count=count-'0';
    printf("You entered: %d\n", count);

return count;

}



int FindExplicitCellToBranch(CELLINFOSTRUCT**  array_of_sudoku_cellstruckts_to_solve, int sudoku_size, int Public_thread_count){

    int best_cardinality_found=6000;
    int cell_with_min_value;
    int i,temp, grid_size=sudoku_size*sudoku_size-1;

     for(i=0;i<=grid_size;i++){
        temp=array_of_sudoku_cellstruckts_to_solve[i]->cardinality;        
        if (temp>1){

            int difference=abs(Public_thread_count-temp);

            if(difference<best_cardinality_found){
                cell_with_min_value=i;
                best_cardinality_found=temp;
            }
            if(temp==Public_thread_count){
                cell_with_min_value=i;
                break;
            }
        }
    }

return cell_with_min_value;
}








