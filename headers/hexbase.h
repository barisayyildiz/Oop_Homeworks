#ifndef LIB
#define LIB

namespace hex
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
					inline cell getCellStatus()const{return cellStatus;};
					inline void setCellStatus(cell c){cellStatus = c;};
					inline int getX()const{return x;};
					inline int getY()const{return y;};
					inline void setX(int _x){x = _x;};
					inline void setY(int _y){y = _y;};
				private:
					cell cellStatus;
					int x,y;
			};

			virtual void readFromFile(const std::string &filename) = 0;
			virtual void writeToFile(const std::string &filename) = 0;
			virtual void reset() = 0;
			virtual void setSize(int newSize) = 0;
			virtual bool isEnd() = 0;
			virtual Cell operator()(int x, int y)const = 0;
			virtual bool operator==(AbstractHex *aHex) = 0;
			virtual Cell lastMove() = 0;
			virtual int numberOfMoves()const = 0;


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

			virtual void gameLoop();

		protected:
			// holds the non empty cells for all objects
			static int nonEmptyCells;
		
			int size, turn, counter, gameType;
			bool gameStatus;
			int cap;

			// gets the raw user input and tokenizes
			int getUserInput(std::string input, std::string &filename, int &xPos, int &yPos);

			// pure virtual functions for calculating score
			virtual int calculateScore() = 0;
			virtual int scoreHelper(int** visited, int xPos, int yPos, cell c) = 0;

			// gets the user input -> size of the board and game type
			virtual void playGame();

			// undo
			virtual void undo() = 0;

			virtual void print()const = 0;
			virtual Cell play() = 0;
			virtual Cell play(Cell c1) = 0;


	};
}


#endif