#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class Hex
{
	private :
	
	class Cell
	{
		public :
		enum cellState {X, O};

		cellState state;
		int row;
		char column;

		Cell();
		Cell(int row, char column, cellState state);

		int getRow()
		{
			return row;
		}
		char getColumn()
		{
			return column;
		}
		cellState getCellState()
		{
			return state;
		}
		void setRow(int row);
		void setColumn(char column);
		void setState(cellState state);

	};

	int size, playStyle;
	bool turn = false, quit = false, p = false;
	vector<vector<Hex::Cell>> hexCells;

	public :
		
	bool getQuit()
	{
		return quit;
	}
	bool getTurn()
	{
		return turn;
	}
	int getSize ()
	{
		return size;
	}

	int getPlayStyle()
	{
		return playStyle;
	}


	Hex();
	Hex(int size , int playStyle);
	bool compare(Hex hex);
	void setQuit(bool quit);
	void setTurn(bool turn);
	void setSize(int size);
	void setPlayStyle(int playStyle);
	vector<vector<Cell>> setVector(int limit);
	void play (const int x, const int y);
	void play();
	void playGame();
	void turnController(int & x, int & y, bool & isAvailable);
	void displayBoard ();
	bool didPlayerOneWin(vector<vector<Hex::Cell>> hexCells, vector<vector<Hex::Cell>> visitedCells, int x, int y, int limit);
	bool didPlayerTwoWin(vector<vector<Hex::Cell>> hexCells, vector<vector<Hex::Cell>> visitedCells, int x, int y, int limit);
	void save(string fileName);
	void load(string fileName);
};





//////////////////////////  SETTING BOARD  //////////////////////////////////////
inline void Hex:: setQuit(bool quit)
{
	this -> quit = quit;
}
inline void Hex:: setTurn(bool turn)
{
	this -> turn = turn;
}

inline void Hex :: setSize (int size)
{
	this -> size = size;	
}

inline void Hex :: setPlayStyle (int playStyle)
{
	this -> playStyle = playStyle;
}

vector<vector<Hex::Cell>> Hex :: setVector(int limit)
{
	Cell cell;
	vector<vector<Cell>> hexCells(size, vector <Cell>(size, cell));
	return hexCells;
}

void Hex :: play(const int x, const int y)
{
	hexCells[x][y].setRow(x);
	hexCells[x][y].setColumn((char)('A' + y));
	if (getTurn() == false && hexCells[x][y].getCellState() != Cell::cellState::X && hexCells[x][y].getCellState() != Cell::cellState::O)
	{	
			hexCells[x][y].setState(Cell::cellState::X);
			setTurn(true);
	}
	else if (getTurn() == true && hexCells[x][y].getCellState() != Cell::cellState::X && hexCells[x][y].getCellState() != Cell::cellState::O)
	{
		hexCells[x][y].setState(Cell::cellState::O);
		setTurn(false);
	}
}

