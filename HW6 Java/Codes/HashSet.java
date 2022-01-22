/**
*
* @author Emre Sezer
This is Hashed Set class
*/

public class HashSet <E> implements Set <E>
{
	public Object [] arr;
	public int size;
	public int used;
	
	public HashSet(int size)
	{
		this.size = size;
		used = 0;
		arr = new Object[this.size];
	}

	public Iterator iterator()
	{
		Iterator hashSetIterator = new Iterator();
		hashSetIterator.setc(this);
		return hashSetIterator;
	}

	public void setArray(int size)
	{
		this.size = size;
		Object [] temp = new Object[this.size + 1];
		for(int i = 0; i < used; i++)
		{
			temp[i] = arr[i];
		}
		arr = temp;
	}

	public Object[] getArray()
	{
		return arr;
	} 		

	public int size()
	{
		return used;
	}

	public void add (E e)
	{
		if(areThereDuplicates(e) == false)
		{
			if(size() == size)			// Checks is array is full
			{
				setArray(size + 1);
			}
				if(size != 1)
				{
					arr[used] = e;
					used++;
				}	
				else 
				{
					arr[0] = e;
					used++;
				}
		}
		else System.out.println("HashSet contains the entered element.");
	}
				
	public void addAll(Collection c)
	{
		if(size >= size() + c.size())
		{
			setArray(size() + c.size());
		}
			for (int i = 0; i < c.size(); i++)
			{
				if(areThereDuplicates(c.getArray()[i]) == false)
				{			
					arr[used] = c.getArray()[i];
					used++;
				}
			}					
	}					

	public boolean contains(E e)
	{
		boolean found = false;
		Iterator it = this.iterator();
		while (it.hasNext())
		{
			if(it.next() == e)	found = true;
		}
		return found;
	}

	public boolean containsAll(Collection c)
	{
		int counter = 0;
		if(c.size() <= size())
		{

			for(int i = 0; i < size(); i++)
			{
				for(int j = 0; j < c.size(); j++)
				{
					if(c.getArray()[j] == arr[i])	counter++;
				}
			}
			if(counter == c.size())	return true;
		}
		
		return false;
	}

	public boolean isEmpty()
	{
		if (size() == 0)	return true;
		return false;
	}

	public void remove (E e)
	{
		if(size() != 1)
		{
			for(int i = 0; i < size(); i++)
			{
				if(e == arr[i])				// Removes the first element that equals to input
				{
					for(int k = i; k < size(); k++)
					{
						arr[k] = arr[k + 1];
					}
					used--;
					break;
				}
			}
		}
		else if(size() == 1 && e == arr[0])
		{
			arr[0] = null;
			used--;
		}
	}

	public void removeAll(Collection c)
	{
		if(size() != 1)
		{	
			for(int i = 0; i < c.size(); i++)
			{
				for(int j = 0; j < size(); j++)
				{
					if(c.getArray()[i] == arr[j])
					{
						for(int k = j; k < size(); k++)
						{
							arr[k] = arr[k + 1];
						}
						used--;
					}
				}
			}
		}
	}

	public void retainAll(Collection c)
	{
		int counter = 0;
		if(size >= c.size())
		{
			Object [] temp = new Object[size];

			for(int i = 0; i < c.size(); i++)
			{
				for(int j = 0; j < size(); j++)
				{
					if(c.getArray()[i] == arr[j] && areThereDuplicates(c.getArray()[i]) == false)
					{
						temp[counter] = arr[j];
						counter++;
					}
				}
			}
			arr = temp;
		}
	}

	public void clear()
	{
		for(int i = 0; i < size(); i++)
		{
			arr[i] = null;
		}
		used = 0;
	}

	public boolean areThereDuplicates(Object o)
	{
		boolean found = false;

		for(int i = 0; i < size(); i++)
		{
			if(arr[i] == o)	found = true;
		}
		return found;
	}
	
}
