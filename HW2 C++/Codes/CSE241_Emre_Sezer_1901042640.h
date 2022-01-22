#include <iostream>
#include <fstream>
#include <string>

enum cellState	{NONE, X, O};	// NONE for null, X for Player 1, O for Player 2

using namespace std;

void gameController();
void drawField(const cellState  field[20][20], const int & size);
bool didPlayerOneWin(cellState field[20][20], cellState visited[20][20], int x, int y, int limit);
bool didPlayerTwoWin(cellState field[20][20], cellState visited[20][20], int x, int y, int limit);
void ai (cellState arr1[20][20], int x0, int y0, int limit, bool* defence);
void arrayZeroing (cellState arr[20][20], int limit);
void turnController(cellState field[20][20] ,int & size ,bool &turn, int & playStyle);
void saveField (cellState field[20][20], const int &size, const  int &playStyle, bool & turn, string fileName);
void loadField(cellState field[20][20], int & size, int & playStyle, string fileName);
char cellStateToCharConverter (cellState state);
cellState charToCellStateConverter (char c);

void gameController()
{
	string strSize, strStyle;
	bool result1 = false, result2 = false, isSizevalid = false, isStyleValid = false;
	auto turn = false;
	int size;
	decltype(size) style;

	cellState field[20][20] = {NONE}, visited[20][20] = {NONE};

	while (!isSizevalid)
	{
		cout << "Enter the size of the field : (Minimum 6, Maximum 12)" << endl;
		getline(cin, strSize);

		if (strSize.length() == 1)	size = strSize.at(0) - '0';
		else if (strSize.length() == 2)	size = 10 + strSize.at(1) - '0';

		if (size >= 6 && size <= 12)
		{			
			isSizevalid = true;
		}	
		else	cerr << "You entered an invalid number." << endl;
			
	}

	while (!isStyleValid)
	{
		cout << "Enter 0 or 1 for play style : (0 for Singleplayer / 1 for Multiplayer)" << endl;
		getline(cin, strStyle);
		style = strStyle.at(0) - '0';

		if (style == 0 || style == 1)
		{
			isStyleValid = true;
		}
		else	cerr << "You entered an invalid number." << endl;
	}

	drawField (field, size);

	while (!result1 && !result2)
		{

			turnController(field, size, turn, style);

			result1 = didPlayerOneWin(field, visited, 0, 0, size);
			result2 = didPlayerTwoWin(field, visited, 0, 0, size); 
		
			arrayZeroing (visited, 12);

			if(result1 == true)	cout << "PLAYER 1 WON!" << endl;
			else if(result2 == true)	cout << "PLAYER 2 WON!" << endl;
		}
}

void saveField (cellState field[20][20], const int & size, const  int &playStyle, bool & turn,  string fileName)
{
	int t;
	char str[20];
	fileName += 5;

	for (int i = 5; i < fileName.length() + 5; i++)	str[i - 5] = fileName[i];
	str[fileName.length() - 1 - 5] = '\0';
	ofstream file;
	file.open(str);		// Saves cordinates, field size, play style and turn
	
	if (file.fail())	cerr<<"Couldn't open file" << endl;
						
	else
	{
		if (turn == false)	t = 0;
		else if (turn == true)	t = 1;

		for(int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				file << cellStateToCharConverter(field[i][j]);
			}
		}
		file  << endl << size  << endl << playStyle  << endl << t;
		file.close();
	}
}

void loadField(cellState field[20][20], int & size, int & playStyle, bool & turn, string fileName)
{
	cellState arr[300];
	fileName += 5;
	char c, str[20];
	int counter = 0, turnFlag, i = 0, j;		// Loads game data
	ifstream file;

	for (int i = 5; i < fileName.length() + 5; i++)	str[i - 5] = fileName[i];
	str[fileName.length() - 1 - 5] = '\0';

	file.open(str);
	if (file.fail())	cerr<<"Couldn't open file" << endl;

	else
	{
		while (!file.eof())
		{

			file >> c;									// Reads file char by char

			if (c != '.' && c != 'X' && c != 'O' && c != '\n')	
			{
				if (counter == 0)
				{		
						if(c == '1')					// If field size has 2 digits
						{
							file >> c;
							size = 10 + c - '0';
						}
						else 	size = c - '0';			// If field size has 1 digit								
					}
					
				
				else if (counter == 1)	playStyle = c - '0';
				else if (counter == 2)
				{
					turnFlag = c - '0'; 
					if (turnFlag == 0)	turn = 0;
					else if(turnFlag == 1)	turn = 1;
				} 
				counter++; 
			}	

			else
			{
				arr[i] = charToCellStateConverter(c);			// Stores field data on an array
				i++;				
			}

		}
	
	}

	for (i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			field[i][j] = arr[size * i + j];					// Puts field data on actually field array
		}
	}


	file.close();
}
char cellStateToCharConverter (cellState state = NONE)		// Converts cellState to Char
{
	char c;
	if(state == NONE)	c = '.';
	else if (state == X)	c = 'X';
	else if (state == O)	c = 'O';	
	return c;
}

