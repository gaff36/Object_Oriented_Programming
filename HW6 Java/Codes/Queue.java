/**
*
* @author Emre Sezer
This is Queue Interface
*/

public interface Queue <E> extends Collection <E>
{
	public void add(E e);
	public Object element ();
	//public void offer (E e);
	public void poll();
}