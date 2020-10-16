#ifndef	LIB
#define	LIB

void drawGrid(char (*grid)[12], int n);

void initGrid(char (*grid)[12], int n);

int isMoveable(char (*grid)[12], int (*allmoves)[12], int xPos, int yPos, int n);

int isEndOfTheGame(char (*grid)[12], int xPos, int yPos, int n, int turn);

void calculateBestMove(char (*grid)[12], int *pos, int counter, int n);

void centerofGravity(int *center, int totalX, int totalY, int counter);

void initVisited(int (*visited)[12]);

int didSomebodyWin(char (*grid)[12], int (*visited)[12], int xPos, int yPos, int n, int turn);

#endif