#include <iostream>
#include <vector>
#include <deque>
#include <exception>

#include "../headers/hexbase.h"

using namespace std;
using namespace hex;

bool isValidSequence(vector<AbstractHex*> arr)
{
	if(arr.size() == 0 || arr.size() == 1)
		return true;


	vector<AbstractHex::Cell> moves;

	int initSize = arr[0]->getSize();
	
	// for difference
	int diffCounter = 0;
	AbstractHex::Cell temp;

	for(int i=0; i<initSize; i++)
	{
		for(int j=0; j<initSize; j++)
		{
			if(arr[0]->operator()(i,j).getCellStatus() != empty)
			{
				moves.push_back(AbstractHex::Cell(arr[0]->operator()(i,j).getCellStatus()));
				moves[moves.size()-1].setX(i);
				moves[moves.size()-1].setY(j);
			}
		}
	}

	for(unsigned int i=1; i<arr.size(); i++)
	{
		if(initSize != arr[i]->getSize() || (arr[i-1]->getCounter() != arr[i]->getCounter() - 1) || (arr[i-1]->getTurn() == arr[i]->getTurn()))
			return false;

		for(unsigned int j=0; j<moves.size(); j++)
		{

			if(arr[i]->operator()(moves[j].getX(), moves[j].getY()).getCellStatus() != moves[j].getCellStatus())
			{
				if(diffCounter == 1 || arr[i-1]->getCounter() == 1)
					return false;
				
				diffCounter++;

				temp.setX(moves[j].getX());
				temp.setY(moves[j].getY());
				temp.setCellStatus(moves[j].getCellStatus());
			}
		}

		moves.push_back(temp);

	}

	return true;	

}