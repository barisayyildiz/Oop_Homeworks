#include <iostream>
#include <vector>
#include <deque>
#include <exception>

#include "../headers/hexbase.h"
#include "../headers/hexarray.h"
#include "../headers/hexvector.h"
#include "../headers/hexadapter.h"
#include "../headers/globals.h"

#include "./hexadapter.cpp"

#include "../headers/exception.h"

#include "../headers/hexbase.h"

using namespace std;
using namespace hex;
using namespace excNamespace;


void checkUserInput(const string& input)
{
	if(input != "1" && input != "2" && input != "3" && input != "4" && input != "5" && input != "6" &&
	input != "7" && input != "8" && input != "9" && input != "10" && input != "11" && input != "12" && input != "q")
	{
		throw InvalidInput();
	}
}

bool isValidSequence(vector<AbstractHex*> arr)
{
	
	cell stat;
	int xCounter, oCounter;

	for(unsigned int i=0; i<arr.size(); i++)
	{
		xCounter = 0;
		oCounter = 0;
		for(int x=0; x<arr[i]->getSize(); x++)
		{
			for(int y=0; y<arr[i]->getSize(); y++)
			{
				stat= arr[i]->operator()(x,y).getCellStatus();
				if(stat != empty && stat != xLower && stat != oLower && stat != xCapital && stat != oCapital)
				{
					return false;
				}

				if(stat == xLower)
				{
					xCounter++;
				}else if(stat == oLower)
				{
					oCounter++;
				}
			}
		}

	}

	if( (xCounter - oCounter > 1) || (xCounter - oCounter < -1) ) 
		return false;

	return true;

}

void testGlobalFuncton()
{
	bool val;
	vector<AbstractHex*> gameVector;

	gameVector.push_back(new HexArray1D(8,0));
	gameVector.push_back(new HexVector(12,1));
	gameVector.push_back(new HexAdapter<vector>(9,0));

	gameVector[2]->readFromFile("nonproper.txt");

	val = isValidSequence(gameVector);
	cout << "Is valid game : " << val << endl;

	cout << "-----------------" << endl;

	gameVector[2]->readFromFile("proper.txt");
	val = isValidSequence(gameVector);
	cout << "Is valid game : " << val << endl << endl;


}
