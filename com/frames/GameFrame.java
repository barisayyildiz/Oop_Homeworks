package com.frames;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.util.*;
import java.lang.NumberFormatException;

import java.io.*;

import com.*;

/**

GameFrame class, implements HexGame

@author Barış Ayyıldız


*/



public class GameFrame extends JFrame implements ActionListener, HexGame
{
	private JButton resetButton;
	private JButton undoButton;
	private JButton writeFileButton;
	private JButton readFileButton;

	private int turn;
	private boolean gameType;

	private JButton[][] buttons;
	private Cell[][] hexCells;

	private int counter;
	private int[][] previousMoves;

	private int BTNSIZE;

	private int size;

	public GameFrame(int s, boolean gt)
	{
		super("Hex Game...");

		setLayout(null);

		this.size = s;
		this.gameType = gt;

		this.counter = 0;

		this.turn = 0;

		BTNSIZE = 1200 / (2 * this.size - 1);


		this.hexCells = initHexCells();

		this.previousMoves = initPreviousMoves();


		buttons = new JButton[size][size];

		for(int i=0; i<size; i++)
		{
			for(int j=0; j<size; j++)
			{
				buttons[i][j] = new JButton();
				buttons[i][j].setPreferredSize(new Dimension(BTNSIZE,BTNSIZE));
				buttons[i][j].addActionListener(this);

				buttons[i][j].setBounds(  (i) * (BTNSIZE/2) +  + j * BTNSIZE    ,  i * BTNSIZE , BTNSIZE, BTNSIZE );

				this.add(buttons[i][j]);
			}
		}

		// ================ RESET/UNDO BUTTONS ================= //
		int width = (size -1) * (BTNSIZE/2) +  size * BTNSIZE;
		int height = (size+5) * BTNSIZE;

		resetButton = new JButton("Reset");
		undoButton = new JButton("Undo");
		writeFileButton = new JButton("Save board");
		readFileButton = new JButton("Load board");

		// resetButton.setBounds( 0, this.size * BTNSIZE, BTNSIZE * 3, BTNSIZE);
		// undoButton.setBounds( 0, (this.size + 1) * BTNSIZE, BTNSIZE * 3, BTNSIZE);
		// writeFileButton.setBounds( 0, (this.size + 2 ) * BTNSIZE, BTNSIZE * 3, BTNSIZE);
		// readFileButton.setBounds( 0, (this.size + 3 ) * BTNSIZE, BTNSIZE * 3, BTNSIZE);

		resetButton.setBounds( 0, this.size * BTNSIZE, width, BTNSIZE);
		undoButton.setBounds( 0, (this.size + 1) * BTNSIZE, width, BTNSIZE);
		writeFileButton.setBounds( 0, (this.size + 2 ) * BTNSIZE, width, BTNSIZE);
		readFileButton.setBounds( 0, (this.size + 3 ) * BTNSIZE, width, BTNSIZE);

		resetButton.addActionListener(this);
		undoButton.addActionListener(this);
		writeFileButton.addActionListener(this);
		readFileButton.addActionListener(this);

		this.add(resetButton);
		this.add(undoButton);
		this.add(writeFileButton);
		this.add(readFileButton);


		// ===================== FRAME OPTIONS ==================== //
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		this.setSize(width , height );
		this.setVisible(true);


	}

	public int[][] initPreviousMoves()
	{

		int[][] temp = new int[size*size][2];
		for(int i=0; i<size*size; i++)
		{
			for(int j=0; j<2; j++)
			{
				temp[i][j] = 0;
			}
		}

		return temp;
	}

	public Cell[][] initHexCells()
	{
		Cell[][] temp = new Cell[size][size];

		for(int i=0; i<size; i++)
		{
			for(int j=0; j<size; j++)
			{
				temp[i][j] = new Cell(cell.empty, i, j);
			}
		}

		return temp;
	}

	/**
	Invoked when a button is pressed
	@param e ActionEvent object
	*/
	public void actionPerformed(ActionEvent e)
	{

		if(e.getSource() == resetButton)
		{
			// reset button
			reset();
			return;

		}else if(e.getSource() == undoButton)
		{
			// undo button

			if(this.counter == 0)
			{
				JOptionPane.showMessageDialog(null, "Cannot undo more...");
				return;				
			}

			undo();

			if(this.gameType == false && this.counter != 0)
				undo();

			return;
		
		}else if(e.getSource() == writeFileButton)
		{
			// write to file, save board
			saveToFile();

			return;

		}else if(e.getSource() == readFileButton)
		{
			// read from file, load board
			loadFromFile();


			return;

		}

		// clicked on board

		int xPos = 0, yPos = 0;

		for(int i=0; i<this.size; i++)
		{
			for(int j=0; j<this.size; j++)
			{
				if((JButton)e.getSource() == this.buttons[i][j] )
				{
					xPos = i;
					yPos = j;

					if(this.hexCells[i][j].getCellStatus() != cell.empty)
						return;
				}
			}
		}
		Cell c1 = new Cell(xPos, yPos);

		play(c1);


		if(isEndOfTheGame())
		{

			JOptionPane.showMessageDialog(null, "Game is Over");
		
			// terminate
			this.dispose();

		}

		toggleTurn();
		
		// Skip if the game is PVP
		if(this.turn == 1 && this.gameType == false)
			play();
		else
			return;

		if(isEndOfTheGame())
		{

			JOptionPane.showMessageDialog(null, "Game is Over");

			// terminate
			this.dispose();

		}

		toggleTurn();

	}

