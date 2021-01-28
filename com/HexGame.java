package com;

public interface HexGame
{
	void play();
	
	void play(Cell c1);

	Cell[][] initHexCells();

	int[][] initPreviousMoves();
	
	boolean isEndOfTheGame();

	boolean didSomebodyWin(int visited[][], int xPos, int yPos);

	boolean isMoveable(int visited[][], int xPos, int yPos);

	public int[][] initVisited();

	void toggleTurn();

	void reset();

	void undo();
	
}


