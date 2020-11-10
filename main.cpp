#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#include "hex.h"

using namespace std;


int main()
{
	Hex h1;


	h1.play();
	h1.play(0,0);
	h1.play();
	h1.play(1,0);
	h1.play();
	h1.play(2,0);
	h1.play();
	h1.play(3,0);
	h1.play();
	h1.play(4,0);
	h1.play();
	h1.play(5,0);

	h1.drawBoard();

	h1.loadBoard("board1.txt");

	// h1.play();
	// h1.play(1,1);
	// h1.play();
	// h1.play();
	// h1.play();
	// h1.play();
	// h1.play();
	// h1.play();
	// h1.play();
	// h1.play();
	// h1.play();
	// h1.play();
	// h1.play();
	// h1.play();
	// h1.play();
	// h1.play();
	// h1.play();
	

	
	// cell c = xLower;
	// h1.getCell(0,0).setStatus(xLower);

	// h1.setStatus(0,0,xCapital);

	// h1.getAdress()[0][0].setStatus(xLower);
	// cout << h1.getAdress()[0][0].getStatus() << endl;
	// cout << h1.getAdress()[1][0].getStatus() << endl;

	// h1.drawBoard();


	return 0;
}