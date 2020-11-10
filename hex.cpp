#include <iostream>
#include <vector>
#include <string>

#include "hex.h"

using namespace std;


Hex::Cell::Cell(cell s):status(s)
{/*left empty*/}

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
	hexCells[xPos][yPos].setStatus(oLower);
}

void Hex::play()
{
	// ai's turn
	int xPos, yPos;
	calculateBestMove(xPos, yPos);

	counter++;
	hexCells[xPos][yPos].setStatus(xLower);
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
	cell visited[12][12];


	if(turn == 0) // x, left to right
	{
		for(int i=0; i<size; i++)
		{
			initVisited(visited);

			if(grid[i][0].getStatus() == xLower && didSomebodyWin(visited, i, 0))
				return 1;
		}
		
	}else
	{
		for(int i=0; i<size; i++)
		{
			initVisited(visited);
			if(grid[0][i].getStatus() == oLower && didSomebodyWin(visited, 0, i))
				return 1;
		}
	}

	return 0;
}

void Hex::initVisited(cell (*visited)[])
{
	for(int i=0; i<size; i++)
	{
		for(int j=0; j<size; j++)
		{
			visited[i][j] = empty;
		}
	}
}

