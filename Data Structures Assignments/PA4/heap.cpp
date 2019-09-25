#ifndef __HEAP_CPP
#define __HEAP_CPP
#include "heap.h"
#include "iostream"

MinHeap::MinHeap(int cap)
{
    capacity=cap;
    harr=new int [cap];
    heap_size=0;
}

void MinHeap::MinHeapify(int i)// check---use neechay wale functions
{
    if (i>-1 && i<heap_size && harr[i]) //base case?
    {
        int change=i;

        if (left(i) <heap_size && harr[change]>harr[left(i)])
        {
            change=left(i);
        }
        if (right(i) <heap_size && harr[change]>harr[right(i)])
        {
            change=right(i);
        }

        if (change!=i)
        {
            int q= harr[i];
            harr[i]=harr[change];
            harr[change]=q;
            MinHeapify(change);
        }
        // if(parent(i)>-1 && harr[parent(i)] && harr[i]<harr[parent(i)])
        // {
        //     int e=parent(i);
        //     int q= harr[i];
        //     harr[i]=harr[e];
        //     harr[e]=q;
        // }


      
    }
}
 
int MinHeap::parent(int i)
{
    return ((i-1)/2); //assuming floor khud ho jaye ga since int
}
 
int MinHeap::left(int i)
{
    return ((2*i)+1);
}
 
int MinHeap::right(int i)
{
    return ((2*i)+2);
}
 
int MinHeap::extractMin() //heapfy isnt fixing
{
    // cout<<"Array before extract min: "<<endl;
    // for(int i=0; i<heap_size; i++)
    // {
    //     cout<<harr[i]<<" "<<endl;
    // }
    // cout<<endl;
    if(heap_size>=1)   
    {
        int a=harr[0]; //stored to return
        harr[0]=harr[heap_size-1]; //last element jo bhi yahan daal diya
        heap_size--; //last element ignored
        MinHeapify(0); //last element ki jaga fixed
        //cout<<"Removed: "<<a<<endl;
        //cout<<"heap size: "<<heap_size<<endl;
        // cout<<"Array after extract min"<<endl;
        // for(int x=0; x<heap_size; x++)
        // {
        //     cout<<harr[x]<<" "<<endl;
        // } 

        return a;
    }
    else
    {
        cout<<"No value to extract"<<endl;
        return -1;
    }
}          
 
void MinHeap::decreaseKey(int i, int new_val)
{
    if (i>-1 && i<heap_size)
    {
        harr[i]=new_val;
        //since new value is smaller, ooper order sahi hona like in increase:
        while (i>-1 && harr[i]< harr[parent(i)]) //added at tu fix ooper ka order
        {
         
            int q= harr[i];
            harr[i]=harr[parent(i)];
            harr[parent(i)]=q;
            i=parent(i);
        }

    }
}
 
int MinHeap::getMin()
{
    return harr[0];
}
 
void MinHeap::deleteKey(int i)
{

    if (i>-1 && i<heap_size && harr[i] && heap_size>0){   

    decreaseKey(i, -10000000);
    extractMin(); //check if sahi nikaal rahi


    }
}
 
void MinHeap::insertKey(int k)
{
    //cout<<"Inserting: "<<k<<endl;
    heap_size++;
    if (heap_size<=capacity)
    {
        harr[heap_size-1]=k;
        //ooper jao to fix order
        int i=heap_size-1;
        while (i>-1 && harr[i]< harr[parent(i)]) //added at tu fix ooper ka order
        {
         
            int q= harr[i];
            harr[i]=harr[parent(i)];
            harr[parent(i)]=q;
            i=parent(i);
        }

    }
    else
    {
        heap_size--;
        cout<<"Maximum capacity reached. Can't insert"<<endl;
    }
}

int* MinHeap::getHeap()
{
	return harr;
}

#endif