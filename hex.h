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

	// saves the previous moves for making undo operation
	int **previousMoves;

	// capacity of the previous moves array
	int cap;

	// init previous moves
	int **initPreviousMoves();

	// functions that calculate best possible move based on the center of gravity
	// of the user's previous moves
	void calculateBestMove(int &xPos, int &yPos);
	void centerofGravity(int *center, int totalX, int totalY, int increment);

	// checks the end of the game
	int isEndOfTheGame();

	// visited array is a helper array
	int** initVisited(int** visited);

	// these two functions are used for detecting end of the game
	int didSomebodyWin(int** visited, int xPos, int yPos);
	int isMoveable(int** visited, int xPos, int yPos);

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

	// for calculating score
	int calculateScore();
	int scoreHelper(int** visited, int xPos, int yPos, cell c);

	// marked cells for the user
	int markedCellsForTheUser();

	// some helper function to get char type of an enum number
	int orderChar(char c);

	// Operator Overloadings
	friend std::ofstream& operator << (std::ofstream& fout, Hex &h1);
	friend std::ifstream& operator >> (std::ifstream& fin, Hex &h1);
	Hex& operator -- ();
	Hex operator --(int);
	friend std::ostream& operator << (std::ostream& out, Hex &h1);


public:

	// Cell class, that contains a cell status with the enum type 'cell'
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

	// conversion constructor
	explicit Hex(int s);

	// BIG 3
	// assignment operator
	Hex& operator = (const Hex& h1);

	// copy constructor
	Hex(const Hex& h1);

	// destructor
	~Hex();

	// gets the size and game type
	Hex(int s, int gT);

	// gets the size, game type and filename
	// and saves the game to the file
	Hex(int s, int gT, std::string &filename);
	

	// Main game loop operations are handled in this function
	void gameLoop();

	// getters and setters
	inline int getCounter() const{return counter;};
	inline void setCounter(int c){counter = c;};

	inline bool getGameStatus() const{return gameStatus;};
	inline void setGameStatus(bool b){gameStatus = b;};

	inline int getTurn() const{return turn;};
	inline void setTurn(int t){turn = t;};

	inline int getGameType() const{return gameType;};
	inline void setGameType(int g){gameType = g;};

	inline int getSize() const{return size;};
	inline void setSize(int s){size = s;};

	inline int getCap() const{return cap;};

	// compares two objects by the user cells
	bool operator ==(Hex h1);

	// gets the non empty cells for all objects
	inline static int getNonEmptyCells(){return nonEmptyCells;};
	

};

#endif
