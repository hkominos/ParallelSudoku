#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "functions.h"

int* SolveSerially(int* Board, int sudoku_size){
//sudoku_size =9
struct Peers** array=generatePeerList(sudoku_size, Board);//arrayofpeers[ptr_sudoku_size*ptr_sudoku_size];



return NULL;

}




struct Peers ** generatePeerList(int sudoku_size, int* Board ){

    struct Peers **ptrtable=NULL;
    int currentcell,gridsize=sudoku_size*sudoku_size-1;
    int i;
    ptrtable=(struct Peers **)malloc(gridsize*sizeof(PEERSSTRUCT * ));

    for (currentcell = 0 ;  currentcell<= (gridsize); currentcell++){
        ptrtable[currentcell]=malloc(sizeof(PEERSSTRUCT)); 
        ptrtable[currentcell]->cellid= currentcell; 
        ptrtable[currentcell]->numberofpeers = (2*sudoku_size -2 ) + (sudoku_size -(2 *((int)sqrt(sudoku_size)))+1);
        ptrtable[currentcell]->possiblevalues = generatepossiblevalues(sudoku_size,Board,currentcell);
        ptrtable[currentcell]->Peerlist = generatepeers(currentcell,ptrtable[currentcell]->numberofpeers, gridsize, sudoku_size );
        }   

    return ptrtable;
}

int* generatepeers(int currentcell,int numberofpeers,int gridsize,int sudoku_size){

    int *peertable=malloc(sizeof(int)*numberofpeers);
    int i,cell2,BoxSize=sqrt(sudoku_size),j=0;    
    
    for(cell2 = 0 ; cell2<= gridsize; cell2++){ 
            if (((currentcell/sudoku_size==cell2/sudoku_size) ||   //if cells in row
                (currentcell%sudoku_size==cell2%sudoku_size) ||   //if cells in column
                (currentcell / sudoku_size / BoxSize == cell2 / sudoku_size / BoxSize && currentcell % sudoku_size / BoxSize == cell2 % sudoku_size / BoxSize)) && //if cells in box
                (currentcell != cell2)){
                    peertable[j++]=cell2;                  
                }
        }    
return peertable;
}

int* generatepossiblevalues(int sudoku_size, int* Board,int currentcell){

    int i;
    int *possiblevalues=malloc(sizeof(int)*sudoku_size);
    
    for (i = 0 ; i < sudoku_size; i++){
        if(Board[currentcell]==0) possiblevalues[i]=i+1;
        else {
                possiblevalues[i]=-1;
                possiblevalues[Board[currentcell]-1]=Board[currentcell];
            }                
        }
return possiblevalues;
}


