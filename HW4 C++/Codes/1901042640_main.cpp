#include "1901042640_source.h"

int main()
{
	string choice1, choice2;
	int menuChoice, gameChoice;
	Hex h0(9, 0), h1 = 7, h2, h3(h1), h4(10);	// Hex objects
	vector<Hex> hex;

	hex.push_back(h0);			// Stores games into a vector
	hex.push_back(h1);
	hex.push_back(h2);
	hex.push_back(h3);
	hex.push_back(h4);
	
	while(1)
	{
		cout << "0) Quit :" << endl;
		cout << "1) Play :" << endl;
		cout << "2) Compare :" << endl; 
		getline(cin, choice1);
		menuChoice = stoi(choice1);


		switch(menuChoice)
		{
			case 0: 		// Quit
			exit(1);	
			break; 
				case 1:			// Play
				cout << "Select the number of the game you want to play :(Enter a number between 1-5)" << endl;
				getline(cin, choice2);
				if(choice2.length() == 1)
				{
					gameChoice = stoi(choice2);
					if(gameChoice == 1)
					{
						cout << "GAME 1" << endl;
						cout << hex[0];
						hex[0].playGame();
					}
					else if(gameChoice == 2)
					{
						cout << "GAME 2" << endl;
						cout << hex[1];
						hex[1].playGame();
					}
					else if(gameChoice == 3)
					{
						bool isValid = false;
						cout << "GAME 3" << endl;
						while(!isValid)
						{	
							cin >> hex[2];
							if (hex[2].getSize() >= 6 && hex[2].getSize() <= 27 && (hex[2].getPlayStyle() == 1 || hex[2].getPlayStyle() == 0))	isValid = true;
							else cerr << "You entered invalid command. Please try again." << endl;
 						}
						hex[2].playGame();
					}
					else if(gameChoice == 4)
					{
						cout << "GAME 4" << endl;
						cout << hex[3];
						hex[3].playGame();
					}
					else if(gameChoice == 5)
					{
						cout << "GAME 5" << endl;
						cout << hex[4];
						hex[4].playGame();
					}
					else 	cerr << "Invalid Command" << endl;
				}	
				break;

				case 2:						// Comparison
				string s1, s2;
				int n1, n2;
				cout << "Enter the first game you want to compare :(Enter a number between 1-5)"<< endl;
				getline(cin, s1);
				n1 = stoi(s1) - 1;
				cout << "Enter the second game you want to compare :(Enter a number between 1-5)"<< endl;		
				getline(cin, s2);
				n2 = stoi(s2) - 1;

				if (n1 > 5 || n1 < 0 || n2 > 5 || n2 < 0 || n1 == n2)	cerr << "You entered an invalid command" << endl;		// Error message
				else if (hex[n1] == hex[n2])	cout << "1st game has more elements" << endl;
				else	cout << "2nd game has more elements" << endl;
				break;
		}
	}
	return 0;
}