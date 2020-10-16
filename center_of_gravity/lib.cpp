#include <iostream>

using namespace std;


int isMoveable(char (*grid)[12], int (*allmoves)[12], int xPos, int yPos, int n, int turn)
{
	/*
	if((turn == 0 && grid[xPos][yPos] == 'x' && allmoves[xPos][yPos] == 0) || (turn == 1 && grid[xPos][yPos] == 'o' && allmoves[xPos][yPos] == 0))
		return 1;
	*/

	if(turn == 0)
	{
		if(grid[xPos][yPos] == 'x' && allmoves[xPos][yPos] == 0)
			return 1;
	}else
	{
		if(grid[xPos][yPos] == 'o' && allmoves[xPos][yPos] == 0)
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

int didXWin(char (*grid)[12], int (*allmoves)[12], int xPos, int yPos, int n, int turn)
{
	if(yPos == n-1)
	{
		// capitalize
		grid[xPos][yPos] -= 32;
		return 1;
	}

	cout << "(" << xPos << "," << yPos << ")" << endl;

	allmoves[xPos][yPos] = 1;

	int tempX = xPos, tempY = yPos;
	int moveRange[6][2] = {{-1,0}, {0,1}, {1,0}, {0,-1}, {-1,1}, {1,-1}};
	for(int i=0; i<6; i++)
	{
		tempX = xPos + moveRange[i][0];
		tempY = yPos + moveRange[i][1];

		//cout << "tempX : " << tempX << " tempY : " << tempY << endl;

		// out of border
		if(tempX < 0 || tempX >= n || tempY < 0 || tempY >= n)
		{
			//cout << "out of border...\n";
			continue;
		}

		if(isMoveable(grid, allmoves, tempX ,tempY, n, turn))
		{
			if(didXWin(grid, allmoves, tempX, tempY, n, turn))
			{
				// capitalize
				cout << "qweqwe" << endl;
				grid[xPos][yPos] -= 32;
				return 1;
			}
		}else
		{
			//cout << "gidilemez!!!\n";
		}
	}

	return 0;

}

int didOWin(char (*grid)[12], int (*allmoves)[12], int xPos, int yPos, int n, int turn)
{
	if(xPos == n-1)
	{
		// capitalize
		grid[xPos][yPos] -= 32;
		return 1;
	}

	allmoves[xPos][yPos] = 1;

	int tempX = xPos, tempY = yPos;
	int moveRange[6][2] = {{-1,0}, {0,1}, {1,0}, {0,-1}, {-1,1}, {1,-1}};
	for(int i=0; i<6; i++)
	{
		tempX = xPos + moveRange[i][0];
		tempY = yPos + moveRange[i][1];

		//cout << "tempX : " << tempX << " tempY : " << tempY << endl;

		// out of border
		if(tempX < 0 || tempX >= n || tempY < 0 || tempY >= n)
		{
			//cout << "out of border...\n";
			continue;
		}

		if(isMoveable(grid, allmoves, tempX ,tempY, n, turn))
		{
			if(didOWin(grid, allmoves, tempX, tempY, n, turn))
			{
				// capitalize
				cout << "qweqwe" << endl;
				grid[xPos][yPos] -= 32;
				return 1;
			}
		}else
		{
			//cout << "gidilemez!!!\n";
		}
	}

	return 0;

}


void calculateBestMove(char (*grid)[12], int *pos, int counter, int n)
{
	// computer is making the first move
	if(counter == 0)
	{
		pos[0] = n/2;
		pos[1] = n/2;
		return ;
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

	cout << "total x : totalY : counter ==> " << totalX << " : " << totalY << " : " << counter << endl;

	cout << "center of gravity : " << center[0] << " : " << center[1] << endl;

	if(grid[center[0]][center[1]] == '.')
	{
		pos[0] = center[0];
		pos[1] = center[1];
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

	pos[0] = center[0];
	pos[1] = center[1];

	return;
}

void initAllMoves(int (*allmoves)[12])
{
	for(int i=0; i<12; i++)
	{
		for(int j=0; j<12; j++)
		{
			allmoves[i][j] = 0;
		}
	}
}

int backTracking(char (*grid)[12], int xPos, int yPos, int n, int turn)
{
	// 0 -> no win
	// 1 -> win

	cout << "xpos : " << xPos << ", ypos : " << yPos << ", n : " << n << endl;

	int allmoves[12][12];
	initAllMoves(allmoves);
	if(turn == 0) // x, left to right
	{
		for(int i=0; i<n; i++)
		{
			initAllMoves(allmoves);

			for(int a=0; a<n; a++)
			{
				for(int b=0; b<n; b++)
				{
					cout << allmoves[a][b];
				}
				cout << endl;
			}

			cout << i << endl;
			if(grid[i][0] == 'x' && didXWin(grid, allmoves, i, 0, n, turn))
			{
				cout << "doğru" << endl;
				return 1;
			}
		}
		
	}else
	{
		for(int i=0; i<n; i++)
		{
			initAllMoves(allmoves);
			if(grid[0][i] == 'o' && didOWin(grid, allmoves, 0, i, n, turn))
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
		// rakamlar
		cout << i+1 << " ";

		// baştaki boşluklar
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
