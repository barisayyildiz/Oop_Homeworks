#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#include "hex.h"

using namespace std;


int main()
{

	vector < Hex > gameVector;

	bool mainLoop = true;
	char input;
	unsigned index;
	unsigned index2;




	cout << "Welcome to the HEX game..." << endl << endl;


	while(mainLoop)
	{
		cout << "\nPress:" << endl;
		cout << "1 : to create a new game" << endl;
		cout << "2 : to continue an active game" << endl;
		cout << "3 : to compare two active games" << endl;
		cout << "q : to exit" << endl << endl;

		cin >> input;


		if(input == '1')
		{
			gameVector.push_back(Hex());

			// if the latest game is terminated
			if(gameVector[gameVector.size()-1].getGameStatus() == false)
			{
				// remove it from active games
				gameVector.pop_back();
			}

		}else if(input == '2')
		{
			cout << "There are " << gameVector.size() << " active games" << endl;

			if(gameVector.size() ==  0)
			{
				cout << "We need at least 1 game to continue, please create a game before..." << endl;
				continue;
			}

			cout << "Which game do you want to continue, (indexing starts at 0) (ex. 0): ";
			cin >> index;

			cin.ignore(1000, '\n');

			if(index >= gameVector.size())
			{
				cerr << "Wrong index number..." << endl;
				continue;
			}

			gameVector[index].gameLoop();


		}else if(input == '3')
		{
			cout << "There are " << gameVector.size() << " active games" << endl;

			if(gameVector.size() < 2)
			{
				cout << "We need at least 2 games to compare, please create more..." << endl;
				continue;
			}

			cout << "Which two games do you want to compare, (indexing starts at 0) (ex. 0 1) : ";
			cin >> index >> index2;

			cin.ignore(1000, '\n');

			if(index >= gameVector.size() || index2 >= gameVector.size())
			{
				cerr << "Wrong index number..." << endl;
				continue;
			}

			cout << gameVector[index].compare(gameVector[index2]);


		}else if(input == 'q')
		{
			mainLoop = false;
		}else
		{
			cerr << "Invalid input, try again..." << endl;
		}

	}




	// cout << "Welcome to the HEX game" << endl << endl;

	// Hex h1;


	// h1.gameLoop();

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