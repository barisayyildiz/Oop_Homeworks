#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "hexbase.h"
#include "hexarray.h"

using namespace std;

namespace hex
{
	
	AbstractHex::Cell::Cell(cell c) : cellStatus(c)
	{/*left empty*/}

	int AbstractHex::nonEmptyCells = 0;

	int AbstractHex::getUserInput(string input, string &filename, int &xPos, int &yPos)
	{
		// return values : 
		// 0 -> invalid input, 1 -> valid position,  2 -> LOAD command, 3 -> SAVE command, 4 -> QUIT, 5 -> UNDO, 6 -> SCORE

		string tokens[5];
		int counter = 0;

		// sstream type
		stringstream stream(input);

		string token;


		while(getline(stream, token, ' '))
		{
			tokens[counter++] = token;
		}


		if(counter == 1)
		{
			if(tokens[0] == "QUIT")
			{
				return 4;
			}else if(tokens[0] == "UNDO")
			{
				return 5;
			}else if(tokens[0] == "SCORE")
			{
				return 6;
			}else if(tokens[0] == "RESIZE")
			{
				return 7;
			}

		}else if(counter == 2)
		{
			if(tokens[0] == "SAVE")
			{
				filename = tokens[1];
				return 3;
			}else if(tokens[0] == "LOAD")
			{
				filename = tokens[1];
				return 2;
			}else if(tokens[0].length() == 1)
			{
				// lower case
				if(tokens[0][0] >= 'a')
					yPos = tokens[0][0] - 'a';
				
				//upper case
				else if(tokens[0][0] >= 'A')
					yPos = tokens[0][0] - 'A';

				if(tokens[1][0] < '0' || tokens[1].length() > 3)
					return 0;

				xPos = tokens[1][0] - '0';

				if(tokens[1].length() == 2)
				{
					xPos *= 10;
					xPos += (tokens[1][1] - '0');
				}

				xPos--;

				return 1;

			}

		}

		return 0;

	}

}
