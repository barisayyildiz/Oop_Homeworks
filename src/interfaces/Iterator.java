package src.interfaces;

/**

	Iterator interface

	@author Barış Ayyıldız

*/

/**
	@param <E> Data type
*/
public interface Iterator<E>
{
	/**
	Returns true if the iteration has more elements
	@return true if the iteration has more elements
	*/
	boolean hasNext();
	
	/**
	Returns the next element in the iteration.
	@return the next element in the iteration
	@throws NoSuchElementException if the iteration has no more elements
	*/
	E next();

	/**
	Removes from the underlying collection the last element returned by this iterator
	@throws IllegalStateException if the next method has not yet been called
	*/
	void remove();
}
