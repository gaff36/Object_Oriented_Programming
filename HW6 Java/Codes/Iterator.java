/**
*
* @author Emre Sezer
This is Iterator Helper Class
*/


public class Iterator
{	
	public Collection c;
	private int current = 0;

	public void setc (Collection c)
	{
		this.c = c;
	}

	public Object next()
	{
		Object temp = c.getArray()[current];
		current++;
		return temp;
	}

	public boolean hasNext()
	{
		if(c.getArray()[current] == null)	return false;
		return true;
	}

	public void resetCurrent()
	{
		current = 0;
	}
	/*
	public void remove ()
	{
		Object temp = c.getArray()[current];
		c.remove(temp);
	}	*/		

}