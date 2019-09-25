#ifndef DOUBLEHASH_CPP
#define DOUBLEHASH_CPP
#include "doubleHash.h"
#include "hashfunctions.cpp"
HashD::HashD(){
    tableSize = 10000; // you cant change this
    count=0;
    hashTable=new block*[tableSize];
    for (int i=0; i<tableSize; i++)
    {
        hashTable[i]= NULL;//new block(-1,""); //initially saare khaali 
    }

}

HashD::~HashD()
{
    delete [] hashTable;
    hashTable=NULL;
}

void HashD::resizeTable(){
    tableSize=7*tableSize;
    block** temp=hashTable; //store old hashtable in temp
    hashTable=new block*[tableSize];
    for (int i=0; i<tableSize; i++)
    {
            hashTable[i]= NULL; //initially saare khaali 
    }//empty original
    count=0;
    for (int i=0; i<tableSize/7; i++)
    {
        if (temp[i]!=NULL && temp[i]->key != -2)
        {
           //cout<<"Inside resize"<<endl;
            insert(temp[i]->value); //rehash ho kar actual mai dall gaya
            // hashTabe[i]=new block(HashL(hashTable[i]->value),hashTable[i]->value) //collision case
        }

    }
    delete [] temp;
    temp=NULL;

}
unsigned long HashD::hash1(string value)
{
    return divCompression(bitHash(value), tableSize);//BitDiv(value,tableSize);
}

unsigned long HashD::hash2(string value)
{
    return madCompression(bitHash(value), tableSize);//BitMad(value,tableSize);
}

void HashD::insert(string value){
    //cout<<"Inserting "<<value<<endl;
    if (count>=tableSize/3)
    {
        //cout<<"resizing, table size is "<<tableSize<<endl;
        resizeTable();
        //cout<<"outside resize: Tablesize after resizing:"<<tableSize<<endl;
    }
    unsigned long key=hash1(value);
    unsigned long index=key%tableSize;
    int i=1;
    while (hashTable[index]!=NULL && hashTable[index]->key != -2)
    {
        index=(hash1(value)+i*(hash2(value)))%tableSize;
        i++;
    }
    count++;
    hashTable[index]=new block(key,value);

  
}

void HashD::deleteWord(string value){
    block* temp=lookup(value);
    if (temp){
        temp->key=-2;
        temp->value="";
    }
}

block* HashD::lookup(string value){
    unsigned long key=hash1(value);
    unsigned long index=key%tableSize;
    int i=0;
    while (hashTable[index]!=NULL && hashTable[index]->value!=value)
    {
        index=(hash1(value)+i*(hash2(value)))%tableSize;
        i++;
    }
    return hashTable[index];
}

#endif