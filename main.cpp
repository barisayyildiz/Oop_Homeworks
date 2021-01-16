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



// bool isValidSequence(vector<AbstractHex*> arr)
// {
// 	if(arr.size() == 0 || arr.size() == 1)
// 		return true;


// 	vector<AbstractHex::Cell> moves;

// 	int initSize = arr[0]->getSize();
	
// 	// for difference
// 	int diffCounter = 0;
// 	AbstractHex::Cell temp;

// 	for(int i=0; i<initSize; i++)
// 	{
// 		for(int j=0; j<initSize; j++)
// 		{
// 			if(arr[0]->operator()(i,j).getCellStatus() != empty)
// 			{
// 				moves.push_back(AbstractHex::Cell(arr[0]->operator()(i,j).getCellStatus()));
// 				moves[moves.size()-1].setX(i);
// 				moves[moves.size()-1].setY(j);
// 			}
// 		}
// 	}

// 	for(unsigned int i=1; i<arr.size(); i++)
// 	{
// 		if(initSize != arr[i]->getSize() || (arr[i-1]->getCounter() != arr[i]->getCounter() - 1))
// 			return false;

// 		for(unsigned int j=0; j<moves.size(); j++)
// 		{

// 			if(arr[i]->operator()(moves[j].getX(), moves[j].getY()).getCellStatus() != moves[j].getCellStatus())
// 			{
// 				if(diffCounter == 1 || arr[i-1]->getCounter() == 1)
// 					return false;
				
// 				diffCounter++;

// 				temp.setX(moves[j].getX());
// 				temp.setY(moves[j].getY());
// 				temp.setCellStatus(moves[j].getCellStatus());
// 			}
// 		}

// 		moves.push_back(temp);

// 	}

// 	return true;	

// }

int main()
{
	vector < AbstractHex* > gameVector;

	bool mainLoop = true;
	char input;
	unsigned int index;
	unsigned int index2;
	int cmp;

	string s1 = "board1.txt", s2 = "board2.txt";

	// For testing
	try
	{
		gameVector.push_back(new HexArray1D());
		gameVector.push_back(new HexVector());

	}catch(const InvalidSize &err)
	{
		cerr << err.what() << endl;

	}catch(const InvalidInput &err)
	{
		cerr << err.what() << endl;
	}

	bool val = isValidSequence(gameVector);
	cout << "val : " << val << endl;



	cout << "Welcome to the HEX game..." << endl << endl;


	while(mainLoop)
	{
		cout << "\nPress:" << endl;
		cout << "1 : to create a new game" << endl;
		cout << "2 : to continue an active game" << endl;
		cout << "3 : to compare two active games" << endl;
		cout << "4 : to get non empty cells for all the games" << endl;
		cout << "q : to exit" << endl << endl;

		cin >> input;


		if(input == '1')
		{
			while(1)
			{
				cout << "1 : to create a HexArray1D object"	<< endl;
				cout << "2 : to create a HexVector object" << endl;
				cout << "3 : to create a HexAdapter object (deque will be given)" << endl;

				cin >> input;
				
				// clears buffer
				cin.ignore(1000, '\n');
				
				if(input != '1' && input != '2' && input != '3')
				{
					cout << "Invalid input..." << endl << endl;
					continue;
				}
				break;
			}

			if(input == '1')
			{
				gameVector.push_back(new HexArray1D());
			}else if(input == '2')
			{
				gameVector.push_back(new HexVector());
			}else if(input == '3')
			{
				gameVector.push_back(new HexAdapter<deque>);
			}

			// if the latest game is terminated
			if(gameVector[gameVector.size()-1]->getGameStatus() == false)
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

			gameVector[index]->gameLoop();

			// if the game is terminated
			if(gameVector[index]->getGameStatus() == false)
			{
				// if the current game is over
				for(unsigned int i=index; i<gameVector.size() - 1; i++)
				{
					gameVector[index] = gameVector[index+1];
				}
				gameVector.resize(gameVector.size() - 1);
			}


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

			// cmp = (gameVector[index] == gameVector[index2]);
			cmp = (*gameVector[index] == gameVector[index2]);

			if(cmp == 1)
				cout << "\nThe games are equal..." << endl << endl;
			else
				cout << "\nThe games are not equal..." << endl << endl;


		}else if(input == '4')
		{
			cout << "Total of non empty cells : " << AbstractHex::getNonEmptyCells() << endl << endl;

		}else if(input == 'q')
		{
			mainLoop = false;
		}else
		{
			cerr << "Invalid input, try again..." << endl;
		}

	}

	return 0;
}
