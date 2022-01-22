#include "AbstractHex.cpp"
#include "Errors.h"
#include <vector>

namespace HexNamespace
{

class HexVector : public AbstractHex
{
	public :

	HexVector();
	HexVector(const int size, const int PlayStyle);

	void setHexCells();
	void setSize(const int size);

	void print();
	void readFromFile (string filename);
	void writeToFile (string fileName);
	void reset();
	
	bool didPlayerOneWin(vector<vector<AbstractHex::Cell>> visitedCells, int x, int y, int limit);
	bool didPlayerTwoWin(vector<vector<AbstractHex::Cell>> visitedCells, int x, int y, int limit);
	bool isEnd();
	void play(const int row, const int column)	throw(fullCellError);
	void play();
	void resetVector(vector <vector<AbstractHex::Cell> > &vec,int limit);
	Cell operator () ( int row,  int column);
	string lastMove()	throw(noMoveError);
	int numberofMoves();
	void playGame();	

	private :
	vector <vector<Cell> > hexCells;
	
};

}