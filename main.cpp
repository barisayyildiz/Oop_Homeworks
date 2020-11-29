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
	unsigned int index;
	unsigned int index2;
	int cmp;

	string s1 = "board1.txt", s2 = "board2.txt";

	gameVector.push_back(Hex(6, 0));
	gameVector.push_back(Hex(8, 0));
	gameVector.push_back(Hex(10, 0));
	gameVector.push_back(Hex(12, 0, s1));
	gameVector.push_back(Hex(6, 0, s2));


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

			// clears buffer
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

			// clears buffer
			cin.ignore(1000, '\n');

			if(index >= gameVector.size() || index2 >= gameVector.size())
			{
				cerr << "Wrong index number..." << endl;
				continue;
			}

			// cmp = gameVector[index].compare(gameVector[index2]);

			cmp = gameVector[index] == gameVector[index2];

			if(cmp == 1)
				cout << "\nThe board with the index " << index << " has more marked cells for the user" << endl;
			else
				cout << "\nThe board with the index " << index2 << " has more marked cells for the user" << endl; 


		}else if(input == 'q')
		{
			mainLoop = false;
		}else
		{
			cerr << "Invalid input, try again..." << endl;
		}

	}


	cout << gameVector[0] << endl;


	return 0;
}