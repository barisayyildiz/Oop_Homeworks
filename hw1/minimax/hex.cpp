#include "hex.h"
#include <iostream>

using namespace std;


int calculateScore(char (*grid)[12], int n)
{
	int visited[12][12];
	int score = SMALL_NUMBER;
	int value;

	for(int i=0; i<n; i++)
		{
			for(int j=0; j<n; j++)
			{
				if(grid[i][j] == 'x')
				{
					initVisited(visited);
					value = scoreHelper(grid, visited, i, j, n);
					if(value > score)
						score = value;
				}
			}
		}

	return score;
}

int scoreHelper(char (*grid)[12], int (*visited)[12], int xPos, int yPos, int n)
{
	if(xPos >= n || xPos < 0 or yPos >= n || yPos < 0)
		return 0;

	int maximum = 0;

	int directionX[4][2] = {{0,1}, {-1,1}, {-1,0}, {1,0}};
	int temp_x, temp_y;
	int total;

	for(int i=0; i<4; i++)
	{
		temp_x = xPos + directionX[i][0];
		temp_y = yPos + directionX[i][1];
		if(temp_x >= n || temp_x < 0 or temp_y >= n || temp_y < 0)
			continue;

		if(visited[temp_x][temp_y] == 1)
			continue;

		if(i == 0 || i == 1)
		{
			// +10 points
			if(grid[temp_x][temp_y] == 'x')
			{
				//cout << "qqqqqqqqq" << endl;
				visited[temp_x][temp_y] = 1;
				total = 10 + scoreHelper(grid, visited, temp_x, temp_y, n);
				if(total > maximum)
					maximum = total;
			}
		}else
		{
			// +1 points
			if(grid[temp_x][temp_y] == 'x')
			{
				visited[temp_x][temp_y] = 1;
				total = 1 + scoreHelper(grid, visited, temp_x, temp_y, n);
				if(total > maximum)
					maximum = total;
			}
		}
	}
	
	
	return maximum;

}

void findFirstEmptySpot(char (*grid)[12], int *xPos, int *yPos, int n)
{
	for(int i=0; i<n; i++)
	{
		for(int j=0; j<n; j++)
		{
			if(grid[i][j] == '.')
			{
				*xPos = i;
				*yPos = j;
				return;
			}
		}
	}
}

int minimax(char (*grid)[12], int depth, int isMaximize, int alpha, int beta, int counter, int n, int *xPos, int *yPos)
{

	if(depth == 4 || counter == n*n-1)
		return calculateScore(grid, n);

	int val, temp, temp_x, temp_y;

	if(isMaximize)
	{
		val = SMALL_NUMBER;
		for(int i=0; i<n; i++)
		{
			for(int j=0; j<n; j++)
			{
				// cell is empty
				if(grid[i][j] == '.')
				{
					grid[i][j] = 'x';
					temp = minimax(grid, depth+1, alpha, beta, !isMaximize, counter+1, n, xPos, yPos);
					grid[i][j] = '.';
					if(temp > val)
					{
						val = temp;
						temp_x = i;
						temp_y = j;

						

						alpha = temp;
					}
				}
			}

			if(val != SMALL_NUMBER)
			{
				*xPos = temp_x;
				*yPos = temp_y;
			}else
			{
				findFirstEmptySpot(grid, xPos, yPos, n);
			}
			
			
			
			if(beta <= alpha)
				break;
		}

		

		
		return val;

	}else
	{

		val = BIG_NUMBER;
		for(int i=0; i<n; i++)
		{
			for(int j=0; j<n; j++)
			{
				// cell is empty
				if(grid[i][j] == '.')
				{
					grid[i][j] = 'o';
					temp = minimax(grid, depth+1, alpha, beta, !isMaximize, counter+1, n, xPos, yPos);
					grid[i][j] = '.';
					if(temp < val)
					{
						val = temp;
						temp_x = i;
						temp_y = j;

						beta = temp;
					}
				}
			}

			if(val != BIG_NUMBER)
			{
				*xPos = temp_x;
				*yPos = temp_y;
			}else
			{
				findFirstEmptySpot(grid, xPos, yPos, n);
			}
			
			if(beta <= alpha)
				break;
		}
		
		return val;

	}

}


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

	if(turn == 0) // x, left to right
	{
		for(int i=0; i<n; i++)
		{
			initVisited(visited);

			if(grid[i][0] == 'x' && didSomebodyWin(grid, visited, i, 0, n, turn))
			{
				return 1;
			}
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

int didSomebodyWin(char (*grid)[12], int (*visited)[12], int xPos, int yPos, int n, int turn)
{
	int tempX = xPos, tempY = yPos;
	int moveRange[6][2] = {{-1,0}, {0,1}, {1,0}, {0,-1}, {-1,1}, {1,-1}};

	if(turn == 0)
	{
		// X's turn
		if(yPos == n-1)
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

		// indentations
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
