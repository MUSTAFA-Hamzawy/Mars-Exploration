
#ifndef _Node_PQ
#define _Node_PQ
template < typename T>
class Node_PQ
{
public:
	T item; // A data item
	float priority;
	Node_PQ<T>* next; // Pointer to next Node_PQ
public:

	Node_PQ()
	{
		next = nullptr;
	}

	Node_PQ(const T& r_Item)
	{
		item = r_Item;
		next = nullptr;
	}

	Node_PQ(const T& r_Item, Node_PQ<T>* nextNode_PQPtr)
	{
		item = r_Item;
		next = nextNode_PQPtr;
	}

	void setItem(const T& r_Item, const float& r_priority)
	{
		item = r_Item;
		priority = r_priority;
	}

	void setNext(Node_PQ<T>* nextNode_PQPtr)
	{
		next = nextNode_PQPtr;
	}

	T getItem() const
	{
		return item;
	}

	float getPriority() const
	{
		return priority;
	}

	Node_PQ<T>* getNext() const
	{
		return next;
	}

}; // end Node_PQ
#endif
