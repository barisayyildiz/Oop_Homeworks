package com;

public interface HexGame
{
	Cell play();
	
	Cell play(Cell c1);

	void initHexCells();

	void randomMove();

	void calculateBestMove();
	
	int isEndOfTheGame();
	
}


