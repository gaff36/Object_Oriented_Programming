import java.awt.FlowLayout; 
import javax.swing.JFrame; 
import javax.swing.JLabel; 
import java.awt.FlowLayout;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import javax.swing.JFrame;
import javax.swing.JTextField;
import javax.swing.JOptionPane;
import javax.swing.JRadioButton;
import javax.swing.ButtonGroup;
import java.awt.FlowLayout;
import java.awt.Font;
import java.awt.event.ItemListener;
import java.awt.event.ItemEvent;
import java.awt.GridLayout;
import java.awt.Container;
import javax.swing.JButton;
import java.awt.Color;
import java.io.File;
import java.io.FileWriter;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.Scanner;
import java.io.FileReader;

public class Hex extends JFrame implements HexGame
{
	private int playStyle = 0;
	private int boardSize = 6;
	private boolean startGame = false;
	private boolean turn = false;
	private Integer visited[];
	private String cells[];
	private int totalPlayNum = 0;
	public boolean resetTheGame = false;
	private boolean hasGameCreated = false;
	public boolean loaded = false;

	public int getPlayStyle()	{return playStyle;}
	public int getBoardSize()	{return boardSize;}
	public int getTotalPlayNum()	{return totalPlayNum;}
	public boolean getTurn()	{return turn;}
	public boolean getResetTheGame() {return resetTheGame;}
	public int getVisited(int index)	{return visited[index];}
	public void setSize(int boardSize)	{this.boardSize = boardSize;}
	public void setPlayStyle(int playStyle)	{this.playStyle = playStyle;}

	boolean hasStarted = false;

	private Game g1;

	private JLabel labelSize;
	private JLabel save;
	private JLabel load;
	private JTextField textFieldSize;
	private JTextField saveFieldSize;
	private JTextField loadFieldSize;
	private JRadioButton radioButtonPlayer;
	private JRadioButton radioButtonComputer;
	private ButtonGroup radioGroup;
	private JButton resetButton;
	private JButton undoButton;

	public Hex()
	{		
		super("Hex Options");
		setLayout(new FlowLayout(10,23,23));
		labelSize = new JLabel("Write size of the board end press enter");
		save = new JLabel("Write the name of the file you want to save :");
		load = new JLabel("Write the name of the file you want to load");

		textFieldSize = new JTextField(25);
		saveFieldSize = new JTextField(25);
		loadFieldSize = new JTextField(25);

		radioGroup = new ButtonGroup();

		radioButtonPlayer = new JRadioButton("Player vs Player",true);
		radioButtonComputer = new JRadioButton("Player vs Computer",false);

		resetButton = new JButton("RESET");
		undoButton = new JButton("UNDO");

		radioGroup.add(radioButtonPlayer);
		radioGroup.add(radioButtonComputer);

		add(labelSize);
		add(textFieldSize);
		add(radioButtonPlayer);
		add(radioButtonComputer);
		add(resetButton);
		add(undoButton);
		add(save);
		add(saveFieldSize);
		add(load);
		add(loadFieldSize);

		radioButtonPlayer.addItemListener(new RadioButtonHandler(0));
		radioButtonComputer.addItemListener(new RadioButtonHandler(1));

		TextFieldHandler texFieldHandler = new TextFieldHandler();
		textFieldSize.addActionListener(texFieldHandler);
		resetButton.addActionListener(texFieldHandler);
		undoButton.addActionListener(texFieldHandler);
		saveFieldSize.addActionListener(texFieldHandler);
		loadFieldSize.addActionListener(texFieldHandler);

	}

/////////////////////////////////////////// INNER CLASS ///////////////////////////////////////////				

	public class Game extends JFrame 			
	{
			private GridLayout hexBoard;
			private Container container;
			private JButton buttons[];

			public Game()				// Creates the game with GridLayout
			{
				super("HEX GAME");
				
				if(loaded == false)
				{
					visited = new Integer[getBoardSize() * getBoardSize()];	
					for(int i = 0; i < getBoardSize() * getBoardSize(); i++)	visited[i] = 0;

					cells = new String[getBoardSize() * getBoardSize()];
					for(int i = 0; i < getBoardSize() * getBoardSize(); i++)	cells[i] = ".";	
				}

				hexBoard = new GridLayout( getBoardSize(), getBoardSize(), 10, 10);
				container = getContentPane();		
				setLayout(hexBoard);

				buttons = new JButton[getBoardSize() * getBoardSize()];
				buttonHandler cellHandler = new buttonHandler();

				for (int count = 0; count < getBoardSize() * getBoardSize(); count++)
 				{

 					buttons[count] = new JButton(cells[count]);
 					buttons[count].addActionListener(cellHandler);

 					if(cells[count].equals("."))	buttons[count].setBackground(Color.white);
 					else if(cells[count].equals("X"))	buttons[count].setBackground(Color.blue);
 					else if(cells[count].equals("O"))	buttons[count].setBackground(Color.red);
 					add(buttons[count]);
 				}
			}

