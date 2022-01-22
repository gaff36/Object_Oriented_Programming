#include <iostream>
#include "1901042640_support.h"

using namespace std;

void gameController();


int main()
{
	gameController();
	return 0;
}

void gameController()
{
	bool  turn = false, result1 = false, result2 = false, isSizevalid = false, isStyleValid = false;
	int size ,style, field[12][12] = {0}, visited[12][12] = {0};

	while (!isSizevalid)
	{
		cout << "Enter the size of the field : (Minimum 6, Maximum 12)" << endl;
		cin >> size;
		if (size >= 6 && size <= 12)
		{			
			isSizevalid = true;
		}	
		else	cout << "You entered an invalid number." << endl;
			
	}

	while (!isStyleValid)
	{
		cout << "Enter 0 or 1 for play style : (0 for Singleplayer / 1 for Multiplayer)" << endl;
		cin >> style;

		if (style == 0 || style == 1)
		{
			isStyleValid = true;
		}
		else	cout << "You entered an invalid number." << endl;
	}

	drawField(field, size);

		while (!result1 && !result2)
		{

			turnController(field, size, &turn, style);

			result1 = didPlayerOneWin(field, visited, 0, 0, size);
			result2 = didPlayerTwoWin(field, visited, 0, 0, size); 
		
			arrayZeroing (visited, size);

			if(result1 == true)	cout << "PLAYER 1 WON!" << endl;
			else if(result2 == true)	cout << "PLAYER 2 WON!" << endl;
	
		}

}


