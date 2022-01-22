#ifndef ErrorsHeader
#define ErrorsHeader

#include <iostream>

using namespace std;

namespace HexNamespace
{

class emptyCellError
{
	public :
	emptyCellError()
	{
		cout << "ENTERED CELL IS EMPTY" << endl;
	}	
};

class fullCellError
{
	public :
	fullCellError()
	{
		cout << "ENTERED CELL IS FULL" << endl;
	}
};

class noMoveError
{
	public :
	noMoveError()
	{
		cout << "THERE IS NO PLAYED CELL" << endl;
	}
};

class fileError
{	
	public :
	fileError()
	{
		cout << "FILE ERROR" << endl;
		exit(1);
	}
};

class wrongTypeError
{
	public :
	wrongTypeError()
	{
		cout << "WRONG TYPE ERROR" << endl;
		exit(1);
	}

};

}

#endif