			private class buttonHandler implements ActionListener
			{
				int cordinate = 0;
				boolean winCheck1 = false;
				boolean winCheck2 = false;
				Integer arr [] = new Integer[getBoardSize() * getBoardSize()];


				public void actionPerformed(ActionEvent event)		// Handler for Hex Buttons
 				{	

					JButton x = (JButton)event.getSource();

					for(int i = 0; i < getBoardSize() * getBoardSize(); i++)	if(x == buttons[i])	cordinate = i;

 					if(visited[cordinate].equals(0) )
					{
						for(int i = 0; i < getBoardSize() * getBoardSize(); i++)	arr[i] = 0;
 						if(getTurn() == false)
 						{
 							x.setText("X");
 							x.setBackground(Color.blue);		// Plays X on Button For Player
 							cells[cordinate] = "X";
 							turn = true;
 							totalPlayNum++;
 							visited[cordinate] = getTotalPlayNum();
 														
 							if(getPlayStyle() == 1)
 							{
 							 	cordinate = playComputer();			// Plays O on Button for Computer
								cells[cordinate] = "O";
								totalPlayNum++;
								visited[cordinate] = getTotalPlayNum();
								buttons[cordinate].setText("O");
 							 	buttons[cordinate].setBackground(Color.red);
 							 	turn = false;
 							}
 													
 						}

 						else
 						{
 							x.setText("O");
 							x.setBackground(Color.red);			// Plays O on Button For Player
 							cells[cordinate] = "O";	
 							turn = false;	
 							totalPlayNum++;
 							visited[cordinate] = getTotalPlayNum();
 						}
 						

 					}
 					winCheck1 = didPlayerOneWin(arr, 0,0,getBoardSize());		// Checks if Player 1 Won the Game
 					winCheck2 = didPlayerTwoWin(arr, 0,0,getBoardSize());		// Checks if Player 2 Won the Game
 			
 					if(winCheck1 == true)
 					{
 						JOptionPane.showMessageDialog(null, String.format("PLAYER 1 WON THE GAME") );		// Closes the game if Player 1 Won the Game
 						System.exit(0);
 					}
 					else if(winCheck2 == true)
 					{
 						JOptionPane.showMessageDialog(null, String.format("PLAYER 2 WON THE GAME") );		// Closes the game if Player 2 Won the Game
 						System.exit(0);
 					}

 					container.validate();

 				}
			}

			public void reset()		// Resets the Board
			{			
				for(int i = 0; i < getBoardSize() * getBoardSize(); i++)
				{
					cells[i] = ".";
					visited[i] = 0;

					buttons[i].setText("."); 
					buttons[i].setBackground(Color.white);
				}
				turn = false;
				resetTheGame = false;
			}

			public void undo()		// Deletes the last move
			{
				if(getTotalPlayNum() != 0)
				{
					for(int i = 0; i < getBoardSize() * getBoardSize(); i++)
					{
						if(visited[i] == getTotalPlayNum())
						{				
							cells[i] = ".";
							visited[i] = 0;
							buttons[i].setText(".");
							buttons[i].setBackground(Color.white);
							totalPlayNum--;
							break;
						}
					}
				}
			}

	}

//////////////////////////////////////////////////////////////////////////////////////

