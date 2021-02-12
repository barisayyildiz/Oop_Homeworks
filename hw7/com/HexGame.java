package com;

/**

HexGame Interface

@author Barış Ayyıldız

*/

public interface HexGame
{
	/**
	Play method for the ai
	*/
	void play();
	
	/**
	Play method for the user
	@param c1 Cell class, x and y position will be used
	*/
	void play(Cell c1);

	/**
	Initializes hexCells
	@return initialized hexCells
	*/
	Cell[][] initHexCells();
	
	/**
	Initializes previousMoves, that is used in isEndOfTheGame method
	@return initialized previousMoves
	*/
	int[][] initPreviousMoves();
	
	/**
	Checks if the game is over
	@return true if the game is over
	*/
	boolean isEndOfTheGame();

	/**
	Helper function for isEndOfTheGame method
	@param visited 2d int array named visited
	@param xPos x position
	@param yPos y position
	@return true if the game is over
	*/
	boolean didSomebodyWin(int visited[][], int xPos, int yPos);

	/**
	Is moveable function, return true if (x,y) coordinate is empty on the board
	@param visited 2d itn array named visited
	@param xPos x position
	@param yPos y position
	@return true if the game is over
	*/
	boolean isMoveable(int visited[][], int xPos, int yPos);
	
	/**
	Initializes 2d int visited array
	@return initialized visited array
	*/
	public int[][] initVisited();

	/**
	Toggles turn of the game<br>
	1 -> 0<br>
	0 -> 1
	*/
	void toggleTurn();

	/**
	Resets the game
	*/
	void reset();

	/**
	Undo for single step
	*/
	void undo();

	/**
	Opens a JOptionPane.showInputDialog, asks for filename and saves the game to the file
	*/
	void saveToFile();

	/**
	Opens a JOptionPane.showInputDialog, asks for filename and loads the game from the file
	*/
	void loadFromFile();
	
}


