/*!\file node.h
 * 
 * \brief Contians the Node class defintion and implementation
 * 
 * \Created by: The TA Gods 
 *
 * This class contians the Node class defintion and implementation.
 */
#ifndef NODE_H_
#define NODE_H_

template <typename T>
class Node
{
	public:
	
		Node(const T& d);
		
		T data;
		Node<T>* next;
};

template <typename T>
Node<T>::Node(const T& d)
: data(d)
{
	this->next = NULL;
}

#endif
