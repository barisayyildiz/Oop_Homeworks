package src.interfaces;

/**

	Collection interface

	@author Barış Ayyıldız

 */

/**
	@param <E> Data type
 */
public interface Collection<E>
{
	/**
	Returns an iterator
	@return Iterator<E> Returns an iterator
	 */
	Iterator<E> iterator();
	
	/**
	Adds the element
	@param e element that is going to be added
	@return true if this collection changed as a result of the call
	 */
	boolean add(E e);

	/**
	Adds all of the elements in the specified collection to this collection
	@param c collection containing elements to be added to this collection
	@return true if this collection changed as a result of the call
	 */

	boolean addAll(Collection c);

	/**
	Removes all of the elements from this collection

	*/
	void clear();

	/**
	Returns true if this collection contains the specified element
	@param e element that is going to be searched inside the collection
	@return true if this collection contains the specified element
	*/
	boolean contains(E e);

	/**
	Returns true if this collection contains all of the elements in the specified collection.
	@param c collection to be checked for containment in this collection
	@return true if this collection contains all of the elements in the specified collection
	*/
	boolean containsAll(Collection c);

	/**
	Returns true if this collection contains no elements.
	@return true if this collection contains no elements
	*/

	boolean isEmpty();

	/**
	Removes a single instance of the specified element from this collection
	@param e element to be removed from this collection
	@return true if an element is removed from the collection
	*/
	boolean remove(E e);

	/**
	Removes all of this collection's elements that are also contained in the specified collection
	@param c collection containing elements to be removed from this collection
	@return true if this collection changed as a result of the call
	*/
	boolean removeAll(Collection c);

	/**
	Retains only the elements in this collection that are contained in the specified collection
	@param c collection containing elements to be retained in this collection
	@return true if this collection changed as a result of the call
	*/
	boolean retainAll(Collection c);

	/**
	Returns the number of elements in this collection
	@return the number of elements in this collection
	*/
	int size();
}
