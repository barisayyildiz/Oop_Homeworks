#ifndef LIB
#define LIB

// cell status
enum cell
{
	empty = '.',
	xLower = 'x',
	oLower = 'o',
	xCapital = 'X',
	oCapital = 'O'
};


class Hex
{
private:

	
	// variables
	int size, turn, counter, gameType;
	bool gameStatus;

	int **previousMoves;
	int cap;

	// init previous moves
	int **initPreviousMoves();

	// functions that calculate best possible move based on the center of gravity
	// of the user's previous moves
	void calculateBestMove(int &xPos, int &yPos);
	void centerofGravity(int *center, int totalX, int totalY, int increment);

	// checks the end of the game
	int isEndOfTheGame();

	int** initVisited(int** visited);
	int didSomebodyWin(int** visited, int xPos, int yPos);
	int isMoveable(int** visited, int xPos, int yPos);

	// void initVisited(std::vector<std::vector<int>> visited);
	// int didSomebodyWin(std::vector<std::vector<int>> visited, int xPos, int yPos);
	// int isMoveable(std::vector<std::vector<int>> visited, int xPos, int yPos);

	// // draws the board
	void drawBoard();

	// gets the raw user input and tokenizes
	int getUserInput(std::string input, std::string &filename, int &xPos, int &yPos);

	// initilizes hex cells by the size of the board
	void initHexCells();

	// play functions play the game for single step
	// play(int, int)	-> for user
	// play()					-> for bot
	void play();
	void play(int xPos, int yPos);

	// gets the user input -> size of the board and game type
	void playGame();

	// holds the non empty cells for all objects
	static int nonEmptyCells;

	// FILE I/O

	// saves the board to the file
	void saveBoard(std::string filename);

	// loads the board from the file
	void loadBoard(std::string filename);

public:

	class Cell
	{
	private:
		cell cellStatus;
	public:
		Cell(cell s = empty);

		// getter and setter functions for cellStatus
		inline cell getCellStatus(){return cellStatus;};
		inline void setCellStatus(cell s){cellStatus = s;};
	};

	// 2d vector that contains hexCells
	Cell **hexCells;


	// constructor functions
	Hex();

	// gets the size and game type
	Hex(int s, int gT);

	// gets the size, game type and filename
	// and saves the game to the file
	Hex(int s, int gT, std::string &filename);
	void gameLoop();

	// getters and setters
	inline int getCounter(){return counter;};
	inline void setCounter(int c){counter = c;};

	inline bool getGameStatus(){return gameStatus;};
	inline void setGameStatus(bool b){gameStatus = b;};

	inline int getTurn(){return turn;};
	inline void setTurn(int t){turn = t;};

	inline int getGameType(){return gameType;};
	inline void setGameType(int g){gameType = g;};

	inline int getSize(){return size;};
	inline void setSize(int s){size = s;};

	// // compares two objects by the user cells
	// bool compare(Hex h1);

	// compares two objects by the user cells
	bool operator ==(Hex h1);

	// gets the non empty cells for all objects
	inline static int getNonEmptyCells(){return nonEmptyCells;};





	// FILE INPUT/OUTPUT

	// some helper function to get char type of an enum number
	int orderChar(char c);

	friend std::ofstream& operator << (std::ofstream& fout, Hex &h1);
	friend std::ifstream& operator >> (std::ifstream& fin, Hex &h1);
	Hex& operator -- ();
	Hex operator --(int);
	friend std::ostream& operator << (std::ostream& out, Hex &h1);




	

};

#endif
