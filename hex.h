#ifndef LIB
#define LIB

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
	class Cell
	{
	private:
		cell cellStatus;
	public:
		Cell(cell s = empty);
		inline cell getCellStatus(){return cellStatus;};
		inline void setCellStatus(cell s){cellStatus = s;};
	};
	std::vector < std::vector <Cell> > hexCells;
	
	// variables
	int size, turn, counter, gameType;

	bool gameStatus;

	// function prototypes
	void calculateBestMove(int &xPos, int &yPos);
	void centerofGravity(int *center, int totalX, int totalY, int increment);
	int isEndOfTheGame();
	void initVisited(std::vector<std::vector<int>> visited);
	int didSomebodyWin(std::vector<std::vector<int>> visited, int xPos, int yPos);
	int isMoveable(std::vector<std::vector<int>> visited, int xPos, int yPos);

	int getUserInput(std::string input, std::string &filename, int &xPos, int &yPos);

	static int nonEmptyCells;

	// FILE I/O
	int orderChar(char c);

public:
	Hex();
	void drawBoard();
	void fileIO();
	void play();
	void play(int xPos, int yPos);
	void playGame();
	void gameLoop();

	// getter
	inline int getCounter(){return counter;};
	bool compare(Hex h1);
	inline bool getGameStatus(){return gameStatus;};
	inline int getTurn(){return turn;};
	inline int getGameType(){return gameType;};
	inline int getSize(){return size;};

	// setter
	inline void setCounter(int c){counter = c;};
	inline void setGameStatus(bool b){gameStatus = b;};
	inline void setTurn(int t){turn = t;};
	inline void setGameType(int g){gameType = g;};
	inline void setSize(int s){size = s;};



	inline static int getNonEmptyCells(){return nonEmptyCells;};

	// FILE I/O
	void saveBoard(std::string filename);
	void loadBoard(std::string filename);

};

#endif
