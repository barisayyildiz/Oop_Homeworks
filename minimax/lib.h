#ifndef	LIB
#define	LIB

#define BIG_NUMBER 1000
#define SMALL_NUMBER -1000

void drawGrid(char (*grid)[12], int n);

void initGrid(char (*grid)[12], int n);

int isMoveable(char (*grid)[12], int (*allmoves)[12], int xPos, int yPos, int n);

int isEndOfTheGame(char (*grid)[12], int xPos, int yPos, int n, int turn);

int didSomebodyWin(char (*grid)[12], int (*visited)[12], int xPos, int yPos, int n, int turn);

int minimax(char (*grid)[12], int depth, int isMaximize, int alpha, int beta, int counter, int n, int *xPos, int *yPos);

void initVisited(int (*visited)[12]);

int scoreHelper(char (*grid)[12], int (*visited)[12], int xPos, int yPos, int n, int turn);

int calculateScore(char (*grid)[12], int n, int turn);

void findFirstEmptySpot(char (*grid)[12], int *xPos, int *yPos, int n);


#endif