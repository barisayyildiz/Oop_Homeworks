package src.classes;

import java.util.NoSuchElementException;
import java.lang.IllegalStateException;

import src.interfaces.*;


/**

	ArrayList class

	@author Barış Ayyıldız

*/


/**
	@param <E> Data type
*/
public class ArrayList<E> implements List<E>//, Iterable<E>
{
	// variables

	private E[] arr;
	private int cap;
	private int counter;

	private final static int INITIAL_CAP = 10;

	/**
		ArrayList default constructor, it sets the initial cap to 10
	*/
	public ArrayList()
	{
		this.cap = INITIAL_CAP;
		this.counter = 0;

		arr = (E[]) new Object[cap];
	}

	/**
		ArrayList constructor, takes initial cap as a paramters
		@param cap Initial capacity
		@throws IllegalArgumentException if the specified initial capacity is negative
	*/
	public ArrayList(int cap)
	{
		if(cap < 0)
			throw new IllegalArgumentException("Initial capacity cannot be negative");


		this.cap = cap;
		this.counter = 0;

		arr = (E[]) new Object[cap];

	}

	// returns the value at the index
	public E get(int index)
	{
		if(index >= counter)
		{
			throw new IndexOutOfBoundsException("Index is out of bound...");
		}
		return arr[index];
	}

	// sets the index with the value
	public void set(int index, E e)
	{
		if(index >= counter)
		{
			throw new IndexOutOfBoundsException("Index is out of bound...");
		}
		arr[index] = e;
	}

	public boolean add(E e)
	{
		if(counter == cap)
		{
			this.cap += 10;

			E[] temp = (E[]) new Object[cap];
			this.arr = temp;
		}

		this.arr[counter++] = e;

		return true;
	}

	public boolean isEmpty()
	{
		return counter == 0;
	}
	
	// removes by value
	public boolean remove(E e)
	{
		int index = -1;

		// find the first index
		for(int i=0; i<counter; i++)
		{
			if(this.arr[i] == e)
			{
				index = i;
				break;
			}
		}

		// not in the ArrayList
		if(index == -1)
			return false;

		for(int i=index+1; i<counter; i++)
		{
			this.arr[i-1] = this.arr[i];			
		}

		this.counter--;
		
		return true;

	}

	public boolean contains(E e)
	{
		for(E temp : this.arr)
		{
			if(temp == e)
				return true;
		}
		return false;
	}

	public int size()
	{
		return counter;
	}

	public boolean containsAll(Collection c)
	{
		Iterator<E> iterR = c.iterator();

		while(iterR.hasNext())
		{
			if(!this.contains(iterR.next()))
				return false;
		}
		return true;

	}

	public int indexOf(E e)
	{
		for(int i=0; i<counter; i++)
		{
			if(e == this.arr[i])
				return i;
		}

		return -1;
	}

	public boolean removeAll(Collection c)
	{
		Iterator<E> iterR = c.iterator();

		int inc = 0;
		E current;

		while(iterR.hasNext())
		{
			current = iterR.next();
			if(this.contains(current))
			{
				inc++;
				this.remove(current);
			}
		}

		if(inc == 0)
			return false;
		return true;

	}

	public boolean retainAll(Collection c)
	{
		Iterator<E> iterR = c.iterator();

		E[] temp = (E[]) new Object[cap];
		int tempCounter = 0;
		E current;

		while(iterR.hasNext())
		{
			current = iterR.next();

			if(this.contains(current))
			{
				temp[tempCounter++] = current;
				this.remove(current);
			}

		}

		this.arr = temp;

		if(this.counter == tempCounter)
		{
			return false;
		}

		this.counter = tempCounter;
		return true;

	}

	public boolean addAll(Collection c)
	{
		Iterator<Integer> iterR = c.iterator();

		if(c.size() == 0)
			return false;

		while(iterR.hasNext())
		{
			this.add((E)iterR.next());
		}

		return true;

	}

	public void clear()
	{
		this.counter = 0;
		this.cap = INITIAL_CAP;
		this.arr = null;
	}

	public Iterator<E> iterator()
	{
		return new ArrayListIter();
	}

	class ArrayListIter implements Iterator<E>
	{
		int current = 0;
		int flag = -1;

		public boolean hasNext()
		{
			return current < counter;
		}

		public E next()
		{
			if(!hasNext())
				throw new NoSuchElementException("cannot iterate more...");
			
			flag = 1;
			return arr[current++];

		}

		public void remove()
		{
			if(flag == -1)
				throw new IllegalStateException("cannot remove...");
				
			int temp = current;
			
			while(current < counter)
			{
				arr[current-1] = arr[current];
				current++;
			}

			current = temp;
			counter--;

			flag = -1;

		}

	}	

}

