#include <iostream>

using namespace std;

int isMoveable(char (*grid)[6], int (*allmoves)[6], int xPos, int yPos)
{
	if(grid[xPos][yPos] != '.' && allmoves[xPos][yPos] == 0)
	{
		cout << (bool)(grid[xPos][yPos] == '.') << endl;
		cout << "hareket edilebilir\n";
		return 1;
	}
	return 0;
}

int backTracking(char (*grid)[6], int (*allmoves)[6], int xPos, int yPos)
{
	//sona gelmişsek
	if(xPos == 5)
		return 1;

	allmoves[xPos][yPos] = 1;

	cout << "=====================\n";
	cout << "xPos : " << xPos << " yPos : " << yPos << endl;

	int tempX = xPos, tempY = yPos;

	int moveRange[6][2] = {{-1,0}, {0,1}, {1,0}, {0,-1}, {-1,1}, {1,-1}};
	for(int i=0; i<6; i++)
	{
		tempX = xPos + moveRange[i][0];
		tempY = yPos + moveRange[i][1];

		cout << "tempX : " << tempX << " tempY : " << tempY << endl;

		// out of border
		if(tempX < 0 || tempX >= 6 || tempY < 0 || tempY >= 6)
		{
			cout << "out of border...\n";
			continue;
		}

		if(isMoveable(grid, allmoves, tempX ,tempY))
		{
			if(backTracking(grid, allmoves, tempX, tempY))
				return 1;
		}else
		{
			cout << "gidilemez!!!\n";
		}
	}

	return 0;
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

int main()
{
	char grid[6][6];
	initGrid(grid);
	drawGrid(grid);

	grid[0][0] = 'x';
	grid[1][0] = 'x';
	grid[2][0] = 'x';
	grid[2][1] = 'x';
	grid[2][2] = 'x';
	grid[3][2] = 'x';
	grid[4][2] = 'x';
	grid[4][3] = 'x';
	grid[4][4] = 'x';

	/*
	x.....
	x.....
	xxx...
	..x...
	..xxx.
	..x...


	*/


	int allmoves[6][6] = {
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0}
	};

	int result = backTracking(grid, allmoves, 0, 0);
	cout << "result : " << result << endl;


	for(int i=0; i<6; i++)
	{
		for(int j=0; j<6; j++)
		{
			cout << allmoves[i][j];
		}
		cout << endl;
	}



	return 0;
}
