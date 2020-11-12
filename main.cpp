#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#include "hex.h"

using namespace std;


int main()
{

	bool mainLoop = true;

	vector < Hex > gameVector;

	cout << "Welcome to the HEX game" << endl << endl;

	Hex h1;


	h1.gameLoop();

	// gameVector.push_back(Hex());
	// gameVector.push_back(Hex());

	// cout << "0.index -> " << gameVector[0].getCounter() << endl;
	// cout << "1.index -> " << gameVector[1].getCounter() << endl;




	// Hex h1;



	// Hex h1;


	// h1.play();
	// h1.play(0,0);
	// h1.play();
	// h1.play(1,0);
	// h1.play();
	// h1.play(2,0);
	// h1.play();
	// h1.play(3,0);
	// // h1.play();
	// // h1.play(4,0);
	// // h1.play();
	// // h1.play(5,0);

	// cout << "non empty : " << Hex::getNonEmptyCells() << endl;

	// h1.drawBoard();

	// h1.loadBoard("board1.txt");

	// cout << "non empty : " << Hex::getNonEmptyCells() << endl;

	// Hex h2;
	// h2.play();
	// h2.play(0,0);
	// h2.play();
	// h2.play(1,0);

	// cout << "sonuc : " << h1.compare(h2) << endl;

	// // h1.play();
	// // h1.play(1,1);
	// // h1.play();
	// // h1.play();
	// // h1.play();
	// // h1.play();
	// // h1.play();
	// // h1.play();
	// // h1.play();
	// // h1.play();
	// // h1.play();
	// // h1.play();
	// // h1.play();
	// // h1.play();
	// // h1.play();
	// // h1.play();
	// // h1.play();
	

	
	// // cell c = xLower;
	// // h1.getCell(0,0).setStatus(xLower);

	// // h1.setStatus(0,0,xCapital);

	// // h1.getAdress()[0][0].setStatus(xLower);
	// // cout << h1.getAdress()[0][0].getStatus() << endl;
	// // cout << h1.getAdress()[1][0].getStatus() << endl;

	// // h1.drawBoard();


	return 0;
}