void Hex :: play ()			// Generates moves for AI.
{
	int x1, y1;
	bool done = false;
	

	for (int i = 0; i < getSize(); i++)
	{
		for (int j = 0; j < getSize(); j++)
		{
			if (!done && hexCells[i][j].getCellState() == Cell::cellState::O && hexCells[i + 1][j].getCellState() != Cell::cellState::X && hexCells[i + 1][j].getCellState() != Cell::cellState::O && i != getSize() - 1)
			{
				x1 = i + 1;
				y1 = j;
				done = true;
			}
			else if (!done && hexCells[i][j].getCellState() == Cell::cellState::O && hexCells[i - 1][j].getCellState() != Cell::cellState::X && hexCells[i - 1][j].getCellState() != Cell::cellState::O && i != 0)
			{
				x1 = i - 1;
				y1 = j;
				done = true;
			}
			else if (!done && hexCells[i][j].getCellState() == Cell::cellState::O && hexCells[i][j + 1].getCellState() != Cell::cellState::X && hexCells[i][j + 1].getCellState() != Cell::cellState::O && j != getSize() - 1)
			{
				x1 = i;
				y1 = j + 1;
				done = true;				
			}
			else if (!done && hexCells[i][j].getCellState() == Cell::cellState::O && hexCells[i][j - 1].getCellState() != Cell::cellState::X && hexCells[i][j - 1].getCellState() != Cell::cellState::O && j != 0)
			{
				x1 = i;
				y1 = j - 1;
				done = true;				
			}
			else if (!done && hexCells[i][j].getCellState() == Cell::cellState::O && hexCells[i - 1][j + 1].getCellState() != Cell::cellState::X && hexCells[i - 1][j + 1].getCellState() != Cell::cellState::O  && i != 0 && j != getSize() - 1)
			{
				x1 = i - 1;
				y1 = j + 1;
				done = true;				
			}
			else if (!done && hexCells[i][j].getCellState() == Cell::cellState::O && hexCells[i + 1][j - 1].getCellState() != Cell::cellState::X && hexCells[i + 1][j - 1].getCellState() != Cell::cellState::O  && i != getSize() && j != 0)
			{
				x1 = i + 1;
				y1 = j - 1;
				done = true;				
			}
			else if(!done && hexCells[i][j].getCellState() == Cell::cellState::X)
			{
				if(hexCells[i][j + 1].getCellState() != Cell::cellState::X && hexCells[i][j + 1].getCellState() != Cell::cellState::O && j != getSize() - 1)	
				{
					x1 = i;
					y1 = j + 1;
				}
				else if(hexCells[i][j - 1].getCellState() != Cell::cellState::X && hexCells[i][j - 1].getCellState() != Cell::cellState::O && j != 0)
				{
					x1 = i;
					y1 = j - 1;
				}
				else if(hexCells[i + 1][j].getCellState()!= Cell::cellState::X && hexCells[i + 1][j].getCellState() != Cell::cellState::O && i != getSize() - 1)
				{
					x1 = i + 1;
					y1 = j;
				}
				else if(hexCells[i - 1][j].getCellState() != Cell::cellState::X && hexCells[i - 1][j].getCellState() != Cell::cellState::O && i != 0)
				{
					x1 = i - 1;
					y1 = j;
				}
				else if(hexCells[i - 1][j + 1].getCellState() != Cell::cellState::X && hexCells[i - 1][j + 1].getCellState() != Cell::cellState::O && i != 0 && j != getSize() - 1)
				{
					x1 = i - 1;
					y1 = j + 1;
				}
				else if(hexCells[i + 1][j - 1].getCellState() != Cell::cellState::X && hexCells[i + 1][j - 1].getCellState() != Cell::cellState::O && i != getSize() - 1 && j != 0)
				{
					x1 = i + 1;
					y1 = j - 1;
				}

			}			
		}
		
	}

	hexCells[x1][y1].setState(Cell::cellState::O);
	cout << "Player 2 (Computer) played on : " << char(y1 + 'A') << x1 + 1 << endl; 
	setTurn(false);

}

/////////////////////////  CELL FUNCTIONS  /////////////////////////////////

void Hex::Cell::setRow(int row)
{
	this -> row = row;
}

void Hex::Cell::setColumn(char column)
{
	this -> column = column;
}

void Hex::Cell:: setState(cellState state)
{
	this -> state = state;
}

Hex :: Cell :: Cell()
{
	setRow(0);
	setColumn('A');
}

Hex :: Cell :: Cell(int row, char column, cellState state)
{
	setRow(row);
	setColumn(column);
	setState(state);
}
///////////////////////////////  HEX FUNCTIONS  //////////////////////////////////////
Hex :: Hex ()
{
	if(p == true)
	playGame();
}

Hex :: Hex (int size, int playStyle)
{
	if(p == true)
	{
		setSize(size);
		setPlayStyle(playStyle);
		playGame();
	}
}

 bool Hex ::  compare(Hex hex)
{
	bool result;
	int counter1 = 0, counter2 = 0, i, j;

	for (i = 0; i < getSize(); i++)
	{
		for (j = 0; j < getSize(); j++)
		{
			if(hexCells[i][j].getCellState() == Cell::cellState::X || hexCells[i][j].getCellState() == Cell::cellState::O)	counter1++;
		}
	}
	for (i = 0; i < hex.getSize(); i++)
	{
		for (j = 0; j < hex.getSize(); j++)
		{
			if(hex.hexCells[i][j].getCellState() == Cell::cellState::X || hex.hexCells[i][j].getCellState() == Cell::cellState::O)	counter2++;
		}
	}

	if(counter1 > counter2)	result = true;
	else return false;
	return result;
}

