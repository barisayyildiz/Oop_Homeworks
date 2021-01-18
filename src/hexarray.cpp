#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "../headers/hexbase.h"
#include "../headers/hexarray.h"
#include "../headers/exception.h"

using namespace std;
using namespace excNamespace;

namespace hex{

	HexArray1D::HexArray1D() : AbstractHex() , previousMoves(nullptr), hexCells(nullptr) 
	{
		// gets user input

		while(1)
		{
			try
			{
				playGame();
				break;
			}catch(const InvalidSize &err)
			{
				cerr << err.what() << endl << endl;
			}catch(const InvalidInput &err)
			{
				cerr << "Input should be 0  or 1" << endl;
			}
		}
		
		initHexCells();

		previousMoves = initPreviousMoves();

		// main game loop
		gameLoop();

	}	

	HexArray1D::HexArray1D(int s) : AbstractHex(), previousMoves(nullptr), hexCells(nullptr)
	{
		// ERROR HANDLING
		if(s < 6)
			throw InvalidSize();

		size = s;
		
		initHexCells();

		previousMoves = initPreviousMoves();
	}

	HexArray1D::HexArray1D(int s, int gT) : AbstractHex(), previousMoves(nullptr), hexCells(nullptr)
	{
		// error handling
		if(s < 6)
			throw InvalidSize();
		if(gT != 0 && gT != 1)
			throw InvalidInput();
		
		size = s;
		gameType = gT;


		initHexCells();

		previousMoves = initPreviousMoves();
	}

	HexArray1D::HexArray1D(int s, int gT, string &filename) : AbstractHex(), previousMoves(nullptr), hexCells(nullptr)
	{
		// error handling
		if(s < 6)
			throw InvalidSize();
		if(gT != 0 && gT != 1)
			throw InvalidInput();

		size = s;
		gameType = gT;

		initHexCells();

		previousMoves = initPreviousMoves();


		writeToFile(filename);

	}

	// assignment operator
	HexArray1D& HexArray1D::operator = (const HexArray1D& h1){

		if(previousMoves != nullptr)
		{
			for(int i=0; i<cap; i++)
			{
				delete[] previousMoves[i];
			}

			delete[] previousMoves;
		}
		previousMoves = nullptr;
		
		if(hexCells != nullptr)
		{
			free(hexCells);
		}

		size = h1.getSize();
		turn = h1.getTurn();
		counter = h1.getCounter();
		gameType = h1.getGameType();
		gameStatus = h1.getGameStatus();
		cap = h1.getCap();
		
		previousMoves = initPreviousMoves();
		initHexCells();

		for(int i=0; i<size; i++)
		{
			for(int j=0; j<size; j++)
			{
				hexCells[i * size + j] = h1.hexCells[i * size + j];
			}
		}

		for(int i=0; i<counter; i++)
		{
			previousMoves[i][0] = h1.previousMoves[i][0];
			previousMoves[i][1] = h1.previousMoves[i][1];
		}

		return *this;
	}


	// copy constructor
	HexArray1D::HexArray1D(const HexArray1D& h1){

		size = h1.getSize();
		turn = h1.getTurn();
		counter = h1.getCounter();
		gameType = h1.getGameType();
		gameStatus = h1.getGameStatus();
		cap = h1.getCap();

		previousMoves = initPreviousMoves();
		initHexCells();

		for(int i=0; i<size; i++)
		{
			for(int j=0; j<size; j++)
			{
				hexCells[i * size + j] = h1.hexCells[i * size + j];
			}
		}

		for(int i=0; i<counter; i++)
		{
			previousMoves[i][0] = h1.previousMoves[i][0];
			previousMoves[i][1] = h1.previousMoves[i][1];
		}

	}

	// destructor
	HexArray1D::~HexArray1D(){

		if(previousMoves != nullptr)
		{
			for(int i=0; i<cap; i++)
			{
				delete[] previousMoves[i];
			}
			delete[] previousMoves;
		}

		// I have used malloc and free, because we were told to use one dimensional dynamic 'C array' for the hexCells
		if(hexCells != nullptr)
			free(hexCells);

	}


	int** HexArray1D::initPreviousMoves()
	{
		int **temp = nullptr;
		temp = new int*[cap];

		for(int i=0; i<cap; i++)
			temp[i] = new int[2];

		return temp;
	}

