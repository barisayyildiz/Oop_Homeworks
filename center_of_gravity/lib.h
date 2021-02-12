#ifndef	LIB
#define	LIB

// draws grid
void drawGrid(char (*grid)[12], int n);

// initializes grid
void initGrid(char (*grid)[12], int n);

// used inside didSomebodyWin function
// if the neighbour cell with the position (xPos, yPos) is filled with the specific char ('x' or 'o') returns 1 else 0
int isMoveable(char (*grid)[12], int (*allmoves)[12], int xPos, int yPos, int n);

// generates 12x12 int array with 0 values
// calls the didSomebodyWin function
int isEndOfTheGame(char (*grid)[12], int xPos, int yPos, int n, int turn);

// uses backtracking algorithm to decide if the game is over
int didSomebodyWin(char (*grid)[12], int (*visited)[12], int xPos, int yPos, int n, int turn);

// makes the computer's move by the center of gravity of opponet's position
void calculateBestMove(char (*grid)[12], int counter, int n, int *xPos, int *yPos);

// calculates center of gravity
void centerofGravity(int *center, int totalX, int totalY, int counter);

void initVisited(int (*visited)[12]);

#endif