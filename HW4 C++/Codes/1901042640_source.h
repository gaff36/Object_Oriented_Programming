#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class Hex
{
	public :

	class Cell
	{
		public :
		enum cellState {X = 'X', O = 'O'};
		cellState state;
		int row, playNum;
		char column;
		Cell();
		Cell(const int row, const char column, const cellState state, const int playNum);
		Cell(const cellState state);
		int getRow()				const	{return row;}				
		int getPlayNum()			const	{return playNum;}	
		char getColumn()			const	{return column;}		
		cellState getCellState()	const 	{return state;}
		void setRow(const int row);
		void setPlayNum(const int playNum);
		void setColumn(const char column);
		void setState(const cellState state);
	};

	void operator = (Hex & hex);		// BIG THREE
	 Hex (const Hex & hex);
	~Hex();

	explicit Hex();
	explicit Hex(int size, int playStyle);
	Hex(const int size);
	int getSize()			const	{return size;}
	int getPlayStyle()		const	{return playStyle;}
	bool getTurn()			const	{return turn;}
	int getMoveNum()		const	{return moveNum;}
	Cell ** getHexCells()	const 	{return hexCells;}

	void setSize(const int size);
	void setPlayStyle(const int playStyle);
	void setMoveNum(const int moveNum);
	void setHexCells();
	friend ostream & operator << (ostream & output, const Hex &hex);
	friend istream & operator >> (istream & input, const Hex & hex);
	friend ofstream & operator << (ofstream & output, const Hex &hex);
	friend ifstream & operator >> (ifstream & input, Hex & hex);
	bool operator == (Hex & h2);
	void operator -- ();
	void operator -- (int ignoreMe);
	
	Cell *play(const int x, const int y);
	void play();
	bool areaScanner(int x, int y, Cell :: cellState state, int visited[24][24]);
	bool didPlayerOneWin(Cell ** visitedCells, int x, int y, int limit);
	bool didPlayerTwoWin(Cell ** visitedCells, int x, int y, int limit);
	int score(int visited[24][24], int x, int y, int currentScore, int highScore);
	int scoreCheck();
	void playGame();
	
	private :
	Cell ** hexCells;
	int size, playStyle, moveNum = -1;
	bool turn = false, p = false;
};

Hex :: Hex()
{
	setSize(6);
	setPlayStyle(0);
	setHexCells();
}

Hex :: Hex (int size, int playStyle)
{
	setSize(size);
	setPlayStyle(playStyle);
	setHexCells();
}

Hex :: Hex (const int size)
{
	setSize(size);
	setPlayStyle(1);
	setHexCells();
}

Hex :: Hex (const Hex & hex)
{
	size = hex.size;
	playStyle = hex.playStyle;
	turn = hex.turn;
	moveNum = hex.moveNum;
	setHexCells();

	for(int i = 0; i < hex.size * hex.size; i++)
	{
		if(hex.hexCells[i] != NULL)
		{
			hexCells[i] = new Cell;
	 		hexCells[i][0] = hex.getHexCells()[i][0];
		}
		else 
		{
			hexCells[i] = nullptr;
		}
	}
}

Hex :: ~Hex()
{
	if(this)
	{
		for(int i = 0; i < getSize() * getSize(); i++)
		{
			delete [] this->hexCells[i];	
			//this->hexCells[i] = nullptr;
		}
		
	}
}

Hex :: Cell :: Cell()
{
}

Hex :: Cell :: Cell(int row, char column, cellState state, int playNum)
{
	setRow(row);
	setColumn(column);
	setState(state);
	setPlayNum(playNum);
}

Hex :: Cell :: Cell (const cellState state)
{
	this -> state = state;
}

////////////////////// SETTERS //////////////////////

void Hex :: setSize(int size)
{
	this -> size = size;
}

void Hex :: setPlayStyle(int playStyle)
{
	this -> playStyle = playStyle;
}

void Hex :: setMoveNum(int moveNum)
{
	this -> moveNum = moveNum;
}

void Hex :: setHexCells()
{
	hexCells = new Cell * [getSize() * getSize()];
	for (int i = 0; i < getSize() * getSize(); i++)
	{
		//hexCells[i] = new Cell;
		hexCells[i] = nullptr;
	}
}

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

void Hex :: Cell :: setPlayNum(int playNum)
{
	this -> playNum = playNum;
}

////////////////////// OPERATOR OVERLOADS ////////////////////// 

