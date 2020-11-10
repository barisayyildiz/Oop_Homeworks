#include <iostream>
#include <vector>
#include <string>

#include "hex.h"

using namespace std;



Hex::Cell::Cell(cell s): status(s)
{/*left empty*/}

cell Hex::Cell::getStatus()
{
	return status;
}

void Hex::Cell::setStatus(int xPos, int yPos, cell s)
{
	status = s;
}


Hex::Hex()
{
	hexCells.resize(5);
	for(int i=0; i<5; i++)
	{
		hexCells[i].resize(5);
	}

	for(int i=0; i<5; i++)
	{
		for(int j=0; j<5; j++)
		{
			hexCells[i][j].setStatus(empty);
		}
	}


	// initHexCells(5);
	// for(int i=0; i<2; i++)
	// {
	// 	hexCells[i] = vector <Cell> (2);

	// 	for(int j=0; j<2; j++)
	// 	{
	// 		hexCells[i][j].setStatus(empty);
	// 	}
	// }
}



Hex::Cell Hex::getCell(int xPos, int yPos)
{
	return hexCells[xPos][yPos];
}

Hex::Cell& Hex::getAdress(int xPos, int yPos)
{
	return hexCells[xPos][yPos];
}

// void Hex::func(int xPos, int yPos, cell s)
// {
// 	getCell(xPos, yPos).setStatus(s);	
// }

/*

	cell getStatus();
public:
	Hex();
	Cell getCell();
};

*/
