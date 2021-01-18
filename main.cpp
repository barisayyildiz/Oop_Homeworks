#include <iostream>
#include <vector>
#include <deque>
#include <exception>

#include "./headers/hexbase.h"
#include "./headers/hexarray.h"
#include "./headers/hexvector.h"
#include "./headers/hexadapter.h"

#include "./src/hexadapter.cpp"
#include "./headers/exception.h"

#include "./headers/globals.h"

using namespace std;
using namespace hex;
using namespace excNamespace;


int main()
{
	vector < AbstractHex* > gameVector;

	AbstractHex::Cell c1(empty);
	bool mainLoop = true;
	string input;
	unsigned int index;
	unsigned int index2;
	int cmp;
	bool val;

	string s1 = "board1.txt", s2 = "board2.txt";

	// For testing
	try
	{
		gameVector.push_back(new HexArray1D(8,0));
		gameVector.push_back(new HexVector(7,1));
		gameVector.push_back(new HexAdapter<deque>(10,0,s1));
		gameVector.push_back(new HexAdapter<vector>(14,1,s2));

	}catch(const InvalidSize &err)
	{
		cerr << err.what() << endl;

	}catch(const InvalidInput &err)
	{
		cerr << err.what() << endl;
	}

	// val = isValidSequence(gameVector);
	// cout << "val : " << val << endl;

	// gameVector.push_back(new HexArray1D(8,0));

	// try
	// {
	// 	gameVector[0]->readFromFile("nonproper.txt");
	// }
	// catch(const std::exception& e)
	// {
	// 	std::cerr << e.what() << '\n';
	// }


	cout << "Welcome to the HEX game..." << endl << endl;


	while(mainLoop)
	{
		cout << "\nPress:" << endl;
		cout << "1 : to create a new game with HexArray1D" << endl;
		cout << "2 : to create a new game with HexVector" << endl;
		cout << "3 : to create a new game with HexAdapter<vector>" << endl;
		cout << "4 : to create a new game with HexAdapter<deque>" << endl;
		cout << "5 : to continue an active game" << endl;
		cout << "6 : to compare two active games" << endl;
		cout << "7 : to get non empty cells for all the games" << endl;
		cout << "8 : to test global function" << endl;
		cout << "9 : to test operator()" << endl;
		cout << "10 : to get last move of a game" << endl;
		cout << "11 : to test numberOfMoves function" << endl;
		
		cout << "q : to exit" << endl << endl;


		try
		{
			cin >> input;
			cin.ignore(1000, '\n');

			checkUserInput(input);

		}catch(const InvalidInput &err)
		{
			cout << err.what() << endl << endl;
			continue;
		}

		if(input == "1")
		{
			gameVector.push_back(new HexArray1D());
		}else if(input == "2")
		{
			gameVector.push_back(new HexVector());
		}else if(input == "3")
		{
			gameVector.push_back(new HexAdapter<vector>());
		}else if(input == "4")
		{
			gameVector.push_back(new HexAdapter<deque>());
		}else if(input == "5")
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

			gameVector[index]->gameLoop();
		}else if(input == "6")
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

			// cmp = (gameVector[index] == gameVector[index2]);
			cmp = (*gameVector[index] == gameVector[index2]);

			if(cmp == 1)
				cout << "\nThe games are equal..." << endl << endl;
			else
				cout << "\nThe games are not equal..." << endl << endl;

		}else if(input == "7")
		{
			cout << "Total of non empty cells : " << AbstractHex::getNonEmptyCells() << endl << endl;
		
		}else if(input == "8")
		{
			testGlobalFuncton();
		}else if(input == "9")
		{
			cout << "There are " << gameVector.size() << " active games" << endl;

			if(gameVector.size() == 0)
			{
				cerr << "At least one game needed..." << endl << endl;
				continue;
			}

			cout << "Enter game index , (indexing starts at 0): ";
			cin >> index;

			cin.ignore(1000, '\n');

			if(index >= gameVector.size())
			{
				cerr << "Wrong index number..." << endl << endl;
				continue;
			}

			cout << "For the game in gameVector[" << index << "] : " << endl;
			cout << "At index (0,0), ASCII val -> " << gameVector[index]->operator()(0,0).getCellStatus() << endl;
			cout << "At index (1,1), ASCII val -> " << gameVector[index]->operator()(1,1).getCellStatus() << endl;
			cout << "At index (2,2), ASCII val -> " << gameVector[index]->operator()(2,2).getCellStatus() << endl;

			cout << "Only for demostration purposes, I have used operator() inside global function named 'isValidSequence'" << endl << endl;

		}else if(input == "10")
		{
			cout << "There are " << gameVector.size() << " active games" << endl;

			if(gameVector.size() == 0)
			{
				cerr << "At least one game needed..." << endl << endl;
				continue;
			}

			cout << "Enter game index, (indexing starts at 0) : ";
			cin >> index;

			cin.ignore(1000, '\n');

			if(index >= gameVector.size())
			{
				cerr << "Wrong index number..." << endl << endl;
				continue;
			}

			try
			{
				c1 = gameVector[index]->lastMove();

				cout << "For the game in gameVector[" << index << "] : " << endl;
				cout << "Last move, x position : " << c1.getX() << endl;
				cout << "Last move, y position : " << c1.getY() << endl;

			}
			catch(const CounterZero& err)
			{
				cerr << err.what() << endl << endl;
			}

		}else if(input == "11")
		{
			cout << "There are " << gameVector.size() << " active games" << endl;
			
			if(gameVector.size() == 0)
			{
				cerr << "At least one game needed..." << endl << endl;
				continue;
			}

			cout << "Enter game index, (indexing starts at 0) : ";
			cin >> index;

			cin.ignore(1000, '\n');

			if(index >= gameVector.size())
			{
				cerr << "Wrong index number..." << endl << endl;
				continue;
			}

			cout << "For the game in gameVector[" << index << "] : " << endl;
			cout << "Number of moves : " << gameVector[index]->getCounter() << endl;


		}else if(input == "q")
		{
			mainLoop = false;
		}

	}

	return 0;
}
