#include <iostream>
#include <string>

using namespace std;


void drawGrid(char (*grid)[6])
{
	// header
	cout << "  ";
	for(int i=0; i<6; i++)
	{
		cout << static_cast<char>(97 + i) << " ";
	}
	cout << "\n";




	for(int i=0; i<6; i++)
	{
		// rakamlar
		cout << i+1 << " ";

		// baştaki boşluklar
		for(int indent=0; indent<=i; indent++)
			cout << " ";

		for(int j=0; j<6; j++)
		{
			cout << grid[i][j] << " ";
		}
		cout << "\n";
	}
}

void initGrid(char (*grid)[6])
{

	for(int i=0; i<6; i++)
	{
		for(int j=0; j<6; j++)
		{
			grid[i][j] = '.';
		}
	}
}

int main()
{
	char grid[6][6];
	initGrid(grid);
	drawGrid(grid);

	int gameOver = 0, gameType;
	string move;

	while(1)
	{
		cout << "Please enter 0 for 2-player and 1 for 1 player mod" << endl;
		cin >> gameType;

		if(gameType == 0 || gameType == 1)
			break;
		else
			cout << "Please enter a valid input..." << endl;
	}

	if(gameType == 0)
	{
		while(!gameOver)
		{
			cout << "Please enter your move : ";
			getline(cin, move);

			cout << move << endl;

			cout << "move : "<< move.length() << endl;


		}





	//multiplayer mode
	}else
	{
		cout << "Not available currently..." << endl;
	}
	


	return 0;
}