	void HexArray1D::initHexCells()
	{
		hexCells = (AbstractHex::Cell*)malloc(sizeof(AbstractHex::Cell) * size * size);

		for(int i=0; i<size*size; i++)
		{
			hexCells[i].setCellStatus(empty);
		}

	}

	void HexArray1D::print()const
	{
		// header
		cout << "  ";
		for(int i=0; i<getSize(); i++)
		{
			cout << static_cast<char>(97 + i) << " ";
		}
		cout << "\n";

		int iter = 0;

		for(int i=0; i<getSize(); i++)
		{
			// numbers
			cout << i+1 << " ";

			// indentation
			for(int indent=0; indent<=i; indent++)
				cout << " ";

			while(iter/getSize() == i)
			{
				cout << static_cast<char>(hexCells[iter++].getCellStatus() ) << " ";
			}

			cout << "\n";
		}
	}

	bool HexArray1D::isEnd()
	{
		int **visited = nullptr;
		visited = initVisited(visited);

		if(turn == 0) // x, left to right
		{
			for(int i=0; i<size; i++)
			{
				initVisited(visited);

				if(hexCells[i*size].getCellStatus() == xLower && didSomebodyWin(visited, i, 0))
					return true;
			}
			
		}else
		{
			for(int i=0; i<size; i++)
			{
				initVisited(visited);
				if(hexCells[i+size].getCellStatus() == oLower && didSomebodyWin(visited, 0, i))
					return true;
			}
		}


		// deleting dynamic visited array
		for(int i=0; i<size; i++)
		{
			delete[] visited[i];
		}
		delete[] visited;

		return false;

	}

	int** HexArray1D::initVisited(int **visited)
	{
		if(visited != nullptr)
		{
			// deleting dynamic visited array
			for(int i=0; i<size; i++)
			{
				delete[] visited[i];
			}
			delete[] visited;
		}


		int **temp = new int*[size];
		for(int i=0; i<size; i++)
			temp[i] = new int[size];

		for(int i=0; i<size; i++)
		{
			for(int j=0; j<size; j++)
			{
				temp[i][j] = 0;
			}
		}

		return temp;

	}

	int HexArray1D::didSomebodyWin(int **visited, int xPos, int yPos)
	{
		int tempX = xPos, tempY = yPos;
		int moveRange[6][2] = {{-1,0}, {0,1}, {1,0}, {0,-1}, {-1,1}, {1,-1}};

		if(turn == 0)
		{
			// X's turn
			if(yPos == size-1)
			{
				hexCells[size * xPos + yPos].setCellStatus(xCapital);
				return 1;
			}

			visited[xPos][yPos] = 1;
			
			for(auto i=0; i<6; i++)
			{
				tempX = xPos + moveRange[i][0];
				tempY = yPos + moveRange[i][1];

				// out of border
				if(tempX < 0 || tempX >= size || tempY < 0 || tempY >= size)
				{
					continue;
				}

				if(isMoveable(visited, tempX ,tempY))
				{
					if(didSomebodyWin(visited, tempX, tempY))
					{
						// capitalize
						hexCells[size * xPos + yPos].setCellStatus(xCapital);
						return 1;
					}
				}
			}

			return 0;

		}else
		{
			// O's turn
			if(xPos == size-1)
			{
				// capitalize
				hexCells[size * xPos + yPos].setCellStatus(oCapital);
				return 1;
			}

			visited[xPos][yPos] = 1;


			for(auto i=0; i<6; i++)
			{
				tempX = xPos + moveRange[i][0];
				tempY = yPos + moveRange[i][1];

				// out of border
				if(tempX < 0 || tempX >= size || tempY < 0 || tempY >= size)
				{
					continue;
				}

				if(isMoveable(visited, tempX ,tempY))
				{
					if(didSomebodyWin(visited, tempX, tempY))
					{
						// capitalize
						hexCells[size * xPos + yPos].setCellStatus(oCapital);
						return 1;
					}
				}
			}
			return 0;
		}

	}

	int HexArray1D::isMoveable(int **visited, int xPos, int yPos)
	{
		if(turn == 0)
		{
			if(hexCells[xPos * size + yPos].getCellStatus() == xLower && visited[xPos][yPos] == 0)
				return 1;
		}else
		{
			if(hexCells[xPos * size + yPos].getCellStatus() == oLower && visited[xPos][yPos] == 0)
				return 1;
		}

		return 0;
	}


