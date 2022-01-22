/**
*
* @author Emre Sezer
This is Collection Interface
*/

public interface  Collection <E>
{
	public Object[] getArray();
	public Iterator iterator();
	public int size();


	public void add (E e);
	public boolean contains(E e);	
	public void clear();
	public void addAll(Collection c);
	public boolean containsAll(Collection c);
	public boolean isEmpty();
	public void remove(E e);
	public void removeAll(Collection c);
	public void retainAll(Collection c);	
	
}

