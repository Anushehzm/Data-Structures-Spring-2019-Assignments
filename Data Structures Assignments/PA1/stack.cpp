#ifndef __STACK_CPP
#define __STACK_CPP
#include "stack.h"
#include "LinkedList.cpp"
#include "LinkedList.h"

template <class T>
Stack<T>::Stack()
{
	
}
    
template <class T>
Stack<T>::Stack(Stack<T>& otherStack):list(otherStack.list)
{
}

template <class T>
Stack<T>::~Stack()
{
}

template <class T>
void Stack<T>::push(T item)
{
	list.insertAtHead(item);

}
//khaali list case
template <class T>
T Stack<T>::top()
{
	if(list.getHead()!=NULL)
	 return (list.getHead()->value);
	
}
//khaali list case---floaring point error if no value returned
template <class T>
T Stack<T>::pop()
{	
	//if (list.getHead()!=NULL)
	//{
	T p=list.getHead()->value;
	list.deleteHead();
	return p;
	//}
}

template <class T>
int Stack<T>::length()
{
	return list.length();
}

template <class T>
bool Stack<T>::isEmpty()
{
	if (list.getHead()==NULL)
	{
		return true;
	}
	else
		return false;
}

#endif