	AbstractHex::Cell HexArray1D::play(AbstractHex::Cell c1)
	{

		if(c1.getX() < 0 || c1.getX() > size || c1.getY() < 0 || c1.getY() > size)
		{
			throw IndexError();

		}else if(hexCells[c1.getX() * size + c1.getY()].getCellStatus() != empty)
		{
			throw AllocatedCell();

		}


		// user's turn
		if(counter == cap)
		{

			cap += 10;
			int **temp = nullptr;

			temp = initPreviousMoves();

			for(int i=0; i<counter; i++)
			{
				temp[i][0] = previousMoves[i][0];
				temp[i][1] = previousMoves[i][1];
				temp[i][2] = previousMoves[i][2];
			}

			// delete and resize previousMoves
			for(int i=0; i<cap-10; i++)
			{
				delete[] previousMoves[i];
			}
			delete[] previousMoves;

			previousMoves = nullptr;

			previousMoves = temp;
		}

		previousMoves[counter][0] = c1.getX();
		previousMoves[counter][1] = c1.getY();

		counter++;
		nonEmptyCells++;

		if(getTurn() == 0)
		{
			hexCells[c1.getX() * size + c1.getY()].setCellStatus(xLower);
		}
		else
		{
			hexCells[c1.getX() * size + c1.getY()].setCellStatus(oLower);
		}

		return hexCells[c1.getX() * size + c1.getY()];

	}


	// helper function for file input output
	int HexArray1D::orderChar(char c)
	{
		if(c == '.')
		{
			return 0;
		}else if(c == 'x')
		{
			return 1;
		}else if(c == 'o')
		{
			return 2;
		}else if(c == 'X')
		{
			return 3;
		}else	// 'O'
		{
			return 4;
		}

	}


	void HexArray1D::writeToFile(const string &filename)
	{
		char temp;

		ofstream fout;

		fout.open(filename);

		fout << getSize() << endl;
		fout << getCounter() << endl;
		fout << getGameType() << endl;
		fout << getTurn() << endl;

		int iter = 0;

		for(int i=0; i<getSize(); i++)
		{

			while(iter/getSize() == i)
			{
				temp = static_cast<char>(hexCells[iter++].getCellStatus() );
				fout << orderChar(temp);
			}

			fout << endl;			
		}

		// save cap
		fout << getCap() << endl;

		// save previous moves
		for(int i=0; i<getCounter(); i++)
		{
			fout << previousMoves[i][0];
			fout << previousMoves[i][1] << endl;
		}

		fout.close();

	}

	void HexArray1D::readFromFile(const string &filename)
	{
		int temp;
		int newSize, newCounter, newGameType, newTurn, newCap;

		// we need to adjust nonEmptyCells
		HexArray1D::nonEmptyCells -= getCounter();

		string line;

		ifstream fin;
		fin.open(filename);

		if(!fin)
		{
			throw FileError();
			return;
		}

		fin >> newSize;
		fin >> newCounter;
		fin >> newGameType;
		fin >> newTurn;

		// free hexCells
		free(hexCells);

		size = newSize;
		counter = newCounter;
		gameType = newGameType;
		turn = newTurn;

		initHexCells();

		for(int i=0; i<getSize(); i++)
		{
			fin >> line;
			for(int j=0; j<getSize(); j++)
			{
				temp = line[j] - '0';
				hexCells[i * size + j] = static_cast<cell>(temp);

				switch(temp)
				{
					case 0:
						hexCells[i * size + j].setCellStatus(empty);
						break;
					case 1:
						hexCells[i * size + j].setCellStatus(xLower);
						HexArray1D::nonEmptyCells++;
						break;
					case 2:
						hexCells[i * size + j].setCellStatus(oLower);
						HexArray1D::nonEmptyCells++;
						break;
					case 3:
						hexCells[i * size + j].setCellStatus(xCapital);
						HexArray1D::nonEmptyCells++;
						break;
					case 4:
						hexCells[i * size + j].setCellStatus(oCapital);
						HexArray1D::nonEmptyCells++;
						break;
				}
			}
		}

		// delete previous moves array
		for(int i=0; i<cap; i++)
		{
			delete[] previousMoves[i];
		}
		delete[] previousMoves;
		previousMoves = nullptr;

		// load cap
		fin >> newCap;
		cap = newCap;

		// load the new previousMoves
		previousMoves = initPreviousMoves();

		for(int i=0; i<getCounter(); i++)
		{
			fin >> line;
			previousMoves[i][0] = line[0] - '0';
			previousMoves[i][1] = line[1] - '0';
		}

	}

