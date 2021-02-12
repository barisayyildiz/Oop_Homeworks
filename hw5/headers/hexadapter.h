#ifndef ADAPTER
#define ADAPTER


namespace hex
{
	template<template<typename...> class T>
	class HexAdapter : public AbstractHex
	{
		public:
			// default constructor
			HexAdapter();

			// conversion constructor
			explicit HexAdapter(int s);

			// BIG 3
			// assignment operator
			HexAdapter& operator = (const HexAdapter& h1);

			// copy constructor
			HexAdapter(const HexAdapter& h1);

			// gets the size and game type
			HexAdapter(int s, int gT);

			// gets the size, game type and filename
			// and saves the game to the file
			HexAdapter(int s, int gT, std::string &filename);

			// destructor
			~HexAdapter();

			void readFromFile(const std::string &filename);
			void writeToFile(const std::string &filename);
			void setSize(int newSize);
			bool operator==(AbstractHex *aHex);
			Cell lastMove();
			int numberOfMoves()const;
			bool isEnd();
			void reset();
			Cell operator()(int x, int y)const;

		private:

			Cell play();
			Cell play(Cell c1);
			void print()const;

			void undo();


			// saves the previous moves for making undo operation
			int **previousMoves;


			// init previous moves
			int **initPreviousMoves();

			// // checks the end of the game
			// int isEndOfTheGame();

			// visited array is a helper array
			int** initVisited(int** visited);

			// these two functions are used for detecting end of the game
			int didSomebodyWin(int** visited, int xPos, int yPos);
			int isMoveable(int** visited, int xPos, int yPos);


			// initilizes hex cells by the size of the board
			void initHexCells();

			// marked cells for the user
			int markedCellsForTheUser()const;

			// some helper function to get char type of an enum number
			int orderChar(char c);

			// for AI
			void calculateBestMove(int &xPos, int &yPos);

			void centerofGravity(int *center, int totalX, int totalY, int increment);

			// for calculating score
			int calculateScore();
			int scoreHelper(int** visited, int xPos, int yPos, cell c);


			T<T< Cell >> hexCells;

	};


}



#endif