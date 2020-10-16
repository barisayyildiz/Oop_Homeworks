#include <iostream>
#include <string>
#include "lib.h"

using namespace std;


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

		if(n < 7 || n > 12)
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

			//score = minimax(grid, 0, 1, SMALL_NUMBER, BIG_NUMBER, counter, n, &xPos, &yPos);

			//cout << xPos << " : "<<yPos << endl << endl;


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

		

		//cout << "n*n : " << n*n << " counter : " << counter << " turn : " << turn << endl;	

		if(isEndOfTheGame(grid, xPos, yPos, n, turn))
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

		turn = !turn;

	}

	return 0;
}