ostream & operator << (ostream & output, Hex &hex)	
{
	output << " ";
	for (int i = 0; i < hex.getSize(); i++)	output << (char)('a' + i) << " ";
	output << endl;

	for (int i = 0; i < hex.getSize(); i++)
	{
		output << i + 1;
		for (int k = 0; k < i; k++)	output << " "; 

		for (int j = 0; j < hex.getSize(); j++)
		{
			if(hex.getHexCells()[i * hex.getSize() + j] == NULL) output << ". ";
			else if (hex.getHexCells()[i * hex.getSize() + j][0].getCellState() == Hex::Cell::cellState::X)	output << "X ";
			else if (hex.getHexCells()[i * hex.getSize() + j][0].getCellState() == Hex::Cell::cellState::O)	output << "O ";
			
		}
		output << endl; 
		
	}

	if (hex.getTurn() == false)	output << "PLAYER 1 TURN" << endl;
	else if (hex.getTurn() == true)	output << "PLAYER 2 TURN" << endl;
	output << "Enter the cordinate (Column / Raw) : ";
	return output;
}

istream & operator >> (istream & input, Hex &hex)
{
	string str;
	cout << "Please enter the size of the board : ";
	input >> str;
	hex.setSize(stoi(str));
	cout << "Please enter a number (0 for Player vs Player , 1 for Player vs Computer): ";
	input >> str;
	hex.setPlayStyle(stoi(str));
	return input;
}

ofstream & operator << (ofstream & output, Hex &hex)
{
	char c;
	int t;

	for(int i = 0; i < hex.getSize(); i++)
	{
		for (int j = 0; j < hex.getSize(); j++)
		{
			if(hex.getHexCells()[i * hex.getSize() + j] == NULL)	c = '.';
			else if(hex.getHexCells()[i * hex.getSize() + j]->getCellState() == Hex::Cell::cellState::X)	c = 'X';
			else if (hex.getHexCells()[i * hex.getSize() + j]->getCellState() == Hex::Cell::cellState::O) c = 'O';			
			output << c;
		}
	}

	if(hex.getTurn() == false)	t = 0;
	else	t = 1;

	output << endl << hex.getSize() << endl << hex.getPlayStyle() << endl << t;

	return output;
}

ifstream & operator >> (ifstream & input, Hex &hex)
{
	string str1, str2, str3, str4;
	int turnFlag;

	input >> str1;			// Reads file line by line
	input >> str2;
	input >> str3;
	input >> str4;

	hex.setSize(stoi(str2));
	hex.setPlayStyle(stoi(str3));
	hex.setHexCells();
	turnFlag = stoi(str4);

	if(turnFlag == 0)	hex.turn = false;
	if(turnFlag == 1)	hex.turn = true;

	for(int i = 0; i < hex.getSize(); i++)
	{
		for(int j = 0; j < hex.getSize(); j++)
		{
			if(str1[i * hex.getSize() + j] == 'X')	hex.getHexCells()[i * hex.getSize() + j]->setState(Hex::Cell::cellState::X);
			else if(str1[i * hex.getSize() + j] == 'O')	hex.getHexCells()[i * hex.getSize() + j]->setState(Hex::Cell::cellState::O);
			
			
			hex.getHexCells()[i * hex.getSize() + j]->setRow(i);
			hex.getHexCells()[i * hex.getSize() + j]->setColumn((char)('A' + j));
			hex.getHexCells()[i * hex.getSize() + j]->setPlayNum(0);
		}
	}

	return input;
}

 bool Hex :: operator == (Hex & h2)			// Operator for comparison
 {
 	int counter1 = 0, counter2 = 0;

 	for (int i = 0; i < getSize() * getSize(); i++)
 	{
 		if(hexCells[i] != NULL && hexCells[i]->getCellState() == Cell :: cellState :: X)	counter1++;
 	}
 	for (int i = 0; i < getSize() * getSize(); i++)
 	{
 		if(h2.hexCells[i] != NULL && h2.hexCells[i]->getCellState() == Cell :: cellState :: X)	counter2++;
 	}

 	if(counter1 > counter2)	return true;
 	else return false;
 }

void Hex :: operator -- (int ignoreMe)			// Post dicrement
{
	for (int i = 0; i < getSize() * getSize(); i++)
	{	
			if(hexCells[i] != NULL && hexCells[i]->playNum == moveNum)	
			{
				delete []hexCells[i];
				hexCells[i] = nullptr;
			}		
	}
	moveNum--;
}

