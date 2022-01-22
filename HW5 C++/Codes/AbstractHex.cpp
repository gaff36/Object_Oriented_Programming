#ifndef AbstractHexHeader
#define AbstractHexHeader

#include <iostream>
#include <string>

using namespace std;

namespace HexNamespace
{

class AbstractHex
{
	public :
	
	class Cell
	{
		public :
		enum cellState {X, O, NONE};

		cellState state;
		int row;
		char column;
		int moveNum;

		Cell();
		Cell(int row, char column, cellState state);


		int getRow(){return row;}	
		char getColumn()	{return column;}
		cellState getCellState()	{return state;}
		int getMoveNum()	{return moveNum;}

		void setRow(int row);
		void setColumn(char column);
		void setState(cellState state);
		void setMoveNum(int moveNum);
	};

	bool getQuit()	const
	{
		return quit;
	}
	bool getTurn()	const
	{
		return turn;
	}
	int getSize ()	const
	{
		return size;
	}

	int getPlayStyle()	const
	{
		return playStyle;
	}

	int getPlayNum()	const
	{
		return playNum;
	}

	void setQuit(bool quit);
	void setTurn(bool turn);
	virtual void setSize(int size);
	void setPlayStyle(int playStyle);
	void setPlayNum(int num);


	AbstractHex();
	AbstractHex(const int size, const int playStyle);
	virtual ~AbstractHex()	{}

	virtual void print() = 0;	
	virtual void readFromFile (string filename) = 0;
	virtual void writeToFile (string fileName) = 0;
	virtual void reset () = 0;

	virtual void play(const int row, const int column) = 0;
	virtual void play() = 0;
	
	virtual bool isEnd() = 0;
	virtual Cell operator () ( int row,  int column) = 0;
	
	virtual string lastMove() = 0;
	virtual int numberofMoves() = 0;

	friend bool operator == (AbstractHex & h1, AbstractHex & h2)		// Compares every content of the cell of both objects
	{
		bool check = true;

		if(h1.getSize() == h2.getSize())
		{
			for(int i = 0; i < h2.getSize(); i++)
			{
				for (int j = 0; j < h2.getSize(); j++)
				{
					if (h1(i, j).getCellState() != h2(i, j).getCellState() && h1(i, j).getRow() != h2(i, j).getRow()			// I used () operator there		
						&& h1(i, j).getColumn() != h2(i, j).getColumn() && h1(i, j).getMoveNum() != h2(i, j).getMoveNum())
					{
						return false;
					}
				}
			}
			return true;
		}

		else	return false;
	}

	private :

	int size, playStyle, playNum = 0;
	bool turn = false, quit = false, p = false;
};

/////////////// CONSTRUCTORS HEX ///////////////

AbstractHex :: AbstractHex()
{
	setSize(5);
	setTurn(false);
	setPlayStyle(0);
	setQuit(false);
	setPlayNum(0);
}

AbstractHex :: AbstractHex(const int size, const int playStyle)
{
	setSize(size);
	setTurn(false);
	setPlayStyle(playStyle);
	setQuit(false);
	setPlayNum(0);
}

/////////////// CONSTRUCTORS CELL ///////////////

AbstractHex :: Cell :: Cell ()
{
	setRow(0);
	setColumn('A');
	setState(NONE);
	setMoveNum(0);	
}

AbstractHex :: Cell :: Cell (int row, char column, cellState state)
{
	setRow(row);
	setColumn(column);
	setState(state);
	setMoveNum(0);	
}

/////////////// SETTERS FOR HEX ///////////////

inline void AbstractHex:: setQuit(bool quit)
{
	this -> quit = quit;
}
inline void AbstractHex:: setTurn(bool turn)
{
	this -> turn = turn;
}

inline void AbstractHex :: setSize (int size)
{
	this -> size = size;	
}

inline void AbstractHex :: setPlayStyle (int playStyle)
{
	this -> playStyle = playStyle;
}

inline void AbstractHex :: setPlayNum(int playNum)
{
	this -> playNum = playNum;
}

/////////////// SETTERS FOR CELL ///////////////

void AbstractHex::Cell::setRow(int row)
{
	this -> row = row;
}

void AbstractHex::Cell::setColumn(char column)
{
	this -> column = column;
}

void AbstractHex::Cell:: setState(cellState state)
{
	this -> state = state;
}

void AbstractHex :: Cell :: setMoveNum(int moveNum)
{
	this -> moveNum = moveNum;
}

}
#endif