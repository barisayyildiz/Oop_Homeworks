#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include "hex.h"

using namespace std;


Hex::Cell::Cell(cell s):cellStatus(s)
{/*left empty*/}

int Hex::nonEmptyCells = 0;

Hex::Hex() : size(0), turn(0), counter(0), gameStatus(true), previousMoves(nullptr), cap(10), hexCells(nullptr)
{
	// gets the user input
	playGame();

	initHexCells();

	previousMoves = initPreviousMoves();

	// main game loop
	gameLoop();

}

Hex::Hex(int s) : size(s), turn(0), counter(0), gameType(0), gameStatus(true), previousMoves(nullptr), cap(10), hexCells(nullptr)
{
	initHexCells();

	previousMoves = initPreviousMoves();
}

Hex::Hex(int s, int gT) : size(s), turn(0), counter(0), gameType(gT), gameStatus(true), previousMoves(nullptr), cap(10), hexCells(nullptr)
{
	initHexCells();

	previousMoves = initPreviousMoves();
}

Hex::Hex(int s, int gT, string &filename) : size(s), turn(0), counter(0), gameType(gT), gameStatus(true), previousMoves(nullptr), cap(10), hexCells(nullptr)
{
	initHexCells();

	previousMoves = initPreviousMoves();

	ofstream fout;

	fout.open(filename);
	fout << (*this);

	fout.close();

}


// BIG 3

// assignment operator
Hex& Hex::operator = (const Hex& h1)
{
	if(previousMoves != nullptr)
	{
		for(int i=0; i<cap; i++)
		{
			delete[] previousMoves[i];
		}

		delete[] previousMoves;
	}
	previousMoves = nullptr;

	if(hexCells != nullptr)
	{
		for(int i=0; i<size; i++)
		{
			delete[] hexCells[i];
		}
		delete[] hexCells;
	}
	hexCells = nullptr;


	size = h1.getSize();
	turn = h1.getTurn();
	counter = h1.getCounter();
	gameType = h1.getGameType();
	gameStatus = h1.getGameStatus();
	cap = h1.getCap();


	previousMoves = initPreviousMoves();
	initHexCells();

	for(int i=0; i<size; i++)
	{
		for(int j=0; j<size; j++)
		{
			hexCells[i][j] = h1.hexCells[i][j];
		}
	}

	for(int i=0; i<counter; i++)
	{
		previousMoves[i][0] = h1.previousMoves[i][0];
		previousMoves[i][1] = h1.previousMoves[i][1];
	}


	return *this;
}

// copy constructor
Hex::Hex(const Hex& h1)
{	
	size = h1.getSize();
	turn = h1.getTurn();
	counter = h1.getCounter();
	gameType = h1.getGameType();
	gameStatus = h1.getGameStatus();
	cap = h1.getCap();


	previousMoves = initPreviousMoves();
	initHexCells();

	for(int i=0; i<size; i++)
	{
		for(int j=0; j<size; j++)
		{
			hexCells[i][j] = h1.hexCells[i][j];
		}
	}

	for(int i=0; i<counter; i++)
	{
		previousMoves[i][0] = h1.previousMoves[i][0];
		previousMoves[i][1] = h1.previousMoves[i][1];
	}

}


// destructor
Hex::~Hex()
{
	if(previousMoves != nullptr)
	{
		for(int i=0; i<cap; i++)
		{
			delete[] previousMoves[i];
		}
		delete[] previousMoves;
	}

	if(hexCells != nullptr)
	{
		for(int i=0; i<size; i++)
		{
			delete[] hexCells[i];
		}
		delete[] hexCells;
	}

}


int** Hex::initPreviousMoves()
{
	int **temp = nullptr;
	temp = new int*[cap];

	for(int i=0; i<cap; i++)
		temp[i] = new int[2];

	return temp;
}



void Hex::initHexCells()
{
	hexCells = new Cell*[size];

	for(int i=0; i<size; i++)
	{
		hexCells[i] = new Cell[size];
	}

	for(int i=0; i<size; i++)
	{
		for(int j=0; j<size; j++)
		{
			hexCells[i][j].setCellStatus(empty);
		}
	}

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
			size = tempSize;
			break;
		}
	}


	while(1)
	{
		cout << "Please enter 0 for 2-player and 1 for 1 player mod" << endl;
		cin >> tempType;

		if(tempType == 0 || tempType == 1)
		{
			gameType = tempType;
			break;
		}else
		{
			cout << "Invalid input..." << endl;

		}
	}

	// clear buffer
	cin.ignore(1000, '\n');

}

