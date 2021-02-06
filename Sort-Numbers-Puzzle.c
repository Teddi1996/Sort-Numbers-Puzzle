/* Simple PuzzleBox */ 

/* Author: Theódór S. Andrésson 
 * Email: TheodorSiAn@gmail.com
 */

#include <stdio.h> 
#include <stdlib.h>
#include <time.h> 

/* Name: Random(int max)
 * Takes: int max 
 * Gives: Random value from 0 to max
 * Desc: Randomization 
 * Note: Probably not the best method
 */ 

int Random(int max) 
{
	return rand() % max; 
}


/* Name: CheckBoard(int Board)
 * Takes: A 2D array, int n  
 * Gives: Value 1 or 0 
 * Desc: True if the board is sorted. False otherwise. 
 */

int CheckBoard(int **Board, int n)
{
	int count = 0; // Count how many rows are sorted

	for(int i = 0; i < n+2; i++)
	{ // Loop through all rows 
		if( Board[i][0] == Board[i][1] && Board[i][1] == Board[i][2] && Board[i][2] == Board[i][3] )
		{
			count++; // Row completed
		}
	}

	if( count == n+2 ) 
	{ 
		return 1;
	}

	return 0;
}
/* Name: GetAllNumbers(int n) 
 * Takes: int n (How many numbers)
 * Gives: int* (n numbers 4 times each)
 * Desc: A list with range [1..n] with each number 4 times   
 */ 

int* GetAllNumbers(int n) 
{
	int nf = n*4;
        int* numbers = (int*) malloc(nf*sizeof(int)); // All possible numbers
        int num = 1; // Number to fill in

        for( int i = 0; i < nf; i++)
        { // Fill in all needed numbers
                int count = 0;
                while( count < 4 )
                { // Every number 4 times
                        numbers[i] = num;
                        i++;
                        count++;
                }

                num++; // Increase number
                i--; // This just looks ugly.... 
        }

	return numbers; 
}

/* Name: CreateBoard(int n) 
 * Takes: int n (How many numbers) 
 * Gives: int** (2D array of the board with 2 empty sets)
 * Desc: Creates the board used to play with
 */

int** CreateBoard(int n) 
{
	// Create a 2D array as the game board with 2 extra rows
	int **Board = malloc( (n+2) * sizeof(int)); // Rows
	
	for ( int i = 0; i < (n+2); i++) 
	{ // Columns
		Board[i] = malloc(4 * sizeof(int));
	}

	int* numbers = GetAllNumbers(n); 
	int range = n*4;

	for(int i = 0; i < n; i++) 
	{
		for( int j = 0; j < 4; j++) 
		{
			int p = Random(range); // Randomize number 
			while ( numbers[p] == 0 )
				p = Random(range); 

			Board[i][j] = numbers[p];
			numbers[p] = 0; // So it isn't repeated 
		}
	}

	// Free memory 
	free(numbers); 

	// Return 2D array of the board 
	return Board; 

}

/* Name: void Move(int** Board, int x, int y, int Bx, int By)
 * Needs: pointer to 2D Board, placement on board, placement on board, 
 * 	  placement to move to, placement to move to 
 * Desc: Responsible to move from one place on 
 * 	 the board to another place.
 * Note: Should remove By as we don't need the column.
 * 	 Number should always go on top
 */

void Move(int** Board, int x, int Bx)
{
	// Do nothing if moving to the same row.
	// Why does it move up ?? 
	if(x == Bx) return; 

	int y = 3; // Placement of moving number
	
	// Lets figure out what number we're moving
	while(y != 0) 
	{
		if(Board[x][y] != 0) break; 
		y--;
	}

	if(Board[Bx][3] != 0) 
	{ // Full
		return;
	}

	if(Board[Bx][2] != 0 && Board[x][y] == Board[Bx][2])
	{ // Possible to move (E.g move 1 to the row 2310 -> 2311)
		Board[Bx][3] = Board[x][y];
		Board[x][y] = 0;
		return;
	}

	if(Board[Bx][1] != 0 && Board[x][y] == Board[Bx][1])
	{ //Possible to move (E.g move 1 to the row 2100 -> 2110) 
		Board[Bx][2] = Board[x][y];
		Board[x][y] = 0;
		return;
	}

	if(Board[Bx][0] != 0 && Board[x][y] == Board[Bx][0])
	{ // Possible to move (E.g move 1 to the row 1000 -> 1100)
		Board[Bx][1] = Board[x][y];
		Board[x][y] = 0;
		return;
	}

	if(Board[Bx][0] == 0) 
	{ // Possible to move 1 to 0000 -> 1000
		Board[Bx][0] = Board[x][y];
		Board[x][y] = 0; 
		return;
	}

	return;
	
}

/* Name: DisplayBoard(int **Board)
 * Needs: A 2D board
 * Returns: Board printed out to stdout 
 */ 

void DisplayBoard(int **Board, int n)
{
        // Print out the board
        for (int i = 0; i < n+2; i++)
        {
        	printf("%d: ", i);
		for( int j = 0; j < 4; j++)
                {
			if(Board[i][j] == 0)
			{ // Lets leave 0's out
				printf("  ");
			} else {
                		printf("%d ", Board[i][j]);
			}
                }
		printf("\n");
	}

}

 /* Name: Main() 
 * Needs: Argument from command line 
 * Desc: Main start of the application 
 */ 
int main(int argc, char* argv[]) {
	srand(time(0)); // A seed for randomization 	
	
	if(argc == 1) 
	{ // The game requires one argument
		printf("The game requires at least one argument passed to it");
		exit(0);
	}

	int n = atoi(argv[1]); // Convert the argument from char to int

	// Disallow 1 or 2 
	if( n == 1 || n == 2 ) 
	{
		printf("Minimum amount of numbers is 3\n");
		exit(0);
	}

	// Create a board
	int** A = CreateBoard(n); 

	while(1)
	{
		DisplayBoard(A, n); 

		int x, Bx; 

		printf("\n(Element to move)X value: "); 
		scanf("%d", &x); 
		
		printf("\n(Placement)Bx value: ");
		scanf("%d", &Bx);

		// Make the move
		Move(A, x, Bx);
	
		// Clear output
		printf("\e[1;1H\e[2J");

		// Check if the board is sorted 
		if(CheckBoard(A, n) == 1)
		{
			printf("\t\t-----> You won the game <----  ");
			break;
		}
	}
	
	// Free Memory used by board
	for( int i = 0; i < n+2; i++ ) 
	{
		free(A[i]);
	}

	free(A);
}

/***************
 * Error list: *
 ***************/

/** Program crashes on input 1 & 2 **
 *
 * Input 1: Program finishes first empty row but returns a seg fault before the second 
 * Input 2: Program does not finish printing out 0's in board. (extra rows) 
 */

