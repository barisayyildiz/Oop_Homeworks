#include <iostream>
#include <vector>

#include "hex.h"

using namespace std;


int main()
{
	Hex h1;
	h1.play();
	h1.play(2,2);
	h1.play();


	h1.drawBoard();

	
	// cell c = xLower;
	// h1.getCell(0,0).setStatus(xLower);

	// h1.setStatus(0,0,xCapital);

	// h1.getAdress()[0][0].setStatus(xLower);
	// cout << h1.getAdress()[0][0].getStatus() << endl;
	// cout << h1.getAdress()[1][0].getStatus() << endl;

	// h1.drawBoard();


	return 0;
}