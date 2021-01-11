#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "hex.h"

using namespace std;

namespace myNamespace
{
	
	AbstractHex::Cell::Cell(cell c) : cellStatus(c)
	{/*left empty*/}

	int AbstractHex::nonEmptyCells = 0;

}
