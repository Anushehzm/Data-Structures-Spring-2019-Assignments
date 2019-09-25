#ifndef __QUEUE_CPP
#define __QUEUE_CPP
#include "queue.h"

template <class T>
Queue<T>::Queue()
{

}
    
template <class T>
Queue<T>::Queue(Queue<T>& otherQueue):list(otherQueue.list)
{
}

template <class T>
Queue<T>::~Queue()
{

}

template <class T>
void Queue<T>::enqueue(T item)
{
	list.insertAtTail(item);

}
//khaali list case
template <class T>
T Queue<T>::front()
{
	return list.getHead()->value; 
}
//khaali case and add return --error dai raha abhi
template <class T>
T Queue<T>::dequeue()
{

	T a=list.getHead()->value;
	list.deleteHead();
	return a;
}

template <class T>
int Queue<T>::length()
{
	return list.length();
}

template <class T>
bool Queue<T>::isEmpty()
{
	if (list.getHead()==NULL)
	{
		return true;
	}
	else
		return false;
}


#endif
