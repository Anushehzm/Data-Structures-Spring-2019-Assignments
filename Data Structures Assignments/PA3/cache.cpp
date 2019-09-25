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



int main()
{
    cout<<"Deciphering message without cache "<<endl;
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
    //int x=0;
    while(!file1.eof())
    {

        file1 >> temp1;
        length=temp1.length();
        if(temp1.substr(length-1,1)==",")
            temp1=temp1.substr(0,length-1);
        file.open("dictionary.txt");
        while(!file.eof())
        {
            file >> temp >> temp2;
            if (temp==temp1)
            {
                cout<<temp2<<endl;
            }
        }
        //x++;
        file.close();

    }
    file1.close();
    duration=(std::clock()-start)/(double) CLOCKS_PER_SEC;
    cout<<"Time taken without using cache: "<<duration<<endl;


}
