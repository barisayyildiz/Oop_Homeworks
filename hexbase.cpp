#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <exception>
#include "hexbase.h"
#include "hexarray.h"
#include "exception.h"

using namespace std;
using namespace excNamespace;

namespace hex
{
	
	AbstractHex::Cell::Cell(cell c) : cellStatus(c)
	{/*left empty*/}

	int AbstractHex::nonEmptyCells = 0;

	int AbstractHex::getUserInput(string input, string &filename, int &xPos, int &yPos)
	{
		// return values : 
		// 0 -> invalid input, 1 -> valid position,  2 -> LOAD command, 3 -> SAVE command, 4 -> QUIT, 5 -> UNDO, 6 -> SCORE

		string tokens[5];
		int counter = 0;

		// sstream type
		stringstream stream(input);

		string token;


		while(getline(stream, token, ' '))
		{
			tokens[counter++] = token;
		}


		if(counter == 1)
		{
			if(tokens[0] == "QUIT")
			{
				return 4;
			}else if(tokens[0] == "UNDO")
			{
				return 5;
			}else if(tokens[0] == "SCORE")
			{
				return 6;
			}else if(tokens[0] == "RESIZE")
			{
				return 7;
			}

		}else if(counter == 2)
		{
			if(tokens[0] == "SAVE")
			{
				filename = tokens[1];
				return 3;
			}else if(tokens[0] == "LOAD")
			{
				filename = tokens[1];
				return 2;
			}else if(tokens[0].length() == 1)
			{
				// lower case
				if(tokens[0][0] >= 'a')
					yPos = tokens[0][0] - 'a';
				
				//upper case
				else if(tokens[0][0] >= 'A')
					yPos = tokens[0][0] - 'A';

				if(tokens[1][0] < '0' || tokens[1].length() > 3)
					return 0;

				xPos = tokens[1][0] - '0';

				if(tokens[1].length() == 2)
				{
					xPos *= 10;
					xPos += (tokens[1][1] - '0');
				}

				xPos--;

				return 1;

			}

		}

		return 0;

	}

	void AbstractHex::gameLoop()
	{
		int xPos, yPos;
		string s1, s2;
		int input;
		Cell temp;

		// draw the board
		// cout << *this << endl;
		print();

		while(getGameStatus() == true)
		{
			if(getGameType() == 1 && getTurn() == 0)
			{
				cout << "\nComputer's turn" << endl;

				play();

			}else
			{
				if(gameType == 1)
				{
					// user vs bot
					cout << "\nUser's turn" << endl;
				}
				else
				{
					cout << "\nUser-" << getTurn()+1 << "'s turn" << endl;
				}

				cout << "Please enter your move or command (ex : A 3) or \n"
				"SAVE/LOAD yourfilename.txt or \n"
				"QUIT or UNDO or SCORE or RESIZE : ";

				getline( cin, s1);

				input = getUserInput(s1, s2, xPos, yPos);
				

				if(input == 0)
				{
					cerr << "Invalid input..." << endl;
					continue;
				}else if(input == 2)
				{
					// // load the board

					try
					{
						readFromFile(s2);

						cout << "Here is the new board : " << endl;
						print();

					}catch(const FileError &err)
					{
						cerr << err.what() << endl;
					}


					continue;
				}else if(input == 3)
				{
					// // save the board

					writeToFile(s2);
					cout << "The board information is saved to the file " << s2 << "..." << endl;

					continue;
				}else if(input == 4)
				{
					cout << "Leaving the game..." << endl;
					return;

				}else if(input == 5)
				{
					// ERROR HANDLING

					try
					{
						undo();
						if(getGameType() == 1)
							undo();
					}catch(const UndoError& err)
					{
						cerr << err.what() << endl << endl;
					}

					

					cout << "Board, after undoing : " << endl << endl;

					// draw the board
					print();
					
					continue;


				}else if(input == 6)
				{
					cout << "Active user's score is : " << calculateScore() << endl;
					continue;
				}else if(input == 7)
				{
					// ERROR HANDLING
					cout << "\nEnter the new size of the board : ";
					cin >> input;

					// clears buffer
					cin.ignore(1000, '\n');

					try
					{
						setSize(input);
						
						cout << "The new board is : \n\n";
						print();
					}catch(const InvalidSize &err)
					{
						cerr << err.what() << endl << endl;
					}

					continue;

				}


				temp.setX(xPos);
				temp.setY(yPos);

				// Exception Handling
				try
				{
					play(temp);
				}catch(const IndexError &err)
				{
					cout << xPos << "," << yPos << endl;
					cerr << "Index is out of board" << endl << endl;
					continue;
				}catch(const AllocatedCell &err)
				{
					cout << xPos << "," << yPos << endl;
					cerr << err.what() << endl << endl;
					continue;
				}
				

				if(isEnd())
				{
					if(getGameType() == 1 && getTurn() == 0)
						cout << "\nComputer wins" << endl;
					else if(getGameType() == 1 && getTurn() == 1)
						cout << "\nUser wins" << endl;
					else
						cout << "\nUser-" << turn+1 << " wins" << endl;

					gameStatus = false;
					nonEmptyCells -= getCounter(); // remove counter from non empty cells
				}

			}

			// toggle the turn
			if(turn)
				turn = 0;
			else
				turn = 1;

			// draw the board
			// cout << *this << endl;
			print();
		}
	}

	void AbstractHex::playGame()
	{
		// ERROR HANDLING YAP!!!!
		int tempSize, tempType;

		cout << "Size of grid (min 6) : ";
		cin >> tempSize;

		if(tempSize < 6)
		{
			// cerr << "Invalid input..." << endl;
			throw InvalidSize();

		}else
		{
			size = tempSize;
		}

		cout << "Please enter 0 for 2-player and 1 for 1 player mod" << endl;
		cin >> tempType;

		if(tempType == 0 || tempType == 1)
		{
			gameType = tempType;
		}else
		{
			// cout << "Invalid input..." << endl;
			throw InvalidInput();
		}

		// clear buffer
		cin.ignore(1000, '\n');
	}

}