	// for AI
	AbstractHex::Cell HexArray1D::play()
	{
		if(counter == cap)
		{
			cap += 10;

			int **temp = nullptr;

			temp = initPreviousMoves();

			for(int i=0; i<counter; i++)
			{
				temp[i][0] = previousMoves[i][0];
				temp[i][1] = previousMoves[i][1];
			}

			// delete and resize previousMoves
			for(int i=0; i<cap-10; i++)
			{
				delete[] previousMoves[i];
			}
			delete[] previousMoves;

			previousMoves = nullptr;

			previousMoves = temp;
		}

		int xPos, yPos;
		calculateBestMove(xPos, yPos);

		previousMoves[counter][0] = xPos;
		previousMoves[counter][1] = yPos;

		nonEmptyCells++;
		counter++;
		hexCells[xPos * size + yPos].setCellStatus(xLower);

		return hexCells[xPos * size + yPos];

	}

	void HexArray1D::calculateBestMove(int &xPos, int &yPos)
	{
		// if the computer is making the first move
		if(counter == 0)
		{
			xPos = size/2;
			yPos = size/2;
			return;
		}
		int increment = 0;

		int totalX = 0, totalY = 0;
		int center[2];

		for(int i=0; i<size; i++)
		{
			for(int j=0; j<size; j++)
			{
				if(hexCells[i * size + j].getCellStatus() == oLower)
				{
					totalX += i;
					totalY += j;
					increment++;
				}
			}
		}

		//calculate the center of gravity
		centerofGravity(center, totalX, totalY, increment);

		center[0] = totalX / increment;
		center[1] = totalY / increment;

		// if the cell is empty, set xPos and yPos
		if(hexCells[center[0] * size + center[1]].getCellStatus() == empty)
		{
			xPos = center[0];
			yPos = center[1];
			return;
		}

		// if it is not, try to find the closest point
		int direction[4][2] = {{0,1}, {1,0}, {0,-1}, {-1,0}};
		int turn = 0;

		while(hexCells[center[0] * size + center[1]].getCellStatus() != empty)
		{
			if(center[0] + direction[turn][0] >= size || center[0] + direction[turn][0] < 0 || center[1] + direction[turn][1] >= size || center[1] + direction[turn][1] < 0)
			{
				turn++;
				turn %= 4;
				continue;
			}

			center[0] += direction[turn][0];
			center[1] += direction[turn][1];

		}

		xPos = center[0];
		yPos = center[1];

		return;
	}


	void HexArray1D::centerofGravity(int *center, int totalX, int totalY, int increment)
	{
		int x = totalX / increment;
		int y = totalY / increment;

		center[0] = x;
		center[1] = y;

		return;
	}


	void HexArray1D::reset()
	{
		
		if(previousMoves != nullptr)
		{
			for(int i=0; i<cap; i++)
			{
				delete[] previousMoves[i];
			}
			delete[] previousMoves;
		}
		previousMoves = nullptr;
		cap = 10;
		
		previousMoves = initPreviousMoves();

		if(hexCells != nullptr)
			free(hexCells);
	
		initHexCells();

		turn = 0;
		counter = 0;

	}

	void HexArray1D::setSize(int newSize)
	{
		if(newSize < 6)
		{
			throw InvalidSize();
		}

		size = newSize;

		reset();

	}


	AbstractHex::Cell HexArray1D::operator()(int x, int y)const
	{

		if(x < 0 || x >= getSize() || y < 0 || y >= getSize())
		{
			throw IndexError();
		}

		return hexCells[x * getSize() + y];

	}

	bool HexArray1D::operator==(AbstractHex *aHex)
	{
		if(getSize() != aHex->getSize())
			return false;

		for(int i=0; i<getSize(); i++)
		{
			for(int j=0; j<getSize(); j++)
			{
				if( this->operator()(i,j).getCellStatus() != aHex->operator()(i,j).getCellStatus() )
					return false;
			}
		}

		return true;
	}