void Hex :: playGame()
{
	bool result1 = false, result2 = false, isAvailable;
	int x, y, num;
	bool isSizeValid = false, isStyleValid = false;
	string str;

	while(!isSizeValid)
	{
		cout << "Please enter the size of the board : ";
		getline(cin, str);
		num = stoi(str);
		if (num < 6 && num < 27)	cerr << "Invalid Number. Please try again." << endl;
		else isSizeValid = true;
 	}
 	setSize(num);	
	
	while(!isStyleValid)
	{
		cout << "Please enter a number (0 for Player vs Player , 1 for Player vs Computer): ";
		getline(cin, str);
		num = stoi(str);
		if (num != 1 && num != 0)	cerr << "Invalid Number. Please try again." << endl;
		else isStyleValid = true;
 	}

 	setPlayStyle(num);
	hexCells = setVector(getSize());

	while (!result1 && !result2 && getQuit() == false)
	{
		
		displayBoard();
		if(getTurn() == true && getPlayStyle() == 1 && isAvailable == true)
		{	
			play();	
			displayBoard();			
		}
		turnController(x, y, isAvailable);
		

		vector<vector<Hex::Cell>> visitedCells = setVector(size);
		result1 = didPlayerOneWin(hexCells, visitedCells, 0, 0, getSize());
		result2 = didPlayerTwoWin(hexCells, visitedCells, 0, 0, getSize());

		if(result1)	cout << "PLAYER 1 WON!";
		else if(result2)	cout << "PLAYER 2 WON!";
	}


}

void Hex :: turnController(int & x, int & y, bool & isAvailable)
{
	string cordinate;
	bool isPlayable = false;

		if (playStyle == 0 && turn)	cout << "Player 2 Turn :" << endl;
		else if (!turn)	cout << "Player 1 Turn :" << endl;
	
		cout << "Enter the cordinate (Column / Raw) : ";
		getline(cin, cordinate);
		cout << endl;

		if(cordinate.length() == 2)		x = cordinate[1] - 1 - '0';
		else if (cordinate.length() == 3)	x = 10 + cordinate[2] - 1 - '0';		

		if(cordinate.substr(0, 4) == "SAVE")
		{
			save(cordinate);
			isPlayable = false;
		}	

		else if(cordinate.substr(0, 4) == "LOAD")
		{
			isPlayable = false;
			load(cordinate);		
		}
		else if (cordinate == "quit")	setQuit(true);

		else if((cordinate.length() == 2 || cordinate.length() == 3) && cordinate.at(0) >= 'A' && cordinate.at(0) < 'A' + size && x >= 0 && x < size)	
		
{			y = cordinate.at(0) - 'A';
			if(hexCells[x][y].getCellState() != Cell::cellState::X && hexCells[x][y].getCellState() != Cell::cellState::O)
			isPlayable = true;
			else isPlayable = false; 
		}
		else 
		{
			isPlayable = false;
			cerr << "You entered an invalid command" << endl;
		}

		if(isPlayable)
		{		
			if(getPlayStyle() == 0)	
			{	
				play(x, y);
			}

			else if (getPlayStyle() == 1)
			{
				isPlayable = true;
					
				if(getTurn() == false)
				{
					play(x, y);
				}
				
			}	
		}

	isAvailable = isPlayable;	
}

void Hex :: displayBoard ()
{
	int i, k, j;

	cout << " ";
	for (i = 0; i < getSize(); i++)	cout << (char)('a' + i) << " ";
	cout << endl;	

	for (i = 0; i < getSize(); i++)
	{
		cout << i + 1;
		for (k = 0; k < i; k++)	cout << " "; 
		
		for (j = 0; j < getSize(); j++)
		{
			if (hexCells[i][j].state == Cell::cellState::X)	cout << "X ";
			else if (hexCells[i][j].state == Cell::cellState::O)	cout << "O ";
			else	cout << ". ";
		}
		cout << endl;
	}
}

///////////////////////   WIN CONDITION   ////////////////////////////

bool Hex :: didPlayerOneWin(vector<vector<Hex::Cell>> hexCells, vector<vector<Hex::Cell>> visitedCells, int x, int y, int limit)		// Recursive function for checking if Player One win the game.(Right to Left)
{
	
	if (y == limit - 1 && hexCells[x][y].state == Cell::cellState::X)
	{
		return true;
	}

	if (hexCells[x][y].state == Cell::cellState::X && ((visitedCells[x][y].state != Cell::cellState::X) && (visitedCells[x][y].state != Cell::cellState::O)))
	{
		visitedCells[x][y].state = Cell::cellState::X;

		if (y != limit - 1)
		{
			if(didPlayerOneWin(hexCells, visitedCells, x, y + 1, limit))		return true;
		}

		if (x != limit - 1)
		{
			if(didPlayerOneWin(hexCells, visitedCells, x + 1, y, limit))		return true;
		}

		if (x != limit - 1 && y != 0 ) 
		{
			if(didPlayerOneWin(hexCells, visitedCells, x + 1, y - 1, limit))	return true;
		}
			
		if (x != 0)
		{
			if(didPlayerOneWin(hexCells, visitedCells, x - 1 , y, limit))		return true;
		}

		if (y != 0)
		{
			if(didPlayerOneWin(hexCells, visitedCells, x, y - 1, limit))		return true;
		}
		
		if (x != 0 && y != limit - 1)
		{
			if(didPlayerOneWin(hexCells, visitedCells, x - 1 , y + 1, limit))	return true;
		}			
		
		return false;
	}
	x++;

	if (x < limit && y == 0 && didPlayerOneWin (hexCells, visitedCells, x, y, limit))	return true;
		return false;
}