void Hex::gameLoop()
{
	int xPos, yPos;
	string s1, s2;
	int input;

	// draw the board
	cout << *this << endl;

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

			cout << "Please enter your move or command (ex : A 3 or SAVE/LOAD yourfilename.txt or QUIT or PREV or SCORE) : ";
			getline( cin, s1);

			input = getUserInput(s1, s2, xPos, yPos);

			if(input == 0)
			{
				cerr << "Invalid input..." << endl;
				continue;
			}else if(input == 2)
			{
				// load the board
				ifstream fin;
				fin.open(s2);
				fin >> (*this);
				fin.close();
				
				cout << "The new board is : " << endl;
				cout << *this << endl;

				continue;
			}else if(input == 3)
			{
				// save the board
				ofstream fout;
				fout.open(s2);
				fout << (*this);
				fout.close();

				cout << "The board information is saved to the file " << s2 << "..." << endl;

				continue;
			}else if(input == 4)
			{
				cout << "Leaving the game..." << endl;
				return;

			}else if(input == 5)
			{
				if(getCounter() <= 0)
				{
					cout << "Cannot undo..." << endl << endl;
					continue;
				}

				--(*this);
				// human vs ai
				if(getGameType() == 1 && getCounter() != 0)
				{
					--(*this);
				}

				// also can be done with
				// (*this)--;
				cout << "Board, after undoing : " << endl << endl;

				// draw the board
				cout << *this << endl;
				continue;
			}else if(input == 6)
			{
				cout << "Active user's score is : " << calculateScore() << endl;
				continue;
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


			// makes move, increases the counter
			play(xPos, yPos);

			if(isEndOfTheGame())
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
		cout << *this << endl;
	}
}


