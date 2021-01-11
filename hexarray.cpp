#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "hexbase.h"
#include "hexarray.h"
#include "exception.h"

using namespace std;
using namespace excNamespace;

namespace hex{

	HexArray1D::HexArray1D() : AbstractHex() , previousMoves(nullptr), hexCells(nullptr)
	{
		// gets user input

		while(1)
		{
			try
			{
				playGame();
				break;
			}catch(const InvalidSize &err)
			{
				cerr << err.what() << endl << endl;
			}catch(const InvalidInput &err)
			{
				cerr << "Input should be 0  or 1" << endl;
			}
		}
		
		initHexCells();

		previousMoves = initPreviousMoves();

		// main game loop
		gameLoop();

	}	

	HexArray1D::HexArray1D(int s) : AbstractHex(), previousMoves(nullptr), hexCells(nullptr)
	{
		// ERROR HANDLING
		if(s < 6)
			throw InvalidSize();

		size = s;
		
		initHexCells();

		previousMoves = initPreviousMoves();
	}

	HexArray1D::HexArray1D(int s, int gT) : AbstractHex(), previousMoves(nullptr), hexCells(nullptr)
	{
		// error handling
		if(s < 6)
			throw InvalidSize();
		if(gT != 0 && gT != 1)
			throw InvalidInput();
		
		size = s;
		gameType = gT;


		initHexCells();

		previousMoves = initPreviousMoves();
	}

	HexArray1D::HexArray1D(int s, int gT, string &filename) : AbstractHex(), hexCells(nullptr), previousMoves(nullptr)
	{
		// error handling
		if(s < 6)
			throw InvalidSize();
		if(gT != 0 && gT != 1)
			throw InvalidInput();

		size = s;
		gameType = gT;

		initHexCells();

		previousMoves = initPreviousMoves();


		writeToFile(filename);

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



	void HexArray1D::playGame()
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
		// // out of border
		// if(xPos < 0 || xPos >= size || yPos < 0 || yPos >= size)
		// {
		// 	cerr << "Out of border..." << endl;
		// 	continue;
		// }

		// if(hexCells[xPos * size + yPos].getCellStatus() != empty)
		// {
		// 	cerr << "Position is not empty" << endl;
		// 	continue;
		// }

		// if(hexCells[xPos][yPos].getCellStatus() != empty)
		// {
		// 	cerr << "Position is not empty" << endl;
		// 	continue;
		// }

		// temp.setX(xPos);
		// temp.setY(yPos);

		// c1->temp


		if(c1.getX() < 0 || c1.getX() > size || c1.getY() < 0 || c1.getY() > size)
		{
			throw IndexError();

		}else if(hexCells[c1.getX() * size + c1.getY()].getCellStatus() != empty)
		{
			throw AllocatedCell();

		}


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
			// cerr << "No such file exists...\n\n";
			throw FileError();
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


	void HexArray1D::reset()
	{
		// cout << "reset function" << endl;

		if(previousMoves != nullptr)
		{
			for(int i=0; i<cap; i++)
			{
				delete[] previousMoves[i];
			}
			delete[] previousMoves;
		}
		previousMoves = nullptr;
		cap = 10;
		
		previousMoves = initPreviousMoves();

		if(hexCells != nullptr)
			free(hexCells);
	
		initHexCells();

		turn = 0;
		counter = 0;

	}

	void HexArray1D::setSize(int newSize)
	{
		if(newSize < 6)
		{
			throw InvalidSize();
		}

		size = newSize;

		reset();

		// AbstractHex::Cell *temp = (AbstractHex::Cell*)malloc(sizeof(AbstractHex::Cell) * newSize * newSize);

		// for(int i=0; i<size * size; i++)
		// {
		// 	temp[i] = hexCells[i];
		// }

		// for(int i=size*size; i<newSize * newSize; i++)
		// {
		// 	temp[i].setCellStatus(empty);
		// }
		
		// free(hexCells);

		// hexCells = temp;
		// size = newSize;

		// cout << "QWEQWEQWEQ" << endl;
	}





	// AbstractHex::Cell HexArray1D::play(AbstractHex::Cell c1)
	// {
	// 	return c1;
	// }

	// bool isEnd()const;
	// Cell operator()(int x, int y)const;

	AbstractHex::Cell HexArray1D::operator()(int x, int y)const
	{
		// ERROR HANDLING YAPILACAK

		if(x < 0 || x >= getSize() || y < 0 || y >= getSize())
		{
			cout << "out of border" << endl;
			exit(1);
		}

		return hexCells[x * getSize() + y];

	}

	bool HexArray1D::operator==(AbstractHex *aHex)
	{
		// HexArray1D* ptr = dynamic_cast<HexArray1D*>(aHex);

		// if(ptr)
		// {
		// 	if(size != aHex->getSize())
		// 		return false;
			
		// 	for(int i=0; i<size * size; i++)
		// 	{
		// 		if(hexCells[i].getCellStatus() != aHex->hexCells[i].getCellStatus())
		// 			return false;
		// 	}
		// }

		return true;


	}

	AbstractHex::Cell HexArray1D::lastMove()
	{
		// ERROR HANDLING!!!
		if(counter == 0)
			exit(1);

		return hexCells[counter-1];
	}

	int HexArray1D::numberOfMoves()const
	{
		return getCounter();
	}

	// ============================= FOR CALCULATING SCORE ========================= //

	int HexArray1D::calculateScore()
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
					if(hexCells[i * size + j].getCellStatus() == xLower)
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
					if(hexCells[i * size + j].getCellStatus() == oLower)
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

	int HexArray1D::scoreHelper(int** visited, int xPos, int yPos, cell c)
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
					if(hexCells[temp_x * size + temp_y].getCellStatus() == c)
					{
						visited[temp_x][temp_y] = 1;
						total = 2 + scoreHelper(visited, temp_x, temp_y, c);
						if(total > maximum)
							maximum = total;
					}
				}else
				{
					// +1 points
					if(hexCells[temp_x * size + temp_y].getCellStatus() == c)
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
					if(hexCells[temp_x * size + temp_y].getCellStatus() == c)
					{
						visited[temp_x][temp_y] = 1;
						total = 2 + scoreHelper(visited, temp_x, temp_y, c);
						if(total > maximum)
							maximum = total;
					}
				}else
				{
					// +1 points
					if(hexCells[temp_x * size + temp_y].getCellStatus() == c)
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


	void HexArray1D::undo()
	{
		// ERROR HANDLING
		if(getCounter() == 0)
		{
			// cout << "Cannot undo..." << endl;
			throw UndoError();
		}

		counter--;
		
		// make the last move empty
		hexCells[previousMoves[counter][0] * size + previousMoves[counter][1]] = empty;

		if(turn == 0)
			turn = 1;
		else
			turn = 0;
			
	}

}
