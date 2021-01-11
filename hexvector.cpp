#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "hexbase.h"
#include "hexvector.h"
#include "exception.h"

using namespace std;
using namespace excNamespace;

namespace hex{

	HexVector::HexVector() : AbstractHex() , previousMoves(nullptr)
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

	HexVector::HexVector(int s) : AbstractHex(), previousMoves(nullptr)
	{
		// ERROR HANDLING
		if(s < 6)
			throw InvalidSize();

		size = s;
		
		initHexCells();

		previousMoves = initPreviousMoves();
	}

	HexVector::HexVector(int s, int gT) : AbstractHex(), previousMoves(nullptr)
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

	HexVector::HexVector(int s, int gT, string &filename) : AbstractHex(), previousMoves(nullptr)
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
	HexVector& HexVector::operator = (const HexVector& h1){

		if(previousMoves != nullptr)
		{
			for(int i=0; i<cap; i++)
			{
				delete[] previousMoves[i];
			}

			delete[] previousMoves;
		}
		previousMoves = nullptr;
		

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
				// hexCells[i * size + j] = h1.hexCells[i * size + j];
				hexCells[i][j] = h1.hexCells[i][j];
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
	HexVector::HexVector(const HexVector& h1){

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
				// hexCells[i * size + j] = h1.hexCells[i * size + j];
				hexCells[i][j] = h1.hexCells[i][j];
			}
		}

