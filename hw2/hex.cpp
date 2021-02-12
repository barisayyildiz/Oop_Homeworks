#include <iostream>
#include <string>
#include <fstream>
#include "hex.h"

using namespace std;

// if the cell is moveable, which means there is a connection between this cell and our current cell, it returns 1
// otherwise it returns 0
int isMoveable(cell (*grid)[12], cell (*visited)[12], int xPos, int yPos, int turn)
{

	if(turn == 0)
	{
		if(grid[xPos][yPos] == xLower && visited[xPos][yPos] == empty)
			return 1;
	}else
	{
		if(grid[xPos][yPos] == oLower && visited[xPos][yPos] == empty)
			return 1;
	}

	return 0;
}


void centerofGravity(int *center, int totalX, int totalY, int counter)
{
	int x = totalX / counter;
	int y = totalY / counter;

	center[0] = x;
	center[1] = y;

	return;
}

int didSomebodyWin(cell (*grid)[12], cell (*visited)[12], int xPos, int yPos, int n, int turn)
{
	int tempX = xPos, tempY = yPos;
	int moveRange[6][2] = {{-1,0}, {0,1}, {1,0}, {0,-1}, {-1,1}, {1,-1}};

	if(turn == 0)
	{
		// X's turn
		if(yPos == n-1)
		{
			grid[xPos][yPos] = xCapital;
			return 1;
		}

		visited[xPos][yPos] = beenThere;
		
		for(int i=0; i<6; i++)
		{
			tempX = xPos + moveRange[i][0];
			tempY = yPos + moveRange[i][1];

			// out of border
			if(tempX < 0 || tempX >= n || tempY < 0 || tempY >= n)
			{
				continue;
			}

			if(isMoveable(grid, visited, tempX ,tempY, turn))
			{
				if(didSomebodyWin(grid, visited, tempX, tempY, n, turn))
				{
					// capitalize
					// grid[xPos][yPos] -= 32;
					grid[xPos][yPos] = xCapital;
					return 1;
				}
			}
		}

		return 0;

	}else
	{
		// O's turn
		if(xPos == n-1)
		{
			// capitalize
			grid[xPos][yPos] = oCapital;
			return 1;
		}

		visited[xPos][yPos] = beenThere;

		for(int i=0; i<6; i++)
		{
			tempX = xPos + moveRange[i][0];
			tempY = yPos + moveRange[i][1];

			// out of border
			if(tempX < 0 || tempX >= n || tempY < 0 || tempY >= n)
			{
				continue;
			}

			if(isMoveable(grid, visited, tempX ,tempY, turn))
			{
				if(didSomebodyWin(grid, visited, tempX, tempY, n, turn))
				{
					// capitalize
					grid[xPos][yPos] = oCapital;
					return 1;
				}
			}
		}
		return 0;
	}
}


