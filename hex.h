#ifndef	HEX
#define	HEX

enum cell 
{
	empty,			// .
	xLower,			// x
	oLower,			// o
	xCapital,		// X
	oCapital,		// O
	beenThere		// if the program have visited a cell before, it does not turn back that cell in our recursive function
};

// initializes grid
void initGrid(cell (*grid)[12], int n);

// draws grid
void drawGrid(cell (*grid)[12], int n);

// makes the computer's move by the center of gravity of opponet's position
void calculateBestMove(cell (*grid)[12], int counter, int n, int &xPos, int &yPos);

// generates 12x12 int array with 0 values
// calls the didSomebodyWin function
int isEndOfTheGame(cell (*grid)[12], int n, int turn = 0);

// saves the board to the specific file
void saveBoard(cell (*grid)[12], const int&n, const int &gameType, const int &turn, const int&counter, std::string filename);

// loads the board from the specific file
void loadBoard(cell (*grid)[12], int&n, int &gameType, int &turn, int &counter, std::string filename);

// gets the user input
int getUserInput(std::string s1, std::string s2, int &xPos, int &yPos);

#endif