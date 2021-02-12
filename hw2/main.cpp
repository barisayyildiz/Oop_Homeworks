// ======================================= //
//
// Name 						:		Barış
// Surname					:		Ayyıldız
// Number						:		1901042252
// Lecture					:		CSE 241
// Homework Number 	:		2
//
// ====================================== //


#include <iostream>
#include <string>
#include <fstream>
#include "hex.h"

using namespace std;


int main()
{

	cell grid[12][12];

	int n, gameType;
	auto gameOver = 0, turn = 0, counter = 0;
	decltype(0) xPos;
	decltype(0) yPos;

	// for user inputs
	string s1, s2;
	int input;


	while(1)
	{
		cout << "Size of grid [7-12] : ";
		cin >> n;

		if(n < 7 || n > 12)
			cerr << "Invalid input" << endl;
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
			cerr << "Please enter a valid input..." << endl;
	}


	while(!gameOver)
	{

		if(gameType == 1 && turn == 0)
		{
			// computer's turn
			cout << "\nComputer's turn" << endl;

			// computer decides its move and saves it to variables xPos and yPos
			calculateBestMove(grid, counter, n, xPos, yPos);

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

			cout << "Please enter your move or command (ex : A 3 or SAVE/LOAD yourfilename.txt) : ";
			cin >> s1 >> s2;

			input = getUserInput(s1, s2, xPos, yPos);

			if(input == 0)
			{
				continue;
			}else if(input == 2)
			{
				loadBoard(grid, n, gameType, turn, counter, s2);
				
				cout << "The new board is : " << endl;
				drawGrid(grid, n);

				continue;
			}else if(input == 3)
			{
				saveBoard(grid, n, gameType, turn, counter, s2);
				cout << "The board information is saved to the file " << s2 << "..." << endl;

				continue;
			}


			// check if the cell is empty
			if(grid[xPos][yPos] != empty)
			{
				cerr << "Position is not empty" << endl; 
				continue;
			}

		}

		// place x's and o's
		if(turn == 0)
		{
			grid[xPos][yPos] = xLower;
			cout << endl << "x to " <<  static_cast<char>(yPos+65) << " " << xPos + 1 << endl << endl;
		}
		else
		{
			grid[xPos][yPos] = oLower;
			cout << endl << "o to " <<  static_cast<char>(yPos+65) << " " << xPos + 1 << endl << endl;
		}

		counter++;


		if(isEndOfTheGame(grid, n, turn))
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

		//draws the grid
		drawGrid(grid, n);

		turn = !turn;

	}


	return 0;
}

