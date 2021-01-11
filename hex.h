#ifndef HEX
#define	HEX

namespace myNamespace
{
	// cell status
	enum cell
	{
		empty = '.',
		xLower = 'x',
		oLower = 'o',
		xCapital = 'X',
		oCapital = 'O'
	};


	class AbstractHex
	{
		public:
			class Cell
			{
				public:
					Cell(cell c = empty);
					inline cell getCellStatus(){return cellStatus;};
					inline void setCellStatus(cell c){cellStatus = c;};
					inline int getX(){return x;};
					inline int getY(){return y;};
					inline void setX(int _x){x = _x;};
					inline void setY(int _y){y = _y;};
				private:
					cell cellStatus;
					int x,y;
			};

			virtual void print()const = 0;
			virtual void readFromFile(const std::string &filename) = 0;
			virtual void writeToFile(const std::string &filename) = 0;
			virtual void reset() = 0;
			virtual void setSize(int newSize) = 0;
			virtual Cell play() = 0;
			virtual Cell play(Cell c1) = 0;
			virtual bool isEnd() = 0;
			virtual Cell operator()(int x, int y)const = 0;
			virtual bool operator==(AbstractHex *aHex) = 0;
			virtual Cell lastMove() = 0;
			virtual int numberOfMoves()const = 0;

			// game loop
			virtual void gameLoop() = 0;

			// undo
			virtual void undo() = 0;

			// constructor
			AbstractHex() : size(0), turn(0), counter(0), gameStatus(true), cap(10)
			{/*left empty*/}

			static int getNonEmptyCells(){
				return nonEmptyCells;
			}
			
			// Main game loop operations are handled in this function
			inline bool getGameStatus() const{return gameStatus;};
		
			// getter functions
			inline int getCounter() const{return counter;};

			inline int getTurn() const{return turn;};

			inline int getGameType() const{return gameType;};

			inline int getSize() const{return size;};

			inline int getCap() const{return cap;};

		protected:
			// holds the non empty cells for all objects
			static int nonEmptyCells;
		
			int size, turn, counter, gameType;
			bool gameStatus;
			int cap;

			// gets the raw user input and tokenizes
			int getUserInput(std::string input, std::string &filename, int &xPos, int &yPos);


	};


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
