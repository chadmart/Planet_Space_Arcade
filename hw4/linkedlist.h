/*!\file linkedlist.h
 * 
 * \brief Contians the LinkedList class defintion and implementation
 * 
 * \Created by: The TA Gods 
 *
 * \Edited by: Chad Martin
 * 
 * \Last Edited: 11/14/2012
 *
 * This class contians the LinkedList class defintion and implementation.
 */
#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

#include <iostream>
#include <stdexcept>
#include "node.h"

template <typename T>
class LinkedList
{
	protected:

		int length;
		Node<T>* head;

	public:

		LinkedList();
		LinkedList(const LinkedList<T>& other);
		~LinkedList();

		LinkedList<T>& operator=(const LinkedList<T> &other);

		bool empty() const;
		int size() const;
		void push_front(const T& val);
		void push_back(const T& val);
		void pop_front();
		T& at(const int& index);
		void print() const;
		void erase(const int& index);
		bool contains(const T& value) const;
		void reverse();

	private:

		void copy(const LinkedList<T>& other);
		void destroy();
};

template <typename T>
LinkedList<T>::LinkedList()
{
	this->length = 0;
	this->head = NULL;
}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& other)
{
	this->length = 0;
	this->head = NULL;

	copy(other);
}

template <typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& other)
{
	if(this != &other) copy(other);
	return *this;
}

template <typename T>
void LinkedList<T>::copy(const LinkedList<T>& other)
{
	destroy();

	Node<T>* current = other.head;
	while(current != NULL)
	{
		// Is something wrong here?!
		push_back(current->data);
		current = current->next;
	}

	this->length = other.length;
}

template <typename T>
LinkedList<T>::~LinkedList()
{
	destroy();
}

template <typename T>
void LinkedList<T>::destroy()
{

	while(head != NULL)
	{
		Node<T>* current = this->head;
		head = head->next;
		delete current;
	}

	this->length = 0;
}

template <typename T>
bool LinkedList<T>::empty() const
{
	return this->length == 0;
}

template <typename T>
int LinkedList<T>::size() const
{
	return this->length;
}

template <typename T>
void LinkedList<T>::push_front(const T& val)
{
	//make a new node
	Node<T>* newOne = new Node<T>(val);

	//push it onto the front of the list
	newOne->next = this->head;
	this->head = newOne;

	//increase the length of the list by one
	this->length++;
}

template <typename T>
void LinkedList<T>::push_back(const T& val)
{
	Node<T>* current = this->head;
	Node<T>* newOne = new Node<T>(val);

	if(!empty())
	{
		//make a new node

		//newOne->next = NULL;


		while(current->next != NULL)
		{
			current = current->next;
		}

		//push it onto the back of the list
		current->next = newOne;

		//increase the length of the list by one

	}
	else
	{
		head = newOne;
	}

	this->length++;
}


template <typename T>
void LinkedList<T>::pop_front()
{
	// this function should drop the node at the head of the list.
	// don’t forget the delete.
	Node<T> * newOne;
	newOne = head;

	// advance head
	head = head->next;

	// delete old head
	delete newOne;

	// decrease the length of the list by one
	this->length--;
}

template <typename T>
T& LinkedList<T>::at(const int& index)
{
	//make sure the index is in bounds
	if(index < 0 || index >= this->length)
	{
		throw std::out_of_range("index was out of bounds in at().");
	}

	//walk through the list until we hit the index we want
	Node<T>* current = this->head;
	int currentIndex = 0;
	while(currentIndex != index)
	{
		current = current->next;
		currentIndex++;
	}

	//return the data at the given index
	return current->data;
}

template <typename T>
void LinkedList<T>::erase(const int& index)
{
	//check that the index is in bounds
	if(index < 0 || index >= this->length)
	{
		throw std::out_of_range("index was out of bounds in erase()!");
	}

	Node<T>* previous = NULL;
	Node<T>* current = this->head;
	int currentIndex = 0;

	//walk through the list until "current" points to
	//the thing we want to get rid of
	while(currentIndex != index)
	{
		previous = current;
		current = current->next;
		currentIndex++;
	}

	//removing the first element
	if(previous == NULL)
	{
		this->head = head->next;
	}
	//remove a middle element
	else
	{
		previous->next = current->next;
	}

	//free up the memory that was allocated by the insert
	delete current;
	this->length--;
}

template <typename T>
void LinkedList<T>::print() const
{
	//walk through the list element by element and print
	//out the value of each element
	Node<T>* current = this->head;
	while(current != NULL)
	{
		std::cout << current->data << " ";
		current = current->next;
	}
	std::cout << std::endl;
}

template <typename T>
bool LinkedList<T>::contains(const T& value) const
{
	// this function checks if the passed value exists
	// in the list and then returns a boolean accordingly.
	Node<T>* current = this->head;

	if(!empty())
	{
		while(current != NULL)
		{
			if(current->data == value)
				{return true;}

			current = current->next;
		}

	}

	return false;
}

template <typename T>
void LinkedList<T>::reverse()
{
	// this function is going to turn the list around.
	// The ‘head’ will point to the last node.
	Node<T>* current = this->head;
	Node<T>* nextNode = NULL;
	Node<T>* prevNode = NULL;

	if(!empty())
	{
		while(current != NULL)
		{
			nextNode = current->next;
			current->next = prevNode;
			prevNode = current;
			current = nextNode;
		}
		this->head = prevNode;
	}

}

#endif
