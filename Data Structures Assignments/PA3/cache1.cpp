/*Cache not used in this file */
#include "hashfunctions.cpp"
#include <string>
#include <iostream>
#include <vector>
#include "fstream"
#include "map"
#include <time.h>
#include <thread>
#include <chrono>
#include <future>
#include "cstdio"
#include "ctime"
using namespace std;
class block{
    public:
        string key;
        string value;
        int accessed;
        block(string _key,string _value){
            this->key = _key;
            this->value = _value;
            this->accessed=1;
        }
        block(string _key,string _value, int _accessed){
            this->key = _key;
            this->value = _value;
            this->accessed=_accessed;
        }
};


class HashL
{
    private:
        block** hashTable;
        long tableSize;
        unsigned long hash(string value)
        {
            return divCompression(bitHash(value), tableSize);
        } // return the corresponding key of the value
        long count; // keeps a count of the number of entries in the table.
        //void resizeTable();
    public:
        HashL()
        {
            tableSize = 1000; // you cant change this
            count=0;
            hashTable=new block*[tableSize];
            for (int i=0; i<tableSize; i++)
            {
                hashTable[i]= NULL;//new block(-1,""); //initially saare khaali 
            }
        }
        ~HashL()
        {
            delete [] hashTable;
            hashTable=NULL;
        }
        void deleteWord(string key)
        {
            block* temp=lookup(key);
            if (temp){
                //cout<<"Deleting "<<temp->value<<endl;
                temp->key="-2";
                temp->value="";
                count--;
            }
        }
        void insert(string key, string value)
        {
            int i=0;

            //cout<<count<<endl;
            while (count==tableSize-1)//if accessed 1 time only tu replace, if first 7 mai na mila koi aisa tu just replace the first index wala to reduce time complexity
            {
                //cout<<"i: "<<i<<endl;
                block* x=hashTable[i];
                if (x->accessed<2)
                {
                    hashTable[i]->accessed=1;
                    hashTable[i]->key=key;
                    hashTable[i]->value=value;
                    return;

                }
                else
                {
                    i++;
                }
                if (i>7)
                {
                    hashTable[0]->accessed=1;
                    hashTable[0]->key=key;
                    hashTable[0]->value=value;
                    return;
                }


            }
            unsigned long index=hash(key);
            //unsigned long index=key;
            while (hashTable[index]!=NULL && hashTable[index]->key != "-2")
            {
                index=(index+1)%tableSize;
            }
            count++;
            hashTable[index]=new block(key,value); //(key secret say aur dict say value)
        }
        block* lookup(string key)
        {
            unsigned long index=hash(key);
            //unsigned long index=key;
            while (hashTable[index]!=NULL && hashTable[index]->key!=key)
            {
                index=(index+1)%tableSize;
            }
            if (hashTable[index])
            {
                hashTable[index]->accessed=(hashTable[index]->accessed)+1;
            }
            return hashTable[index];
        }
};

int main()
{
    HashL cache;
    cout<<"Deciphering message with cache "<<endl;
    std::clock_t start;
    double duration;
    start=std::clock();
    string temp1;
    ifstream file1;
    file1.open("secret1.txt");
    ifstream file;
//    cout << "Loading Dictionary" << endl;
    string temp;
    string temp2;
   // cout << "Loading Secret" << endl;
    int length;
    int x=0;
    while(!file1.eof())
    {

        file1 >> temp1;
        length=temp1.length();
        if(temp1.substr(length-1,1)==",")
            temp1=temp1.substr(0,length-1);
        block* t=cache.lookup(temp1);
        if (t)//found in cache
        {
            cout<<t->value<<endl;
           // cout<<"Accessed "<< t->accessed<<" times"<<endl;
        }
        else
        {
            file.open("dictionary.txt");    
            while(!file.eof())
            {
                file >> temp >> temp2;
                if (temp==temp1)
                {
                 //   cout<<"before insert"<<endl;
                    cache.insert(temp, temp2);
                    cout<<temp2<<endl;
                }
            }
            file.close();
        }


        x++;
        if (x==200) //kitne words karne 
        {
            break;
        }

    }
    file1.close();
    duration=(std::clock()-start)/(double) CLOCKS_PER_SEC;
    cout<<"Time taken using cache : "<<duration<<endl;


}
