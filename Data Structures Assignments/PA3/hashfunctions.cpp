#ifndef HASHFUNCTIONS_CPP
#define HASHFUNCTIONS_CPP
#include <string>
#include <iostream>
#include <cmath>

using namespace std;
// this takes in a string and returns a 64bit hash.
unsigned long polyHash(std::string value,int a=9){
    unsigned long k=value.length();
    unsigned long hash=0;
    char temp;
    for (int i=0; i<k; i++)
    {
        temp=value.at(i);
        unsigned long p=(temp);
        hash=hash+p*pow(a, k-1-i);
    }
    return hash;
}

//does some bitwise operation and generates a 64bit hash.
unsigned long bitHash(std::string value){
    unsigned long k=value.length();
    unsigned long hash=0;
    char temp;
    for (int i=0; i<k; i++)
    {
        temp=value.at(i);
        unsigned long p=(temp);
        hash ^= (hash << 5) + (hash >> 2) + p;
    }
    return hash;
}
// Size is the size of array maintained by the hashtable.
unsigned long divCompression(unsigned long hash,long size){
    if (size!=0)
        return hash%size;
    else{
        cout<<"Incorrect size entered"<<endl;
        return 0;
    }

}
// multiplication addition and division compression. 
unsigned long madCompression(unsigned long hash,long size,int m = 1993,int a = 1637){
    if (size==0)
    {
        cout<<"Incorrect size entered"<<endl;
        return 0;
    }
    else
    {
        return (m*hash + a)%size;
    }
}

unsigned long PolyDiv(string value,long size, int a=9)
{
    unsigned long f=divCompression(polyHash(value,a), size);
    //cout<<"hash complete"<<endl;
    return f;
}

unsigned long PolyMad(string value, long size, int a=9)
{
    unsigned long f=madCompression(polyHash(value,a), size);
    // cout<<"hash complete"<<endl;
    return f;
}

unsigned long BitDiv(string value, long size)
{
    unsigned long f= divCompression(bitHash(value), size);
    // cout<<"hash complete"<<endl;
    return f;

}

unsigned long BitMad(string value, long size)
{
    unsigned long f= madCompression(bitHash(value), size);
    // cout<<"hash complete"<<endl;
    return f;
}

#endif
// you may write your own program to test these functions.
// int main()
//{
//     cout<<"PolyHash test: "<<polyHash("cat", 9)<<endl;
//     cout<<"Bitwise Hash: "<<bitHash("cat")<<endl;
//     cout<<"Division compress after polyhash: "<<divCompression(polyHash("cat",9), 5)<<endl;
//     cout<<"Division compress after bithash: "<<divCompression(bitHash("cat"), 23)<<endl;
//     cout<<"Mad compress after polyhash: "<<madCompression(polyHash("cat",9), 5)<<endl;
//     cout<<"Mad compress after bithash: "<<madCompression(bitHash("cat"), 23)<<endl;
  //  return 0;
//}