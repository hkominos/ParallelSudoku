#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_


#define INVALID                 0
#define MADE_PROGRESS           1
#define DID_NOT_MAKE_PROGRESS   2




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
int* SolveSerially(int* board_to_solve, int ptr_sudoku_size);
CELLINFOSTRUCT** GenerateSudokuStruct (int sudoku_size,int* board_to_solve);
int* GeneratePeers(int current_cell,int number_of_peers,int grid_size,int sudoku_size );
VALUESTRUCT* GeneratePossibleValues (int sudoku_size, int* Board, int current_cell);
int CountPossibleValues(VALUESTRUCT* head);
int *SolveBoard(CELLINFOSTRUCT** array_of_sudoku_cellstruckts_to_solve, int* board_to_solve, int sudoku_size);
int propagete(CELLINFOSTRUCT** array_of_sudoku_cellstruckts_to_solve,int * board_to_solve,int sudoku_size);
int RemoveAllValuesFromPeers(CELLINFOSTRUCT** array_of_sudoku_cellstruckts_to_solve,int * board_to_solve,int sudoku_size);
int ForEveryCellDo(CELLINFOSTRUCT** array_of_sudoku_cellstruckts_to_solve,int * board_to_solve,int sudoku_size);
int RemoveValue(int from_peer,int value_to_remove,CELLINFOSTRUCT** array_of_sudoku_cellstruckts_to_solve);


void PrintSET(CELLINFOSTRUCT** array_of_sudoku_cellstruckts_to_solve);

#endif /* FUNCTIONS_H_ */
