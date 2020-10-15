#include <iostream>
#include <string>

using namespace std;


#define EPSILONE 0.0001


void drawGrid(char (*grid)[12], int n);

void initGrid(char (*grid)[12], int n);

int isMoveable(char (*grid)[12], int (*allmoves)[12], int xPos, int yPos, int n);

int backTracking(char (*grid)[12], int xPos, int yPos, int n, int turn);

int didXWin(char (*grid)[12], int (*allmoves)[12], int xPos, int yPos, int n, int turn);

int didOWin(char (*grid)[12], int (*allmoves)[12], int xPos, int yPos, int n, int turn);

void calculateBestMove(char (*grid)[12], int *pos, int counter, int n);

int manhattanDistance(int p1x, int p1y, int p2x, int p2y);

double abs(double num);

void centerofGravity(int *center, int totalX, int totalY, int counter);

int minimax(char (*grid)[12], int depth, int isMaximize, int alpha, int beta, int counter, int n, int *xPos, int *yPos);

void initAllMoves(int (*allmoves)[12]);

int scoreHelper(char (*grid)[12], int (*visited)[12], int xPos, int yPos, int n, int turn);

int calculateScore(char (*grid)[12], int n, int turn);

int main()
{
	char grid[12][12];

	// turn => 0 : computer / user-1, 1 : user-1 / user-2
	int gameOver = 0, gameType, turn = 0, n, counter = 0;
	string moveChar;
	int moveNum;
	int xPos, yPos;

	int bestPos[2];

	int score;

	int visited[12][12];

	while(1)
	{
		cout << "Size of grid [7-12] : ";
		cin >> n;

		if(n < 2 || n > 12)
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

	while(!gameOver)
	{

		if(gameType == 1 && turn == 0)
		{
			// computer's turn
			cout << "\nComputer's turn" << endl;

			// make your move

			score = minimax(grid, 0, 1, -10000, 10000, counter, n, &xPos, &yPos);

			cout << xPos << " : "<<yPos << endl << endl;

			

			//initAllMoves(visited);

			/*
			calculateBestMove(grid, bestPos, counter, n);

			xPos = bestPos[0];
			yPos = bestPos[1];

			cout << bestPos[0] << " : "<<bestPos[1] << endl << endl;
			*/


		}else
		{
			// user's turn

			// header message
			if(gameType == 1)
			{
				// user vs bot
				cout << "\nUser's turn" << endl;
			}else
			{
				cout << "\nUser-" << turn+1 << "'s turn" << endl;
			}

			cout << "Please enter your move (ex : A 3) : ";
			cin >> moveChar >> moveNum;

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
		}

		// place x's and o's
		if(turn == 0)
			grid[xPos][yPos] = 'x';
		else
			grid[xPos][yPos] = 'o';

		counter++;

		score = calculateScore(grid, n, turn);

		cout << "score : " << score << endl << endl;

		

		cout << "n*n : " << n*n << " counter : " << counter << " turn : " << turn << endl;	

		if(backTracking(grid, xPos, yPos, n, turn))
		{
			// winning message
			if(gameType == 1 && turn == 0)
				cout << "\nComputer wins" << endl;
			else if(gameType == 1 && turn == 1)
				cout << "\nUser wins" << endl;
			else
				cout << "\nUser-" << turn+1 << " wins" << endl;

			gameOver = 1;
		}else if(counter == n*n)
		{
			cout << "It's a tie..." << endl;
			gameOver = 1;
		}

		//draw grid
		drawGrid(grid, n);

		cout << "how to turn tables..." << endl;
		turn = !turn;

	}

	return 0;
}




//===================FUNCTIONS==========================//

int calculateScore(char (*grid)[12], int n, int turn)
{
	int visited[12][12];
	initAllMoves(visited);
	int score = -100;
	int value;

	for(int i=0; i<n; i++)
		{
			for(int j=0; j<n; j++)
			{
				if(grid[i][j] == 'x')
				{
					initAllMoves(visited);
					value = scoreHelper(grid, visited, i, j, n, turn);
					if(value > score)
						score = value;
				}
			}
		}

	return score;
}

int scoreHelper(char (*grid)[12], int (*visited)[12], int xPos, int yPos, int n, int turn)
{
	if(xPos >= n || xPos < 0 or yPos >= n || yPos < 0)
		return 0;

	int maximum = 0;

	int directionX[4][2] = {{0,1}, {-1,1}, {-1,0}, {1,0}};
	int directionO[4][2] = {{1,0}, {1,-1}, {0,-1}, {0,1}};
	int temp_x, temp_y;
	int total;

	//cout << "x : " << xPos << " , y : " << yPos << endl;

	if(turn == 0)
	{
		// X's turn
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
					total = 10 + scoreHelper(grid, visited, temp_x, temp_y, n, turn);
					if(total > maximum)
						maximum = total;
				}
			}else
			{
				// +1 points
				if(grid[temp_x][temp_y] == 'x')
				{
					//cout << "wwwwwwwwwww" << endl;
					visited[temp_x][temp_y] = 1;
					total = 1 + scoreHelper(grid, visited, temp_x, temp_y, n, turn);
					if(total > maximum)
						maximum = total;
				}
			}
		}
	}else
	{
		// O's turn
		for(int i=0; i<4; i++)
		{
			temp_x = xPos + directionO[i][0];
			temp_y = yPos + directionO[i][1];
			if(temp_x >= n || temp_x < 0 or temp_y >= n || temp_y < 0)
				continue;

			if(visited[temp_x][temp_y] == 1)
				continue;

			if(i == 0 || i == 1)
			{
				// +10 points
				if(grid[temp_x][temp_y] == 'o')
				{
					cout << "qqqqqqqqq" << endl;
					visited[temp_x][temp_y] = 1;
					total = 10 + scoreHelper(grid, visited, temp_x, temp_y, n, turn);
					if(total > maximum)
						maximum = total;
				}
			}else
			{
				// +1 points
				if(grid[temp_x][temp_y] == 'o')
				{
					cout << "wwwwwwwwwww" << endl;
					visited[temp_x][temp_y] = 1;
					total = 1 + scoreHelper(grid, visited, temp_x, temp_y, n, turn);
					if(total > maximum)
						maximum = total;
				}
			}
		}


	}

	
	return maximum;

}