	public void saveToFile()
	{
		String filename = JOptionPane.showInputDialog("Enter filename...");

		try
		{
			BufferedWriter bw = new BufferedWriter(new FileWriter(filename));

			bw.write( String.valueOf(this.size) + "\n");
			bw.write( String.valueOf(this.counter) + "\n");
			bw.write( String.valueOf(this.gameType) + "\n");
			bw.write( String.valueOf(this.turn) + "\n");
			
			// SAVE BOARD
			for(int i=0; i<this.size; i++)
			{
				for(int j=0; j<this.size; j++)
				{
					bw.write( this.hexCells[i][j].getCellStatus() + "\n");
				}
			}

			// SAVE PREVIOUS MOVES
			for(int i=0; i<this.counter; i++)
			{
				bw.write( this.previousMoves[i][0] + "_" + this.previousMoves[i][1] + "\n");
			}


			bw.close();

			
		}catch(Exception e)
		{
			JOptionPane.showInputDialog(null, e.getMessage());
		}

	}

	public void loadFromFile()
	{

		String filename = JOptionPane.showInputDialog("Enter filename...");

		try
		{
			BufferedReader br = new BufferedReader(new FileReader(filename));
			
			String s;
			String[] tokens;
			int val;
			
			s = br.readLine();

			if(this.size != Integer.parseInt(s))
				throw new Exception("Board sizes should be same...");

			this.size = Integer.parseInt(s);

			s = br.readLine();
			this.counter = Integer.parseInt(s);

			s = br.readLine();
			this.gameType = Boolean.parseBoolean(s);

			s = br.readLine();
			this.turn = Integer.parseInt(s);

			// LOAD BOARD
			for(int i=0; i<this.size; i++)
			{
				for(int j=0; j<this.size; j++)
				{
					s = br.readLine();

					this.hexCells[i][j].setCellStatus( cell.valueOf( s ) );

				}
			}

			// LOAD PREVIOUS MOVES
			for(int i=0; i<this.counter; i++)
			{
				s = br.readLine();
				tokens = s.split("_");

				this.previousMoves[i][0] = Integer.parseInt(tokens[0]);
				this.previousMoves[i][1] = Integer.parseInt(tokens[1]);

			}




			// ADJUST BUTTON COLORS
			for(int i=0; i<this.size; i++)
			{
				for(int j=0; j<this.size; j++)
				{
					
					if(this.hexCells[i][j].getCellStatus() == cell.empty)
					{
						this.buttons[i][j].setBackground(null);
					}else if(this.hexCells[i][j].getCellStatus() == cell.xLower)
					{
						this.buttons[i][j].setBackground(Color.RED);
					}else if(this.hexCells[i][j].getCellStatus() == cell.oLower)
					{
						this.buttons[i][j].setBackground(Color.BLUE);
					}

				}
			}


			br.close();

			
		}catch(Exception e)
		{
			JOptionPane.showMessageDialog(null, e.getMessage());
		}
		

	}

	public void toggleTurn()
	{
		// toggle turn
		this.turn += 1;
		this.turn %= 2;
	}

	public void reset()
	{
		this.counter = 0;
		this.previousMoves = null;
		
		for(int i=0; i<this.size; i++)
		{
			for(int j=0; j<this.size; j++)
			{
				this.hexCells[i][j].setCellStatus(cell.empty);
			}
		}
		
		for(int i=0; i<this.size; i++)
		{
			for(int j=0; j<this.size; j++)
			{
				this.buttons[i][j].setBackground(null);
			}
		}

		this.previousMoves = new int[size*size][2];
		for(int i=0; i<size*size; i++)
		{
			for(int j=0; j<2; j++)
			{
				this.previousMoves[i][j] = 0;
			}
		}


	}

	public void undo()
	{
		this.counter--;
		this.hexCells[this.previousMoves[this.counter][0]][this.previousMoves[this.counter][1]].setCellStatus(cell.empty);

		this.buttons[this.previousMoves[this.counter][0]][this.previousMoves[this.counter][1]].setBackground(null);

		toggleTurn();
	}

