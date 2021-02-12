package src.classes;

import java.util.NoSuchElementException;
import java.lang.IllegalStateException;

import src.interfaces.*;

/**

	LinkedList class
	@author Barış Ayyıldız


*/

/**
	@param <E> Data type
*/
public class LinkedList<E> implements List<E>,Queue<E>//,Iterable<E>
{
	private int counter;
	private Node start;
	private Node end;

	/**
		Constructs an empty list.
	*/
	public LinkedList()
	{
		this.counter = 0;
		this.start = null;
		this.end = this.start;
	}

	public boolean add(E e)
	{
		if(counter == 0)
		{
			// this.start = this.end
			this.start = new Node(e);
			this.end = this.start;
			this.counter++;
			return true;
		}

		Node temp = this.end;
		temp.next = new Node(e);

		temp = temp.next;
		temp.prev = this.end;

		// this.end = temp.next;
		this.end = temp;

		this.counter++;
		return true;

	}

	public boolean addAll(Collection c)
	{
		Iterator<E> rIter = c.iterator();
		Node lIter = end;

		if(c.size() == 0)
			return false;

		while(rIter.hasNext())
		{
			lIter.next = new Node((E)rIter.next());
			lIter = lIter.next;
		}

		return true;
	
	}

	public void clear()
	{
		if(counter == 0)
			return;
		else if(counter == 1)
		{
			this.counter = 0;
			this.start = null;
			return;
		}

		Node temp = this.start;
		Node temp2 = this.start.next;

		while(temp2 != null)
		{
			temp = null;
			temp = temp2;
			temp2 = temp2.next;
		}

		this.counter = 0;
		temp = null;
	}

	public boolean contains(E e)
	{
	
		Iterator<E> iter = this.iterator();
		E current;

		while(iter.hasNext())
		{
			if(iter.next() == e)
				return true;
		}

		return false;
		
	}

	public boolean containsAll(Collection c)
	{
		Iterator<E> iterR = c.iterator();

		while(iterR.hasNext())
		{
			if(!this.contains((E)iterR.next()))
				return false;
		}
		return true;

	}

	public boolean isEmpty()
	{
		return counter == 0;
	}

	public boolean remove(E e)
	{
		if(this.counter == 0)
			return false;
		
		Node temp = this.start;

		// in the first node
		if(temp.val == e)
		{
			this.start = this.start.next;
			temp = null;
			return true;
		}

		// have one node and it's value is not equal to e
		if(this.counter == 1)
			return false;


		Node temp2 = temp.next;
		

		while(temp2 != null)
		{
			if(temp2.val == e)
			{		
				temp.next = temp2.next;
				temp2 = null;
				this.counter--;
				return true;
			}

			temp = temp.next;
			temp2 = temp2.next;		
		}

		return false;
	}

	public boolean removeAll(Collection c)
	{
		Iterator<E> iterR = c.iterator();

		int inc = 0;
		E current;

		while(iterR.hasNext())
		{
			current = (E)iterR.next();
			if(this.contains(current))
			{
				inc++;
				this.remove(current);
			}
		}

		return inc != 0;

	}

	public boolean retainAll(Collection c)
	{
		Node newStart = null;
		Node newIter = null;
		Node newEnd = null;
		int newCounter = 0;

		Iterator<E> iterR = c.iterator();
		E current;

		while(iterR.hasNext())
		{
			current = (E)iterR.next();

			if(this.contains(current))
			{
				if(newCounter == 0)
				{
					newStart = new Node(current);
					newEnd = newStart;
					newCounter++;
					continue;
				}

				newIter = newEnd;
				newIter.next = new Node(current);
				newEnd = newIter.next;
				newCounter++;
				continue;
			}
		}

		if(newCounter == this.counter)
		{
			return false;
		}

		this.counter = newCounter;
		this.start = newStart;
		this.end = newEnd;
	
		return true;
	}

	public int size()
	{
		return counter;
	}

	public E get(int index)
	{
		if(index > counter)
		{
			throw new IndexOutOfBoundsException("Index is out of bound...");
		}

		Node temp = this.start;
		for(int i=0; i<index; i++)
		{
			temp = temp.next;
		}

		return (E)temp.val;

	}

	public void set(int index, E e)
	{
		if(index > counter)
		{
			throw new IndexOutOfBoundsException("Index is out of bound...");
		}

		Node temp = this.start;
		for(int i=0; i<index; i++)
		{
			temp = temp.next;
		}

		temp.val = e;
	}

	public int indexOf(E e)
	{
		Node temp = this.start;
		int i = 0;
		
		while(temp != null)
		{
			if(temp.val == e)
				return i;
			i++;
		}
		return -1;
	}

	public E element()
	{
		return (E)this.start.val;
	}

	public boolean offer(E e)
	{

		return this.add(e);

	}


	public E poll()
	{
		E val;

		if(this.counter == 0)
			return null;
		else if(this.counter == 1)
		{
			val = (E)this.start.val;
			this.clear();
			return val;
		}
			
		val = (E)this.start.val;
		Node temp = this.start;

		this.start = this.start.next;
		temp = null;

		return val;
	}

	public Iterator<E> iterator()
	{
		return new LinkedListIter();
	}


	class LinkedListIter implements Iterator<E>
	{
		Node current = start;
		int flag = -1;

		public boolean hasNext()
		{
			return current != null;
		}

		public E next()
		{
			if(!hasNext())
				throw new NoSuchElementException("cannot iterate more...");
			
			// return arr[current++];

			flag = 1;
			
			E temp = (E)current.val;
			current = current.next;

			return temp;

		}

		public void remove()
		{
			if(flag == -1)
				throw new IllegalStateException("cannot remove...");

			// only 1 element
			if(counter == 1)
			{
				clear();
				flag = -1;
				return;
			}

			if(current == null)
			{
				// last element
				end = end.prev;
				end.next = null;
			}else if(current.prev.prev == null)
			{
				// first element
				start = current;
			}else
			{
				current.prev.prev.next = current;
			}

			flag = -1;
			counter--;

		}

	}

}

class Node<E>
{
	public E val;
	public Node next;
	public Node prev;
	Node(E e)
	{
		val = e;
		next = null;
		prev = null;
	}
}

