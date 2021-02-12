package src.interfaces;

/**

	Queue interface

	@author Barış Ayyıldız

 */

/**
	@param <E> Data type
 */
public interface Queue<E> extends Collection<E>
{
	/**
	Retrieves, but does not remove, the head of this queue
	@return the head of this queue
	*/
	E element();

	/**
	Inserts the specified element into this queue
	@param e the element to add
	@return true if the element is added to this queue
	*/
	boolean offer(E e);

	/**
	Retrieves and removes the head of this queue, or returns null if this queue is empty.
	@return the head of this queue, or null if this queue is empty
	*/
	E poll();
}
