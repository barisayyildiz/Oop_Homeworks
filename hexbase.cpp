#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "hexbase.h"
#include "hexarray.h"

using namespace std;

namespace hex
{
	
	AbstractHex::Cell::Cell(cell c) : cellStatus(c)
	{/*left empty*/}

	int AbstractHex::nonEmptyCells = 0;

}
