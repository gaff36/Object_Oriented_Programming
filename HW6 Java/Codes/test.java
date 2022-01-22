import java.util.*;

/**
* This is the test class for testing my code.
* 
* @author Emre Sezer
* 
*/

public class test 
{
	public static void main(String [] args)
	{
		String x;
		// TESTS FOR arrayList<Integer> :

		Scanner in  = new Scanner(System.in);

		System.out.println("TESTS FOR arrayList<Integer> :");

		ArrayList<Integer> a1 = new ArrayList<Integer> (5);
		ArrayList<Integer> b1 = new ArrayList<Integer> (3);
		ArrayList<Integer> c1 = new ArrayList<Integer> (6);
		ArrayList<Integer> d1 = new ArrayList<Integer> (7);
		Iterator ita1 = a1.iterator();


		a1.add(4);		// Tests add functions
		a1.add(5);
		a1.add(6);
		a1.add(1);

		b1.add(30);
		b1.add(2);

		c1.add(1);
		c1.add(32);
		c1.add(4);

		d1.add(5);
		d1.add(6);
		d1.add(13);
																					
		a1.addAll(b1);		// Tests addAll function
		
		System.out.println("Tests For add and addAll Functions:");

		while (ita1.hasNext())	System.out.println(ita1.next());		// Tests iterator's next and hasNext functions. As you can see b1's elements are added to a1
		System.out.println();

		System.out.println("Tests For Clear Function:");
		b1.clear();														// Tests clear function

		System.out.println("b1 has " + b1.size() + " elements inside.");
		System.out.println();

		System.out.println("Tests For contains and containsAll Functions:");
		if(a1.contains(4))	System.out.println("a1 contains " + 4);				// prints if it contains the input
		else System.out.println("a1 doesn not contain " + 4);					// prints if it doesn't contain the input

		if(a1.contains(32))	System.out.println("a1 contains " + 32);			// prints if it contains the input
		else System.out.println("a1 does not contain " + 32);					// prints if it doesn't contain the input

		System.out.println();
		if(a1.containsAll(b1))	System.out.println("a1 contains b1." );			// prints if it contains the input
		else System.out.println("a1 doesn not contain b1.");					// prints if it doesn't contain the input

		if(a1.containsAll(c1))	System.out.println("a1 contains c1." );			// prints if it contains the input
		else System.out.println("a1 does not contain c1.");						// prints if it doesn't contain the input
		System.out.println();

		System.out.println("Tests For isEmpty Function:");
		if(b1.isEmpty())	System.out.println("b1 is empty.");		// Since i cleared b1 before i exptect to get "b1 is empty"
		else System.out.println("b1 is not empty.");

		if(a1.isEmpty())	System.out.println("a1 is empty.");		// a1 is not empty so, i exptect to get "a1 is not empty"
		else System.out.println("a1 is not empty.");
		System.out.println();

		System.out.println("Tests For remove and removeAll Functions:");
		System.out.println();
		 
		System.out.println("a1 Before remove:");
		for(int i = 0; i < a1.size(); i++)				// As you can see a1 contains 30 before remove function
		{
			System.out.println(a1.get(i));
		}

		a1.remove(30);
		a1.remove(65);								// a1 doesn't contain 65 so, no effect will happen on a1 for element 65

		System.out.println("a1 After Remove:");		// As you can see a1 doesn't contain 30 after remove function	
		for(int i = 0; i < a1.size(); i++)
		{
			System.out.println(a1.get(i));
		}
		System.out.println();

		a1.removeAll(c1);

		System.out.println("a1 After removeAll:");		// c1 contains 1, 32, 4. So, elements that a1 and c1 both has will be removed from a1
		for(int i = 0; i < a1.size(); i++)
		{
			System.out.println(a1.get(i));				// As you can see elements that c1 and a1 both have removed from a1
		}
		System.out.println();

		System.out.println("Tests For retainAll Function:");
		System.out.println();

		a1.retainAll(d1);		// d1 contains 5, 6, 13, After retainAll function a1 will be the only elements that a1 and d1 both contain

		System.out.println("a1 After retainAll:");
		for(int i = 0; i < a1.size(); i++)
		{
			System.out.println(a1.get(i));				// As you can see elements that a1 is the only elements that a1 and d1 both contain
		}
		
		System.out.println();
		System.out.println("Press Anything To See arrayList<String> Tests :");
		x = in.nextLine();
																
		///////////////////////////////////////
		// TESTS FOR arrayList<String> :

		System.out.println("TESTS FOR arrayList<String> :");

		ArrayList<String> a2 = new ArrayList<String> (5);
		ArrayList<String> b2 = new ArrayList<String> (3);
		ArrayList<String> c2 = new ArrayList<String> (6);
		ArrayList<String> d2 = new ArrayList<String> (7);
		Iterator ita2 = a2.iterator();


		a2.add("abc");		// Tests add functions
		a2.add("b");
		a2.add("c");
		a2.add("d");

		b2.add("f");
		b2.add("efef");

		c2.add("b");
		c2.add("c");
		c2.add("r");

		d2.add("d");
		d2.add("c");
		d2.add("y");

		a2.addAll(b2);		// Tests addAll function
		
		System.out.println("Tests For add and addAll Functions:");

		while (ita2.hasNext())	System.out.println(ita2.next());		// Tests iterator's next and hasNext functions. As you can see b2's elements are added to a2
		System.out.println();

		System.out.println("Tests For Clear Function:");
		b2.clear();														// Tests clear function

		System.out.println("b2 has " + b2.size() + " elements inside.");			// As you can see b2 is cleared
		System.out.println();
		
		System.out.println("Tests For contains and containsAll Functions:");
		if(a2.contains("b"))	System.out.println("a2 contains b");				// prints if it contains the input
		else System.out.println("a2 doesn not contain b");							// prints if it doesn't contain the input

		if(a2.contains("emre"))	System.out.println("a1 contains emre");			// prints if it contains the input
		else System.out.println("a1 does not contain emre" );					// prints if it doesn't contain the input

		System.out.println();
		if(a2.containsAll(b2))	System.out.println("a2 contains b2." );			// prints if it contains the input
		else System.out.println("a2 doesn not contain b2.");					// prints if it doesn't contain the input

		if(a2.containsAll(c2))	System.out.println("a2 contains c2." );			// prints if it contains the input
		else System.out.println("a2 does not contain c2.");						// prints if it doesn't contain the input
		System.out.println();

		System.out.println("Tests For isEmpty Function:");
		if(b1.isEmpty())	System.out.println("b2 is empty.");		// Since i cleared b2 before i exptect to get "b2 is empty"
		else System.out.println("b2 is not empty.");

		System.out.println("Tests For remove and removeAll Functions:");
		System.out.println();
		 
		System.out.println("a2 Before remove:");
		for(int i = 0; i < a2.size(); i++)				
		{
			System.out.println(a2.get(i));
		}

		a2.remove("b");
		a2.remove("z");								// a2 doesn't contain "z" so, no effect will happen on a2 for element "z"

		System.out.println("a2 After Remove:");		// As you can see a2 doesn't contain "b" after remove function	
		for(int i = 0; i < a2.size(); i++)
		{
			System.out.println(a2.get(i));
		}
		System.out.println();

		a2.removeAll(c2);

		System.out.println("a2 After removeAll:");		// c2 contains "b", "c", "r". So, elements that a2 and c2 both has will be removed from a2
		for(int i = 0; i < a2.size(); i++)
		{
			System.out.println(a2.get(i));				// As you can see elements that c2 and a2 both have removed from a2 which is "c" for that example
		}
		System.out.println();

		System.out.println("Tests For retainAll Function:");
		System.out.println();

		a2.retainAll(d2);		// d2 contains "d", "c", "y", After retainAll function a2 will be the only elements that a2 and d2 both contain

		System.out.println("a2 After retainAll:");
		for(int i = 0; i < a2.size(); i++)
		{
			System.out.println(a2.get(i));				// As you can see elements that "d" is the only elements that a2 and d2 both contain
		}			

		System.out.println();
		System.out.println("Press Anything To See LinkedList<Integer> Tests :");
		x = in.nextLine();

		///////////////////////////////////////
		// TESTS FOR linkedList<Integer> :

		LinkedList <Integer> a3 = new LinkedList<Integer>(5);
		LinkedList <Integer> b3 = new LinkedList<Integer>(4);
		LinkedList <Integer> c3 = new LinkedList<Integer>(7);
		LinkedList <Integer> d3 = new LinkedList<Integer>(10);
		Iterator ita3 = a3.iterator();

		a3.add(4);		// Tests add functions
		a3.add(5);
		a3.add(6);
		a3.add(1);

		b3.add(30);
		b3.add(2);

		c3.add(1);
		c3.add(32);
		c3.add(4);

		d3.add(5);
		d3.add(6);
		d3.add(13);

		

		System.out.println("Tests For add and addAll Functions:");

		a3.addAll(b3);
		while (ita3.hasNext())	System.out.println(ita3.next());		// Tests iterator's next and hasNext functions. As you can see b1's elements are added to a1
		System.out.println();

		System.out.println("Tests For Clear Function:");
		b3.clear();														// Tests clear function

		System.out.println("b3 has " + b3.size() + " elements inside.");
		System.out.println();

		System.out.println("Tests For contains and containsAll Functions:");
		if(a3.contains(4))	System.out.println("a3 contains " + 4);				// prints if it contains the input
		else System.out.println("a3 doesn not contain " + 4);					// prints if it doesn't contain the input

		if(a3.contains(32))	System.out.println("a2 contains " + 32);			// prints if it contains the input
		else System.out.println("a3 does not contain " + 32);					// prints if it doesn't contain the input

		System.out.println();
		if(a3.containsAll(b3))	System.out.println("a3 contains b3." );			// prints if it contains the input
		else System.out.println("a3 doesn not contain b3.");					// prints if it doesn't contain the input

		if(a3.containsAll(c3))	System.out.println("a3 contains c3." );			// prints if it contains the input
		else System.out.println("a3 does not contain c3.");						// prints if it doesn't contain the input
		System.out.println();

		System.out.println("Tests For isEmpty Function:");
		if(b3.isEmpty())	System.out.println("b3 is empty.");		// Since i cleared b3 before i exptect to get "b3 is empty"
		else System.out.println("b3 is not empty.");

		if(a3.isEmpty())	System.out.println("a3 is empty.");		// a3 is not empty so, i expected to get "a3 is not empty"
		else System.out.println("a3 is not empty.");
		System.out.println();

		System.out.println("Tests For remove and removeAll Functions:");
		System.out.println();
		 
		ita3.resetCurrent();
		System.out.println("a3 Before remove:");
		while(ita3.hasNext())
		{
			System.out.println(ita3.next());
		}

		a3.remove(30);
		a3.remove(65);								// a3 doesn't contain 65 so, no effect will happen on a3 for element 65
		ita3.resetCurrent();


		System.out.println("a3 After Remove:");		// As you can see a3 doesn't contain 30 after remove function	
		while(ita3.hasNext())
		{
			System.out.println(ita3.next());
		}
		ita3.resetCurrent();	// Resets iterator
		System.out.println();

		a3.removeAll(c3);

		System.out.println("a3 After removeAll:");		// c3 contains 1, 32, 4. So, elements that a3 and c3 both has will be removed from a1
		while(ita3.hasNext())
		{
			System.out.println(ita3.next());
		}
		System.out.println();

		System.out.println("a3's top element Before poll:");
		System.out.println(a3.element());
		System.out.println("a3's top element After poll:");
		a3.poll();
		System.out.println(a3.element());

		System.out.println("Tests For retainAll Function:");
		System.out.println();

		a3.retainAll(d3);		// d3 contains 5, 6, 13, After retainAll function a3 will be the only elements that a3 and d3 both contain

		System.out.println("a3 After retainAll:");
		ita3.resetCurrent();
		while(ita3.hasNext())
		{
			System.out.println(ita3.next());		// Prints 5 and 6 as expected
		}				

		System.out.println();
		System.out.println("Press Anything To See Linkedlist<String> Tests :");
		x = in.nextLine();
																
		///////////////////////////////////////
		// TESTS FOR Linkedlist<String> :
		
		LinkedList<String> a4 = new LinkedList<String> (5);
		LinkedList<String> b4 = new LinkedList<String> (3);
		LinkedList<String> c4 = new LinkedList<String> (6);
		LinkedList<String> d4 = new LinkedList<String> (7);
		Iterator ita4 = a4.iterator();


		a4.add("abc");		// Tests add functions
		a4.add("b");
		a4.add("c");
		a4.add("d");

		b4.add("f");
		b4.add("efef");

		c4.add("b");
		c4.add("c");
		c4.add("r");

		d4.add("d");
		d4.add("c");
		d4.add("y");

		a4.addAll(b4);		// Tests addAll function
		
		System.out.println("Tests For add and addAll Functions:");

		while (ita4.hasNext())	System.out.println(ita4.next());		// Tests iterator's next and hasNext functions. As you can see b4's elements are added to a4
		System.out.println();

		System.out.println("Tests For Clear Function:");
		b4.clear();														// Tests clear function

		System.out.println("b4 has " + b4.size() + " elements inside.");		// As you can see b4 is cleared
		System.out.println();

		System.out.println("Tests For contains and containsAll Functions:");
		if(a4.contains("b"))	System.out.println("a4 contains b");				// prints if it contains the input
		else System.out.println("a4 doesn not contain b");							// prints if it doesn't contain the input

		if(a4.contains("emre"))	System.out.println("a4 contains emre");			// prints if it contains the input
		else System.out.println("a4 does not contain emre" );					// prints if it doesn't contain the input

		System.out.println();
		if(a4.containsAll(b4))	System.out.println("a4 contains b4." );			// prints if it contains the input
		else System.out.println("a4 doesn not contain b4.");					// prints if it doesn't contain the input

		if(a4.containsAll(c4))	System.out.println("a4 contains c4." );			// prints if it contains the input
		else System.out.println("a4 does not contain c4.");						// prints if it doesn't contain the input
		System.out.println();

		System.out.println("Tests For isEmpty Function:");
		if(b1.isEmpty())	System.out.println("b2 is empty.");		// Since i cleared b4 before i exptect to get "b4 is empty"
		else System.out.println("b2 is not empty.");

		System.out.println("Tests For remove and removeAll Functions:");
		System.out.println();
		 
		ita4.resetCurrent();

		System.out.println("a4 Before remove:");
		while (ita4.hasNext())
		{
			System.out.println(ita4.next());
		}
		ita4.resetCurrent();
		a4.remove("b");
		a4.remove("z");								// a4 doesn't contain "z" so, no effect will happen on a4 for element "z"

		System.out.println("a4 After Remove:");		// As you can see a4 doesn't contain "b" after remove function	
		while (ita4.hasNext())
		{
			System.out.println(ita4.next());
		}
		System.out.println();

		a4.removeAll(c4);
		ita4.resetCurrent();

		System.out.println("a4 After removeAll:");		// c4 contains "b", "c", "r". So, elements that a4 and c4 both has will be removed from a4
		while (ita4.hasNext())
		{
			System.out.println(ita4.next());
		}
		System.out.println();

		System.out.println("Tests For retainAll Function:");
		System.out.println();

		System.out.println("a4's top element Before poll:");
		System.out.println(a4.element());
		System.out.println("a4's top element After poll:");
		a4.poll();
		System.out.println(a4.element());


		a4.retainAll(d4);		// d4 contains "d", "c", "y", After retainAll function a4 will be the only elements that a4 and d4 both contain
		ita4.resetCurrent();

		System.out.println("a4 After retainAll:");
		while (ita4.hasNext())
		{
			System.out.println(ita4.next());
		}			

		System.out.println();
		System.out.println("Press Anything To See HashSet<Integer> Tests :");
		x = in.nextLine();
					

		// TESTS FOR HashSet<Integer> :

		HashSet <Integer> a5 = new HashSet <Integer>(7); 
		HashSet <Integer> b5 = new HashSet <Integer>(6); 
		HashSet <Integer> c5 = new HashSet <Integer>(9); 
		HashSet <Integer> d5 = new HashSet <Integer>(10); 
		Iterator ita5 = a5.iterator();

		a5.add(4);		// Tests add functions
		a5.add(5);
		a5.add(6);
		a5.add(6);		// It will print the message "HashSet contains the entered element.". Since there will be no duplicate elements.
		a5.add(1);


		b5.add(30);
		b5.add(2);

		c5.add(1);
		c5.add(32);
		c5.add(4);

		d5.add(5);
		d5.add(6);
		d5.add(13);

		System.out.println();
		System.out.println("Tests For add and addAll Functions:");

		a5.addAll(b5);
		while (ita5.hasNext())	System.out.println(ita5.next());		// Tests iterator's next and hasNext functions. As you can see b1's elements are added to a1
		System.out.println();

		System.out.println("Tests For Clear Function:");
		b5.clear();														// Tests clear function

		System.out.println("b5 has " + b5.size() + " elements inside.");
		System.out.println();

		System.out.println("Tests For contains and containsAll Functions:");
		if(a5.contains(4))	System.out.println("a5 contains " + 4);				// prints if it contains the input
		else System.out.println("a5 doesn not contain " + 4);					// prints if it doesn't contain the input

		if(a5.contains(32))	System.out.println("a2 contains " + 32);			// prints if it contains the input
		else System.out.println("a5 does not contain " + 32);					// prints if it doesn't contain the input

		System.out.println();
		if(a5.containsAll(b5))	System.out.println("a5 contains b5." );			// prints if it contains the input
		else System.out.println("a5 doesn not contain b5.");					// prints if it doesn't contain the input

		if(a5.containsAll(c5))	System.out.println("a5 contains c5." );			// prints if it contains the input
		else System.out.println("a5 does not contain c5.");						// prints if it doesn't contain the input
		System.out.println();

		System.out.println("Tests For isEmpty Function:");
		if(b5.isEmpty())	System.out.println("b5 is empty.");		// Since i cleared b5 before i exptect to get "b5 is empty"
		else System.out.println("b5 is not empty.");

		if(a5.isEmpty())	System.out.println("a5 is empty.");		// a5 is not empty so, i expected to get "a5 is not empty"
		else System.out.println("a5 is not empty.");
		System.out.println();

		System.out.println("Tests For remove and removeAll Functions:");
		System.out.println();
		 
		ita5.resetCurrent();
		System.out.println("a5 Before remove:");
		while(ita5.hasNext())
		{
			System.out.println(ita5.next());
		}

		a5.remove(30);
		a5.remove(65);								// a5 doesn't contain 65 so, no effect will happen on a3 for element 65
		ita5.resetCurrent();


		System.out.println("a5 After Remove:");		// As you can see a5 doesn't contain 30 after remove function	
		while(ita5.hasNext())
		{
			System.out.println(ita5.next());
		}
		ita5.resetCurrent();	// Resets iterator
		System.out.println();

		a5.removeAll(c5);

		System.out.println("a5 After removeAll:");		// c5 contains 1, 32, 4. So, elements that a5 and c5 both has will be removed from a1
		while(ita5.hasNext())
		{
			System.out.println(ita5.next());
		}
		System.out.println();
									
		System.out.println();
		System.out.println("Press Anything To See HashSet<Integer> Tests :");
		x = in.nextLine();	

		HashSet<String> a6 = new HashSet<String>(7);
		HashSet<String> b6 = new HashSet<String>(8);
		HashSet<String> c6 = new HashSet<String>(8);
		HashSet<String> d6 = new HashSet<String>(9);
		Iterator ita6 = a6.iterator();

		a6.add("abc");		// Tests add functions
		a6.add("b");
		a6.add("c");
		a6.add("c");		// It will print the message "HashSet contains the entered element.". Since there will be no duplicate elements.
		a6.add("d");

		b6.add("f");
		b6.add("efef");

		c6.add("b");
		c6.add("c");
		c6.add("r");

		d6.add("d");
		d6.add("c");
		d6.add("y");

		a6.addAll(b6);

		while (ita6.hasNext())	System.out.println(ita6.next());		// Tests iterator's next and hasNext functions. As you can see b6's elements are added to a6
		System.out.println();

		System.out.println("Tests For Clear Function:");
		b6.clear();														// Tests clear function

		System.out.println("b6 has " + b6.size() + " elements inside.");		// As you can see b6 is cleared
		System.out.println();

		System.out.println("Tests For contains and containsAll Functions:");
		if(a6.contains("b"))	System.out.println("a6 contains b");				// prints if it contains the input
		else System.out.println("a6 doesn not contain b");							// prints if it doesn't contain the input

		if(a6.contains("emre"))	System.out.println("a6 contains emre");			// prints if it contains the input
		else System.out.println("a6 does not contain emre" );					// prints if it doesn't contain the input

		System.out.println();
		if(a6.containsAll(b6))	System.out.println("a6 contains b6." );			// prints if it contains the input
		else System.out.println("a6 doesn not contain b6.");					// prints if it doesn't contain the input

		if(a6.containsAll(c6))	System.out.println("a6 contains c6." );			// prints if it contains the input
		else System.out.println("a6 does not contain c6.");						// prints if it doesn't contain the input
		System.out.println();

		System.out.println("Tests For isEmpty Function:");
		if(b6.isEmpty())	System.out.println("b6 is empty.");		// Since i cleared b6 before i exptect to get "b6 is empty"
		else System.out.println("b6 is not empty.");

		System.out.println("Tests For remove and removeAll Functions:");
		System.out.println();
		 
		ita6.resetCurrent();

		System.out.println("a6 Before remove:");
		while (ita6.hasNext())
		{
			System.out.println(ita6.next());
		}
		ita6.resetCurrent();
		a6.remove("b");
		a6.remove("z");								// a6 doesn't contain "z" so, no effect will happen on a6 for element "z"

		System.out.println("a6 After Remove:");		// As you can see a6 doesn't contain "b" after remove function	
		while (ita6.hasNext())
		{
			System.out.println(ita6.next());
		}
		System.out.println();

		a6.removeAll(c6);
		ita6.resetCurrent();

		System.out.println("a6 After removeAll:");		// c6 contains "b", "c", "r". So, elements that a4 and c6 both has will be removed from a6
		while (ita6.hasNext())
		{
			System.out.println(ita6.next());
		}
		System.out.println();

	}
}