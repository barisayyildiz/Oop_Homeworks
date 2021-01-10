#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "hex.h"

using namespace std;

namespace myNamespace{

	AbstractHex::Cell::Cell(cell c) : cellStatus(c)
	{/*left empty*/}

	int AbstractHex::nonEmptyCells = 0;

	HexArray1D::HexArray1D() : size(0), turn(0), counter(0), gameStatus(true), previousMoves(nullptr), cap(10), hexCells(nullptr)
	{
		// gets user input
		playGame();
		
		initHexCells();

		previousMoves = initPreviousMoves();


	}	


	void HexArray1D::playGame()
	{
		// ERROR HANDLING YAP!!!!
		int tempSize, tempType;

		while(1)
		{
			cout << "Size of grid (min 6) : ";
			cin >> tempSize;

			if(tempSize < 6)
			{
				cerr << "Invalid input..." << endl;
			}else
			{
				size = tempSize;
				break;
			}
		}


		while(1)
		{
			cout << "Please enter 0 for 2-player and 1 for 1 player mod" << endl;
			cin >> tempType;

			if(tempType == 0 || tempType == 1)
			{
				gameType = tempType;
				break;
			}else
			{
				cout << "Invalid input..." << endl;

			}
		}

		// clear buffer
		cin.ignore(1000, '\n');
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

	void HexArray1D::print() const
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
				// hexCells[xPos][yPos].setCellStatus(xCapital);
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
						// hexCells[xPos][yPos].setCellStatus(xCapital);
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
				// hexCells[xPos][yPos] = oCapital;
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
						// hexCells[xPos][yPos].setCellStatus(oCapital);
						hexCells[size * xPos + yPos].setCellStatus(xCapital);
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
			// if(hexCells[xPos][yPos].getCellStatus() == xLower && visited[xPos][yPos] == 0)
			// 	return 1;
			if(hexCells[xPos * size + yPos].getCellStatus() == xLower && visited[xPos][yPos] == 0)
				return 1;
		}else
		{
			// if(hexCells[xPos][yPos].getCellStatus() == oLower && visited[xPos][yPos] == 0)
			// 	return 1;
			if(hexCells[xPos * size + yPos].getCellStatus() == oLower && visited[xPos][yPos] == 0)
				return 1;
		}

		return 0;
	}






	// assignment operator
	HexArray1D& HexArray1D::operator = (const HexArray1D& h1){
		cout << "assignment operator" << endl;
		return *this;
	}

	// copy constructor
	HexArray1D::HexArray1D(const HexArray1D& h1){
		cout << "copy constructor" << endl;
	}

	// destructor
	HexArray1D::~HexArray1D(){
		cout << "destructor" << endl;
	}

	void HexArray1D::readFromFile()
	{
		cout << "readFromFile function" << endl;
	}

	void HexArray1D::writeToFile()const
	{
		cout << "writeToFile function" << endl;
	}

	void HexArray1D::reset()
	{
		cout << "reset function" << endl;
	}

	void HexArray1D::setSize()
	{
		cout << "setSize function" << endl;
	}

	AbstractHex::Cell HexArray1D::play()
	{
		AbstractHex::Cell temp;
		return temp;
	}

	AbstractHex::Cell HexArray1D::play(AbstractHex::Cell c1)
	{
		return c1;
	}

	// bool isEnd()const;
	// Cell operator()(int x, int y)const;

	AbstractHex::Cell HexArray1D::operator()(int x, int y)const
	{
		AbstractHex::Cell temp;
		return temp;
	}

	bool HexArray1D::operator==(const AbstractHex &aHex)const
	{
		return true;
	}

	AbstractHex::Cell HexArray1D::lastMove()
	{
		AbstractHex::Cell temp;
		return temp;

	}

	int HexArray1D::numberOfMoves()const
	{
		return 0;
	}

}
