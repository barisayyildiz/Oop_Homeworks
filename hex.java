import java.util.*;

public class hex
{
	enum cell
	{
		empty, xLower, oLower, xCapital, oCapital
	}
	
	preivate int size;
	private int turn;
	private int turn;
	private int counter;
	private int gameType;
	private int cap;
	private boolean gamStatus;

	private ArrayList<ArrayList<Integer>> previousMoves;
	private ArrayList<ArrayList<Cell>> hexCells;

	private void initPreviousMoves();

	private calculateMove();

	private boolean isEndOfTheGame();

	private void initVisited();

	private int didSomebodyWin(ArrayList<ArrayList<Integer>> visited, int xPos, int yPos);

	private int isMoveable(ArrayList<ArrayList<Integer>> visited, int xPos, int yPost);

	private int getUserInput(String input, String filename, int xPos, int yPos);

	private void initHexCells();

	private void playGame();

	private static int nonEmptyCells;

	private int calculateScore();
	
	private int scoreHelper(ArrayList<ArrayList<Integer>> visited, int xPos, int yPos, cell c);

	private int markedCellsForTheUser();

	private int orderChar(char c);

	private void print();

	// FILE I/O

	// public methods

	class Cell
	{
		private cell cellStatus;
		private int x;
		private int y;

		public Cell();
		public Cell(cell c);
		public cell getCellStatus();
		public void setCellStatus(cell c);
		public int getX();
		public int getY();
		public int setX(int _x);
		public int setY(int _y);
	}

	public Hex()
	{
		this.size = 0;
		this.turn = 0;
		this.counter = 0;
		this.gameStatus = true;
		this.previousMoves = null;
		this.cap = 10;
		this.hexCells = null;

	}
	

	public Cell play();
	public Cell play(Cell c1);

	// public void undo();

	public void gameLoop();

	public int getCounter();
	public int getGameStatus();
	public int getTurn();
	public int getGameType();
	public int getSize();
	public int getCap();

	public boolean compare(hex h1);


}