cellState charToCellStateConverter (char c = '.')			// Converts char to cellState
{
	cellState state;
	if(c == '.')	state = NONE;
	else if(c == 'X')	state = X;
	else if(c == 'O')	state = O;
	return state;
}


void drawField(const cellState field[20][20], const int &size)			// Draws the field.
{
	int i, j, k;

	cout << " ";
	for (i = 0; i < size; i++)	cout << (char)('a' + i) << " ";
	cout << endl;	

	for (i = 0; i < size; i++)
	{
		cout << i + 1;
		for (k = 0; k < i; k++)	
			{
				cout << " "; 
			}
		
		for (j = 0; j < size; j++)
		{

			if(field[i][j] == NONE)	cout << ". ";
			else if (field[i][j] == X)	cout << "X ";
			else if (field[i][j] == O)	cout << "O ";
		}
		cout << endl;
	}
}	

void ai (cellState arr1[20][20], int x0, int y0, int limit, bool* defence)			// Generates moves for AI.
{
	int x1, y1;
	bool done = false;
	

	for (int i = 0; i < limit; i++)
	{
		for (int j = 0; j < limit; j++)
		{
			if (!done && arr1[i][j] == O && arr1[i + 1][j] == NONE && i != limit - 1)
			{
				x1 = i + 1;
				y1 = j;
				done = true;
			}
			else if (!done && arr1[i][j] == O && arr1[i - 1][j] == NONE && i != 0)
			{
				x1 = i - 1;
				y1 = j;
				done = true;
			}
			else if (!done && arr1[i][j] == O && arr1[i][j + 1] == NONE && j != limit - 1 && (arr1[i + 1][j] != NONE || arr1[i - 1][j] != NONE))
			{
				x1 = i;
				y1 = j + 1;
				done = true;				
			}
			else if (!done && arr1[i][j] == O && arr1[i][j - 1] == NONE && j != 0 && (arr1[i + 1][j] != NONE || arr1[i - 1][j] != NONE))
			{
				x1 = i;
				y1 = j - 1;
				done = true;				
			}
			else if (!done && arr1[i][j] == O && arr1[i - 1][j + 1] == NONE  && i != 0 && j != limit - 1 && (arr1[i + 1][j] != NONE || arr1[i - 1][j] != NONE))
			{
				x1 = i - 1;
				y1 = j + 1;
				done = true;				
			}
			else if (!done && arr1[i][j] == O && arr1[i + 1][j - 1] == NONE   && i != limit - 1 && j != 0 && (arr1[i + 1][j] != NONE || arr1[i - 1][j] != NONE))
			{
				x1 = i + 1;
				y1 = j - 1;
				done = true;				
			}
			else if(!done)
			{
				if(y0 == limit - 1)
				{
					x1 = x0;
					y1 = y0 - 1;
				}
				else if(y0 == 0)
				{
					x1 = x0;
					y1 = y0 + 1;
				}

			}			
		}
		
	}

	
		
		
	

	
	arr1[x1][y1] = O;
	cout << "Player 2 (Computer) played on : " << char(y1 + 'A') << x1 + 1 << endl; 

}

void arrayZeroing (cellState arr[20][20], int limit = 12)		// It makes array's all of the elements zero. It is a support function for win condition.
{
	for (int i = 0; i < limit; i++)
	{
			for (int j = 0; j < limit; j++)	arr[i][j] = NONE;
	}
}

