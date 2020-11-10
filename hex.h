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
	void initVisited(cell (*visited)[]);
	int didSomebodyWin(cell (*visited)[], int xPos, int yPos);

public:
	Hex();
	void drawBoard();
	void fileIO();
	void play();
	void play(int xPos, int yPos);
	void playGame();
	void compare(Hex h1);
};

#endif


// class Hex
// {
// private:
// 	class Cell
// 	{
// 	private:
// 		cell status;
// 	public:
// 		Cell(cell s = empty);
// 		cell getStatus();
// 		void setStatus(cell s);
// 	};

// 	std::vector < std::vector <Cell> > hexCells;
	
// 	// std::vector < std::vector<Cell> > hexCells(5, vector<Cell> (5, empty));	// expected identifier before numeric constant
// 	// std::vector< std::vector< Cell > > hexCells;
// 	// Cell hexCells;
// 	// vector<vector<int>> vec(m, vector<int> (n, 0));

// public:
// 	Hex();
// 	std::vector < std::vector <Cell> >& getAdress();
// 	std::vector < std::vector <Cell> > getSingleCell(int i, int j);
// 	void drawBoard();
// };

