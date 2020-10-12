#include <iostream>

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



	return 0;
}