	public void play(Cell c1)
	{
		// for user move

		if(this.turn == 0)
			this.hexCells[c1.getX()][c1.getY()].setCellStatus(cell.xLower);
		else
			this.hexCells[c1.getX()][c1.getY()].setCellStatus(cell.oLower);

		this.previousMoves[this.counter][0] = c1.getX();
		this.previousMoves[this.counter][1] = c1.getY();
		this.counter++;

		if(this.turn == 0)
		{
			this.buttons[c1.getX()][c1.getY()].setBackground(Color.RED);
		}

		if(this.turn == 1)
		{
			this.buttons[c1.getX()][c1.getY()].setBackground(Color.BLUE);
		}


	}



	public void play()
	{
		int xPos, yPos;
		while(true)
		{
			xPos = (int)(Math.random() * this.size);
			yPos = (int)(Math.random() * this.size);

			if( this.hexCells[xPos][yPos].getCellStatus() != cell.empty )
				continue;
			else
				break;		
		
		}

		this.hexCells[xPos][yPos].setCellStatus(cell.oLower);

		this.buttons[xPos][yPos].setBackground(Color.BLUE);

		this.previousMoves[this.counter][0] = xPos;
		this.previousMoves[this.counter][1] = yPos;
		this.counter++;

	}

	public boolean isEndOfTheGame()
	{
		int visited[][] = null;

		if(this.turn == 0)
		{
			for(int i=0; i<this.size; i++)
			{
				visited = initVisited();

				if(this.hexCells[i][0].getCellStatus() == cell.xLower && didSomebodyWin(visited, i, 0))
					return true;
			}
		}else
		{
			for(int i=0; i<this.size; i++)
			{
				visited = initVisited();

				if(this.hexCells[0][i].getCellStatus() == cell.oLower && didSomebodyWin(visited, 0, i))
					return true;
			}
		}

		visited = null;
		return false;
	}

	public boolean didSomebodyWin(int visited[][], int xPos, int yPos)
	{
		int tempX = xPos, tempY = yPos;
		int moveRange[][] = {{-1,0}, {0,1}, {1,0}, {0,-1}, {-1,1}, {1,-1}};

		if(this.turn == 0)
		{
			// X's turn
			if(yPos == this.size-1)
			{
				this.hexCells[xPos][yPos].setCellStatus(cell.xCapital);
				this.buttons[xPos][yPos].setBackground(Color.BLACK);
				return true;
			}

			visited[xPos][yPos] = 1;
			
			for(int i=0; i<6; i++)
			{
				tempX = xPos + moveRange[i][0];
				tempY = yPos + moveRange[i][1];

				// out of border
				if(tempX < 0 || tempX >= this.size || tempY < 0 || tempY >= this.size)
				{
					continue;
				}

				if(isMoveable(visited, tempX ,tempY))
				{
					if(didSomebodyWin(visited, tempX, tempY))
					{
						// capitalize
						this.hexCells[xPos][yPos].setCellStatus(cell.xCapital);
						this.buttons[xPos][yPos].setBackground(Color.BLACK);
						return true;
					}
				}
			}

			return false;

		}else
		{
			// O's turn
			if(xPos == this.size-1)
			{
				// capitalize
				this.hexCells[xPos][yPos].setCellStatus(cell.oCapital);
				this.buttons[xPos][yPos].setBackground(Color.BLACK);
				return true;
			}

			visited[xPos][yPos] = 1;


			for(int i=0; i<6; i++)
			{
				tempX = xPos + moveRange[i][0];
				tempY = yPos + moveRange[i][1];

				// out of border
				if(tempX < 0 || tempX >= this.size || tempY < 0 || tempY >= this.size)
				{
					continue;
				}

				if(isMoveable(visited, tempX ,tempY))
				{
					if(didSomebodyWin(visited, tempX, tempY))
					{
						// capitalize
						this.hexCells[xPos][yPos].setCellStatus(cell.oCapital);
						this.buttons[xPos][yPos].setBackground(Color.BLACK);
						return true;
					}
				}
			}
			return false;
		}
	}

	public boolean isMoveable(int visited[][], int xPos, int yPos)
	{
		if(turn == 0)
		{
			if(this.hexCells[xPos][yPos].getCellStatus() == cell.xLower && visited[xPos][yPos] == 0)
				return true;
		}else
		{
			if(this.hexCells[xPos][yPos].getCellStatus() == cell.oLower && visited[xPos][yPos] == 0)
				return true;
		}

		return false;

	}

	public int[][] initVisited()
	{

		int temp[][] = new int[this.size][this.size];

		for(int i=0; i<this.size; i++)
		{
			for(int j=0; j<this.size; j++)
			{
				temp[i][j] = 0;
			}
		}

		return temp;
	}

	@Override
	public Object clone() throws CloneNotSupportedException
	{
		GameFrame temp = (GameFrame)super.clone();

		JButton tempButton[][] = new JButton[size][size];
		Cell tempCell[][] = new Cell[size][size];
		int tempPrev[][] = new int[size*size][2];

		temp.buttons = tempButton;
		temp.hexCells = tempCell;
		temp.previousMoves = tempPrev;
		
		return temp;

		// private JButton[][] buttons;
		// private Cell[][] hexCells;
		// private int[][] previousMoves;

	}

}