void Hex :: operator -- ()				// Pre dicrement
{
	for (int i = 0; i < getSize() * getSize(); i++)
	{	
			if(hexCells[i] != NULL && hexCells[i]->playNum == moveNum)	
			{
				delete []hexCells[i];
				hexCells[i] = nullptr;
			}		
	}
	moveNum--;
}

void Hex :: operator = (Hex & hex)		// Assign operator
{
	size = hex.size;
	playStyle = hex.playStyle;
	turn = hex.turn;
	moveNum = hex.moveNum;
	setHexCells();

	for(int i = 0; i < hex.size * hex.size; i++)
	{
		if(hex.hexCells[i] != NULL)
		{
			hexCells[i] = new Cell;
	 		hexCells[i][0] = hex.getHexCells()[i][0];
		}
		else 
		{
			hexCells[i] = nullptr;
		}
	}
}

///////////////// WIN CONDITION ///////////////////

bool Hex :: didPlayerOneWin(Cell ** visitedCells, int x, int y, int limit)		// Recursive function for checking if Player One win the game.(Right to Left)
{
	
	if (y == limit - 1 && hexCells[x * getSize() + y]->state == Cell::cellState::X)
	{
		return true;
	}

	if (hexCells[x * getSize() + y]->state == Cell::cellState::X && ((visitedCells[x * getSize() + y]->state != Cell::cellState::X) && (visitedCells[x * getSize() + y]->state != Cell::cellState::O)))
	{
		visitedCells[x * getSize() + y]->state = Cell::cellState::X;

		if (y != limit - 1)
		{
			if(didPlayerOneWin(visitedCells, x, y + 1, limit))		return true;
		}

		if (x != limit - 1)
		{
			if(didPlayerOneWin(visitedCells, x + 1, y, limit))		return true;
		}

		if (x != limit - 1 && y != 0 ) 
		{
			if(didPlayerOneWin(visitedCells, x + 1, y - 1, limit))	return true;
		}
			
		if (x != 0)
		{
			if(didPlayerOneWin(visitedCells, x - 1 , y, limit))		return true;
		}

		if (y != 0)
		{
			if(didPlayerOneWin(visitedCells, x, y - 1, limit))		return true;
		}
		
		if (x != 0 && y != limit - 1)
		{
			if(didPlayerOneWin(visitedCells, x - 1 , y + 1, limit))	return true;
		}			
		
		return false;
	}
	x++;

	if (x < limit && y == 0 && didPlayerOneWin (visitedCells, x, y, limit))	return true;
		return false;
}

bool Hex :: didPlayerTwoWin(Cell ** visitedCells, int x, int y, int limit)		// Recursive function for checking if Player Two win the game.(Top to Bottom)
{

	if (x == limit - 1 && hexCells[x * getSize() + y]->state == Cell::cellState::O)
	{
		return true;
	}

	if (hexCells[x * getSize() + y]->state == Cell::cellState::O && ((visitedCells[x * getSize() + y]->state != Cell::cellState::X) && (visitedCells[x * getSize() + y]->state != Cell::cellState::O)))
	{
		visitedCells[x * getSize() + y]->state = Cell::cellState::O;

		if (y != limit - 1)
		{
			if(didPlayerTwoWin(visitedCells, x, y + 1, limit))		return true;
		}

		if (x != limit - 1)
		{
			if(didPlayerTwoWin(visitedCells, x + 1, y, limit))		return true;
		}

		if (x != limit - 1 && y != limit -1 ) 
		{
			if(didPlayerTwoWin(visitedCells, x + 1, y + 1, limit))	return true;
		}
			
		if (x != 0)
		{
			if(didPlayerTwoWin(visitedCells, x - 1 , y, limit))		return true;
		}

		if (y != 0)
		{
			if(didPlayerTwoWin(visitedCells, x, y - 1, limit))		return true;
		}
		
		if (x != 0 && y != 0)
		{
			if(didPlayerTwoWin(visitedCells, x - 1 , y + 1, limit))	return true;
		}			
		
		return false;
	}
	y++;

	if (y < limit && x == 0 && didPlayerTwoWin (visitedCells, x, y, limit))	return true;
		return false;
}