		for(int i=0; i<counter; i++)
		{
			previousMoves[i][0] = h1.previousMoves[i][0];
			previousMoves[i][1] = h1.previousMoves[i][1];
		}

	}

	// destructor
	HexVector::~HexVector(){
		cout << "~destructor" << endl;

		if(previousMoves != nullptr)
		{
			for(int i=0; i<cap; i++)
			{
				delete[] previousMoves[i];
			}
			delete[] previousMoves;
		}

		// I have used malloc and free, because we were told to use one dimensional dynamic 'C array' for the hexCells
		// if(hexCells != nullptr)
		// 	free(hexCells);

	}



	void HexVector::playGame()
	{
		// ERROR HANDLING YAP!!!!
		int tempSize, tempType;

		cout << "Size of grid (min 6) : ";
		cin >> tempSize;

		if(tempSize < 6)
		{
			// cerr << "Invalid input..." << endl;
			throw InvalidSize();

		}else
		{
			size = tempSize;
		}

		cout << "Please enter 0 for 2-player and 1 for 1 player mod" << endl;
		cin >> tempType;

		if(tempType == 0 || tempType == 1)
		{
			gameType = tempType;
		}else
		{
			// cout << "Invalid input..." << endl;
			throw InvalidInput();
		}

		// clear buffer
		cin.ignore(1000, '\n');
	}

	int** HexVector::initPreviousMoves()
	{
		int **temp = nullptr;
		temp = new int*[cap];

		for(int i=0; i<cap; i++)
			temp[i] = new int[2];

		return temp;
	}

	void HexVector::initHexCells()
	{
		hexCells.resize(size);

		for(int i=0; i<size; i++)
		{
			hexCells[i].resize(size, Cell(empty));
		}

	}

	void HexVector::print()
	{
		// header
		cout << "  ";
		for(int i=0; i<getSize(); i++)
		{
			cout << static_cast<char>(97 + i) << " ";
		}
		cout << "\n";

		for(int i=0; i<getSize(); i++)
		{
			// numbers
			cout << i+1 << " ";

			// indentation
			for(int indent=0; indent<=i; indent++)
				cout << " ";

			for(int j=0; j<getSize(); j++)
			{
				cout << static_cast<char>( hexCells[i][j].getCellStatus() ) << " ";
			}
			cout << "\n";
		}
	}

	bool HexVector::isEnd()
	{
		int **visited = nullptr;
		visited = initVisited(visited);

		if(turn == 0) // x, left to right
		{
			for(int i=0; i<size; i++)
			{
				initVisited(visited);

				if(hexCells[i][0].getCellStatus() == xLower && didSomebodyWin(visited, i, 0))
					return true;
			}
			
		}else
		{
			for(int i=0; i<size; i++)
			{
				initVisited(visited);
				if(hexCells[0][i].getCellStatus() == oLower && didSomebodyWin(visited, 0, i))
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

	int** HexVector::initVisited(int **visited)
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

	int HexVector::didSomebodyWin(int **visited, int xPos, int yPos)
	{
		int tempX = xPos, tempY = yPos;
		int moveRange[6][2] = {{-1,0}, {0,1}, {1,0}, {0,-1}, {-1,1}, {1,-1}};

		if(turn == 0)
		{
			// X's turn
			if(yPos == size-1)
			{
				hexCells[xPos][yPos].setCellStatus(xCapital);
				// hexCells[size * xPos + yPos].setCellStatus(xCapital);
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
						hexCells[xPos][yPos].setCellStatus(xCapital);
						// hexCells[size * xPos + yPos].setCellStatus(xCapital);
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
				hexCells[xPos][yPos] = oCapital;
				// hexCells[size * xPos + yPos].setCellStatus(oCapital);
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
						hexCells[xPos][yPos].setCellStatus(oCapital);
						// hexCells[size * xPos + yPos].setCellStatus(oCapital);
						return 1;
					}
				}
			}
			return 0;
		}

	}

	int HexVector::isMoveable(int **visited, int xPos, int yPos)
	{
		if(turn == 0)
		{
			if(hexCells[xPos][yPos].getCellStatus() == xLower && visited[xPos][yPos] == 0)
				return 1;
			// if(hexCells[xPos * size + yPos].getCellStatus() == xLower && visited[xPos][yPos] == 0)
			// 	return 1;
		}else
		{
			if(hexCells[xPos][yPos].getCellStatus() == oLower && visited[xPos][yPos] == 0)
				return 1;
			// if(hexCells[xPos * size + yPos].getCellStatus() == oLower && visited[xPos][yPos] == 0)
			// 	return 1;
		}

		return 0;
	}


	AbstractHex::Cell HexVector::play(AbstractHex::Cell c1)
	{
		// // out of border
		// if(xPos < 0 || xPos >= size || yPos < 0 || yPos >= size)
		// {
		// 	cerr << "Out of border..." << endl;
		// 	continue;
		// }

		// if(hexCells[xPos * size + yPos].getCellStatus() != empty)
		// {
		// 	cerr << "Position is not empty" << endl;
		// 	continue;
		// }

		// if(hexCells[xPos][yPos].getCellStatus() != empty)
		// {
		// 	cerr << "Position is not empty" << endl;
		// 	continue;
		// }

		// temp.setX(xPos);
		// temp.setY(yPos);

		// c1->temp


		if(c1.getX() < 0 || c1.getX() > size || c1.getY() < 0 || c1.getY() > size)
		{
			throw IndexError();

		}else if(hexCells[c1.getX()][c1.getY()].getCellStatus() != empty)
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
			hexCells[c1.getX()][c1.getY()].setCellStatus(xLower);
			// hexCells[c1.getX() * size + c1.getY()].setCellStatus(xLower);
		}
		else
		{
			hexCells[c1.getX()][c1.getY()].setCellStatus(oLower);
			// hexCells[c1.getX() * size + c1.getY()].setCellStatus(oLower);
		}

		// return hexCells[c1.getX() * size + c1.getY()];
		return hexCells[c1.getX()][c1.getY()];

	}


	// helper function for file input output
	int HexVector::orderChar(char c)
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


	void HexVector::writeToFile(const string &filename)
	{
		char temp;

		ofstream fout;

		fout.open(filename);

		fout << getSize() << endl;
		fout << getCounter() << endl;
		fout << getGameType() << endl;
		fout << getTurn() << endl;


		for(int i=0; i<getSize(); i++)
		{
			for(int  j=0; j<getSize(); j++)
			{
				temp = static_cast<char>( hexCells[i][j].getCellStatus() );

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

	void HexVector::readFromFile(const string &filename)
	{
		int temp;
		int newSize, newCounter, newGameType, newTurn, newCap;

		// we need to adjust nonEmptyCells
		HexVector::nonEmptyCells -= getCounter();

		string line;

		ifstream fin;
		fin.open(filename);

		if(!fin)
		{
			// cerr << "No such file exists...\n\n";
			throw FileError();
			return;
		}

		fin >> newSize;
		fin >> newCounter;
		fin >> newGameType;
		fin >> newTurn;

		// // free hexCells
		// free(hexCells);

		for(int i=0; i<size; i++)
		{
			hexCells[i].erase(hexCells[i].begin(), hexCells[i].end());
		}
		hexCells.erase(hexCells.begin(), hexCells.end());


		// for(int i=0; i<h1.getSize(); i++)
		// {
		// 	delete[] h1.hexCells[i];
		// }
		// delete[] h1.hexCells;

		size = newSize;
		counter = newCounter;
		gameType = newGameType;
		turn = newTurn;

		// hexCells = (AbstractHex::Cell*)malloc(sizeof(AbstractHex::Cell) * newSize * newSize);
		initHexCells();

		for(int i=0; i<getSize(); i++)
		{
			fin >> line;
			for(int j=0; j<getSize(); j++)
			{
				temp = line[j] - '0';
				hexCells[i][j] = static_cast<cell>(temp);

				switch(temp)
				{
					case 0:
						hexCells[i][j].setCellStatus(empty);
						break;
					case 1:
						hexCells[i][j].setCellStatus(xLower);
						HexVector::nonEmptyCells++;
						break;
					case 2:
						hexCells[i][j].setCellStatus(oLower);
						HexVector::nonEmptyCells++;
						break;
					case 3:
						hexCells[i][j].setCellStatus(xCapital);
						HexVector::nonEmptyCells++;
						break;
					case 4:
						hexCells[i][j].setCellStatus(oCapital);
						HexVector::nonEmptyCells++;
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
	AbstractHex::Cell HexVector::play()
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
		// hexCells[xPos * size + yPos].setCellStatus(xLower);
		hexCells[xPos][yPos].setCellStatus(xLower);

		// return hexCells[xPos * size + yPos];
		return hexCells[xPos][yPos];

	}

	void HexVector::calculateBestMove(int &xPos, int &yPos)
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
				if(hexCells[i][j].getCellStatus() == oLower)
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
		if(hexCells[center[0]][center[1]].getCellStatus() == empty)
		{
			xPos = center[0];
			yPos = center[1];
			return;
		}

		// if it is not, try to find the closest point
		int direction[4][2] = {{0,1}, {1,0}, {0,-1}, {-1,0}};
		int turn = 0;

		while(hexCells[center[0]][center[1]].getCellStatus() != empty)
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


	void HexVector::centerofGravity(int *center, int totalX, int totalY, int increment)
	{
		int x = totalX / increment;
		int y = totalY / increment;

		center[0] = x;
		center[1] = y;

		return;
	}


	void HexVector::reset()
	{
		// cout << "reset function" << endl;

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

		for(int i=0; i<size; i++)
		{
			hexCells[i].erase(hexCells[i].begin(), hexCells[i].end());
		}
		hexCells.erase(hexCells.begin(), hexCells.end());

		initHexCells();

		turn = 0;
		counter = 0;

	}

	void HexVector::setSize(int newSize)
	{
		if(newSize < 6)
		{
			throw InvalidSize();
		}

		size = newSize;

		reset();

	}


	AbstractHex::Cell HexVector::operator()(int x, int y)const
	{
		// ERROR HANDLING YAPILACAK

		if(x < 0 || x >= getSize() || y < 0 || y >= getSize())
		{
			cout << "out of border" << endl;
			exit(1);
		}

		// return hexCells[x * getSize() + y];
		return hexCells[x][y];

	}

	bool HexVector::operator==(AbstractHex *aHex)
	{
		

		return true;


	}

	AbstractHex::Cell HexVector::lastMove()
	{
		// ERROR HANDLING!!!
		if(counter == 0)
			exit(1);

		return hexCells[previousMoves[counter-1][0]][previousMoves[counter-1][1]];
	}

	int HexVector::numberOfMoves()const
	{
		return getCounter();
	}

	// ============================= FOR CALCULATING SCORE ========================= //

	int HexVector::calculateScore()
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
					if(hexCells[i][j].getCellStatus() == xLower)
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
					if(hexCells[i][j].getCellStatus() == oLower)
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

	int HexVector::scoreHelper(int** visited, int xPos, int yPos, cell c)
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
					if(hexCells[temp_x][temp_y].getCellStatus() == c)
					{
						visited[temp_x][temp_y] = 1;
						total = 2 + scoreHelper(visited, temp_x, temp_y, c);
						if(total > maximum)
							maximum = total;
					}
				}else
				{
					// +1 points
					if(hexCells[temp_x][temp_y].getCellStatus() == c)
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
					if(hexCells[temp_x][temp_y].getCellStatus() == c)
					{
						visited[temp_x][temp_y] = 1;
						total = 2 + scoreHelper(visited, temp_x, temp_y, c);
						if(total > maximum)
							maximum = total;
					}
				}else
				{
					// +1 points
					if(hexCells[temp_x][temp_y].getCellStatus() == c)
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


	void HexVector::undo()
	{
		// ERROR HANDLING
		if(getCounter() == 0)
		{
			// cout << "Cannot undo..." << endl;
			throw UndoError();
		}

		counter--;
		
		// make the last move empty
		// hexCells[previousMoves[counter][0] * size + previousMoves[counter][1]] = empty;
		hexCells[previousMoves[counter][0]][previousMoves[counter][1]] = empty;

		if(turn == 0)
			turn = 1;
		else
			turn = 0;
			
	}

}
