/**
*
* @author Emre Sezer
This is Array List class
*/

public class ArrayList <E> implements List <E>
{
	public Object [] arr;
	public int size;
	public int used;

	public ArrayList(int size)
	{
		this.size = size;
		used = 0;
		arr = new Object[this.size + 1];
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

	public Object get(int n)
	{
		return arr[n];
	}

	public Object [] getArray()
	{
		return arr;
	}

	public void setSize(int size)
	{
		this.size = size;
	}

	public Iterator iterator()
	{
		Iterator arrayListIterator = new Iterator();
		arrayListIterator.setc(this);
		return arrayListIterator;
	}

	public int size()
	{
		return used;
	}

	public void add (E e)
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
	
	public void addAll(Collection c)
	{
		if(size < size() + c.size() )
		{
			setArray(size() + c.size());
		}
			for (int i = 0; i < c.size(); i++)
			{
				arr[used] = c.getArray()[i];
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

	

	public static void main(String [] args)
	{
		ArrayList<Integer> a = new ArrayList<Integer>(10);
		ArrayList<Integer> b = new ArrayList<Integer>(3);
		a.add(31);
		a.add(32);
		a.add(33);
		a.add(34);
		Iterator here  = a.iterator();

		b.add(1);
		b.add(2);
		b.add(3);

		b.addAll(a);
		for(int i = 0; i < b.size; i++)	System.out.println(b.get(i));

		
			
		

	}

}
