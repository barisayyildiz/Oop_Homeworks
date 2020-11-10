#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#include "hex.h"

using namespace std;


Hex::Cell::Cell(cell s):status(s)
{/*left empty*/}

int Hex::nonEmptyCells = 0;

Hex::Hex() : size(0), turn(0), counter(0)
{
	playGame();

	hexCells.resize(size);
	for(int i=0; i<size; i++)
		hexCells[i].resize(size);

	for(int i=0; i<size; i++)
	{
		for(int j=0; j<size; j++)
		{
			hexCells[i][j].setStatus(empty);
		}
	}
}

void Hex::drawBoard()
{
	// header
	cout << "  ";
	for(int i=0; i<size; i++)
	{
		cout << static_cast<char>(97 + i) << " ";
	}
	cout << "\n";

	for(int i=0; i<size; i++)
	{
		// numbers
		cout << i+1 << " ";

		// indentation
		for(int indent=0; indent<=i; indent++)
			cout << " ";

		for(int j=0; j<size; j++)
		{
			cout << static_cast<char>( hexCells[i][j].getStatus() ) << " ";
			// cout << static_cast<char>( board[i][j] ) << " ";
		}
		cout << "\n";
	}


	// cout << (hexCells[0][0].getStatus() == empty) << endl;
}

void Hex::playGame()
{
	while(1)
	{
		cout << "Size of grid (min 6) : ";
		cin >> size;

		if(size < 6)
		{
			cerr << "Invalid input..." << endl;
		}else
		{
			break;
		}
	}


	while(1)
	{
		cout << "Please enter 0 for 2-player and 1 for 1 player mod" << endl;
		cin >> gameType;

		if(gameType == 0 || gameType == 1)
		{
			break;
		}else
		{
			cerr << "Invalid input..." << endl;
		}
	}

}

void Hex::play(int xPos, int yPos)
{
	// user's turn
	counter++;
	nonEmptyCells++;

	hexCells[xPos][yPos].setStatus(oLower);
	

	cout << "turn : " << turn << endl;
	cout << "bitti : " << isEndOfTheGame() << endl;

	if(turn)
		turn = 0;
	else
		turn = 1;

}

void Hex::play()
{
	// ai's turn
	int xPos, yPos;
	calculateBestMove(xPos, yPos);

	nonEmptyCells++;
	counter++;
	hexCells[xPos][yPos].setStatus(xLower);


	cout << "turn : " << turn << endl;
	cout << "bitti : " << isEndOfTheGame() << endl;

	if(turn)
		turn = 0;
	else
		turn = 1;


}

void Hex::calculateBestMove(int &xPos, int &yPos)
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
			if(hexCells[i][j].getStatus() == oLower)
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
	if(hexCells[center[0]][center[1]].getStatus() == empty)
	{
		xPos = center[0];
		yPos = center[1];
		return;
	}

	// if it is not, try to find the closest point
	int direction[4][2] = {{0,1}, {1,0}, {0,-1}, {-1,0}};
	int turn = 0;

	while(hexCells[center[0]][center[1]].getStatus() != empty)
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

	// cout << "xPos : " << xPos << ", yPos : " << yPos << endl;

	return;
}


void Hex::centerofGravity(int *center, int totalX, int totalY, int increment)
{
	int x = totalX / increment;
	int y = totalY / increment;

	center[0] = x;
	center[1] = y;

	return;
}


int Hex::isEndOfTheGame()
{
	// int visited[12][12];
	vector<vector<int>> visited(size, vector<int> (size, 0));


	if(turn == 0) // x, left to right
	{
		for(int i=0; i<size; i++)
		{
			initVisited(visited);

			if(hexCells[i][0].getStatus() == xLower && didSomebodyWin(visited, i, 0))
				return 1;
		}
		
	}else
	{
		for(int i=0; i<size; i++)
		{
			initVisited(visited);
			if(hexCells[0][i].getStatus() == oLower && didSomebodyWin(visited, 0, i))
				return 1;
		}
	}

	return 0;
}

void Hex::initVisited(vector<vector<int>> visited)
{
	for(int i=0; i<size; i++)
	{
		for(int j=0; j<size; j++)
		{
			visited[i][j] = 0;
		}
	}
}


int Hex::didSomebodyWin(vector<vector<int>> visited, int xPos, int yPos)
{
	int tempX = xPos, tempY = yPos;
	int moveRange[6][2] = {{-1,0}, {0,1}, {1,0}, {0,-1}, {-1,1}, {1,-1}};

	if(turn == 0)
	{
		// X's turn
		if(yPos == size-1)
		{
			hexCells[xPos][yPos].setStatus(xCapital);
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
					// grid[xPos][yPos] -= 32;
					hexCells[xPos][yPos].setStatus(xCapital);
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
					hexCells[xPos][yPos].setStatus(oCapital);
					return 1;
				}
			}
		}
		return 0;
	}


}

int Hex::isMoveable(vector<vector<int>> visited, int xPos, int yPos)
{
	if(turn == 0)
	{
		if(hexCells[xPos][yPos].getStatus() == xLower && visited[xPos][yPos] == 0)
			return 1;
	}else
	{
		if(hexCells[xPos][yPos].getStatus() == oLower && visited[xPos][yPos] == 0)
			return 1;
	}

	return 0;
}


bool Hex::compare(Hex h1)
{
	return (getCounter() > h1.getCounter());
}


// ===================== FILE IO ==================== //


int Hex::orderChar(char c)
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

void Hex::saveBoard(string filename)
{
	ofstream fout;

	char temp;

	fout.open(filename);

	fout << size << endl;
	fout << counter << endl;
	fout << gameType << endl;
	fout << turn << endl;

	for(int i=0; i<size; i++)
	{
		for(int  j=0; j<size; j++)
		{
			temp = static_cast<char>( hexCells[i][j].getStatus() );

			fout << orderChar(temp);
		}
		fout << endl;
	}


	fout.close();
}

void Hex::loadBoard(string filename)
{
	ifstream fin;

	int temp;
	int newSize;

	// we need to adjust nonEmptyCells
	nonEmptyCells -= counter;

	string line;

	fin.open(filename);

	if(!fin)
	{
		cerr << "No such file exists...\n\n";
		return;
	}

	fin >> newSize;
	fin >> counter;
	fin >> gameType;
	fin >> turn;

	cout << "test!!!!!!!!!!!!!!!!!!!!" << endl;
	// Need to resize!!!

	hexCells.resize(newSize);
	for(int i=0; i<newSize; i++)
		hexCells[i].resize(newSize);

	size = newSize;


	for(int i=0; i<size; i++)
	{
		fin >> line;
		for(int j=0; j<size; j++)
		{
			temp = line[j] - '0';
			hexCells[i][j] = static_cast<cell>(temp);

			switch(temp)
			{
				case 0:
					hexCells[i][j].setStatus(empty);
					break;
				case 1:
					hexCells[i][j].setStatus(xLower);
					nonEmptyCells++;
					break;
				case 2:
					hexCells[i][j].setStatus(oLower);
					nonEmptyCells++;
					break;
				case 3:
					hexCells[i][j].setStatus(xCapital);
					nonEmptyCells++;
					break;
				case 4:
					hexCells[i][j].setStatus(oCapital);
					nonEmptyCells++;
					break;
			}
		}
	}

	drawBoard();

}


