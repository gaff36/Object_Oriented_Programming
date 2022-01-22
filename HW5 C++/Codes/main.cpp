#include "HexVector.cpp"
#include "HexArray1D.cpp"
#include "HexAdapter.cpp"

using namespace std;
using namespace HexNamespace;


bool areGamesValid (AbstractHex * array[],  int size)	throw(wrongTypeError)		// I use () operator at this function
{
	bool isValid = true;
	bool numCheck = false;

	for (int i = 0; i < size; i++)
	{
		if(HexVector * hv = dynamic_cast<HexVector*> (array[i]))
		{
			numCheck = false;
			for (int j = 0; j < array[i]->getSize(); j++)
			{
				for (int k = 0; k < array[i]->getSize(); k++)
				{
					if (hv->operator()(j,k).getCellState() != AbstractHex :: Cell :: cellState :: NONE		// Checks if cellStates have valid states(X, O or NONE)
						&& hv->operator()(j,k).getCellState() != AbstractHex :: Cell :: cellState :: X
						&& hv->operator()(j,k).getCellState() != AbstractHex :: Cell :: cellState :: O)
					{	
						isValid = false;
					}
					if(hv->operator()(j,k).getMoveNum() == hv->getPlayNum())	numCheck = true;		// Checks if playNum and moveNum matches

				}
				
			}
			if(numCheck == false)	isValid = false;		// If playNum and moveNum doesn't match. returns false
		}
		else if (HexAdapter<vector<AbstractHex :: Cell>> * ha1 = dynamic_cast<HexAdapter<vector<AbstractHex :: Cell>>*> (array[i]))	
		{
			numCheck = false;
			for (int j = 0; j < array[i]->getSize(); j++)
			{
				for (int k = 0; k < array[i]->getSize(); k++)
				{
					if (ha1->operator()(j,k).getCellState() != AbstractHex :: Cell :: cellState :: NONE		// Checks if cellStates have valid states(X, O or NONE)
						&& ha1->operator()(j,k).getCellState() != AbstractHex :: Cell :: cellState :: X
						&& ha1->operator()(j,k).getCellState() != AbstractHex :: Cell :: cellState :: O)
					{	
						isValid = false;
					}
					if(ha1->operator()(j,k).getMoveNum() == ha1->getPlayNum())	numCheck = true;		// Checks if playNum and moveNum matches
	
				}			
			}
			if(numCheck == false)	isValid = false;		// If playNum and moveNum doesn't match. returns false
		}

		else if (HexAdapter<deque<AbstractHex :: Cell>> * ha2 = dynamic_cast<HexAdapter<deque<AbstractHex :: Cell>>*> (array[i]))	
		{
			numCheck = false;
			for (int j = 0; j < array[i]->getSize(); j++)
			{
				for (int k = 0; k < array[i]->getSize(); k++)
				{
					if (ha2->operator()(j,k).getCellState() != AbstractHex :: Cell :: cellState :: NONE		// Checks if cellStates have valid states(X, O or NONE)
						&& ha2->operator()(j,k).getCellState() != AbstractHex :: Cell :: cellState :: X		
						&& ha2->operator()(j,k).getCellState() != AbstractHex :: Cell :: cellState :: O)
					{	
						isValid = false;
					}
					if(ha2->operator()(j,k).getMoveNum() == ha2->getPlayNum())	numCheck = true;		// Checks if playNum and moveNum matches
				}		
			}
			if(numCheck == false)	isValid = false;		// If playNum and moveNum doesn't match. returns false
		}
		else if (HexArray1D * hd = dynamic_cast<HexArray1D*> (array[i]))	
		{
			numCheck = false;
			for (int j = 0; j < array[i]->getSize(); j++)
			{
				for (int k = 0; k < array[i]->getSize(); k++)
				{
					if (hd->operator()(j,k).getCellState() != AbstractHex :: Cell :: cellState :: NONE			// Checks if cellStates have valid states(X, O or NONE)
						&& hd->operator()(j,k).getCellState() != AbstractHex :: Cell :: cellState :: X
						&& hd->operator()(j,k).getCellState() != AbstractHex :: Cell :: cellState :: O)
					{	
						isValid = false;
					}
					if(hd->operator()(j,k).getMoveNum() == hd->getPlayNum())	numCheck = true;		// Checks if playNum and moveNum matches
				}
			}
			if(numCheck == false)	isValid = false;		// If playNum and moveNum doesn't match. returns false
		}
		else
		{
			throw wrongTypeError();
		}

	}

	if(!isValid)	return false;
	return true;
}

void playGame(AbstractHex * hex)
{
	bool result1;
	int x, y, num;
	bool quit = false;
	string str;

	while(result1 == false && quit == false)
	{
		hex->print();

		bool check = false;
		cout << "Enter the cordinates (Column - Row): ";		
 		getline(cin, str);
		if(str.length() == 2)		x = str[1] - 1 - '0';
		else if (str.length() == 3)	x = 10 + str[2] - 1 - '0';
		y = str[0] - 'A';

		if (str.substr(0, 4) == "SAVE")			// Writes to file and saves the game
		{
			ofstream saveFile;
			str = str.substr(5,str.length() - 1);	
			hex->writeToFile(str);		
			
		}

		else if (str.substr(0, 4) == "LOAD")	// Reads from the file and loads the game
		{
			ifstream loadFile;
			str = str.substr(5,str.length() - 1);
			hex->readFromFile(str);	
		}

		else if (str.substr(0, 4) == "quit")	// Quits the game
		{	
			quit = true;
			cout << endl;
		}
		else if (str.substr(0, 5) == "reset")	// Resets the board
		{
			hex->reset();
		}
		else if (str.substr(0, 5) == "stats")	// Prints last move and number of moves
		{
			try
			{
				cout << "Last Move is : " << hex->lastMove() << ", " << "Number of Moves are : " << hex->numberofMoves() << endl;
			}
			catch(noMoveError e)
			{
			}
			
		}
		else
		{
			check = true;
		}

		if(check)
		{
			try
			{
				hex->play(x, y);								// Plays one move
				if(hex->getPlayStyle() == 1)	hex->play();
			}
			catch(fullCellError e)
			{
			}
		}

		result1 = hex->isEnd();			// Checks if anyone won the game
	}

}

