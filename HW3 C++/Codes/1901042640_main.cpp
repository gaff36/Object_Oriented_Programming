#include "1901042640_source.h"

int main()
{
	vector<Hex> hex(5);
	string choice1, choice2;
	int menuChoice, gameChoice;

	
	while(1)
	{
		cout << "0) Quit :" << endl;
		cout << "1) Play :" << endl;
		cout << "2) Compare :" << endl;
		getline(cin, choice1);
		menuChoice = stoi(choice1);


		switch(menuChoice)
		{
			case 0: 
			exit(1);
			break; 
				case 1:
				cout << "Select the number of the game you want to play :(Enter a number between 1-5)" << endl;
				getline(cin, choice2);
				if(choice2.length() == 1)
				{
					gameChoice = stoi(choice2);
					if(gameChoice == 1)
					{
						cout << "GAME 1" << endl;
						hex[0].playGame();
					}
					else if(gameChoice == 2)
					{
						cout << "GAME 2" << endl;
						hex[1].playGame();
					}
					else if(gameChoice == 3)
					{
						cout << "GAME 3" << endl;
						hex[2].playGame();
					}
					else if(gameChoice == 4)
					{
						cout << "GAME 4" << endl;
						hex[3].playGame();
					}
					else if(gameChoice == 5)
					{
						cout << "GAME 5" << endl;
						hex[4].playGame();
					}
					else 	cerr << "Invalid Command" << endl;
				}	
				break;

				case 2:
				string s1, s2;
				int n1, n2;
				cout << "Enter the first game you want to compare :(Enter a number between 1-5)"<< endl;
				getline(cin, s1);
				n1 = stoi(s1) - 1;
				cout << "Enter the second game you want to compare :(Enter a number between 1-5)"<< endl;
				getline(cin, s2);
				n2 = stoi(s2) - 1;

				if (hex[n1].compare(hex[n2]) == false)	cout << "2nd game has more elements" << endl;
				else if (hex[n1].compare(hex[n2]) == true)	cout << "1st game has more elements" << endl;

				break;
		}
	}
	return 0;
}