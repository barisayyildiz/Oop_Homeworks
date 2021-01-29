package com;

/**

Cell class, represents each cell on the board

@author Barış Ayyıldız

*/


public class Cell
{
	private cell cellStatus;
	private int x;
	private int y;

	/**
	Cell constructor that takes initial cellstatus

	@param cellstatus enum cell value
	@param x xPosition
	@param y yPosition
	*/
	public Cell(cell cellstatus, int x, int y)
	{
		this.cellStatus = cellstatus;
		this.x = x;
		this.y = y;
	}

	/**
	Cell constructor
	@param x xPosition
	@param y yPosition
	 */
	public Cell(int x, int y)
	{
		this.cellStatus = cell.empty;
		this.x = x;
		this.y = y;
	}

	/**
	Returns cell status
	@return cell enum
	 */
	public cell getCellStatus(){return cellStatus;};

	/**
	Sets cell status
	@param cell cell enum
	 */
	public void setCellStatus(cell s){cellStatus = s;};

	/**
	Returns x position
	@return x position
	 */
	public int getX(){return x;};

	/**
	Returns y position
	@return y position
	 */
	public int getY(){return y;};

	/**
	Sets x position
	@param x position
	 */
	public void setX(int _x){x = _x;};

	/**
	Sets y position
	@param y position
	 */
	public void setY(int _y){y = _y;};
}