void calculateBestMove(cell (*grid)[12], int counter, int n, int &xPos, int &yPos)
{
	// if the computer is making the first move
	if(counter == 0)
	{
		xPos = n/2;
		yPos = n/2;
		return;
	}
	counter = 0;

	int totalX = 0, totalY = 0;
	int center[2];

	for(int i=0; i<n; i++)
	{
		for(int j=0; j<n; j++)
		{
			if(grid[i][j] == oLower)
			{
				totalX += i;
				totalY += j;
				counter++;
			}
		}
	}

	//calculate the center of gravity
	centerofGravity(center, totalX, totalY, counter);

	center[0] = totalX / counter;
	center[1] = totalY / counter;

	// if the cell is empty, set xPos and yPos
	if(grid[center[0]][center[1]] == empty)
	{
		xPos = center[0];
		yPos = center[1];
		return;
	}

	// if it is not, try to find the closest point
	int direction[4][2] = {{0,1}, {1,0}, {0,-1}, {-1,0}};
	int turn = 0;

	while(grid[center[0]][center[1]] != empty)
	{
		if(center[0] + direction[turn][0] >= n || center[0] + direction[turn][0] < 0 || center[1] + direction[turn][1] >= n || center[1] + direction[turn][1] < 0)
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

// Initilizes an empty 2d cell grid
// We try to save the places that are visited in our recursive algorithm to prevent endless loops
void initVisited(cell (*visited)[12])
{
	for(int i=0; i<12; i++)
	{
		for(int j=0; j<12; j++)
		{
			visited[i][j] = empty;
		}
	}
}


int isEndOfTheGame(cell (*grid)[12], int n, int turn)
{
	// 0 -> no win
	// 1 -> win

	cell visited[12][12];


	if(turn == 0) // x, left to right
	{
		for(int i=0; i<n; i++)
		{
			initVisited(visited);

			if(grid[i][0] == xLower && didSomebodyWin(grid, visited, i, 0, n, turn))
				return 1;
		}
		
	}else
	{
		for(int i=0; i<n; i++)
		{
			initVisited(visited);
			if(grid[0][i] == oLower && didSomebodyWin(grid, visited, 0, i, n, turn))
				return 1;
		}

	}

	return 0;
}

char convertEnumtoChar(cell (*grid)[12], int i, int j)
{
	if(grid[i][j] == empty)
	{
		return '.';
	}else if(grid[i][j] == xLower)
	{
		return 'x';
	}else if(grid[i][j] == oLower)
	{
		return 'o';
	}else if(grid[i][j] == xCapital)
	{
		return 'X';
	}else
	{
		return 'O';
	}
}


void drawGrid(cell (*grid)[12], int n)
{
	// header
	cout << "  ";
	for(int i=0; i<n; i++)
	{
		cout << static_cast<char>(97 + i) << " ";
	}
	cout << "\n";




	for(int i=0; i<n; i++)
	{
		// numbers
		cout << i+1 << " ";

		// indentation
		for(int indent=0; indent<=i; indent++)
			cout << " ";

		for(int j=0; j<n; j++)
		{
			cout << convertEnumtoChar(grid, i, j) << " ";
		}
		cout << "\n";
	}
}


// Initilizes the game board
void initGrid(cell (*grid)[12], int n)
{
	for(int i=0; i<n; i++)
	{
		for(int j=0; j<n; j++)
		{
			grid[i][j] = empty;
		}
	}
}

int getUserInput(string s1, string s2, int &xPos, int &yPos)
{
	// return values : 
	// 0 -> invalid input, 1 -> valid position,  2 -> LOAD command, 3 -> SAVE command

	if(s1 == "LOAD")
		return 2;
	else if(s1 == "SAVE")
		return 3;

	if(s1.length() == 1)
	{
		//A 3

		//lower case
		if(s1[0] >= 97)
			yPos = s1[0] - 97;
		//upper case
		else if(s1[0] >= 65)
			yPos = s1[0] - 65;

		xPos = s2[0] - '0';

		if(s2.length() == 2)
		{
			xPos *= 10;
			xPos += (s2[1] - '0');
		}

		xPos--;

		return 1;
	}


	cerr << "Invalid input..." << endl;
	return 0;
	
}

// ====================== FILE HANDLING ======================== //

// saves the game board and saves some information about the game
// it saves board size, game counter, type of game, turn and game board respectively
void saveBoard(cell (*grid)[12], const int&n, const int &gameType, const int &turn, const int &counter, string filename)
{
	ofstream fout;

	fout.open(filename);

	fout << n << endl;
	fout << counter << endl;
	fout << gameType << endl;
	fout << turn << endl;

	for(int i=0; i<n; i++)
	{
		for(int  j=0; j<n; j++)
		{
			fout << grid[i][j];
		}
		fout << endl;
	}


	fout.close();

}

// loads the game from the file
void loadBoard(cell (*grid)[12], int&n, int &gameType, int &turn, int &counter, string filename)
{
	ifstream fin;

	int temp;

	string line;

	fin.open(filename);

	fin >> n;
	fin >> counter;
	fin >> gameType;
	fin >> turn;


	for(int i=0; i<n; i++)
	{
		fin >> line;
		for(int j=0; j<n; j++)
		{
			temp = line[j] - '0';
			grid[i][j] = static_cast<cell>(temp);
		}
	}

	fin.close();
}
