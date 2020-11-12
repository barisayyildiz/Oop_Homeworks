#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

#include "hex.h"

using namespace std;


Hex::Cell::Cell(cell s):cellStatus(s)
{/*left empty*/}

int Hex::nonEmptyCells = 0;

Hex::Hex() : size(0), turn(0), counter(0), gameStatus(true)
{
	// gets user input
	playGame();

	hexCells.resize(size);
	for(int i=0; i<size; i++)
		hexCells[i].resize(size);

	for(int i=0; i<size; i++)
	{
		for(int j=0; j<size; j++)
		{
			hexCells[i][j].setCellStatus(empty);
		}
	}

	// main game loop
	gameLoop();

}

void Hex::drawBoard()
{
	// header
	cout << "  ";
	for(int i=0; i<size; i++)
	{
		cout << static_cast<char>(97 + i) << " ";
	}
	cout << "\n";

	for(int i=0; i<size; i++)
	{
		// numbers
		cout << i+1 << " ";

		// indentation
		for(int indent=0; indent<=i; indent++)
			cout << " ";

		for(int j=0; j<size; j++)
		{
			cout << static_cast<char>( hexCells[i][j].getCellStatus() ) << " ";
			// cout << static_cast<char>( board[i][j] ) << " ";
		}
		cout << "\n";
	}


	// cout << (hexCells[0][0].getCellStatus() == empty) << endl;
}

void Hex::playGame()
{
	int tempSize, tempType;

	while(1)
	{
		cout << "Size of grid (min 6) : ";
		cin >> tempSize;

		if(tempSize < 6)
		{
			cerr << "Invalid input..." << endl;
		}else
		{
			setSize(tempSize);
			break;
		}
	}


	while(1)
	{
		cout << "Please enter 0 for 2-player and 1 for 1 player mod" << endl;
		cin >> tempType;

		if(tempType == 0 || tempType == 1)
		{
			setGameType(tempType);
			break;
		}else
		{
			cout << "Invalid input..." << endl;

		}
	}

	cin.ignore(1000, '\n');

}

void Hex::gameLoop()
{
	// // active -> 0, terminated -> 1
	// cout << "game status : " << getGameStatus() << endl;

	int xPos, yPos;
	string s1, s2;
	int input;

	/*
	gameType -> 0		2-player
	gameType -> 1		1-player vs bot
	*/

	/*
	gameOver	false
	*/

	drawBoard();

	while(getGameStatus() == true)
	{
		if(getGameType() == 1 && getTurn() == 0)
		{
			cout << "\nComputer's turn" << endl;

			calculateBestMove(xPos, yPos);

		}else
		{
			if(gameType == 1)
			{
				// user vs bot
				cout << "\nUser's turn" << endl;
			}else
			{
				cout << "\nUser-" << getTurn()+1 << "'s turn" << endl;
			}

			// ==================== BURADAN SONRASI DÜZELTİLECEK!!! ==================== //

			cout << "Please enter your move or command (ex : A 3 or SAVE/LOAD yourfilename.txt or QUIT) : ";
			// cin >> s1;
			getline( cin, s1);

			// input = getUserInput(s1, s2, xPos, yPos);
			input = getUserInput(s1, s2, xPos, yPos);

			if(input == 0)
			{
				continue;
			}else if(input == 2)
			{
				loadBoard(s2);
				
				cout << "The new board is : " << endl;
				drawBoard();

				continue;
			}else if(input == 3)
			{
				saveBoard(s2);
				cout << "The board information is saved to the file " << s2 << "..." << endl;

				continue;
			}else if(input == 4)
			{
				cout << "Leaving the game..." << endl;
				return;
			}

			// out of border
			if(xPos < 0 || xPos >= size || yPos < 0 || yPos >= size)
			{
				cerr << "Out of border..." << endl;
				continue;
			}

			if(hexCells[xPos][yPos].getCellStatus() != empty)
			{
				cerr << "Position is not empty" << endl;
				continue;
			}

		}

		// place x's and o's
		if(getTurn() == 0)
		{
			// grid[xPos][yPos] = xLower;
			hexCells[xPos][yPos].setCellStatus(xLower);
			cout << endl << "x to " <<  static_cast<char>(yPos+65) << " " << xPos + 1 << endl << endl;
		}
		else
		{
			// grid[xPos][yPos] = oLower;
			hexCells[xPos][yPos].setCellStatus(oLower);
			cout << endl << "o to " <<  static_cast<char>(yPos+65) << " " << xPos + 1 << endl << endl;
		}

		// counter++;
		setCounter(counter+1);

		if(isEndOfTheGame())
		{
			if(getGameType() == 1 && getTurn() == 0)
				cout << "\nComputer wins" << endl;
			else if(getGameType() == 1 && getTurn() == 1)
				cout << "\nUser wins" << endl;
			else
				cout << "\nUser-" << turn+1 << " wins" << endl;

			setGameStatus(false);
		}

		drawBoard();

		if(getTurn() == 0)
			setTurn(1);
		else
			setTurn(0);

	}

}


