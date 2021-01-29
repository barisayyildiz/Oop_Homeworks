package com.frames;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.util.*;
import java.lang.NumberFormatException;

import java.io.*;

import com.*;


public class InputFrame extends JFrame implements ActionListener
{
	private JRadioButton radioButton2;
	private JRadioButton radioButton1;
	private JTextField textField;
	private JLabel textLabel;
	private JButton submitButton;
	private ButtonGroup radioGroup;
	

	public InputFrame()
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

		boolean isSelected = this.radioButton2.isSelected();
		String textVal = this.textField.getText();
		int size = 0;

		try
		{
			size = Integer.parseInt(textVal);
		}catch(NumberFormatException ex)
		{
			JOptionPane.showMessageDialog(null, "Invalid input, try again");
			return;
		}

		if(size < 6)
		{
			JOptionPane.showMessageDialog(null, "Size should be greater than 5");
			return;
		}

		GameFrame f1 = new GameFrame( size , isSelected );
		

		this.dispose();

	}

}