bool Hex :: didPlayerTwoWin(vector<vector<Hex::Cell>> hexCells, vector<vector<Hex::Cell>> visitedCells, int x, int y, int limit)		// Recursive function for checking if Player Two win the game.(Top to Bottom)
{
	
	if (x == limit - 1 && hexCells[x][y].state == Cell::cellState::O)
	{
		return true;
	}

	if (hexCells[x][y].state == Cell::cellState::O && ((visitedCells[x][y].state != Cell::cellState::X) && (visitedCells[x][y].state != Cell::cellState::O)))
	{
		visitedCells[x][y].state = Cell::cellState::O;

		if (y != limit - 1)
		{
			if(didPlayerTwoWin(hexCells, visitedCells, x, y + 1, limit))		return true;
		}

		if (x != limit - 1)
		{
			if(didPlayerTwoWin(hexCells, visitedCells, x + 1, y, limit))		return true;
		}

		if (x != limit - 1 && y != limit -1 ) 
		{
			if(didPlayerTwoWin(hexCells, visitedCells, x + 1, y + 1, limit))	return true;
		}
			
		if (x != 0)
		{
			if(didPlayerTwoWin(hexCells, visitedCells, x - 1 , y, limit))		return true;
		}

		if (y != 0)
		{
			if(didPlayerTwoWin(hexCells, visitedCells, x, y - 1, limit))		return true;
		}
		
		if (x != 0 && y != 0)
		{
			if(didPlayerTwoWin(hexCells, visitedCells, x - 1 , y + 1, limit))	return true;
		}			
		
		return false;
	}
	y++;

	if (y < limit && x == 0 && didPlayerTwoWin (hexCells, visitedCells, x, y, limit))	return true;
		return false;
}


////////////////////   SAVE / LOAD FUNCTIONS /////////////////////////

void Hex :: save (string fileName)
{
	int t, ps, s;
	char str[20], c;
	fileName += 5;

	for (int i = 5; i < fileName.length() + 5; i++)	str[i - 5] = fileName[i];
	str[fileName.length() - 1 - 5] = '\0';
	ofstream file;
	file.open(str);		// Saves cordinates, field size, play style and turn
	
	if (file.fail())	cerr<<"Couldn't open file" << endl;
						
	else
	{
		if (getTurn() == false)	t = 0;
		else if (getTurn() == true)	t = 1;

		for(int i = 0; i < getSize(); i++)
		{
			for (int j = 0; j < getSize(); j++)
			{
				if(hexCells[i][j].getCellState() == Cell::cellState::X)	c = 'X';
				else if (hexCells[i][j].getCellState() == Cell::cellState::O) c = 'O';
				else	c = '.';
				file << c;
			}
		}

		ps = getPlayStyle();
		s = getSize();

		file  << endl << s  << endl << ps  << endl << t;
		file.close();
	}

}

void Hex :: load (string fileName)
{
	string str, str1, str2, str3, str4;
	fileName += 5;
	int counter = 0, turnFlag, i = 0, j;		// Loads game data
	ifstream file;

	for (int i = 5; i < fileName.length() + 5; i++)	str[i - 5] = fileName[i];
	str[fileName.length() - 1 - 5] = '\0';

	file.open(str);
	if (file.fail())	cerr<<"Couldn't open file" << endl;

	else
	{	
		getline(file, str1);								// Reads file line by line
		getline(file, str2);
		getline(file, str3);
		getline(file, str4);
	}

	setSize(stoi(str2));
	setPlayStyle(stoi(str3));
	turnFlag = stoi(str4);

	if(!turnFlag)	setTurn(false);
	else if(turnFlag)	setTurn(true);

	hexCells = setVector(size);

	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
		{
			if(str1[i * size + j] == 'X')	hexCells[i][j].setState(Cell::cellState::X);
			if(str1[i * size + j] == 'O')	hexCells[i][j].setState(Cell::cellState::O);	
			
			hexCells[i][j].setRow(i);
			hexCells[i][j].setColumn((char)('A' + j));
		}
	}

	file.close();
} 