bool Hex :: areaScanner(int x, int y, Cell :: cellState state, int visited[24][24])			// Scans cells next to this
{
	bool result = false;

		if(x < getSize() && hexCells[(x + 1) * getSize() + y] != NULL && hexCells[(x + 1) * getSize() + y]->getCellState() == Cell :: cellState :: X && visited[x + 1][y] == 0)	result = true;
		if(x > 0 && hexCells[(x - 1) * getSize() + y] != NULL && hexCells[(x - 1) * getSize() + y]->getCellState() == Cell :: cellState :: X && visited[x - 1][y] == 0)	result = true;
		if(y < getSize() && hexCells[x * getSize() + y + 1] != NULL && hexCells[x * getSize() + y + 1]->getCellState() == Cell :: cellState :: X && visited[x][y + 1] == 0)	result = true;
		if(y > 0 && hexCells[x * getSize() + y - 1] != NULL && hexCells[x * getSize() + y - 1]->getCellState() == Cell :: cellState :: X && visited[x][y - 1] == 0)	result = true;
		if(x < getSize() && y > 0 && hexCells[(x + 1) * getSize() + y - 1] != NULL && hexCells[(x + 1) * getSize() + y - 1]->getCellState() == Cell :: cellState :: X && visited[x + 1][y - 1] == 0)	result = true;
		if(x > 0 && y < getSize() && hexCells[(x - 1) * getSize() + y + 1] != NULL && hexCells[(x - 1) * getSize() + y + 1]->getCellState() == Cell :: cellState :: X && visited[x - 1][y + 1] == 0)	result = true;
	
	return result;
}

int Hex :: scoreCheck()			// counts score
{
	int max = 0, current;	
	int visitedCells[24][24] = {0};
	
	for (int i = 0; i < getSize(); i++)
	{
		for (int i = 0; i < 24; i++)
		{
			for (int j = 0; j < 24; j++)	visitedCells[i][j] = 0;
		}

		current  = score(visitedCells, i, 0, 0, 0);
		if(current > max)	max = current;
	}
	return max;
}

int Hex :: score (int visited[24][24], int x, int y, int currentScore, int highScore)
{
	if(x == getSize() - 1 && hexCells[x * getSize() + y] != NULL && hexCells[x * getSize() + y]->getCellState() == Cell :: cellState :: X && areaScanner(x, y, Cell :: cellState :: X, visited) == false
		&& visited[x][y] == 0)
	{
		return 0;
	}

	if(hexCells[x * getSize() + y] != NULL && hexCells[x * getSize() + y]->getCellState() == Cell :: cellState :: X && visited[x][y] == 0)
	{
		visited[x][y] = 1;
		if(y != getSize())
		{
			currentScore++;
			return score(visited, x, y + 1, currentScore, highScore) + 1;
		}
		else if(y >= 0)
		{
			currentScore++;
			return score(visited, x, y - 1, currentScore, highScore) + 1;
		}
		else if(x != getSize())
		{
			currentScore++;
			return score(visited, x + 1, y, currentScore, highScore) + 1;
		}
		else if(x >= 0)
		{
			currentScore++;
			return score(visited, x - 1, y, currentScore, highScore) + 1;
		}
		else if(x >= 0 && y != getSize())
		{
			currentScore++;
			return score(visited, x - 1, y + 1, currentScore, highScore) + 1;
		}
		else if(y >= 0 && x != getSize())
		{
			currentScore++;
			return score(visited, x + 1, y - 1, currentScore, highScore) + 1;
		}

		if(currentScore > highScore)	highScore = currentScore;
			
	}
		
}

Hex :: Cell* Hex :: play(int x, int y)		// User play function
{
	Cell *cell = new Cell;
	moveNum++;
	if(getTurn() == false)
	{
		*cell = {x, y, Cell :: cellState :: X, moveNum};
	}	
	else	
	{
		*cell = {x, y, Cell :: cellState :: O, moveNum};
	}
	
	return cell;		
}

////////////////////// GAMEPLAY //////////////////////
	
