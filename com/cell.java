package com;

/**

Enum type for each Cell object

@author Barış Ayyıldız

*/

public enum cell
{
	/**
	The cell is empty
	 */
	empty,
	/**
	The cell is allocated by the first player, cell is red
	 */
	xLower,
	/**
	The cell is allocated by the second player, cell is blue
	 */
	oLower,
	/**
	The cell is allocated by the second player, cell is blue
	 */
	/**
	Winning path for the first player, cell is black
	 */
	xCapital,
	/**
	Winning path for the second player, cell is black
	 */
	oCapital
}
