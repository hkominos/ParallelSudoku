#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_


struct Peers{
int cellid;
int numberofpeers;
int* Peerlist;

};


typedef struct Peers PEERSSTRUCT;

int UserChoice(void);
int *LoadSudoku(int *sudoku_size);
void PrintSudoku(int* Board,int sudoku_size);
int* SolveSerially(int* Board, int ptr_sudoku_size);
struct Peers **generatePeerList(int sudoku_size);
int * generatepeers(int currentcell,int numberofpeers,int gridsize,int sudoku_size );





#endif /* FUNCTIONS_H_ */