	public int playComputer()		// Generates move for Computer
	{
		boolean done = false;
		int index = 0;

		for (int i = 0; i < getBoardSize(); i++)
		{
			for (int j = 0; j < getBoardSize(); j++)
			{
				if (!done && cells[i * getBoardSize() + j] == "X")
				{
					if(	j < getBoardSize() - 1	&& cells[i * getBoardSize() + j + 1]  == "."  )				{index = i * getBoardSize() + j + 1;done = true;}
					else if( j > 0 && cells[i * getBoardSize() + j - 1]  == "." )									{index = i * getBoardSize() + j - 1;done = true;}
					else if(i < getBoardSize() - 1 && cells[(i + 1) * getBoardSize() + j]  == "."  )				{index = (i + 1) * getBoardSize() + j;done = true;}
					else if(i > 0 && cells[(i - 1) * getBoardSize() + j]  == ".")								{index = (i - 1) * getBoardSize() + j;done = true;}
					else if(j > 0 && i < getBoardSize() - 1 && cells[(i + 1) * getBoardSize() + j - 1]  == ".")	{index = (i + 1) * getBoardSize() + j - 1;done = true;}
					else if(j < getBoardSize() - 1 && i > 0 && cells[(i - 1) * getBoardSize() + j + 1]  == ".")	{index = (i - 1) * getBoardSize() + j + 1;done = true;}
													
				}

				else if (i < getBoardSize() - 1 && !done && cells[i * getBoardSize() + j]  == "O" && cells[(i + 1) * getBoardSize() + j] == ".")
				{
					index = (i + 1) * getBoardSize() + j;
					done = true;
					break;
				}
				else if (i > 0 && !done &&  cells[i * getBoardSize() + j]  == "O" && cells[(i - 1) * getBoardSize() + j] == ".")
				{
					index = (i - 1) * getBoardSize() + j;
					done = true;
					break;
				}
				else if (j < getBoardSize() - 1 && !done &&  cells[i * getBoardSize() + j]  == "O" && cells[i * getBoardSize() + j + 1] == ".")
				{
					index = i * getBoardSize() + j + 1;
					done = true;
					break;
				}
				else if (j > 0 && !done &&  cells[i * getBoardSize() + j]  == "O" && cells[i * getBoardSize() + j - 1] == ".")
				{
					index = i * getBoardSize() + j - 1;
					done = true;
					break;
				}
				else if (i > 0 && j < getBoardSize() - 1 && !done &&  cells[i * getBoardSize() + j]  == "O" && cells[(i - 1) * getBoardSize() + j + 1] == ".")
				{
					index = (i - 1) * getBoardSize() + j + 1;
					done = true;
					break;
				}
				else if (j > 0 && i < getBoardSize() - 1 && !done &&  cells[i * getBoardSize() + j]  == "O" && cells[(i + 1) * getBoardSize() + j - 1] == ".")
				{
					index = (i + 1) * getBoardSize() + j - 1;
					done = true;
					break;
				}
				
				else if(cells[i * getBoardSize() + j] == ".")
				{
					index = i * getBoardSize() + j;
					done = true;
				}
				
			}
			if(done)	break;
		
		}
		return index;

	}

	public boolean didPlayerOneWin(Integer check[], int x, int y, int limit)	// Checks if Player 1 Won the game
	{
		if (y == limit - 1 && cells[x * getBoardSize() + y] == "X")
		{
			return true;
		}
		if (cells[x * getBoardSize() + y] == "X" && check[x * getBoardSize() + y] == 0)
		{
			check[x * getBoardSize() + y] = 1;

			if (y != limit - 1)
			{
				if(didPlayerOneWin(check, x, y + 1, limit))		return true;
			}

			if (x != limit - 1)
			{
				if(didPlayerOneWin(check, x + 1, y, limit))		return true;
			}

			if (x != limit - 1 && y != 0 ) 
			{
				if(didPlayerOneWin(check, x + 1, y - 1, limit))		return true;
			}
			
			if (x != 0)
			{
				if(didPlayerOneWin(check, x - 1, y, limit))		return true;
			}

			if (y != 0)
			{
				if(didPlayerOneWin(check, x, y - 1, limit))		return true;
			}
		
			if (x != 0 && y != limit - 1)
			{
				if(didPlayerOneWin(check, x - 1, y + 1, limit))		return true;
			}			
		
			return false;
		}
		x++;

		if (x < limit && y == 0 && didPlayerOneWin (check, x, y, limit))	return true;
		return false;

	}
	
	public boolean didPlayerTwoWin(Integer check [], int x, int y, int limit)		// Checks if Player 2 Won the game
	{
	
	if (x == limit - 1 && cells[x * getBoardSize() + y] == "O")
	{
		return true;
	}

	if (cells[x * getBoardSize() + y] == "O" && check[x * getBoardSize() + y] == 0)
	{
		check[x * getBoardSize() + y] = 2;

		if (y != limit - 1)
		{
			if(didPlayerTwoWin(check, x, y + 1, limit))		return true;
		}

		if (x != limit - 1)
		{
			if(didPlayerTwoWin(check, x + 1, y, limit))		return true;
		}

		if (x != limit - 1 && y != limit -1 ) 
		{
			if(didPlayerTwoWin(check, x + 1, y - 1, limit))		return true;
		}
			
		if (x != 0)
		{
			if(didPlayerTwoWin(check, x - 1, y, limit))		return true;
		}

		if (y != 0)
		{
			if(didPlayerTwoWin(check, x, y - 1, limit))		return true;
		}
		
		if (x != 0 && y != 0)
		{
			if(didPlayerTwoWin(check, x - 1, y + 1, limit))		return true;
		}			
		
		return false;
	}
	y++;

	if (y < limit && x == 0 && didPlayerTwoWin (check, x, y, limit))	return true;
		return false;
}