int Hex::getUserInput(string input, string &filename, int &xPos, int &yPos)
{
	// return values : 
	// 0 -> invalid input, 1 -> valid position,  2 -> LOAD command, 3 -> SAVE command, 4 -> QUIT, 5 -> PREV, 6 -> SCORE

	string tokens[5];
	int counter = 0;

	// sstream type
	stringstream stream(input);

	string token;


	while(getline(stream, token, ' '))
	{
		tokens[counter++] = token;
	}


	for(int i=0; i<counter; i++)
	{
		cout << tokens[i] << endl;
	}


	if(counter == 1)
	{
		if(tokens[0] == "QUIT")
		{
			return 4;
		}else if(tokens[0] == "PREV")
		{
			return 5;
		}else if(tokens[0] == "SCORE")
		{
			return 6;
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


void Hex::play(int xPos, int yPos)
{
	// user's turn
	if(counter == cap)
	{

		cap += 10;
		int **temp = nullptr;

		temp = initPreviousMoves();

		for(int i=0; i<counter; i++)
		{
			temp[i][0] = previousMoves[i][0];
			temp[i][1] = previousMoves[i][1];
			temp[i][2] = previousMoves[i][2];
		}

		// delete and resize previousMoves
		for(int i=0; i<cap-10; i++)
		{
			delete[] previousMoves[i];
		}
		delete[] previousMoves;

		previousMoves = nullptr;

		previousMoves = temp;
	}

	previousMoves[counter][0] = xPos;
	previousMoves[counter][1] = yPos;

	counter++;
	nonEmptyCells++;

	if(getTurn() == 0)
		hexCells[xPos][yPos].setCellStatus(xLower);
	else
		hexCells[xPos][yPos].setCellStatus(oLower);

}

void Hex::play()
{
	// bot's turn
	if(counter == cap)
	{
		cap += 10;

		int **temp = nullptr;

		temp = initPreviousMoves();

		for(int i=0; i<counter; i++)
		{
			temp[i][0] = previousMoves[i][0];
			temp[i][1] = previousMoves[i][1];
		}

		// delete and resize previousMoves
		for(int i=0; i<cap-10; i++)
		{
			delete[] previousMoves[i];
		}
		delete[] previousMoves;

		previousMoves = nullptr;

		previousMoves = temp;
	}


	int xPos, yPos;
	calculateBestMove(xPos, yPos);

	previousMoves[counter][0] = xPos;
	previousMoves[counter][1] = yPos;

	nonEmptyCells++;
	counter++;
	hexCells[xPos][yPos].setCellStatus(xLower);


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
	int **visited = nullptr;
	visited = initVisited(visited);


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


	// deleting dynamic visited array
	for(int i=0; i<size; i++)
	{
		delete[] visited[i];
	}
	delete[] visited;

	return 0;
}

int** Hex::initVisited(int **visited)
{
	if(visited != nullptr)
	{
		// deleting dynamic visited array
		for(int i=0; i<size; i++)
		{
			delete[] visited[i];
		}
		delete[] visited;
	}


	int **temp = new int*[size];
	for(int i=0; i<size; i++)
		temp[i] = new int[size];

	for(int i=0; i<size; i++)
	{
		for(int j=0; j<size; j++)
		{
			temp[i][j] = 0;
		}
	}

	return temp;

}


int Hex::didSomebodyWin(int **visited, int xPos, int yPos)
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

int Hex::isMoveable(int **visited, int xPos, int yPos)
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

int Hex::markedCellsForTheUser()
{
	int temp = 0;
	if(getGameType() == 0)
	{
		// user vs user
		// get all the cells
		temp = getCounter();
	}else if(getGameType() == 1)
	{
		// user vs bot
		// get the cells for the user
		for(int i=0; i<getSize(); i++)
		{
			for(int j=0; j<getSize(); j++)
			{
				if(hexCells[i][j].getCellStatus() == oLower)
					temp++;
			}
		}
	}

	return temp;
}

bool Hex::operator == (Hex h1)
{

	return (markedCellsForTheUser() > h1.markedCellsForTheUser());

}



// helper function for file input output
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


// ============================ OPERATOR OVERLOADINGS ============================= //

// =========================== FILE I/0 ============================= //

ofstream& operator << (ofstream& fout, Hex &h1)
{
	char temp;

	fout << h1.getSize() << endl;
	fout << h1.getCounter() << endl;
	fout << h1.getGameType() << endl;
	fout << h1.getTurn() << endl;

	for(int i=0; i<h1.getSize(); i++)
	{
		for(int  j=0; j<h1.getSize(); j++)
		{
			temp = static_cast<char>( h1.hexCells[i][j].getCellStatus() );

			fout << h1.orderChar(temp);
		}
		fout << endl;
	}

	return fout;
}

ifstream& operator >> (ifstream& fin, Hex &h1)
{
	int temp;
	int newSize, newCounter, newGameType, newTurn;

	// we need to adjust nonEmptyCells
	Hex::nonEmptyCells -= h1.counter;

	string line;


	if(!fin)
	{
		cerr << "No such file exists...\n\n";
		return fin;
	}



	fin >> newSize;
	fin >> newCounter;
	fin >> newGameType;
	fin >> newTurn;


	for(int i=0; i<h1.getSize(); i++)
	{
		delete[] h1.hexCells[i];
	}
	delete[] h1.hexCells;

	h1.hexCells = new Hex::Cell*[newSize];
	for(int i=0; i<newSize; i++)
		h1.hexCells[i] = new Hex::Cell[newSize];

	h1.size = newSize;
	h1.counter = newCounter;
	h1.gameType = newGameType;
	h1.turn = newTurn;
	

	for(int i=0; i<h1.getSize(); i++)
	{
		fin >> line;
		for(int j=0; j<h1.getSize(); j++)
		{
			temp = line[j] - '0';
			h1.hexCells[i][j] = static_cast<cell>(temp);

			switch(temp)
			{
				case 0:
					h1.hexCells[i][j].setCellStatus(empty);
					break;
				case 1:
					h1.hexCells[i][j].setCellStatus(xLower);
					Hex::nonEmptyCells++;
					break;
				case 2:
					h1.hexCells[i][j].setCellStatus(oLower);
					Hex::nonEmptyCells++;
					break;
				case 3:
					h1.hexCells[i][j].setCellStatus(xCapital);
					Hex::nonEmptyCells++;
					break;
				case 4:
					h1.hexCells[i][j].setCellStatus(oCapital);
					Hex::nonEmptyCells++;
					break;
			}
		}
	}


	// draw the board
	cout << h1 << endl;

	return fin;

}


// ===================== UNDO OPERATIONS ================== //

Hex& Hex::operator -- ()
{
	counter--;
	hexCells[previousMoves[counter][0]][previousMoves[counter][1]] = empty;

	if(turn == 0)
		turn = 1;
	else
		turn = 0;

	return *this;
}

Hex Hex::operator --(int)
{
	Hex temp = *this;
	--(*this);
	return temp;
}

// =========================== DRAWING BOARD =============================== //

ostream& operator << (ostream& out, Hex &h1)
{
	// header
	out << "  ";
	for(int i=0; i<h1.getSize(); i++)
	{
		out << static_cast<char>(97 + i) << " ";
	}
	out << "\n";

	for(int i=0; i<h1.getSize(); i++)
	{
		// numbers
		out << i+1 << " ";

		// indentation
		for(int indent=0; indent<=i; indent++)
			out << " ";

		for(int j=0; j<h1.getSize(); j++)
		{
			out << static_cast<char>( h1.hexCells[i][j].getCellStatus() ) << " ";
		}
		out << "\n";
	}


	return out;
}

// ============================= FOR CALCULATING SCORE ========================= //

int Hex::calculateScore()
{
	int **visited = nullptr;
	int value;
	int score = 0;

	int turn = getTurn();

	if(turn == 0)
	{
		// x
		for(int i=0; i<getSize(); i++)
		{
			for(int j=0; j<getSize(); j++)
			{
				if(hexCells[i][j].getCellStatus() == xLower)
				{
					visited = initVisited(visited);
					value = scoreHelper(visited, i, j, xLower);
					if(value > score)
						score = value;
				}

			}
		}

	}else
	{
		// o
		for(int i=0; i<getSize(); i++)
		{
			for(int j=0; j<getSize(); j++)
			{
				if(hexCells[i][j].getCellStatus() == oLower)
				{
					visited = initVisited(visited);
					value = scoreHelper(visited, i, j, oLower);
					if(value > score)
						score = value;
				}
			}
		}
	}

	return score;

}

int Hex::scoreHelper(int** visited, int xPos, int yPos, cell c)
{
	if(xPos >= getSize() || xPos < 0 || yPos >= getSize() || yPos < 0)
		return 0;

	int temp_x, temp_y;
	int total = 0;

	int maximum = 0;

	if(c == xLower)
	{
		// first two is +2, last two is +1
		int directionX[4][2] = {{0,1}, {-1,1}, {-1,0}, {1,0}};
		for(int i=0; i<4; i++)
		{
			total = 0;

			temp_x = xPos + directionX[i][0];
			temp_y = yPos + directionX[i][1];
			if(temp_x >= getSize() || temp_x < 0 || temp_y >= getSize() || temp_y < 0 || visited[temp_x][temp_y] == 1)
				continue;


			if(i == 0 || i == 1)
			{
				// +2 points
				if(hexCells[temp_x][temp_y].getCellStatus() == c)
				{
					visited[temp_x][temp_y] = 1;
					total = 2 + scoreHelper(visited, temp_x, temp_y, c);
					if(total > maximum)
						maximum = total;
				}
			}else
			{
				// +1 points
				if(hexCells[temp_x][temp_y].getCellStatus() == c)
				{
					visited[temp_x][temp_y] = 1;
					total = 1 + scoreHelper(visited, temp_x, temp_y, c);
					if(total > maximum)
						maximum = total;
				}
			}

		}


	}else
	{
		// first two is +2, last two is +1
		int directionO[4][2] = {{1,0}, {1,-1}, {0,-1}, {0,1}};
		for(int i=0; i<4; i++)
		{
			total = 0;

			temp_x = xPos + directionO[i][0];
			temp_y = yPos + directionO[i][1];
			if(temp_x >= getSize() || temp_x < 0 || temp_y >= getSize() || temp_y < 0 || visited[temp_x][temp_y] == 1)
				continue;


			if(i == 0 || i == 1)
			{
				// +2 points
				if(hexCells[temp_x][temp_y].getCellStatus() == c)
				{
					visited[temp_x][temp_y] = 1;
					total = 2 + scoreHelper(visited, temp_x, temp_y, c);
					if(total > maximum)
						maximum = total;
				}
			}else
			{
				// +1 points
				if(hexCells[temp_x][temp_y].getCellStatus() == c)
				{
					visited[temp_x][temp_y] = 1;
					total = 1 + scoreHelper(visited, temp_x, temp_y, c);
					if(total > maximum)
						maximum = total;
				}
			}

		}

	}


	return maximum;
}
