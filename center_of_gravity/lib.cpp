#include <iostream>

using namespace std;


int isMoveable(char (*grid)[12], int (*visited)[12], int xPos, int yPos, int n, int turn)
{

	if(turn == 0)
	{
		if(grid[xPos][yPos] == 'x' && visited[xPos][yPos] == 0)
			return 1;
	}else
	{
		if(grid[xPos][yPos] == 'o' && visited[xPos][yPos] == 0)
			return 1;
	}

	return 0;
}


void centerofGravity(int *center, int totalX, int totalY, int counter)
{
	int x = totalX / counter;
	int y = totalX / counter;

	center[0] = x;
	center[1] = y;

	return;
}

int didSomebodyWin(char (*grid)[12], int (*visited)[12], int xPos, int yPos, int n, int turn)
{
	int tempX = xPos, tempY = yPos;
	int moveRange[6][2] = {{-1,0}, {0,1}, {1,0}, {0,-1}, {-1,1}, {1,-1}};

	if(turn == 0)
	{
		// X's turn
		if(yPos == n-1)
		{
			grid[xPos][yPos] -= 32;
			return 1;
		}

		visited[xPos][yPos] = 1;
		
		for(int i=0; i<6; i++)
		{
			tempX = xPos + moveRange[i][0];
			tempY = yPos + moveRange[i][1];

			// out of border
			if(tempX < 0 || tempX >= n || tempY < 0 || tempY >= n)
			{
				continue;
			}

			if(isMoveable(grid, visited, tempX ,tempY, n, turn))
			{
				if(didSomebodyWin(grid, visited, tempX, tempY, n, turn))
				{
					// capitalize
					grid[xPos][yPos] -= 32;
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
			grid[xPos][yPos] -= 32;
			return 1;
		}

		visited[xPos][yPos] = 1;

		for(int i=0; i<6; i++)
		{
			tempX = xPos + moveRange[i][0];
			tempY = yPos + moveRange[i][1];

			// out of border
			if(tempX < 0 || tempX >= n || tempY < 0 || tempY >= n)
			{
				//cout << "out of border...\n";
				continue;
			}

			if(isMoveable(grid, visited, tempX ,tempY, n, turn))
			{
				if(didSomebodyWin(grid, visited, tempX, tempY, n, turn))
				{
					// capitalize
					grid[xPos][yPos] -= 32;
					return 1;
				}
			}
		}

		return 0;
	}

}


void calculateBestMove(char (*grid)[12], int counter, int n, int *xPos, int *yPos)
{
	// computer is making the first move
	if(counter == 0)
	{
		*xPos = n/2;
		*yPos = n/2;
		return;
	}
	counter = 0;

	int totalX = 0, totalY = 0;
	int center[2];

	for(int i=0; i<n; i++)
	{
		for(int j=0; j<n; j++)
		{
			if(grid[i][j] == 'o')
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


	if(grid[center[0]][center[1]] == '.')
	{
		*xPos = center[0];
		*yPos = center[1];
		return;
	}

	int direction[4][2] = {{0,1}, {1,0}, {0,-1}, {-1,0}};
	int turn = 0;

	while(grid[center[0]][center[1]] != '.')
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

	*xPos = center[0];
	*yPos = center[1];

	return;
}

void initVisited(int (*visited)[12])
{
	for(int i=0; i<12; i++)
	{
		for(int j=0; j<12; j++)
		{
			visited[i][j] = 0;
		}
	}
}

int isEndOfTheGame(char (*grid)[12], int xPos, int yPos, int n, int turn)
{
	// 0 -> no win
	// 1 -> win

	int visited[12][12];
	initVisited(visited);


	if(turn == 0) // x, left to right
	{
		for(int i=0; i<n; i++)
		{
			initVisited(visited);

			if(grid[i][0] == 'x' && didSomebodyWin(grid, visited, i, 0, n, turn))
				return 1;
		}
		
	}else
	{
		for(int i=0; i<n; i++)
		{
			initVisited(visited);
			if(grid[0][i] == 'o' && didSomebodyWin(grid, visited, 0, i, n, turn))
				return 1;
		}

	}

	return 0;
}


void drawGrid(char (*grid)[12], int n)
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
			cout << grid[i][j] << " ";
		}
		cout << "\n";
	}
}



void initGrid(char (*grid)[12], int n)
{
	for(int i=0; i<n; i++)
	{
		for(int j=0; j<n; j++)
		{
			grid[i][j] = '.';
		}
	}
}
