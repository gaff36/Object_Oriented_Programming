/**
*
* @author Emre Sezer
This is Linked List class
*/

public class LinkedList <E> implements Queue <E> , List <E>
{
	public Object [] arr;
	public int size;
	public int used;

	public LinkedList(int size)
	{
		this.size = size;
		used = 0;
		arr = new Object[this.size];
	}

	public Object get(int n)
	{
		return arr[n];
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

	public Object [] getArray()
	{
		return arr;
	}

	public Iterator iterator()
	{
		Iterator linkedListIterator = new Iterator();
		linkedListIterator.setc(this);
		return linkedListIterator;
	}

	public int size()
	{
		return used;
	}

	public Object element()
	{
		return arr[0];
	}

	public void add(E e)
	{
		if(size() == size)
		{	
			setArray(size + 1);
		}
		if(size() > 1)
		{
			for(int i = size() - 1; i >= 0; i--)
			{	
				arr[i + 1] = arr[i];
			}
			arr[0] = e;
			used++;
		}
		else
		{
			arr[1] = arr[0];
			arr[0] = e;
			used++;
		}
	}

	public void poll()
	{
		for(int i = 1; i < size(); i++)
		{
			arr[i - 1] = arr[i];
		}
		used--;
	}

	public void addAll(Collection c)
	{
		if(size < size() + c.size())
		{
			setArray(size() + c.size());
		}

		for(int i = 0; i < c.size(); i++)
		{	
			for(int j = size() - 1; j >= 0; j--)
			{
				arr[j + 1] = arr[j];
			}
			arr[0] = c.getArray()[i];	
			used++;
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

	public boolean contains(E e)
	{
		boolean found = false;

		for(int i = 0; i < size(); i++)
		{
			if(arr[i] == e)	found = true;
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
				if(e == arr[i])			// Removes the first element that equals to input
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
					if(c.getArray()[i] == arr[j])
					{
						temp[counter] = arr[j];
						counter++;
					}
				}
			}
			arr = temp;
		}
		else
		{
			System.out.println("ERROR:");
		}
	}
	
}