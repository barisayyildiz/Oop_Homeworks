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
		cell status;
	public:
		Cell(cell s = empty);
		inline cell getStatus(){return status;};
		inline void setStatus(cell s){status = s;};
	};
	std::vector < std::vector <Cell> > hexCells;
	
	int size, gameType, turn, counter;

	void calculateBestMove(int &xPos, int &yPos);
	void centerofGravity(int *center, int totalX, int totalY, int increment);
	int isEndOfTheGame();
	void initVisited(std::vector<std::vector<int>> visited);
	int didSomebodyWin(std::vector<std::vector<int>> visited, int xPos, int yPos);
	int isMoveable(std::vector<std::vector<int>> visited, int xPos, int yPos);

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

	// getter
	inline int getCounter(){return counter;};
	bool compare(Hex h1);

	inline static int getNonEmptyCells(){return nonEmptyCells;};

	// FILE I/O
	void saveBoard(std::string filename);
	void loadBoard(std::string filename);

};

#endif
