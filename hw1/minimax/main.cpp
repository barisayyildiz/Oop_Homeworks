//===============================
//
//	Name 						:	Barış
//	Surname 				: Ayyıldız
//	Number 					:	1901042252
//	Lecture					:	CSE 241
//	Homework number	:	1
//
//===============================


#include <iostream>
#include <string>
#include "hex.h"

using namespace std;


int main()
{
	// 12x12 grid
	char grid[12][12];

	// turn => 0 : computer / user-1, 1 : user-1 / user-2
	// gameType => 0 : 2-player mode, 1 : human vs ai 
	// n : size of the grid that user wants to play
	// counter : number of moves
	// moveChar moveNum (row and column) => A 3
	int gameOver = 0, gameType, turn = 0, n, counter = 0;
	string moveChar;
	int moveNum;
	int xPos, yPos;

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

			// computer decides its move and saves it to variables xPos and yPos
			minimax(grid, 0, 1, SMALL_NUMBER, BIG_NUMBER, counter, n, &xPos, &yPos);

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
		{
			grid[xPos][yPos] = 'x';
			cout << "x to " <<  static_cast<char>(yPos+65) << " " << xPos + 1 << endl << endl;
		}
		else
		{
			grid[xPos][yPos] = 'o';
			cout << "o to " <<  static_cast<char>(yPos+65) << " " << xPos + 1 << endl << endl;
		}

		counter++;
		
		// if it is end of the game print message and quit from the game loop
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
			// if all the cells are filled but there is not a winner
			cout << "It's a tie..." << endl;
			gameOver = 1;
		}

		// draws grid
		drawGrid(grid, n);

		// switch the turn
		turn = !turn;

	}

	return 0;
}
