#ifndef LIB
#define LIB

namespace hex
{
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
public:

	// Cell class, that contains a cell status with the enum type 'cell'
	class Cell
	{
	private:
		cell cellStatus;
		int x,y;

	public:
		Cell(cell s = empty);

		// getters and setters
		inline cell getCellStatus(){return cellStatus;};
		inline void setCellStatus(cell s){cellStatus = s;};

		inline int getX(){return x;};
		inline int getY(){return y;};
		inline void setX(int _x){x = _x;};
		inline void setY(int _y){y = _y;};

	};

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

	// play functions play the game for single step
	// play(int, int)	-> for user
	// play()					-> for bot

	// put them in public part, to be able to return Cell type
	Cell play();
	Cell play(Cell c1);

	

	// Main game loop operations are handled in this function
	void gameLoop();

	// getter functions
	inline int getCounter() const{return counter;};

	inline bool getGameStatus() const{return gameStatus;};

	inline int getTurn() const{return turn;};

	inline int getGameType() const{return gameType;};

	inline int getSize() const{return size;};

	inline int getCap() const{return cap;};

	// compares two objects by the user cells
	bool operator ==(const Hex h1);

	// gets the non empty cells for all objects
	inline static int getNonEmptyCells(){return nonEmptyCells;};


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

	// gets the user input -> size of the board and game type
	void playGame();

	// holds the non empty cells for all objects
	static int nonEmptyCells;

	// for calculating score
	int calculateScore();
	int scoreHelper(int** visited, int xPos, int yPos, cell c);

	// marked cells for the user
	int markedCellsForTheUser()const;

	// some helper function to get char type of an enum number
	int orderChar(char c);

	// Operator Overloadings
	friend std::ofstream& operator << (std::ofstream& fout, Hex &h1);
	friend std::ifstream& operator >> (std::ifstream& fin, Hex &h1);
	Hex& operator -- ();
	Hex operator --(int);
	friend std::ostream& operator << (std::ostream& out, const Hex &h1);
	
	// 2d vector that contains hexCells
	Cell **hexCells;


};

}

#endif