	public void saveGame(String fileName)		// Saves game data to a file
	{
		try 
		{
			String s;
      		FileWriter myWriter = new FileWriter(fileName);

			s = String.valueOf(getBoardSize());
			myWriter.write(s);
			myWriter.write("\n");

      		for(int i = 0; i < getBoardSize() * getBoardSize(); i++)
      		{
      			myWriter.write(cells[i]);
      			myWriter.write("\n");
      		}	

      		s = String.valueOf(getPlayStyle());
      		myWriter.write(s);  
      		myWriter.write("\n");
      		if(getTurn() == false)	s = "0";
      		else s = "1";
      		myWriter.write(s);  

     		myWriter.close();
     		JOptionPane.showMessageDialog(null, String.format("GAME SAVED"));
     	}	
    	catch (IOException e)
    	{
      		System.out.println("An error occurred.");
      		JOptionPane.showMessageDialog(null, String.format("ERROR OCCURED"));
      		e.printStackTrace();
   		}
	}

	public boolean loadGame(String fileName)		// Gets game data from a file
	{	
		
		try 
		{
		 	int i = 0;
		 	String data;
      		File myObj = new File(fileName);
      		if(myObj.exists())
      		{
      			loaded = true;
      			Scanner myReader = new Scanner(myObj);

      			data = myReader.nextLine();
      			boardSize = Integer.parseInt(data);
      			cells = new String[getBoardSize() * getBoardSize()];
      			visited = new Integer[getBoardSize() * getBoardSize()];
      			for(int j = 0; j < getBoardSize() * getBoardSize(); j++)	visited[j] = 0;

      			while (i < getBoardSize() * getBoardSize()) 
      			{
      			
       				data = myReader.nextLine();
       				cells[i] = data;
       				if(cells[i].equals(".") == false)	visited[i] = -1;
        			i++;
      			}

      			data = myReader.nextLine();
      			playStyle = Integer.parseInt(data);

      			data = myReader.nextLine();
      			if(data == "0")	turn = false;
      			else if(data == "1") turn = true;
     			myReader.close();
     			return true;
     		}
    	}
    	catch (FileNotFoundException e) 
    	{
      		System.out.println("An error occurred.");
      		//e.printStackTrace();
    	}
    	return false;
	}
	
	////////////////////////////////// HANDLERS //////////////////////////////////////////////		

	private class RadioButtonHandler implements ItemListener
	{
		int style;
		public RadioButtonHandler(int p)
		{
			style = p;	
		}

		public void itemStateChanged(ItemEvent event )		// 
 		{	
 			if(!hasStarted)
 			setPlayStyle(style);
 			else JOptionPane.showMessageDialog(null, String.format("GAME ALREADY STARTED") );
 		}
	}

	private class  TextFieldHandler	implements ActionListener
	{
		public void actionPerformed(ActionEvent event)
		{
			String string = "";

			if(event.getSource() == textFieldSize)	
			{
				string = String.format("%s", event.getActionCommand());
				if(!hasStarted)
				{	try	
					{	
						int s = Integer.parseInt(string);
					
					if(s > 5 && s < 24)			// Gets the board size and starts the game
					{
						setSize(s);
						g1 = new Game();
						g1.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
						g1.setSize(600, 600);
						g1.setVisible(true);
						hasGameCreated = true;
						startGame = true;
						hasStarted = true;
					}
					else JOptionPane.showMessageDialog(null, String.format("INVALID BOARD SIZE") );
					}
					catch(NumberFormatException ex)
					{
						JOptionPane.showMessageDialog(null, String.format("INPUT IS INVALID") );
					}
				}
			}

			else if(event.getSource() == saveFieldSize)			// Saves the game
			{
				string = String.format("%s", event.getActionCommand());
				if(hasStarted == true)
				saveGame(string);
				else JOptionPane.showMessageDialog(null, String.format("YOU NEED TO START A GAME FIRST TO SAVE") );
			}

			else if(event.getSource() == loadFieldSize)		// Loads the game from a file
			{
				
				string = String.format("%s", event.getActionCommand());
				if(loadGame(string))
				{
					if(hasStarted)
					{				
						g1.dispose();
					}
					hasStarted = true;
					g1 = new Game();
					g1.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
					g1.setSize(600, 600);
					g1.setVisible(true);
				}	
				else JOptionPane.showMessageDialog(null, String.format("COULDN'T OPEN THE FILE"));		
			}

			else if(event.getSource() == resetButton)		// Resets the board
			{
				if(hasStarted)	g1.reset();
				else JOptionPane.showMessageDialog(null, String.format("GAME HAS NOT STARTED YET"));
			}
			else if(event.getSource() == undoButton)		// Deletes the last move
			{
				if(hasStarted)
				{
						if(getPlayStyle() == 1)
						{
							g1.undo();		// DELETES COMPUTER'S MOVE TOO
							g1.undo();
						}
						else	g1.undo();
				}
				else JOptionPane.showMessageDialog(null, String.format("GAME HAS NOT STARTED YET"));
			}
			
		}
	}
	//////////////////////////////////////////////////////////////////////////////////////
	
}