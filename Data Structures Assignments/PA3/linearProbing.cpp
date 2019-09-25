#ifndef LINEARPROBING_CPP
#define LINEARPROBING_CPP
#include "linearProbing.h"
#include "hashfunctions.cpp"
//quadratic probing bhi karna

HashL::HashL(){
    tableSize = 1000; // you cant change this
    count=0;
    hashTable=new block*[tableSize];
    for (int i=0; i<tableSize; i++)
    {
            hashTable[i]= NULL;//new block(-1,""); //initially saare khaali 
    }
}

HashL::~HashL(){
   // cout<<"Destructor"<<endl;
    // for(int i=0; i<tableSize; i++)
    // {
    //     delete[] hashTable[i];
    // }
    delete [] hashTable;
    hashTable=NULL;

}

unsigned long HashL :: hash(string value){
    return divCompression(bitHash(value), tableSize);


    //     // cout<<"hash"<<endl;
    // int c=3;
    // // cout<<"Choose one of the four hashfunctions: \nPress 1 for Polynomial hash with division compression. \nPress 2 for Polynomial hash with mad compression. \nPress 3 for Bitwise hash with division compression. \nPress 4 for Bitwise hash with mad compression. \n";
    // // cin>>c;
    // // while (c<1 || c>4)
    // // {
    // //     cout<<"Invalid entry. Press a number from 1-4."<<endl;
    // //     cin>>c;
    // // }
    // if (c==1)
    // {
    //     return PolyDiv(value, tableSize);
    // }
    // else if(c==2)
    // {
    //     return PolyMad(value, tableSize);
    // }
    // else if(c==3)
    // {
    //     return BitDiv(value, tableSize);
    // }
    // else if (c==4)
    // {
    //     return BitMad(value, tableSize);
    // }
}

void HashL::resizeTable(){
    tableSize=2*tableSize;
    // cout<<"TABLE SIZE :  _____________________________"<<tableSize;
    block** temp=hashTable; //store old hashtable in temp
    hashTable=new block*[tableSize];
    for (int i=0; i<tableSize; i++)
    {
            hashTable[i]= NULL; //initially saare khaali 
    }//empty original
    count=0;
    for (int i=0; i<tableSize/2; i++)
    {
        if (temp[i]!=NULL && temp[i]->key != -2)
        {
      //      cout<<"Inside resize"<<endl;
            insert(temp[i]->value); //rehash ho kar actual mai dall gaya
            // hashTabe[i]=new block(HashL(hashTable[i]->value),hashTable[i]->value) //collision case
        }

    }
    delete [] temp;
    temp=NULL;
}

void HashL::insert(string value){
    if (count>=tableSize/2)
    {
        //cout<<"resizing, table size is "<<tableSize<<endl;
        resizeTable();
        //cout<<"outside resize: Tablesize after resizing:"<<tableSize<<endl;
    }
    unsigned long key=hash(value);
    unsigned long index=key;
    while (hashTable[index]!=NULL && hashTable[index]->key != -2)
    {
        index=(index+1)%tableSize;
    }
    count++;
    hashTable[index]=new block(key,value);
    // hashTable[index]->value=value;
    //cout<<"Count is now: "<<count<<endl;
    //cout<<"TS is: "<<tableSize<<endl;
}

void HashL::deleteWord(string value){//key ko -2 aur value ko empty
    block* temp=lookup(value);
    if (temp){
        temp->key=-2;
        temp->value="";
        count--;
    }
}
block* HashL::lookup(string value){//stop if -1 in cluster, if -2 tu chalta rahe
    unsigned long key=hash(value);
    unsigned long index=key;
    while (hashTable[index]!=NULL && hashTable[index]->value!=value)
    {
        index=(index+1)%tableSize;
    }
    return hashTable[index];
}
#endif
