#include <iostream>
#include <string>

using namespace std;


void drawGrid(char (*grid)[12], int n)
{
	// header
	cout << "  ";
	for(int i=0; i<n; i++)
	{
		cout << static_cast<char>(97 + i) << " ";
	}
	cout << "\n";




	for(int i=0; i<n; i++)
	{
		// rakamlar
		cout << i+1 << " ";

		// baştaki boşluklar
		for(int indent=0; indent<=i; indent++)
			cout << " ";

		for(int j=0; j<n; j++)
		{
			cout << grid[i][j] << " ";
		}
		cout << "\n";
	}
}

void initGrid(char (*grid)[12], int n)
{
	for(int i=0; i<n; i++)
	{
		for(int j=0; j<n; j++)
		{
			grid[i][j] = '.';
		}
	}
}


int main()
{
	char grid[12][12];

	// turn => 0 : computer / user-1, 1 : user-1 / user-2
	int gameOver = 0, gameType, turn = 0, n;
	string moveChar;
	int moveNum;
	int xPos, yPos;

	while(1)
	{
		cout << "Size of grid [7-12] : ";
		cin >> n;

		if(n < 7 || n > 12)
			cout << "Invalid input" << endl;
		else
			break;
	}

	initGrid(grid, n);
	drawGrid(grid, n);

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
			cout << "\nUser-" << turn+1 << "'s turn" << endl;
			cout << "Please enter your move (ex : A 3) : ";
			//getline(cin, move);
			cin >> moveChar >> moveNum;

			//moveChar.length() > 1
			cout << moveChar.length() << " " << moveNum << endl;

			// invalid input
			if(moveChar.length() > 1 || moveNum > n || moveNum < 0 || !((moveChar[0] >= 'A' && moveChar[0] < 'A' + n) || (moveChar[0] >= 'a' && moveChar[0] < 'a' + n)))
			{
				cout << "Invalid input" << endl;
				continue;
			}

			// valid input
			xPos = moveNum - 1;
			if(moveChar[0] >= 'A')
				yPos = moveChar[0] - 65;
			else
				yPos = moveChar[0] - 97;

			if(turn == 0)
				grid[xPos][yPos] = 'x';
			else
				grid[xPos][yPos] = 'o';

			turn = !turn;

			drawGrid(grid, n);

		}


	//multiplayer mode
	}else
	{
		cout << "Not available currently..." << endl;
	}
	


	return 0;
}
