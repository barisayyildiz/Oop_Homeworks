#include <iostream>
#include <vector>
#include <string>

#include "hex.h"

using namespace std;



Hex::Cell::Cell(cell s): status(s)
{/*left empty*/}

cell Hex::Cell::getStatus() const
{
	return status;
}

void Hex::Cell::setStatus(cell s)
{
	status = s;
}


Hex::Hex()
{
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

/*

	cell getStatus();
public:
	Hex();
	Cell getCell();
};

*/
