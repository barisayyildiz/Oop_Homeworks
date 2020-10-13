#include <iostream>
#include <string>

using namespace std;


void drawGrid(char (*grid)[12], int n);

void initGrid(char (*grid)[12], int n);

int isMoveable(char (*grid)[12], int (*allmoves)[12], int xPos, int yPos, int n);

int backTracking(char (*grid)[12], int xPos, int yPos, int n, int turn);

int didXWin(char (*grid)[12], int (*allmoves)[12], int xPos, int yPos, int n, int turn);

int didOWin(char (*grid)[12], int (*allmoves)[12], int xPos, int yPos, int n, int turn);




int main()
{
	char grid[12][12];

	// turn => 0 : computer / user-1, 1 : user-1 / user-2
	int gameOver = 0, gameType, turn = 0, n, counter = 0;
	string moveChar;
	int moveNum;
	int xPos, yPos;

	while(1)
	{
		cout << "Size of grid [7-12] : ";
		cin >> n;

		if(n < 3 || n > 12)
			cout << "Invalid input" << endl;
		else
			break;
	}

	initGrid(grid, n);
	drawGrid(grid, n);

	while(1)
	{
		cout << "Please enter 0 for 2-player and 1 for 1 player mod" << endl;
		cin >> gameType;

		if(gameType == 0 || gameType == 1)
			break;
		else
			cout << "Please enter a valid input..." << endl;
	}

	if(gameType == 0)
	{
		while(!gameOver)
		{
			cout << "\nUser-" << turn+1 << "'s turn" << endl;
			cout << "Please enter your move (ex : A 3) : ";
			//getline(cin, move);
			cin >> moveChar >> moveNum;

			//moveChar.length() > 1
			cout << moveChar.length() << " " << moveNum << endl;

			// invalid input
			if(moveChar.length() > 1 || moveNum > n || moveNum <= 0 || !((moveChar[0] >= 'A' && moveChar[0] < 'A' + n) || (moveChar[0] >= 'a' && moveChar[0] < 'a' + n)))
			{
				cout << "Invalid input" << endl;
				continue;
			}

			// set positions
			xPos = moveNum - 1;
			if(moveChar[0] >= 'a')
				yPos = moveChar[0] - 97;
			else
				yPos = moveChar[0] - 65;

			// check if the cell is empty
			if(grid[xPos][yPos] != '.')
			{
				cout << "Position is not empty" << endl; 
				continue;
			}

			// place x's and o's
			if(turn == 0)
				grid[xPos][yPos] = 'x';
			else
				grid[xPos][yPos] = 'o';

			// switch the turn and increase the counter
			counter++;

			//draw grid
			drawGrid(grid, n);

			cout << "n*n : " << n*n << " counter : " << counter << " turn : " << turn << endl;



			if(backTracking(grid, xPos, yPos, n, turn))
			{
				cout << "\nUser-" << turn+1 << " wins" << endl;
				drawGrid(grid, n);
				gameOver = 1;
			}else if(counter == n*n)
			{
				cout << "It's a tie..." << endl;
				gameOver = 1;
			}

			turn = !turn;

		}


	//multiplayer mode
	}else
	{
		cout << "Not available currently..." << endl;
	}
	


	return 0;
}




//===================FUNCTIONS==========================//

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

	int allmoves[12][12];
	initAllMoves(allmoves);
	if(turn == 0) // x, left to right
	{
		for(int i=0; i<n; i++)
		{
			if(grid[i][0] == 'x' && didXWin(grid, allmoves, 0, i, n, turn))
				return 1;
		}
		
	}else
	{
		for(int i=0; i<n; i++)
		{
			if(grid[0][i] == 'o' && didOWin(grid, allmoves, 0, i, n, turn))
				return 1;
		}

	}

	return 0;
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

/*
int backTracking(char (*grid)[12], int (*allmoves)[12], int xPos, int yPos)
{
	//sona gelmişsek
	if(xPos == 5)
		return 1;

	allmoves[xPos][yPos] = 1;

	cout << "=====================\n";
	cout << "xPos : " << xPos << " yPos : " << yPos << endl;

	int tempX = xPos, tempY = yPos;

	int moveRange[6][2] = {{-1,0}, {0,1}, {1,0}, {0,-1}, {-1,1}, {1,-1}};
	for(int i=0; i<6; i++)
	{
		tempX = xPos + moveRange[i][0];
		tempY = yPos + moveRange[i][1];

		cout << "tempX : " << tempX << " tempY : " << tempY << endl;

		// out of border
		if(tempX < 0 || tempX >= 6 || tempY < 0 || tempY >= 6)
		{
			cout << "out of border...\n";
			continue;
		}

		if(isMoveable(grid, allmoves, tempX ,tempY))
		{
			if(backTracking(grid, allmoves, tempX, tempY))
				return 1;
		}else
		{
			cout << "gidilemez!!!\n";
		}
	}

	return 0;
}
*/


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