bool didPlayerOneWin(cellState field[20][20], cellState visited[20][20], int x, int y, int limit)		// Recursive function for checking if Player One win the game.(Right to Left)
{
	
	if (y == limit - 1 && field[x][y] == X)
	{
		return true;
	}

	if (field[x][y] == X && visited[x][y] == NONE)
	{
		visited[x][y] = X;

		if (y != limit - 1)
		{
			if(didPlayerOneWin(field, visited, x, y + 1, limit))		return true;
		}

		if (x != limit - 1)
		{
			if(didPlayerOneWin(field, visited, x + 1, y, limit))		return true;
		}

		if (x != limit - 1 && y != 0 ) 
		{
			if(didPlayerOneWin(field, visited, x + 1, y - 1, limit))	return true;
		}
			
		if (x != 0)
		{
			if(didPlayerOneWin(field, visited, x - 1 , y, limit))		return true;
		}

		if (y != 0)
		{
			if(didPlayerOneWin(field, visited, x, y - 1, limit))		return true;
		}
		
		if (x != 0 && y != limit - 1)
		{
			if(didPlayerOneWin(field, visited, x - 1 , y + 1, limit))	return true;
		}			
		
		return false;
	}
	x++;

	if (x < limit && y == 0 && didPlayerOneWin (field, visited, x, y, limit))	return true;
		return false;
}

bool didPlayerTwoWin(cellState field[20][20], cellState visited[20][20], int x, int y, int limit)		// Recursive function for checking if Player Two win the game.(Top to Bottom)
{
	
	if (x == limit - X && field[x][y] == O)
	{
		return true;
	}

	if (field[x][y] == O && visited[x][y] == NONE)
	{
		visited[x][y] = O;

		if (y != limit - 1)
		{
			if(didPlayerTwoWin(field, visited, x, y + 1, limit))		return true;
		}

		if (x != limit - 1)
		{
			if(didPlayerTwoWin(field, visited, x + 1, y, limit))		return true;
		}

		if (x != limit - 1 && y != limit -1 ) 
		{
			if(didPlayerTwoWin(field, visited, x + 1, y + 1, limit))	return true;
		}
			
		if (x != 0)
		{
			if(didPlayerTwoWin(field, visited, x - 1 , y, limit))		return true;
		}

		if (y != 0)
		{
			if(didPlayerTwoWin(field, visited, x, y - 1, limit))		return true;
		}
		
		if (x != 0 && y != 0)
		{
			if(didPlayerTwoWin(field, visited, x - 1 , y + 1, limit))	return true;
		}			
		
		return false;
	}
	y++;

	if (y < limit && x == 0 && didPlayerTwoWin (field, visited, x, y, limit))	return true;
		return false;
}

void turnController(cellState field[20][20] ,int& size ,bool & turn, int & playStyle)		// It controls turns
{
	// Turn 0 for Player 1 / 1 for Player 2
	
	string cordinate;
	int x, y;
	bool def = true, play = false;

		if (playStyle == 0 && turn)	cout << "Player 2 Turn :" << endl;
		else if (!turn)	cout << "Player 1 Turn :" << endl;
	
		cout << "Enter the cordinate (Column / Raw) : ";
		getline(cin, cordinate);
		cout << endl;

		if(cordinate.length() == 2)		x = cordinate[1] - 1 - '0';
		else if (cordinate.length() == 3)	x = 10 + cordinate[2] - 1 - '0';		

		if(cordinate.substr(0, 4) == "SAVE")	saveField(field, size, playStyle, turn, cordinate);

		else if(cordinate.substr(0, 4) == "LOAD")
		{
		arrayZeroing(field, 12);
		loadField(field, size, playStyle, turn, cordinate);		
		}

		else if((cordinate.length() == 2 || cordinate.length() == 3) && cordinate.at(0) >= 'A' && cordinate.at(0) < 'A' + size && x >= 0 && x < size)	
		{
			y = cordinate.at(0) - 'A';
			play = true;
		}
		else cerr << "You entered an invalid command" << endl;

	if(play)
	{	
		if(!turn && field[x][y] == NONE && x < size && y < size)	
		{
			field[x][y] = X;
			turn = true;
		}

		else if (!playStyle && turn)
		{
			if (turn && field[x][y] == NONE && x < size && y < size)	
			{			
				field[x][y] = O;
				turn = false;
			}
		}
		if (playStyle && turn)
		{
			ai (field ,x , y, size, &def);
			turn = false;
		}
	}
		drawField(field, size);	
}
