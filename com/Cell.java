package com;

public class Cell
{
	public cell cellStatus;
	public int x;
	public int y;

	public Cell(cell cellstatus, int x, int y)
	{
		this.cellStatus = cellstatus;
		this.x = x;
		this.y = y;
	}

	public Cell(int x, int y)
	{
		this.cellStatus = cell.empty;
		this.x = x;
		this.y = y;
	}

	public cell getCellStatus(){return cellStatus;};
	public void setCellStatus(cell s){cellStatus = s;};

	public int getX(){return x;};
	public int getY(){return y;};
	public void setX(int _x){x = _x;};
	public void setY(int _y){y = _y;};
}
