package src.interfaces;

/**

	List interface

	@author Barış Ayyıldız

*/

/**
	@param <E> Data type
 */
public interface List<E> extends Collection<E>
{
	/**
	Returns the element at the specified position in this list.
	@param index index of the element to return

	*/
	E get(int index);
	/**
	Replaces the element at the specified position in this list with the specified element
	@param index index of the element to replace
	@param e element to be stored at the specified position
	*/
	void set(int index, E e);

	/**
	Returns the index of the first occurrence of the specified element in this list, or -1 if this list does not contain the element.
	@return the index of the first occurrence of the specified element in this list, or -1 if this list does not contain the element
	*/
	int indexOf(E e);
}
