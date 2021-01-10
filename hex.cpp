#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "hex.h"

using namespace std;

namespace myNamespace{

	AbstractHex::Cell::Cell(cell c) : cellStatus(c)
	{/*left empty*/}

	int AbstractHex::nonEmptyCells = 0;

	HexArray1D::HexArray1D() : size(0), turn(0), counter(0), gameStatus(true), previousMoves(nullptr), cap(10), hexCells(nullptr)
	{
		// gets user input
		playGame();
		
		initHexCells();

		previousMoves = initPreviousMoves();

		// main game loop
		gameLoop();

	}	


	void HexArray1D::playGame()
	{
		// ERROR HANDLING YAP!!!!
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

	int** HexArray1D::initPreviousMoves()
	{
		int **temp = nullptr;
		temp = new int*[cap];

		for(int i=0; i<cap; i++)
			temp[i] = new int[2];

		return temp;
	}

	void HexArray1D::initHexCells()
	{
		hexCells = (AbstractHex::Cell*)malloc(sizeof(AbstractHex::Cell) * size * size);

		for(int i=0; i<size*size; i++)
		{
			hexCells[i].setCellStatus(empty);
		}

	}

	void HexArray1D::print() const
	{
		// header
		cout << "  ";
		for(int i=0; i<getSize(); i++)
		{
			cout << static_cast<char>(97 + i) << " ";
		}
		cout << "\n";

		int iter = 0;

		for(int i=0; i<getSize(); i++)
		{
			// numbers
			cout << i+1 << " ";

			// indentation
			for(int indent=0; indent<=i; indent++)
				cout << " ";

			while(iter/getSize() == i)
			{
				cout << static_cast<char>(hexCells[iter++].getCellStatus() ) << " ";
			}

			cout << "\n";
		}
	}

	bool HexArray1D::isEnd()
	{
		int **visited = nullptr;
		visited = initVisited(visited);

		if(turn == 0) // x, left to right
		{
			for(int i=0; i<size; i++)
			{
				initVisited(visited);

				if(hexCells[i*size].getCellStatus() == xLower && didSomebodyWin(visited, i, 0))
					return true;
			}
			
		}else
		{
			for(int i=0; i<size; i++)
			{
				initVisited(visited);
				if(hexCells[i+size].getCellStatus() == oLower && didSomebodyWin(visited, 0, i))
					return true;
			}
		}


		// deleting dynamic visited array
		for(int i=0; i<size; i++)
		{
			delete[] visited[i];
		}
		delete[] visited;

		return false;

	}

	int** HexArray1D::initVisited(int **visited)
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

	int HexArray1D::didSomebodyWin(int **visited, int xPos, int yPos)
	{
		int tempX = xPos, tempY = yPos;
		int moveRange[6][2] = {{-1,0}, {0,1}, {1,0}, {0,-1}, {-1,1}, {1,-1}};

		if(turn == 0)
		{
			// X's turn
			if(yPos == size-1)
			{
				// hexCells[xPos][yPos].setCellStatus(xCapital);
				hexCells[size * xPos + yPos].setCellStatus(xCapital);
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
						// hexCells[xPos][yPos].setCellStatus(xCapital);
						hexCells[size * xPos + yPos].setCellStatus(xCapital);
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
				// hexCells[xPos][yPos] = oCapital;
				hexCells[size * xPos + yPos].setCellStatus(oCapital);
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
						// hexCells[xPos][yPos].setCellStatus(oCapital);
						hexCells[size * xPos + yPos].setCellStatus(oCapital);
						return 1;
					}
				}
			}
			return 0;
		}

	}

	int HexArray1D::isMoveable(int **visited, int xPos, int yPos)
	{
		if(turn == 0)
		{
			// if(hexCells[xPos][yPos].getCellStatus() == xLower && visited[xPos][yPos] == 0)
			// 	return 1;
			if(hexCells[xPos * size + yPos].getCellStatus() == xLower && visited[xPos][yPos] == 0)
				return 1;
		}else
		{
			// if(hexCells[xPos][yPos].getCellStatus() == oLower && visited[xPos][yPos] == 0)
			// 	return 1;
			if(hexCells[xPos * size + yPos].getCellStatus() == oLower && visited[xPos][yPos] == 0)
				return 1;
		}

		return 0;
	}


	AbstractHex::Cell HexArray1D::play(AbstractHex::Cell c1)
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

		previousMoves[counter][0] = c1.getX();
		previousMoves[counter][1] = c1.getY();

		counter++;
		nonEmptyCells++;

		if(getTurn() == 0)
		{
			// hexCells[c1.getX()][c1.getY()].setCellStatus(xLower);
			hexCells[c1.getX() * size + c1.getY()].setCellStatus(xLower);
		}
		else
		{
			// hexCells[c1.getX()][c1.getY()].setCellStatus(oLower);
			hexCells[c1.getX() * size + c1.getY()].setCellStatus(oLower);
		}

		return hexCells[c1.getX() * size + c1.getY()];

	}


	int HexArray1D::getUserInput(string input, string &filename, int &xPos, int &yPos)
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

	void HexArray1D::gameLoop()
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

				cout << "Please enter your move or command (ex : A 3 or SAVE/LOAD yourfilename.txt or QUIT or UNDO or SCORE) : ";
				getline( cin, s1);

				input = getUserInput(s1, s2, xPos, yPos);

				if(input == 0)
				{
					cerr << "Invalid input..." << endl;
					continue;
				}else if(input == 2)
				{
					// // load the board

					readFromFile(s2);

					cout << "Here is the new board : " << endl;
					print();

					// ifstream fin;
					// fin.open(s2);
					// fin >> (*this);
					// fin.close();
					
					// cout << "The new board is : " << endl;
					// cout << *this << endl;

					continue;
				}else if(input == 3)
				{
					// // save the board

					writeToFile(s2);
					cout << "The board information is saved to the file " << s2 << "..." << endl;

					// ofstream fout;
					// fout.open(s2);
					// fout << (*this);
					// fout.close();

					// cout << "The board information is saved to the file " << s2 << "..." << endl;

					cout << "qweqweqe" << endl;
					continue;
				}else if(input == 4)
				{
					cout << "Leaving the game..." << endl;
					return;

				}else if(input == 5)
				{
					// if(getCounter() <= 0)
					// {
					// 	cout << "Cannot undo..." << endl << endl;
					// 	continue;
					// }

					// --(*this);
					// // human vs bot
					// // if the user is playing against the computer, take two step back
					// if(getGameType() == 1 && getCounter() != 0)
					// {
					// 	--(*this);
					// }

					// // also can be done with
					// // (*this)--;
					// cout << "Board, after undoing : " << endl << endl;

					// // draw the board
					// cout << *this << endl;
					
					continue;
				}else if(input == 6)
				{
					// cout << "Active user's score is : " << calculateScore() << endl;
					continue;
				}

				// out of border
				if(xPos < 0 || xPos >= size || yPos < 0 || yPos >= size)
				{
					cerr << "Out of border..." << endl;
					continue;
				}

				if(hexCells[xPos * size + yPos].getCellStatus() != empty)
				{
					cerr << "Position is not empty" << endl;
					continue;
				}

				// if(hexCells[xPos][yPos].getCellStatus() != empty)
				// {
				// 	cerr << "Position is not empty" << endl;
				// 	continue;
				// }


				// makes move, increases the counter
				// play(xPos, yPos);
				temp.setX(xPos);
				temp.setY(yPos);
				play(temp);

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

	// helper function for file input output
	int HexArray1D::orderChar(char c)
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


	void HexArray1D::writeToFile(const string &filename)
	{
		char temp;

		ofstream fout;

		fout.open(filename);

		fout << getSize() << endl;
		fout << getCounter() << endl;
		fout << getGameType() << endl;
		fout << getTurn() << endl;

		int iter = 0;

		for(int i=0; i<getSize(); i++)
		{

			while(iter/getSize() == i)
			{
				temp = static_cast<char>(hexCells[iter++].getCellStatus() );
				fout << orderChar(temp);
			}

			fout << endl;			
		}

		// save cap
		fout << getCap() << endl;

		// save previous moves
		for(int i=0; i<getCounter(); i++)
		{
			fout << previousMoves[i][0];
			fout << previousMoves[i][1] << endl;
		}

		fout.close();

	}

	void HexArray1D::readFromFile(const string &filename)
	{
		int temp;
		int newSize, newCounter, newGameType, newTurn, newCap;

		// we need to adjust nonEmptyCells
		HexArray1D::nonEmptyCells -= getCounter();

		string line;

		ifstream fin;
		fin.open(filename);

		if(!fin)
		{
			cerr << "No such file exists...\n\n";
			return;
		}

		fin >> newSize;
		fin >> newCounter;
		fin >> newGameType;
		fin >> newTurn;

		// free hexCells
		free(hexCells);

		// for(int i=0; i<h1.getSize(); i++)
		// {
		// 	delete[] h1.hexCells[i];
		// }
		// delete[] h1.hexCells;

		size = newSize;
		counter = newCounter;
		gameType = newGameType;
		turn = newTurn;

		// hexCells = (AbstractHex::Cell*)malloc(sizeof(AbstractHex::Cell) * newSize * newSize);
		initHexCells();

		for(int i=0; i<getSize(); i++)
		{
			fin >> line;
			for(int j=0; j<getSize(); j++)
			{
				temp = line[j] - '0';
				hexCells[i * size + j] = static_cast<cell>(temp);

				switch(temp)
				{
					case 0:
						hexCells[i * size + j].setCellStatus(empty);
						break;
					case 1:
						hexCells[i * size + j].setCellStatus(xLower);
						HexArray1D::nonEmptyCells++;
						break;
					case 2:
						hexCells[i * size + j].setCellStatus(oLower);
						HexArray1D::nonEmptyCells++;
						break;
					case 3:
						hexCells[i * size + j].setCellStatus(xCapital);
						HexArray1D::nonEmptyCells++;
						break;
					case 4:
						hexCells[i * size + j].setCellStatus(oCapital);
						HexArray1D::nonEmptyCells++;
						break;
				}
			}
		}

		// delete previous moves array
		for(int i=0; i<cap; i++)
		{
			delete[] previousMoves[i];
		}
		delete[] previousMoves;
		previousMoves = nullptr;

		// load cap
		fin >> newCap;
		cap = newCap;

		// load the new previousMoves
		previousMoves = initPreviousMoves();

		for(int i=0; i<getCounter(); i++)
		{
			fin >> line;
			previousMoves[i][0] = line[0] - '0';
			previousMoves[i][1] = line[1] - '0';
		}

	}

	// for AI
	AbstractHex::Cell HexArray1D::play()
	{
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
		hexCells[xPos * size + yPos].setCellStatus(xLower);

		return hexCells[xPos * size + yPos];

	}

	void HexArray1D::calculateBestMove(int &xPos, int &yPos)
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
				if(hexCells[i * size + j].getCellStatus() == oLower)
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
		if(hexCells[center[0] * size + center[1]].getCellStatus() == empty)
		{
			xPos = center[0];
			yPos = center[1];
			return;
		}

		// if it is not, try to find the closest point
		int direction[4][2] = {{0,1}, {1,0}, {0,-1}, {-1,0}};
		int turn = 0;

		while(hexCells[center[0] * size + center[1]].getCellStatus() != empty)
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


	void HexArray1D::centerofGravity(int *center, int totalX, int totalY, int increment)
	{
		int x = totalX / increment;
		int y = totalY / increment;

		center[0] = x;
		center[1] = y;

		return;
	}







	// assignment operator
	HexArray1D& HexArray1D::operator = (const HexArray1D& h1){

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
			free(hexCells);
		}

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
				hexCells[i * size + j] = h1.hexCells[i * size + j];
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
	HexArray1D::HexArray1D(const HexArray1D& h1){

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
				hexCells[i * size + j] = h1.hexCells[i * size + j];
			}
		}

		for(int i=0; i<counter; i++)
		{
			previousMoves[i][0] = h1.previousMoves[i][0];
			previousMoves[i][1] = h1.previousMoves[i][1];
		}

	}

	// destructor
	HexArray1D::~HexArray1D(){
		cout << "~destructor" << endl;

		if(previousMoves != nullptr)
		{
			for(int i=0; i<cap; i++)
			{
				delete[] previousMoves[i];
			}
			delete[] previousMoves;
		}

		// I have used malloc and free, because we were told to use one dimensional dynamic 'C array' for the hexCells
		if(hexCells != nullptr)
			free(hexCells);

	}



	


	void HexArray1D::reset()
	{
		cout << "reset function" << endl;
	}

	void HexArray1D::setSize()
	{
		cout << "setSize function" << endl;
	}

	// AbstractHex::Cell HexArray1D::play(AbstractHex::Cell c1)
	// {
	// 	return c1;
	// }

	// bool isEnd()const;
	// Cell operator()(int x, int y)const;

	AbstractHex::Cell HexArray1D::operator()(int x, int y)const
	{
		AbstractHex::Cell temp;
		return temp;
	}

	bool HexArray1D::operator==(const AbstractHex &aHex)const
	{
		return true;
	}

	AbstractHex::Cell HexArray1D::lastMove()
	{
		AbstractHex::Cell temp;
		return temp;

	}

	int HexArray1D::numberOfMoves()const
	{
		return 0;
	}

}
