#ifndef __LIST_CPP
#define __LIST_CPP
#include "LinkedList.h"
#include <cstdlib>
using namespace std;

template <class T>
LinkedList<T>::LinkedList()
{
	head=NULL;
}

//iske const wala masla sahi karo
template <class T>
LinkedList<T>::LinkedList(const LinkedList<T>& otherLinkedList)
{
	head=NULL;
	if (otherLinkedList.head!=NULL)
	{
		ListItem<T> *p=otherLinkedList.head;
	while(p->next!=NULL)
	{
		insertAtTail(p->value);
		p=p->next;
	}
	insertAtTail(p->value);
		// int len=otherLinkedList.length();
		// for (int i=0; i<len; i++)
		// {
		// 	this->insertAtTail((otherLinkedList.head->value);
		// }
	}

	// ListItem<T> *p=(const otherLinkedList.getHead());
	// while(p->next!=NULL)
	// {
	// 	insertAtHead((const otherLinkedList.getTail())->value);
	// 	p=p->next;
	// }
	// insertAtHead((const otherLinkedList.getTail())->value);
	
}

template <class T>
LinkedList<T>::~LinkedList()
{
	if (head!=NULL)
	{
		ListItem<T> *p=head;
		while (p !=NULL)
		{
		ListItem<T>* t= p->next;
		delete p;
		p=t;
		}
		head=NULL;
	}
}

template <class T>
void LinkedList<T>::insertAtHead(T item)
{
ListItem<T> *t = new ListItem<T> (item);
t->prev = NULL;
t->next = head;
if (head != NULL)
{
head->prev = t;
}
head = t;
}

template <class T>
void LinkedList<T>::insertAtTail(T item)
{
ListItem<T> *t = new ListItem<T>(item);
if (head == NULL)
{
t->next = NULL;
t->prev = NULL;
head = t;

}
else
{
ListItem<T> *p = head;
while (p->next != NULL)
{
p = p->next;
}
p->next = t;
t->prev = p;
t->next = NULL;
}
}

template <class T>
void LinkedList<T>::insertAfter(T toInsert, T afterWhat)
{
if (head!=NULL)
	{
		ListItem<T> *traverse = head;
		while (traverse->next != NULL)
		{
			if (traverse->value==afterWhat)
			{
				ListItem<T> *add=new ListItem<T>(toInsert);
				add->next=traverse->next;
				add->prev=traverse;
				traverse->next->prev=add;
				traverse->next=add;
				return;
			}	
			traverse=traverse->next;		
		}
		//last
		if (traverse->value==afterWhat)
		{
			ListItem<T> *add=new ListItem<T>(toInsert);
			add->next=traverse->next;
			add->prev=traverse;
			//traverse->next->prev=add;
			traverse->next=add;
		}
	}	
}


template <class T>
ListItem<T>* LinkedList<T>::getHead()
{
return head;
}

template <class T>
ListItem<T>* LinkedList<T>::getTail()
{
if (head == NULL)
{
return head;
}
ListItem<T> *p = head;
while (p->next != NULL)
{
p = p->next;
}
return p;
}

template <class T>
ListItem<T> *LinkedList<T>::searchFor(T item)
{
	if (head==NULL)
	{
	return NULL;		
	}
	else
	{
		ListItem<T> *p = head;
		while (p->next != NULL)
		{
			if (p->value==item)
			{
				return p;
			}
			p = p->next;
		}		
		if (p->value==item)
			{
				return p;
			}
	}
}

template <class T>
void LinkedList<T>::deleteElement(T item)
{
	if (head!=NULL)
	{

		ListItem<T> *p = searchFor(item);
		if ((p->prev==NULL))//one element or first 
		{
			deleteHead();
		}
		else if (p->next==NULL)//last
		{
			deleteTail();
		}
		else 
		{
		p->next->prev=p->prev;
		p->prev->next=p->next;
		delete p;
		p=NULL;
		}
	
	}
}

template <class T>
void LinkedList<T>::deleteHead()
{
	if (head!=NULL)
	{
		
		if (head->next!=NULL)
		{
			head=head->next;
			delete head->prev;
			head->prev=NULL;
		}
		else
		{
			delete head;
			head=NULL;
		}		
	}
	
} 

template <class T>
void LinkedList<T>::deleteTail()
{
	if (head!=NULL)
	{
		if (head->next==NULL)
		{
			delete head;
			head=NULL;
		}
		else
		{
		ListItem<T> *p=head;
		while(p->next!=NULL)
		{
			p=p->next;
		}
		p->prev->next=NULL;
		//p->prev=NULL;
		delete p;
		p=NULL;
		
		}
	}
}

template <class T>
int LinkedList<T>::length()
{
if (head == NULL)
{ 
return 0;
}
ListItem<T> *p = head;
int count = 1;
while (p->next != NULL)
{
p = p->next;
count++;
}
p=NULL;
return count;
}


#endif

