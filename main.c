#include <stdlib.h>
#include <stdio.h>

#include "functions.h"

int *Board=NULL; 


int main(){

    printf("\n Sudoku Solver\n");
 	printf("\nwhat would you like to do\n\n");
 	while(1){
 	    switch(UserChoice()){
 	    	case 1: Board=LoadSudoku();
 	    	//case 1: Board=LoadSudoku();
 	    	case 0: exit(0);
 	    	default: exit(0);

 	    }
 	    	
 	}




	return 0;


}



int UserChoice(void){
	int user_chosen_action;
    printf( "1)----   Load the Sudoku    ----\n"
            "2)----   Print Loaded Sudoku    ----\n"
            "3)----   Solve Serialy    ----\n"
            "4)----   Solve in Parallel    ----\n"
            "4)----   Print Solved Sudoku    ----\n"	    
		    "5)----   Exit    ----\n");

	scanf("%d",&user_chosen_action); 
	fflush(stdin);
	return user_chosen_action;
}