void Hex :: play ()			// Play function for computer
{		
	int x1, y1;
	bool done = false;

	for (int i = 0; i < getSize(); i++)
	{
		for (int j = 0; j < getSize(); j++)
		{
			if (!done && hexCells[i * getSize() + j] != NULL && hexCells[i * getSize() + j]->getCellState() == Cell :: cellState :: O && hexCells[(i + 1) * getSize() + j] == NULL)
			{
				x1 = i + 1;
				y1 = j;
				done = true;
				break;
			}
			else if (!done && hexCells[i * getSize() + j] != NULL && hexCells[i * getSize() + j]->getCellState() == Cell :: cellState :: O && hexCells[(i - 1) * getSize() + j] == NULL)
			{
				x1 = i - 1;
				y1 = j;
				done = true;
				break;
			}
			else if (!done && hexCells[i * getSize() + j] != NULL && hexCells[i * getSize() + j]->getCellState() == Cell :: cellState :: O && hexCells[i * getSize() + j + 1] == NULL)
			{
				x1 = i;
				y1 = j + 1;
				done = true;
				break;
			}
			else if (!done && hexCells[i * getSize() + j] != NULL && hexCells[i * getSize() + j]->getCellState() == Cell :: cellState :: O && hexCells[i * getSize() + j - 1] == NULL)
			{
				x1 = i;
				y1 = j - 1;
				done = true;
				break;
			}
			else if (!done && hexCells[i * getSize() + j] != NULL && hexCells[i * getSize() + j]->getCellState() == Cell :: cellState :: O && hexCells[(i - 1 )* getSize() + j + 1] == NULL)
			{
				x1 = i - 1;
				y1 = j + 1;
				done = true;
				break;
			}
			else if (!done && hexCells[i * getSize() + j] != NULL && hexCells[i * getSize() + j]->getCellState() == Cell :: cellState :: O && hexCells[(i + 1 )* getSize() + j - 1] == NULL)
			{
				x1 = i + 1;
				y1 = j - 1;
				done = true;
				break;
			}
			else 
			{	
				x1 = i;
				y1 = j;
				done = true;
				break;
			}
		}
		if(done)	break;
	}
	
	if(done && hexCells[x1 * getSize() + y1] == NULL)
	{
		Cell * cell = new Cell;
		moveNum++;
		turn = false;
		*cell = {x1, y1, Cell :: cellState :: O, moveNum};
		cout << "Player 2 (Computer) played on : " << char(y1 + 'A') << x1 + 1 << endl;
		hexCells[x1 * getSize() + y1] = cell;
	}
}

void Hex :: playGame()		// Main play function
{
	bool played = false;
	bool result1 = false, result2 = false;
	int x, y, num;
	bool isValid = false, quit = false;
	string str;
	Cell ** visitedCells = new Cell * [getSize() * getSize()];

 	Cell ** visited = new Cell * [getSize()];
	for (int i = 0; i < getSize(); i++)	visited[i] = new Cell [getSize()];

	this->setHexCells();	

	while (!result1 && !result2 && !quit)
	{
		played = false;
		getline(cin, str);
		if(str.length() == 2)		x = str[1] - 1 - '0';
		else if (str.length() == 3)	x = 10 + str[2] - 1 - '0';
		y = str[0] - 'A';			
	
		if (str.substr(0, 4) == "SAVE")			// Saves the game to a file
		{
			ofstream saveFile;
			str = str.substr(5,str.length() - 1);
			saveFile.open(str);
			if (saveFile.fail())	cerr<<"Couldn't open file" << endl;
			else	saveFile << *this;
			saveFile.close();
		}

		else if (str.substr(0, 4) == "LOAD")		// Loads from file
		{				
			ifstream loadFile;
			str = str.substr(5,str.length() - 1);cout << str;

			loadFile.open(str);
			if (loadFile.fail())	cerr<<	"Couldn't open file" << endl;
			else	loadFile >> *this;
		
		

			loadFile.close();
		}

		else if (str.substr(0, 4) == "quit")		// quits game
		{	
			quit = true;
			cout << endl;
		}

		else if (str.substr(0, 5) == "score")			// prints the user's score
		{
			cout << "User's score is:" << scoreCheck() << endl;;
		}

		else if (str.substr(0, 4) == "undo")		// deletes the last move
		{
			if(getPlayStyle() == 0)
			--(*this);
			else if(getPlayStyle() == 1)
			{
				--(*this);
				(*this)--;
			}
		}

		if(x >= 0 && x < getSize() && y >= 0 && y < getSize())
		{
			if(hexCells[x * getSize() + y] == nullptr);
			{
				hexCells[x * getSize() + y] = play(x, y);
				if(getTurn() == false)	turn = true; 
				else	turn = false; 
				played = true;
			}
		}
		if(getPlayStyle() == 1 && played == true)
		{
			play();
		}

		if(result1)	cout << "PLAYER 1 WON!" << "User's score is :" << scoreCheck() << endl;
		else if(result2)	cout << "PLAYER 2 WON!";
		if(!result1 && !result2 && !quit)cout << *this;

		for (int i = 0; i < getSize() * getSize(); i++)	visitedCells[i] = nullptr;
	}
}


