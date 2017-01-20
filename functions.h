#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_


#define INVALID                 0
#define MADE_PROGRESS           1
#define DID_NOT_MAKE_PROGRESS   2

#define YES                     1
#define NO                      0

typedef struct VALUE{

    int possible_value;
    struct VALUE *next;

} VALUESTRUCT;


typedef struct CELLINFO{

    int number_of_peers;
    int cardinality;
    struct VALUE* values_list;
    int* Peerlist;

}CELLINFOSTRUCT ;


typedef enum { false, true } bool;


int UserChoice(void);
int* LoadSudoku(int *sudoku_size);
void PrintSudoku(int* Board,int sudoku_size);
int* SolveSerially(int* board_to_solve, int ptr_sudoku_size);
CELLINFOSTRUCT** GenerateSudokuStruct (int sudoku_size,int* board_to_solve);
int* GeneratePeers(int current_cell,int number_of_peers,int grid_size,int sudoku_size );
VALUESTRUCT* GeneratePossibleValues (int sudoku_size, int* Board, int current_cell);
int CountPossibleValues(VALUESTRUCT* head);
int *SolveBoard(CELLINFOSTRUCT** array_of_sudoku_cellstruckts_to_solve, int* board_to_solve, int sudoku_size,int** array_of_units);
int propagete(CELLINFOSTRUCT** array_of_sudoku_cellstruckts_to_solve,int * board_to_solve,int sudoku_size,int* run_again,int** array_of_units);
int RemoveAllValuesFromPeers(CELLINFOSTRUCT** array_of_sudoku_cellstruckts_to_solve,int * board_to_solve,int sudoku_size);
int ForEveryCellDo(CELLINFOSTRUCT** array_of_sudoku_cellstruckts_to_solve,int * board_to_solve,int sudoku_size);
int RemoveValue(int from_peer,int value_to_remove,CELLINFOSTRUCT** array_of_sudoku_cellstruckts_to_solve);
int CheckIfPeerContainsValue(int possible_value,VALUESTRUCT* head);
int PeersHaveValue(int possible_value,CELLINFOSTRUCT** array_of_sudoku_cellstruckts_to_solve,int current_cell);
int SetValueToCurrentcell();
bool IfSudokuIsSolved(CELLINFOSTRUCT** array_of_sudoku_cellstruckts_to_solve,int sudoku_size);
int * PutStrucktInBoard(CELLINFOSTRUCT** array_of_sudoku_cellstruckts_to_solve,int sudoku_size);
int FindCellToBranch(CELLINFOSTRUCT** array_of_sudoku_cellstruckts_to_solve,int sudoku_size);
CELLINFOSTRUCT** CreateNewBoard(CELLINFOSTRUCT** old_board,int sudoku_size,int possible_value,int celltoedit);
void PrintSET(CELLINFOSTRUCT** array_of_sudoku_cellstruckts_to_solve);
VALUESTRUCT* CopyValuesStruckt(VALUESTRUCT* old_values_head);
void FreeOldBoard(CELLINFOSTRUCT** board_to_free,int sudoku_size);
int** GenerateUnitsArray(int sudoku_size);
void FreeArrayOfUnits(int ** array_of_units,int sudoku_size);
int CHECKALL(CELLINFOSTRUCT** array_of_sudoku_cellstruckts_to_solve,int * board_to_solve,int sudoku_size,int** array_of_units);
void Validate(int* Board,int sudoku_size);
int PeersHaveValue2(int possible_value,CELLINFOSTRUCT** array_of_sudoku_cellstruckts_to_solve,int* array_of_peers,int sudoku_size,int* ptr_tocell);

#endif /* FUNCTIONS_H_ */
