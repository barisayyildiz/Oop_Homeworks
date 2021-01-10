#include <iostream>
#include <vector>
#include "hex.h"

using namespace std;
using namespace myNamespace;

int main()
{
	HexArray1D h1;

	cout << h1.getGameStatus() << endl;
	cout << h1.getSize() << endl;
	cout << h1.getCap() << endl;
	cout << h1.getCounter() << endl;	
	


	return 0;
}
