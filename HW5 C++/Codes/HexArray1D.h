#include "Errors.h"
#include "AbstractHex.cpp"
#include <vector>

namespace HexNamespace
{

class HexArray1D : public AbstractHex
{
	public :

	HexArray1D();
	HexArray1D(const int size, const int PlayStyle);

	HexArray1D (const HexArray1D & other);
	~HexArray1D();
	HexArray1D operator = (const HexArray1D & other);

	void setHexCells ();
	void setSize (const int size);

	void print();
	void readFromFile (string fileName)	throw(fileError);
	void writeToFile (string fileName)	throw(fileError);
	void reset ();
	void play(const int row, const int column)	throw(fullCellError);
	void play();
	void resetVector(vector <vector<Cell> > & vec, const int limit);
	bool didPlayerOneWin(vector<vector<AbstractHex::Cell>> visitedCells, int x, int y, int limit);
	bool didPlayerTwoWin(vector<vector<AbstractHex::Cell>> visitedCells, int x, int y, int limit);
	bool isEnd();
	Cell operator () ( int row,  int column);
	string lastMove()	throw(noMoveError);
	int numberofMoves();

	private :
	Cell *hexCells;

};

}