	AbstractHex::Cell HexArray1D::lastMove()
	{
		// Exception handling
		if(counter == 0)
		{
			throw CounterZero();
		}

		// returns the lastMove, a Cell object	
		return hexCells[previousMoves[counter-1][0] * size + previousMoves[counter-1][1]];
	}

	int HexArray1D::numberOfMoves()const
	{
		return getCounter();
	}

	// ============================= FOR CALCULATING SCORE ========================= //

	int HexArray1D::calculateScore()
	{
		int **visited = nullptr;
		int value;
		int score = 0;

		int turn = getTurn();

		if(turn == 0)
		{
			// x
			for(int i=0; i<getSize(); i++)
			{
				for(int j=0; j<getSize(); j++)
				{
					if(hexCells[i * size + j].getCellStatus() == xLower)
					{
						visited = initVisited(visited);
						value = scoreHelper(visited, i, j, xLower);
						if(value > score)
							score = value;
					}

				}
			}

		}else
		{
			// o
			for(int i=0; i<getSize(); i++)
			{
				for(int j=0; j<getSize(); j++)
				{
					if(hexCells[i * size + j].getCellStatus() == oLower)
					{
						visited = initVisited(visited);
						value = scoreHelper(visited, i, j, oLower);
						if(value > score)
							score = value;
					}
				}
			}
		}

		return score;

	}

	int HexArray1D::scoreHelper(int** visited, int xPos, int yPos, cell c)
	{
		if(xPos >= getSize() || xPos < 0 || yPos >= getSize() || yPos < 0)
			return 0;

		int temp_x, temp_y;
		int total = 0;

		int maximum = 0;

		if(c == xLower)
		{
			// first two is +2, last two is +1
			int directionX[4][2] = {{0,1}, {-1,1}, {-1,0}, {1,0}};
			for(int i=0; i<4; i++)
			{
				total = 0;

				temp_x = xPos + directionX[i][0];
				temp_y = yPos + directionX[i][1];
				if(temp_x >= getSize() || temp_x < 0 || temp_y >= getSize() || temp_y < 0 || visited[temp_x][temp_y] == 1)
					continue;


				if(i == 0 || i == 1)
				{
					// +2 points
					if(hexCells[temp_x * size + temp_y].getCellStatus() == c)
					{
						visited[temp_x][temp_y] = 1;
						total = 2 + scoreHelper(visited, temp_x, temp_y, c);
						if(total > maximum)
							maximum = total;
					}
				}else
				{
					// +1 points
					if(hexCells[temp_x * size + temp_y].getCellStatus() == c)
					{
						visited[temp_x][temp_y] = 1;
						total = 1 + scoreHelper(visited, temp_x, temp_y, c);
						if(total > maximum)
							maximum = total;
					}
				}

			}


		}else
		{
			// first two is +2, last two is +1
			int directionO[4][2] = {{1,0}, {1,-1}, {0,-1}, {0,1}};
			for(int i=0; i<4; i++)
			{
				total = 0;

				temp_x = xPos + directionO[i][0];
				temp_y = yPos + directionO[i][1];
				if(temp_x >= getSize() || temp_x < 0 || temp_y >= getSize() || temp_y < 0 || visited[temp_x][temp_y] == 1)
					continue;


				if(i == 0 || i == 1)
				{
					// +2 points
					if(hexCells[temp_x * size + temp_y].getCellStatus() == c)
					{
						visited[temp_x][temp_y] = 1;
						total = 2 + scoreHelper(visited, temp_x, temp_y, c);
						if(total > maximum)
							maximum = total;
					}
				}else
				{
					// +1 points
					if(hexCells[temp_x * size + temp_y].getCellStatus() == c)
					{
						visited[temp_x][temp_y] = 1;
						total = 1 + scoreHelper(visited, temp_x, temp_y, c);
						if(total > maximum)
							maximum = total;
					}
				}

			}

		}


		return maximum;
	}


	void HexArray1D::undo()
	{
		// ERROR HANDLING
		if(getCounter() == 0)
		{
			throw UndoError();
		}

		counter--;
		
		// make the last move empty
		hexCells[previousMoves[counter][0] * size + previousMoves[counter][1]] = empty;

		if(turn == 0)
			turn = 1;
		else
			turn = 0;
			
	}

}
