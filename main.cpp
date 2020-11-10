#include <iostream>
#include <vector>

#include "hex.h"

using namespace std;


int main()
{
	Hex h1;
	
	// cell c = xLower;
	// h1.getCell(0,0).setStatus(xLower);

	// h1.setStatus(0,0,xCapital);

	h1.getCell()[0][0].setStatus(xLower);
	cout << h1.getCell()[0][0].getStatus() << endl;
	cout << h1.getCell()[1][0].getStatus() << endl;



	return 0;
}