int Hex::getUserInput(string input, string &filename, int &xPos, int &yPos)
{
	// return values : 
	// 0 -> invalid input, 1 -> valid position,  2 -> LOAD command, 3 -> SAVE command, 4 -> QUIT

	vector <string> tokens;

	// sstream type
	stringstream stream(input);

	string token;


	while(getline(stream, token, ' '))
	{
		tokens.push_back(token);
	}

	cout << "tokens are : " << endl;

	for(decltype(tokens.size()) i = 0; i<tokens.size(); i++)
	{
		cout << tokens[i] << endl;
	}

	if(tokens.size() == 1)
	{
		if(tokens[0] == "QUIT")
		{
			return 4;
		}

	}else if(tokens.size() == 2)
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
			// konum almışız
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

// int Hex::getUserInput(string s1, string s2, int &xPos, int &yPos)
// {
// 	// return values : 
// 	// 0 -> invalid input, 1 -> valid position,  2 -> LOAD command, 3 -> SAVE command

// 	if(s1 == "LOAD")
// 		return 2;
// 	else if(s1 == "SAVE")
// 		return 3;

// 	if(s1.length() == 1)
// 	{
// 		//A 3

// 		//lower case
// 		if(s1[0] >= 97)
// 			yPos = s1[0] - 97;
// 		//upper case
// 		else if(s1[0] >= 65)
// 			yPos = s1[0] - 65;

// 		xPos = s2[0] - '0';

// 		if(s2.length() == 2)
// 		{
// 			xPos *= 10;
// 			xPos += (s2[1] - '0');
// 		}

// 		xPos--;

// 		return 1;
// 	}


// 	cerr << "Invalid input..." << endl;
// 	return 0;
	
// }


void Hex::play(int xPos, int yPos)
{
	// user's turn
	counter++;
	nonEmptyCells++;

	hexCells[xPos][yPos].setCellStatus(oLower);
	

	cout << "turn : " << turn << endl;
	cout << "bitti : " << isEndOfTheGame() << endl;

	if(turn)
		turn = 0;
	else
		turn = 1;

}

void Hex::play()
{
	// ai's turn
	int xPos, yPos;
	calculateBestMove(xPos, yPos);

	nonEmptyCells++;
	counter++;
	hexCells[xPos][yPos].setCellStatus(xLower);


	cout << "turn : " << turn << endl;
	cout << "bitti : " << isEndOfTheGame() << endl;

	if(turn)
		turn = 0;
	else
		turn = 1;


}

void Hex::calculateBestMove(int &xPos, int &yPos)
{
	// if the computer is making the first move
	if(counter == 0)
	{
		xPos = size/2;
		yPos = size/2;
		return;
	}
	int increment = 0;

	int totalX = 0, totalY = 0;
	int center[2];

	for(int i=0; i<size; i++)
	{
		for(int j=0; j<size; j++)
		{
			if(hexCells[i][j].getCellStatus() == oLower)
			{
				totalX += i;
				totalY += j;
				increment++;
			}
		}
	}

	//calculate the center of gravity
	centerofGravity(center, totalX, totalY, increment);

	center[0] = totalX / increment;
	center[1] = totalY / increment;

	// if the cell is empty, set xPos and yPos
	if(hexCells[center[0]][center[1]].getCellStatus() == empty)
	{
		xPos = center[0];
		yPos = center[1];
		return;
	}

	// if it is not, try to find the closest point
	int direction[4][2] = {{0,1}, {1,0}, {0,-1}, {-1,0}};
	int turn = 0;

	while(hexCells[center[0]][center[1]].getCellStatus() != empty)
	{
		if(center[0] + direction[turn][0] >= size || center[0] + direction[turn][0] < 0 || center[1] + direction[turn][1] >= size || center[1] + direction[turn][1] < 0)
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

	// cout << "xPos : " << xPos << ", yPos : " << yPos << endl;

	return;
}


void Hex::centerofGravity(int *center, int totalX, int totalY, int increment)
{
	int x = totalX / increment;
	int y = totalY / increment;

	center[0] = x;
	center[1] = y;

	return;
}


int Hex::isEndOfTheGame()
{
	// int visited[12][12];
	vector<vector<int>> visited(size, vector<int> (size, 0));


	if(turn == 0) // x, left to right
	{
		for(int i=0; i<size; i++)
		{
			initVisited(visited);

			if(hexCells[i][0].getCellStatus() == xLower && didSomebodyWin(visited, i, 0))
				return 1;
		}
		
	}else
	{
		for(int i=0; i<size; i++)
		{
			initVisited(visited);
			if(hexCells[0][i].getCellStatus() == oLower && didSomebodyWin(visited, 0, i))
				return 1;
		}
	}

	return 0;
}

void Hex::initVisited(vector<vector<int>> visited)
{
	for(int i=0; i<size; i++)
	{
		for(int j=0; j<size; j++)
		{
			visited[i][j] = 0;
		}
	}
}


int Hex::didSomebodyWin(vector<vector<int>> visited, int xPos, int yPos)
{
	int tempX = xPos, tempY = yPos;
	int moveRange[6][2] = {{-1,0}, {0,1}, {1,0}, {0,-1}, {-1,1}, {1,-1}};

	if(turn == 0)
	{
		// X's turn
		if(yPos == size-1)
		{
			hexCells[xPos][yPos].setCellStatus(xCapital);
			return 1;
		}

		visited[xPos][yPos] = 1;
		
		for(auto i=0; i<6; i++)
		{
			tempX = xPos + moveRange[i][0];
			tempY = yPos + moveRange[i][1];

			// out of border
			if(tempX < 0 || tempX >= size || tempY < 0 || tempY >= size)
			{
				continue;
			}

			if(isMoveable(visited, tempX ,tempY))
			{
				if(didSomebodyWin(visited, tempX, tempY))
				{
					// capitalize
					// grid[xPos][yPos] -= 32;
					hexCells[xPos][yPos].setCellStatus(xCapital);
					return 1;
				}
			}
		}

		return 0;

	}else
	{
		// O's turn
		if(xPos == size-1)
		{
			// capitalize
			hexCells[xPos][yPos] = oCapital;
			return 1;
		}

		visited[xPos][yPos] = 1;


		for(auto i=0; i<6; i++)
		{
			tempX = xPos + moveRange[i][0];
			tempY = yPos + moveRange[i][1];

			// out of border
			if(tempX < 0 || tempX >= size || tempY < 0 || tempY >= size)
			{
				continue;
			}

			if(isMoveable(visited, tempX ,tempY))
			{
				if(didSomebodyWin(visited, tempX, tempY))
				{
					// capitalize
					hexCells[xPos][yPos].setCellStatus(oCapital);
					return 1;
				}
			}
		}
		return 0;
	}


}

int Hex::isMoveable(vector<vector<int>> visited, int xPos, int yPos)
{
	if(turn == 0)
	{
		if(hexCells[xPos][yPos].getCellStatus() == xLower && visited[xPos][yPos] == 0)
			return 1;
	}else
	{
		if(hexCells[xPos][yPos].getCellStatus() == oLower && visited[xPos][yPos] == 0)
			return 1;
	}

	return 0;
}


bool Hex::compare(Hex h1)
{
	return (getCounter() > h1.getCounter());
}


// ===================== FILE IO ==================== //


int Hex::orderChar(char c)
{
	if(c == '.')
	{
		return 0;
	}else if(c == 'x')
	{
		return 1;
	}else if(c == 'o')
	{
		return 2;
	}else if(c == 'X')
	{
		return 3;
	}else	// 'O'
	{
		return 4;
	}

}

void Hex::saveBoard(string filename)
{
	ofstream fout;

	char temp;

	fout.open(filename);

	fout << size << endl;
	fout << counter << endl;
	fout << gameType << endl;
	fout << turn << endl;

	for(int i=0; i<size; i++)
	{
		for(int  j=0; j<size; j++)
		{
			temp = static_cast<char>( hexCells[i][j].getCellStatus() );

			fout << orderChar(temp);
		}
		fout << endl;
	}


	fout.close();
}

void Hex::loadBoard(string filename)
{
	ifstream fin;

	int temp;
	int newSize;

	// we need to adjust nonEmptyCells
	nonEmptyCells -= counter;

	string line;

	fin.open(filename);

	if(!fin)
	{
		cerr << "No such file exists...\n\n";
		return;
	}

	fin >> newSize;
	fin >> counter;
	fin >> gameType;
	fin >> turn;

	cout << "test!!!!!!!!!!!!!!!!!!!!" << endl;
	// Need to resize!!!

	hexCells.resize(newSize);
	for(int i=0; i<newSize; i++)
		hexCells[i].resize(newSize);

	size = newSize;


	for(int i=0; i<size; i++)
	{
		fin >> line;
		for(int j=0; j<size; j++)
		{
			temp = line[j] - '0';
			hexCells[i][j] = static_cast<cell>(temp);

			switch(temp)
			{
				case 0:
					hexCells[i][j].setCellStatus(empty);
					break;
				case 1:
					hexCells[i][j].setCellStatus(xLower);
					nonEmptyCells++;
					break;
				case 2:
					hexCells[i][j].setCellStatus(oLower);
					nonEmptyCells++;
					break;
				case 3:
					hexCells[i][j].setCellStatus(xCapital);
					nonEmptyCells++;
					break;
				case 4:
					hexCells[i][j].setCellStatus(oCapital);
					nonEmptyCells++;
					break;
			}
		}
	}

	drawBoard();

}


