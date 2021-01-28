import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.util.*;
import com.*;

public class Main
{
	public static void main(String[] args)
	{

		MyFrame f1 = new MyFrame();

		f1.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		f1.setSize(325, 100);
		f1.setVisible(true);

		
	}
}


class MyFrame extends JFrame implements ActionListener
{
	private JRadioButton radioButton2;
	private JRadioButton radioButton1;
	private JTextField textField;
	private JLabel textLabel;
	private JButton submitButton;
	private ButtonGroup radioGroup;
	

	public MyFrame()
	{
		super("Hex Game...");

		setLayout(new FlowLayout());

		textField = new JTextField(20);
		
		textLabel = new JLabel("Enter size : ");

		radioButton2 = new JRadioButton("2-player", true);
		radioButton1 = new JRadioButton("1-player");

		radioGroup = new ButtonGroup();

		submitButton = new JButton("Submit");

		submitButton.addActionListener(this);

		radioGroup.add(radioButton2);
		radioGroup.add(radioButton1);

		add(textLabel);
		add(textField);
		add(radioButton2);
		add(radioButton1);
		add(submitButton);

	}

	public void actionPerformed(ActionEvent e)
	{
		System.out.println(this.radioButton2.isSelected());
		System.out.println(this.textField.getText());
		
		GameFrame f1 = new GameFrame( Integer.parseInt( this.textField.getText() ) , this.radioButton2.isSelected() );

		this.dispose();

	}

}


class GameFrame extends JFrame implements ActionListener
{
	private JButton btn;
	private JButton btn2;

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

		hexCells = new Cell[size][size];

		for(int i=0; i<size; i++)
		{
			for(int j=0; j<size; j++)
			{
				this.hexCells[i][j] = new Cell(cell.empty, i, j);
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
		btn = new JButton("Reset");
		btn2 = new JButton("Undo");

		btn.setBounds( 0, this.size * BTNSIZE, BTNSIZE * 3, BTNSIZE);
		btn2.setBounds( 0, (this.size + 1) * BTNSIZE, BTNSIZE * 3, BTNSIZE);

		btn.addActionListener(this);
		btn2.addActionListener(this);

		this.add(btn);
		this.add(btn2);


		// ===================== FRAME OPTIONS ==================== //
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		this.setSize((size -1) * (BTNSIZE/2) +  size * BTNSIZE , (size+3) * BTNSIZE );
		this.setVisible(true);


	}

	public void printHexCells()
	{
		System.out.printf("\n");
		for(int i=0; i<this.size; i++)
		{
			for(int j=0; j<this.size; j++)
			{
				System.out.printf("%s\t|", this.hexCells[i][j].getCellStatus());			
			}
			System.out.printf("\n");
		}
		System.out.printf("\n");
	}

	public void actionPerformed(ActionEvent e)
	{

		System.out.println(e.getSource() == btn);

		if(e.getSource() == btn)
		{
			// reset button
			reset();
			return;

		}else if(e.getSource() == btn2)
		{
			// undo button
			undo();

			if(this.gameType == false && this.counter != 0)
				undo();

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
			System.out.println("GAME IS OVER!!!!");

			JOptionPane.showMessageDialog(null, "Game is Over");

			// terminate
			this.dispose();

		}

		toggleTurn();

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

		// toggle turn
		this.turn += 1;
		this.turn %= 2;
	}

	public void play(Cell c1)
	{

		// PLAY FONKSİYONUN BURALARA BİR YERE EKLE
		if(this.turn == 0)
			this.hexCells[c1.getX()][c1.getY()].setCellStatus(cell.xLower);
		else
			this.hexCells[c1.getX()][c1.getY()].setCellStatus(cell.oLower);

		this.previousMoves[this.counter][0] = c1.getX();
		this.previousMoves[this.counter][1] = c1.getY();
		this.counter++;


		// printHexCells();

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

		// // toggle turn
		// this.turn += 1;
		// this.turn %= 2;


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
		// int moveRange[6][2] = {{-1,0}, {0,1}, {1,0}, {0,-1}, {-1,1}, {1,-1}};
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
				// this.hexCells[xPos][yPos] = cell.oCapital;
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

}


