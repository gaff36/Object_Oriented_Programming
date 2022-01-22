#include "Errors.h"
#include "AbstractHex.cpp"
#include <vector>


namespace HexNamespace
{

template <class T>
class HexAdapter	: public AbstractHex
{
	public :
	HexAdapter ();
	HexAdapter (const int size);

	void setSize(const int size);
	void setHexCells ();

	void print();
	void readFromFile (string fileName)	throw(fileError);
	void writeToFile (string fileName)	throw(fileError);
	void reset ();
	void play(const int row, const int column)	throw(fullCellError);
	void play ();
	void resetVector(vector <vector<Cell> > & vec, const int limit);
	bool didPlayerOneWin(vector<vector<AbstractHex::Cell>> visitedCells, int x, int y, int limit);
	bool didPlayerTwoWin(vector<vector<AbstractHex::Cell>> visitedCells, int x, int y, int limit);
	bool isEnd();
	Cell operator () ( int row,  int column);
	string lastMove()	throw(noMoveError);
	int numberofMoves ();

	private :
	
	T hexCells;
};

}