int minimax(char (*grid)[12], int depth, int isMaximize, int alpha, int beta, int counter, int n, int *xPos, int *yPos)
{
	/*
	int aiWin = backTracking(grid, 0, 0, n, 0);
	int userWin = backTracking(grid, 0, 0, n, 1);

	if(aiWin != 0)
		return 10;
	else if(userWin != 0)
		return -10;
	*/

	if(depth == 4 || counter == n*n-1)
		return calculateScore(grid, n, 0);

	int val, temp, temp_x, temp_y;

	if(isMaximize)
	{
		val = -1000;
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

			if(val != -1000)
			{
				*xPos = temp_x;
				*yPos = temp_y;
			}
			

			cout << "=====>>" << temp_x << " : " << temp_y << endl;
			
			
			if(beta <= alpha)
				break;
		}

		

		
		return val;

	}else
	{

		val = 1000;
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

			if(val != 1000)
			{
				*xPos = temp_x;
				*yPos = temp_y;
			}
			
			if(beta <= alpha)
				break;
		}
		
		return val;

	}

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


void centerofGravity(int *center, int totalX, int totalY, int counter)
{
	int x = totalX / counter;
	int y = totalX / counter;

	center[0] = x;
	center[1] = y;

	return;
}


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
			if(grid[i][0] == 'x' && didXWin(grid, allmoves, i, 0, n, turn))
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

	//cout << "(" << xPos << "," << yPos << ")" << endl;

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
				//cout << "qweqwe" << endl;
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
				//cout << "qweqwe" << endl;
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
