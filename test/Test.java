import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class Test
{
	public static void main(String[] args)
	{

		MyFrame f1 = new MyFrame();

		f1.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		f1.setSize(325, 100);
		f1.setVisible(true);


		System.out.println("asdeasdasd");

		// f1.dispose(); // closes the frame

		
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
		super("HEX GAME!!");

		setLayout(new FlowLayout());

		textField = new JTextField(20);
		
		textLabel = new JLabel("Enter size : ");

		radioButton2 = new JRadioButton("2-player", true);
		radioButton1 = new JRadioButton("1-player");

		// radioButton2.setBounds(120,30,120,50);
		// radioButton1.setBounds(250,30,80,50);

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
		
		GameFrame f1 = new GameFrame();

		this.dispose();
		
		// this.dispose();
		// System.out.println("clicked...");
	}

}


class GameFrame extends JFrame implements ActionListener
{
	private JButton btn;
	private JButton btn2;

	private JButton[][] buttons;

	public GameFrame()
	{
		super("HEX GAME...");

		// setLayout(new FlowLayout());
		setLayout(new GridLayout(6,6));

		buttons = new JButton[6][6];

		for(int i=0; i<6; i++)
		{
			for(int j=0; j<6; j++)
			{
				buttons[i][j] = new JButton();
				buttons[i][j] .setPreferredSize(new Dimension(100,100));
				buttons[i][j] .addActionListener(this);
				add(buttons[i][j]);
			}
		}

		// setLayout(new GridLayout(2,1));

		btn = new JButton("Reset");
		btn2 = new JButton("Undo");


		// this.add(btn);
		// this.add(btn2);



		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		this.setSize(500, 500);
		this.setVisible(true);


	}

	public void actionPerformed(ActionEvent e)
	{
		// System.out.println(e.getSource());

		// System.out.println(e.getSource().getBackground());

		// System.out.println(((JButton)e.getSource()).getBackground());

		((JButton)e.getSource()).setBackground(Color.RED);

	}


}










// class MyFrame extends JFrame
// {
// 	private JTextField textfield1;
// 	private JButton mybutton;

// 	public MyFrame()
// 	{
// 		super("Text field header...");

// 		setLayout(new FlowLayout());

// 		textfield1 = new JTextField(10);

// 		mybutton = new JButton("Send");

// 		add(textfield1);
// 		add(mybutton);

// 		TextFieldHandler handler = new TextFieldHandler();

// 		mybutton.addActionListener(handler);

// 		this.dispose();

// 	}

// 	private class TextFieldHandler implements ActionListener
// 	{
// 		public void actionPerformed(ActionEvent event)
// 		{
// 			if(event.getSource() == mybutton)
// 			{
// 				System.out.println(textfield1.getText());

// 				// System.out.println(event.getActionCommand());
// 				// JOptionPane.showMessageDialog(null, "you entered");
// 			}
// 		}
// 	}


// }