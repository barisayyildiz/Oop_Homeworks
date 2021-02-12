import src.interfaces.*;
import src.classes.*;


public class Driver
{
	public static void main(String[] argv)
	{
		TestCases.TestCase1();
		TestCases.TestCase2();
		TestCases.TestCase3();
		TestCases.TestCase4();
	}
}


class TestCases
{
	static void TestCase1()
	{
		System.out.println("#Test Case1");
		ArrayList<Integer> a1 = new ArrayList<Integer>(20);
		a1.add(7);
		a1.add(8);
		a1.add(9);
		a1.remove(8);

		Iterator<Integer> iter = a1.iterator();

		while(iter.hasNext())
			System.out.println("->" + iter.next());

		System.out.println("IsEmpty : " + a1.isEmpty());
		System.out.println("0th element : " + a1.get(0));
		System.out.println("Index of 21 : " + a1.indexOf(21));

		System.out.println("After addAll method : ");

		LinkedList<Integer> a2 = new LinkedList<Integer>();
		a2.add(99);
		a2.add(146);
		a2.add(276);

		a1.addAll(a2);

		iter = a1.iterator();

		while(iter.hasNext())
			System.out.println("->" + iter.next());

		System.out.println("------------");
	}

	static void TestCase2()
	{
		System.out.println("#Test Case2");
		LinkedList<Integer> a1 = new LinkedList<Integer>();
		a1.add(12);
		a1.add(21);
		a1.add(35);

		Iterator<Integer> iter = a1.iterator();

		while(iter.hasNext())
			System.out.println("->" + iter.next());

		System.out.println("First element (element method) : " + a1.element());

		a1.offer(5555);
		a1.poll();
		a1.poll();

		System.out.printf("\n");

		iter = a1.iterator();

		while(iter.hasNext())
			System.out.println("->" + iter.next());


		a1.clear();
		System.out.println("After clear method : ");

		System.out.println("Size : " + a1.size());
		System.out.println("IsEmpty : " + a1.isEmpty());


		System.out.println("------------");
	}

	static void TestCase3()
	{
		System.out.println("#Test Case3");
		HashSet<String> h1 = new HashSet<String>();
		h1.add("C");
		h1.add("C++");
		h1.add("Java");
		h1.add("Python");
		h1.add("JavaScript");

		// doesn't add dublicate elements
		h1.add("Java");
		h1.add("C++");

		Iterator<String> iter = h1.iterator();

		while(iter.hasNext())
			System.out.println("->" + iter.next());

		System.out.println("Does it contains Python : " + h1.contains("Python"));
		System.out.println("Does it contains Pascal : " + h1.contains("Pascal"));


		ArrayList<String> a1 = new ArrayList<String>();

		a1.add("C");
		a1.add("C++");

		System.out.println("Contains all : " + h1.containsAll(a1));
	
		System.out.println("After clear all method...");

		h1.removeAll(a1);

		iter = h1.iterator();
		
		while(iter.hasNext())
			System.out.println("->" + iter.next());



		System.out.println("------------");

	}

	static void TestCase4()
	{
		System.out.println("#Test Case4");
		ArrayList<Integer> a1 = new ArrayList<Integer>();
		a1.add(3);
		a1.add(12);
		a1.add(99);
		a1.add(2456);
		a1.add(55);

		Iterator<Integer> iter = a1.iterator();

		int i;

		while(iter.hasNext())
		{
			i = iter.next();
			
			if(i % 2 == 1)
				iter.remove();
		}

		System.out.println("Even numbers : ");

		iter = a1.iterator();
		while(iter.hasNext())
		{
			System.out.println(iter.next());
		}


		System.out.println("------------");
	}
}
