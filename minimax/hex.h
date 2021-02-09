#ifndef	HEX
#define	HEX

#define BIG_NUMBER 1000
#define SMALL_NUMBER -1000

// draws grid
void drawGrid(char (*grid)[12], int n);

// initializes grid
void initGrid(char (*grid)[12], int n);

// used inside didSomebodyWin function
// if the neighbour cell with the position (xPos, yPos) is filled with the specific char ('x' or 'o') returns 1 else 0
int isMoveable(char (*grid)[12], int (*visited)[12], int xPos, int yPos, int n);

// generates 12x12 int array with 0 values
// calls the didSomebodyWin function
int isEndOfTheGame(char (*grid)[12], int xPos, int yPos, int n, int turn);

// uses backtracking algorithm to decide if the game is over
int didSomebodyWin(char (*grid)[12], int (*visited)[12], int xPos, int yPos, int n, int turn);

// minimax algorithm with depth of 4
// tries to get the smartes possible move for ai
// tries to maximize the score of ai
int minimax(char (*grid)[12], int depth, int isMaximize, int alpha, int beta, int counter, int n, int *xPos, int *yPos);

// when minimax function reaches the depth of 4 it calls calculateScore function
// generates 12x12 int array with 0 values
// calls scoreHelper function
int calculateScore(char (*grid)[12], int n);

// uses the backtracking algorithm
// if x's are connected horizontally it returns +10 points
// if x's are connected vertically it returns +1 points
// it basically tries to calculate biggest chain on the grid that is created with x's
int scoreHelper(char (*grid)[12], int (*visited)[12], int xPos, int yPos, int n);

// if minimax algorithm return BIG_NUMBER or SMALL_NUMBER, which means ai wins or loses the game with any possible move
// this function assigns xPos and yPos with the coordinates of the first empty cell
void findFirstEmptySpot(char (*grid)[12], int *xPos, int *yPos, int n);

void initVisited(int (*visited)[12]);


#endif