bool comparison (AbstractHex * a, AbstractHex * b)		// Function for comparing 2 boards
{
	if(*a == *b)	return true;
	return false;
}

int main()
{
	// Board pointers for testing

	AbstractHex * arr1[4];
	HexVector *h1 = new HexVector(8,1);		// Test board for playing against computer
	HexArray1D *h2 = new HexArray1D(6, 0);		
	HexAdapter<vector<AbstractHex :: Cell>> *h3 = new HexAdapter<vector<AbstractHex :: Cell>>;
	HexAdapter<deque<AbstractHex :: Cell>> *h4 = new HexAdapter<deque<AbstractHex :: Cell>>;
	HexArray1D *h5 = new HexArray1D;
	HexAdapter<deque<AbstractHex :: Cell>> *h6 = new HexAdapter<deque<AbstractHex :: Cell>>;
	
	arr1[0] = h1;	// HexVector
	arr1[1] = h2;	// HexArray1D
	arr1[2] = h3;	// HexAdapter<vector>
	arr1[3] = h4;	// HexAdapter<deque>

	AbstractHex * arr2[1];		// I play some moves
	h5->play(3,4);
	h5->play(2,1);
	h5->play(0,3);
	arr2[0] = h5;	// HexArray1D

	AbstractHex * arr3[2];		// I change playNum to prove invalidity and show global function works.
	arr3[0] = h1;			// HexVector
	h5->setPlayNum(22);
	arr3[1] = h5;		// HexArray1D

	AbstractHex * arr4[3];		// I created different variations of boards to test global function
	arr4[0] = h2;		// HexArray1D
	arr4[1] = h4;		// HexAdapter<deque>
	arr4[2] = h3;		// HexAdapter<vector>

	AbstractHex * arr5[5];
	arr5[0] = h1;	// HexVector
	arr5[1] = h2;	// HexArray1D
	arr5[2] = h3;	// HexAdapter<vector>
	arr5[3] = h4;	// HexAdapter<deque>
	arr5[4] = h6;	// HexAdapter<deque>



	// Board Pointers For Testing Global Function of Validity



	// MENU FOR TESTS

	string choice1, choice2;
	int menuChoice, gameChoice;

	while(1)
	{	
		cout << "0) Quit :" << endl;		
		cout << "1) Play :" << endl;							// For testing class functions
		cout << "2) Compare :" << endl;							// For comparing 2 boards
		cout << "3) Global Function For Validity :" << endl;	// For testing global function of validity
		getline(cin, choice1);
		menuChoice = stoi(choice1);

		switch(menuChoice)
		{
			case 0: 
			exit(1);
			break; 
				case 1:
				{
				cout << "Select the number of the game you want to play :(Enter a number between 1-4)" << endl
					 << "1 : HexVector" << endl << "2 : HexArray1D" << endl << "3 : HexAdapter <vector>" << endl << "4 : HexAdapter <deque>" << endl;

				getline(cin, choice2);
				if(choice2.length() == 1)
				{
					gameChoice = stoi(choice2);
					if(gameChoice == 1)
					{
						cout << "GAME 1 (HexVector)" << endl;
						playGame(h1);
					}
					else if(gameChoice == 2)
					{
						cout << "GAME 2 (HexArray1D)" << endl;
						playGame(h2);
					}
					else if(gameChoice == 3)
					{
						cout << "GAME 3 (HexAdapter <vector>)" << endl;
						playGame(h3);
					}
					else if(gameChoice == 4)
					{
						cout << "GAME 4 (HexAdapter <deque>)" << endl;
						playGame(h4);
					}
					
					else 	cerr << "Invalid Command" << endl;
				}
				}	
				break;

					case 2:
					{
					string s1, s2;
					int n1, n2;
					cout << "Enter the first game you want to compare :(Enter a number between 1-4)" << endl;
					getline(cin, s1);
					n1 = stoi(s1) - 1;
					cout << "Enter the second game you want to compare :(Enter a number between 1-4)" << endl;
					getline(cin, s2);
					n2 = stoi(s2) - 1;
					if(comparison(arr1[n1], arr1[n2]) == true)	cout << "Both games are the same" << endl;
					else	cout << "Entered games are not the same" << endl;
					}
					break;

						case 3:
						{
						if(areGamesValid(arr1, 4))	cout << "First array of boards are valid." << endl;
						else cout << "First array of boards are not valid." << endl;
						if(areGamesValid(arr2, 1))	cout << "Second array of boards are valid." << endl;
						else cout << "Second array of boards are not valid." << endl;
						if(areGamesValid(arr3, 2))	cout << "Third array of boards are valid." << endl;
						else cout << "Third array of boards are not valid." << endl;
						if(areGamesValid(arr4, 3))	cout << "Fourth array of boards are valid." << endl;
						else cout << "Fourth array of boards are not valid." << endl;
						if(areGamesValid(arr5, 5))	cout << "Fifth array of boards are valid." << endl;
						else cout << "Fifth array of boards are not valid." << endl;
						}
						break;

							default:
							{
							cerr << "Invalid Command" << endl;
							break;
							}
			}

	}

	return 0;
}
