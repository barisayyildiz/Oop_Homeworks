#include <iostream>
#include <vector>
#include <exception>
#include "hexbase.h"
#include "hexvector.h"
#include "exception.h"

using namespace std;
using namespace hex;
using namespace excNamespace;

int main()
{
	vector < AbstractHex * > gameVector;

	gameVector.push_back(new HexVector());

	gameVector[0]->gameLoop();




}