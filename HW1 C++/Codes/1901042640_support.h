#include <iostream>

using namespace std;

void drawField(int field[12][12], int size);
void turnController(int field[12][12] ,int size ,bool *turn, int playStyle);
bool isContinuous(int field[12][12], int x, int y);
bool didPlayerOneWin(int field[12][12], int visited[12][12], int x, int y, int limit);
bool didPlayerTwoWin(int field[12][12], int visited[12][12], int x, int y, int limit);
void arrayZeroing (int arr[12][12], int limit);
void ai (int arr1[12][12], int x0, int y0, int limit, bool* defence);
int areaScanner (int field[12][12], int x, int y, int num);

// Win Condition________________

bool didPlayerOneWin(int field[12][12], int visited[12][12], int x, int y, int limit)		// Recursive function for checking if Player One win the game.(Right to Left)
{
	
	if (y == limit - 1 && field[x][y] == 1)
	{
		return true;
	}

	if (field[x][y] == 1 && visited[x][y] == 0)
	{
		visited[x][y] = 1;

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

bool didPlayerTwoWin(int field[12][12], int visited[12][12], int x, int y, int limit)		// Recursive function for checking if Player Two win the game.(Top to Bottom)
{
	
	if (x == limit - 1 && field[x][y] == 2)
	{
		return true;
	}

	if (field[x][y] == 2 && visited[x][y] == 0)
	{
		visited[x][y] = 1;

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

void arrayZeroing (int arr[12][12], int limit)		// It makes array's all of the elements zero. It is a support function for win condition.
{
	for (int i = 0; i < limit; i++)
	{
			for (int j = 0; j < limit; j++)	arr[i][j] = 0;
	}
}

//_______________________________

int areaScanner (int field[12][12], int x, int y, int num)
{
	int sum = 0;
	if (field[x][y + 1] == num)	sum++;
	if (field[x][y - 1] == num)	sum++;
	if (field[x + 1][y] == num)	sum++;
	if (field[x - 1][y] == num)	sum++;
	if (field[x + 1][y - 1] == num)	sum++;
	if (field[x - 1][y + 1] == num)	sum++;

	return sum;
}


void ai (int arr1[12][12], int x0, int y0, int limit, bool* defence)	// Generates moves for AI.
{
	int x1, y1;
	bool done = false;
	
	for (int i = 0; i < limit; i++)
	{
		for (int j = 0; j < limit; j++)
		{
			if (arr1[i][j] == 0 && !done && arr1[i][j] == 2 && arr1[i + 2][j] == 0)
			{
				x1 = i + 2;
				y1 = j;
				done = true;
			}
			else if (arr1[i][j] == 0 && !done && arr1[i][j] == 2 && arr1[i - 2][j] == 0)
			{
				x1 = i - 2;
				y1 = j;
				done = true;
			}
			else if (arr1[i][j] == 0 && !done && (arr1[i + 1][j] == 2 || arr1[i - 1][j] == 2))
			{
				x1 = i;
				y1 = j;
				done = true;				
			}
			else if (arr1[i][j] == 0 && !done && areaScanner (arr1, i, j, 1) >= 2)
			{
				x1 = i;
				y1 = j;
				done = true;
			}
			else if (arr1[i][j] == 0 && !done && areaScanner (arr1, i, j, 2) >= 2)
			{
				x1 = i;
				y1 = j;
				done = true;
			}
			
		}
		
	}

	if(*defence && arr1[x0][y0 + 1] == 0 && !done)
	{
		x1 = x0;
		y1 = y0 + 1;
		*defence = false;
	}

	else if (y0 < limit - 2 && x0 > 0 && arr1[x0 - 1][y0 + 2] == 0 && !done)
	{
		x1 = x0 - 1;
		y1 = y0 + 2;
		*defence = true;
	}
	else if (y0 < limit - 2 && x0 == 0 && arr1[x0][y0 + 2] == 0 && !done)
	{
		x1 = x0;
		y1 = y0 + 2;
	}
	else if (!done)
	{
		for (int i = 0; i < limit; i++)
		{
			for (int j = 0; j < limit; j++)
			{
				if (arr1[i][j] == 0)
				{
					x1 = i;
					y1 = j;
					done = true;
				}
			}
		}
	}
	
	arr1[x1][y1] = 2;

}

void turnController(int field[12][12] ,int size ,bool *turn, int playStyle)		// It controls turns
{
	// Turn 0 for Player 1 / 1 for Player 2
	
	int x = 0, y;
	char c;
	bool def;

		if (playStyle == 0 && *turn)	cout << "Player 2 Turn :" << endl;
		else if (!*turn)	cout << "Player 1 Turn :" << endl;
	
		cout << "Enter the cordinate (Column / Raw) :";
		cin >> c; 		// Column cordinate should be entered upper case.
		cin >> x;
		y = c - 'A';
		x--;
		cout << endl;

		if(!*turn && field[x][y] == 0 && x < size && y < size)	
		{
			field[x][y] = 1;
			*turn = true;
		}

		else if (!playStyle && *turn)
		{
			if (*turn && field[x][y] == 0 && x < size && y < size)	
			{			
				field[x][y] = 2;
				*turn = false;
			}
		}
		if (playStyle && *turn)
		{
			ai (field ,x , y, size, &def);
			*turn = false;
		}

		drawField(field, size);	
}  

void drawField(int field[12][12], int size)			// Draws the field.
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

			if(field[i][j] == 0)	cout << ". ";
			else if (field[i][j] == 1)	cout << "X ";
			else if (field[i][j] == 2)	cout << "O ";
		}
		cout << endl;
	}
}	
