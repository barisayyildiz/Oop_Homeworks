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


	// assignment operator
	HexArray1D& HexArray1D::operator = (const HexArray1D& h1){
		cout << "assignment operator" << endl;
		return *this;
	}

	// copy constructor
	HexArray1D::HexArray1D(const HexArray1D& h1){
		cout << "copy constructor" << endl;
	}

	// destructor
	HexArray1D::~HexArray1D(){
		cout << "destructor" << endl;
	}

	void HexArray1D::readFromFile()
	{
		cout << "readFromFile function" << endl;
	}

	void HexArray1D::writeToFile()const
	{
		cout << "writeToFile function" << endl;
	}

	void HexArray1D::reset()
	{
		cout << "reset function" << endl;
	}

	void HexArray1D::setSize()
	{
		cout << "setSize function" << endl;
	}

	AbstractHex::Cell HexArray1D::play()
	{
		AbstractHex::Cell temp;
		return temp;
	}

	AbstractHex::Cell HexArray1D::play(AbstractHex::Cell c1)
	{
		return c1;
	}

	// bool isEnd()const;
	// Cell operator()(int x, int y)const;

	bool HexArray1D::isEnd()const
	{
		return true;
	}

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
