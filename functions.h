#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_




struct VALUE{

int possible_value;
struct VALUE *next;

};


struct CELLINFO{

    int cellid;
    int number_of_peers;
    int possible_values;
    struct VALUE* values_list;
    int* Peerlist;
};

typedef struct VALUE VALUESTRUCT;
typedef struct CELLINFO CELLINFOSTRUCT;
typedef enum { false, true } bool;



int UserChoice(void);
int* LoadSudoku(int *sudoku_size);
void PrintSudoku(int* Board,int sudoku_size);
int* SolveSerially(int* Board, int ptr_sudoku_size);
struct CELLINFO** GeneratePeerList (int sudoku_size,int* Board);
int* GeneratePeers(int current_cell,int number_of_peers,int grid_size,int sudoku_size );
struct VALUE* GeneratePossibleValues (int sudoku_size, int* Board, int current_cell);



#endif /* FUNCTIONS_H_ */
