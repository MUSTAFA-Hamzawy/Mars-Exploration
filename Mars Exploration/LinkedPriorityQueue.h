/*
This is a program that implements the queue abstract data type using a linked list.
The queue is implemented as a chain of linked Node_PQs that has two pointers,
a frontPtr pointer for the front of the queue and a backPtr pointer for the back of the queue.
*/

/*

The Node_PQ: item of type T and a "next" pointer
-------------
| item| next | --->
-------------
General Queue case:

frontPtr																backPtr
\											   						/
\											  					   /
------------- 	  ------------- 	  ------------- 	  -------------
| item| next |--->| item| next |--->  | item| next |--->  | item| next |---> NULL
------------- 	  ------------- 	  ------------- 	  -------------

Empty Case:

frontptr	 backptr
\	 /
\	/
---- NULL ------


Single Node_PQ Case:
frontPtr	 backPtr
\		/
\	   /
-----------
|item| next| -->NULL
-----------

*/

#ifndef LINKED_PriorityQUEUE_
#define LINKED_PriorityQUEUE_

#include "Node_PQ.h"
#include "PriorityQueueADT.h"
using namespace std;


template <typename T>
class LinkedPriorityQueue :public PriorityQueueADT<T>
{
private:

	Node_PQ<T>* backPtr;
	Node_PQ<T>* frontPtr;
public:
	/*
	Function: Queue()
	The constructor of the Queue class.

	*/

	LinkedPriorityQueue()
	{
		backPtr = nullptr;
		frontPtr = nullptr;

	}
	/////////////////////////////////////////////////////////////////////////////////////////

	/*
	Function: isEmpty
	Sees whether this queue is empty.

	Input: None.
	Output: True if the queue is empty; otherwise false.
	*/
	bool isEmpty() const
	{
		return (frontPtr == nullptr);
	}

	/////////////////////////////////////////////////////////////////////////////////////////

	/*Function:enqueue
	Adds newEntry at the back of this queue.

	Input: newEntry .
	Output: True if the operation is successful; otherwise false.
	*/

	bool enqueue(const T& newEntry, const float& ppriority)
	{
		Node_PQ<T>* newNode_PQPtr = new Node_PQ<T>;
		Node_PQ<T>* newNode_PQPtr22;
		newNode_PQPtr->item = newEntry;
		newNode_PQPtr->priority = ppriority;
		// Insert the new Node_PQ
		if (isEmpty() || ppriority > frontPtr->priority)	//special case if this is the first Node_PQ to insert
		{
			newNode_PQPtr->next = frontPtr;
			frontPtr = newNode_PQPtr; // The queue is empty
		}
		else
		{
			newNode_PQPtr22 = frontPtr;
			while (newNode_PQPtr22->next != nullptr && newNode_PQPtr22->next->priority > ppriority)
				newNode_PQPtr22 = newNode_PQPtr22->next;
			newNode_PQPtr->next = newNode_PQPtr22->next;
			newNode_PQPtr22->next = newNode_PQPtr;

			//backPtr->setNext(newNode_PQPtr); // The queue was not empty
		}


		//backPtr = newNode_PQPtr; // New Node_PQ is the last Node_PQ now
		return true;
	} // end enqueue


	  /////////////////////////////////////////////////////////////////////////////////////////////////////////

	  /*Function: dequeue
	  Removes the front of this queue. That is, removes the item that was added
	  earliest.

	  Input: None.
	  Output: True if the operation is successful; otherwise false.
	  */

	bool dequeue(T& frntEntry)
	{
		if (isEmpty())
			return false;

		Node_PQ<T>* Node_PQToDeletePtr = frontPtr;
		frntEntry = frontPtr->getItem();
		//priorityy = frontPtr->getPriority();
		frontPtr = frontPtr->getNext();
		// Queue is not empty; remove front
		if (Node_PQToDeletePtr == backPtr)	 // Special case: last Node_PQ in the queue
			backPtr = nullptr;

		// Free memory reserved for the dequeued Node_PQ
		delete Node_PQToDeletePtr;

		return true;

	}
	/////////////////////////////////////////////////////////////////////////////////////////
	/*
	Function: peek
	copies the front of this queue to the passed param. The operation does not modify the queue.

	Input: None.
	Output: The front of the queue.
	*/
	bool peek(T& frntEntry) const
	{
		if (isEmpty())
			return false;

		frntEntry = frontPtr->getItem();
		return true;

	}
	///////////////////////////////////////////////////////////////////////////////////
	/*
	Function: destructor
	removes all Node_PQs from the queue by dequeuing them
	*/
	~LinkedPriorityQueue()
	{
		T temp;
		//Free (Dequeue) all Node_PQs in the queue
		while (dequeue(temp));
	}
	/////////////////////////////////////////////////////////////////////////////////////////
	/*
	Function: Copy constructor
	To avoid shallow copy,
	copy constructor is provided

	Input: LinkedPriorityQueue<T>: The Queue to be copied
	Output: none
	*/

	
	LinkedPriorityQueue(const LinkedPriorityQueue<T>& LQ)
	{
		Node_PQ<T>* Node_PQPtr = LQ.frontPtr;
		if (!Node_PQPtr) //LQ is empty
		{
			frontPtr = backPtr = nullptr;
			return;
		}

		//insert the first Node_PQ
		Node_PQ<T>* ptr = new Node_PQ<T>(Node_PQPtr->getItem());
		frontPtr = backPtr = ptr;
		Node_PQPtr = Node_PQPtr->getNext();

		//insert remaining Node_PQs
		while (Node_PQPtr)
		{
			Node_PQ<T>* ptr = new Node_PQ<T>(Node_PQPtr->getItem());
			backPtr->setNext(ptr);
			backPtr = ptr;
			Node_PQPtr = Node_PQPtr->getNext();
		}
	}
};
/////////////////////////////////////////////////////////////////////////////////////////



#endif