#ifndef CHAINING_CPP
#define CHAINING_CPP
#include "Chaining.h"
#include "hashfunctions.cpp"
#include "iostream"
using namespace std;

HashC::HashC(int size){
    //cout<<"constructor"<<endl;
    tableSize=size;
    hashTable=new LinkedList<string>[size];
    // cout<<"Size of hastable: "<<sizeof(list)/sizeof(hashTable[0])<<endl;
}
HashC::~HashC(){
    for(int i=0; i<tableSize; i++)
    {
        hashTable[i].~LinkedList();
    }
    delete [] hashTable;
    hashTable=NULL;
}

unsigned long HashC :: hash(string input)
{
    // cout<<"hash"<<endl;
    int c=3;
    // cout<<"Choose one of the four hashfunctions: \nPress 1 for Polynomial hash with division compression. \nPress 2 for Polynomial hash with mad compression. \nPress 3 for Bitwise hash with division compression. \nPress 4 for Bitwise hash with mad compression. \n";
    // cin>>c;
    // while (c<1 || c>4)
    // {
    //     cout<<"Invalid entry. Press a number from 1-4."<<endl;
    //     cin>>c;
    // }
    if (c==1)
    {
        return PolyDiv(input, tableSize);
    }
    else if(c==2)
    {
        return PolyMad(input, tableSize);
    }
    else if(c==3)
    {
        return BitDiv(input, tableSize);
    }
    else if (c==4)
    {
        return BitMad(input, tableSize);
    }

 
}

void HashC::insert(string word)
{
    // cout<<"insert"<<endl;
    //cout<<"word ka hash: "<<hash(word)<<endl;
    long x=hash(word);
    //cout<<"Word: "<<word<<endl;
    //cout<<"Hash word: "<<x<<endl;
    LinkedList <string> f= hashTable[x];
    // cout<<"Indexing done"<<endl;
    // try
    // {
    //     hashTable[x].insertAtHead(word);
    // }
    // catch(std::bad_alloc)
    // {
    //     cout<<"bad alloc error"<<endl;
    // }
    //hashTable[hash(word)].insertAtHead(word);
    // cout<<"Insert done"<<endl;
} 

ListItem<string>* HashC :: lookup(string word)
{
    return hashTable[hash(word)].searchFor(word);
}

void HashC :: deleteWord(string word)
{
    hashTable[hash(word)].deleteElement(word);
}
#endif