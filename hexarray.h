#ifndef HEX
#define	HEX

namespace hex
{
	class HexArray1D : public AbstractHex
	{
		public:
			// default constructor
			HexArray1D();

			// conversion constructor
			explicit HexArray1D(int s);

			// BIG 3
			// assignment operator
			HexArray1D& operator = (const HexArray1D& h1);

			// copy constructor
			HexArray1D(const HexArray1D& h1);

			// gets the size and game type
			HexArray1D(int s, int gT);

			// gets the size, game type and filename
			// and saves the game to the file
			HexArray1D(int s, int gT, std::string &filename);

			// destructor
			~HexArray1D();

			void gameLoop();

			// private'a al sonra
			void print()const;
			bool isEnd();
			void reset();
			Cell operator()(int x, int y)const;

		private:

			void readFromFile(const std::string &filename);
			void writeToFile(const std::string &filename);
			void setSize(int newSize);
			Cell play();
			Cell play(Cell c1);
			bool operator==(AbstractHex *aHex);
			Cell lastMove();
			int numberOfMoves()const;

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

			// gets the user input -> size of the board and game type
			void playGame();

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

			Cell *hexCells;



	};


}


#endif
