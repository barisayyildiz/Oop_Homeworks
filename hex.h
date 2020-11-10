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
		cell getStatus();
		void setStatus(cell s);
	};

	std::vector < std::vector <Cell> > hexCells;
	
	// std::vector < std::vector<Cell> > hexCells(5, vector<Cell> (5, empty));	// expected identifier before numeric constant
	// std::vector< std::vector< Cell > > hexCells;
	// Cell hexCells;
	// vector<vector<int>> vec(m, vector<int> (n, 0));

public:
	Hex();
	Cell getCell(int xPos, int yPos);
	Cell& getAdress(int xPos, int yPos);
	void func(int xPos, int yPos, cell);
};



#endif
