#include <iostream>

using namespace std;

enum cell
{
	empty = '.',
	xLower = 'x',
	oLower = 'o',
	xCapital = 'X',
	oCapital = 'O'
};

class Hex
{
private:
	int boardSize, gameType, turn, counter;
	bool gameOver;
public:
	Hex();
	void playGame();
	void getData();
};

// test amaçlı yazıldı
void Hex::getData()
{
	cout << boardSize << " : " << gameType << " : " << turn << " : " << counter << endl;

}

Hex::Hex() : turn(0), counter(0), gameOver(false)
{
	playGame();
}

void Hex::playGame()
{
	while(true)
	{
		cout << "Size of grid (min 6) : ";
		cin >> boardSize;
		if(boardSize >= 6)
			break;
		else
			cerr << "Invalid input, try again...\n\n";
	}

	while(true)
	{
		cout << "Please enter 0 for 2-player and 1 for 1 player mod" << endl;
		cin >> gameType;

		if(gameType == 0 || gameType == 1)
			break;
		else
			cerr << "Invalid input, try again...\n\n";
	}

}

int main()
{

	// Hex h1;

	// h1.getData();



	return 0;
}