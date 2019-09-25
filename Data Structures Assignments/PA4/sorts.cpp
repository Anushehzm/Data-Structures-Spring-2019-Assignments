#ifndef __SORTS_CPP
#define __SORTS_CPP
#include "sorts.h"
#include "heap.cpp"
#include "heap.h"
#include "iostream"
#include "vector"
#include "list.cpp"
#include "list.h"
#include "ctime"
#include "cstdlib"
#include <algorithm>
#include <cmath>
using namespace std;
//=====================================================================================
vector<long> InsertionSort(vector<long> nums)
{
    //copying into an array
    int* arr= new int[nums.size()];
    for (int x=0; x<nums.size(); x++)
    {
        arr[x]=nums.at(x);
    }

     for (int i=1; i<nums.size(); i++)
    {
        int temp=arr[i]; //to add later
        int j=i-1;
     //   cout<<"j: "<<j<<endl;
        while(j>-1 && temp<arr[j])//find i ki location in sorted list---keep shifting j aagay
        {
            arr[j+1]=arr[j];
            j=j-1;
            // for (int o=0; o<nums.size(); o++)
            // {
            //     cout<<arr[o]<<" ";
            // }
            // cout<<endl;
        }
        arr[j+1]=temp;
    }


    for (int y=0; y<nums.size(); y++)
    {
        //cout<<arr[y]<<" ";
        nums.at(y)=arr[y];
    }
    return nums;
}

vector <long> merge (vector <long> Q1, vector <long> Q2)
{
    List<long> q1;
    List<long> q2;

    for (int i= Q1.size()-1; i>-1; i--)
        q1.insertAtHead(Q1.at(i));

    for (int y=Q2.size()-1; y>-1; y--)
        q2.insertAtHead(Q2.at(y));


    // cout<<"q1: "<<endl;
    // q1.display_list();
    // cout<<"q2   "<<endl;
    // q2.display_list();
    vector <long int> nums(q1.length() + q2.length());
    List<long> merged;
    ListItem<long int>* h1= q1.getHead();
    ListItem<long int>* h2= q2.getHead();

    while(h1!=NULL && h2!=NULL)
    {
        int a=h1->value;
        int b=h2->value;
       
        if (a<b)
        {
            merged.insertAtTail(a);
            h1=h1->next;
            //q1.deleteHead();
        }
        else
        {
            merged.insertAtTail(b);
            h2=h2->next;
            //q2.deleteHead();

        }
    
    }
    while (h1!=NULL)
    {
        merged.insertAtTail(h1->value);
        h1=h1->next;
        //q1.deleteHead();
    }
    while (h2!=NULL)
    {
        merged.insertAtTail(h2->value);
        h2=h2->next;
        //q2.deleteHead();
    }
    // cout<<"merged final: "<<endl;
    // merged.display_list();
    ListItem<long int>* head2= merged.getHead();

    for (int q=0; q<nums.size(); q++)
    {
        nums.at(q)=head2->value;
        head2=head2->next;
    }
    return nums;

}    

//=====================================================================================
vector<long> MergeSort(vector<long> nums)
{
    //use two queues as halves then merge
    if(nums.size()>1){
        List<long int> first; 
        List<long int> second;
        //ismai daalo sab

        // for (int o=0; o<nums.size(); o++)
        // {
        //     first.insertAtTail(nums.at(o));
        // }

        for (int o=nums.size()-1; o>-1; o--)
        {
            first.insertAtHead(nums.at(o));
        }
        //split into two
        ListItem<long int>* head2= first.getHead();

        int length=first.length();
        int mid_index=nums.size()/2; //5

        if (length%2==0) //even eg 10
        {

            for (int i=0; i< mid_index; i++)// 5 jumps so lands on 6th node
            {
                head2=head2->next;
            }

        }
        else//odd case
        {
            for (int i=0; i<(mid_index+1); i++) //0-5
            {
                head2=head2->next;
            }
        }
        //break link
        head2->prev->next=NULL;
        head2->prev=NULL;
        //fill in right---try if head of right could just point to head2
        while(head2!=NULL)
        {
            second.insertAtTail(head2->value);
            head2=head2->next;
        }

            // convert back to vectors to pass to merge
        vector <long int> left;
        vector <long int> right;
        int length1=first.length();
        int length2=second.length(); 
        ListItem<long int>* head3= first.getHead();
        ListItem<long int>* head4= second.getHead();
        for (int i=0; i<length1; i++)
        {
            
            left.push_back(head3->value);
            head3=head3->next;
            //first.deleteHead();
        }
        for (int i=0; i<length2; i++)
        {
            right.push_back(head4->value);
            head4=head4->next;
            //second.deleteHead();
        }

       return merge(MergeSort(left), MergeSort(right));  //FIX --copy merged back to vector
    }
 
    else
    {
        return nums;
    }
}

// List <long> merge (List <long> q1, List <long> q2)
// {

//     vector <long int> nums(q1.length() + q2.length());
//     List<long> merged;
//     while(q1.length()>0 && q2.length()>0)
//     {
//         int a=q1.getHead()->value;
//         int b=q2.getHead()->value;
//         if (a<b)
//         {
//             merged.insertAtTail(a);
//              q1.deleteHead();
//         }
//         else
//         {
//             merged.insertAtTail(b);
//             q2.deleteHead();

//         }
    
//     }
//     while (q1.length()!=0)
//     {
//         merged.insertAtTail(q1.getHead()->value);
//         q1.deleteHead();
//     }
//     while (q2.length()!=0)
//     {
//         merged.insertAtTail(q2.getHead()->value);
//         q2.deleteHead();
//     }
//     cout<<"merged final: "<<endl;
//     merged.display_list();

//     return merged;

// } 


// List<long int > mergelist(List<long int > first)
// {

//     if (first.length()>1)
//     {
//         ListItem<long int>* head2= first.getHead();
//         List<long int> second; 

//         int length=first.length();
//         int mid_index=length/2; //5

//         if (length%2==0) //even eg 10
//         {

//             for (int i=0; i< mid_index; i++)// 5 jumps so lands on 6th node
//             {
//                 head2=head2->next;
//             }

//         }
//         else//odd case
//         {
//             for (int i=0; i<(mid_index+1); i++) //0-5
//             {
//                 head2=head2->next;
//             }
//         }
//         //break link
//         head2->prev->next=NULL;
//         head2->prev=NULL;
//         //fill in right---try if head of right could just point to head2
//         while(head2!=NULL)
//         {
//             second.insertAtTail(head2->value);
//             head2=head2->next;
//         }

//         return merge(mergelist(first), mergelist(second));
//     }
//     else
//     {

//         return first;
//     }

// }   

// //=====================================================================================
// vector<long> MergeSort(vector<long> nums)
// {
    // //cout<<"MergeSort"<<endl;
    // //use two queues as halves then merge
    //     List<long int> first; 
    //     //ismai daalo sab

    //     for (int o=0; o<nums.size(); o++)
    //     {
    //         first.insertAtTail(nums.at(o));
    //     }
    //     //split into two
    //     List<long int> second=mergelist(first);
    //     for (int i=0; i< second.length(); i++)
    //     {
    //         nums.at(i)=second.getHead()->value;
    //         second.deleteHead();
    //     }

    //     return nums; 
// }


long int pivot_median(long int arr[], int size)
{
    // cout<<"size in helper: "<<size<<std::flush<<endl;
    if (size>0)
    {
        int first=rand()%size;
        int second=rand()%size;
        // while(second==first)
        // {
        //     second=rand()%size;
        // }
        int third=rand()%size;
        // while(third==second || third==first)
        // {
        //     third=rand()%size;
        // }
        // cout<<"first index: "<<first<<"   second index: "<<second<<"   third index: "<<third<<endl;
        // cout<<"first val: "<<arr[first]<<"   second val: "<<arr[second]<<"   third val: "<<arr[third]<<endl;
        if(arr[first]>arr[third])
        {
            int x=first;
            first=third;
            third=x;
        }
        if(arr[first]>arr[second])
        {
            int x=first;
            first=second;
            second=x;
        }
        if(arr[second]>arr[third])
        {
            int x=third;
            third=second;
            second=x;
        }
        // cout<<"pivot index: "<<second<<std::flush<<endl;
        return second;
        // if ((a[first]<a[second] && a[first]>a[third]) || (a[first]>a[second] && a[first]<a[third]) || a[first]==a[second] || a[first]==a[third])
        // {
        //   //  cout<<"first"<<endl;
        //     return first;
        // }
        // if ((a[third]<a[second] && a[first]<a[third]) || (a[third]>a[second] && a[first]>a[third]) || a[third]==a[second])
        // {
        //     //cout<<"third"<<endl;
        //     return third;
        // }
        // if ((a[first]<a[second] && a[second]<a[third]) || (a[first]>a[second] &&a[second]>a[third]))
        // {
        //     //cout<<"second"<<endl;
        //     return second;
        // }

    }
    else
    {
        cout<<"Empty list passed"<<endl;
        return 0;
    }

}

long int* QSA (long int arr[], int start, int end)
{
    int size=end-start+1;
    // cout<<"start: "<<start<<endl;
    // cout<<"end "<<end<<endl;
    if (start<0)
    {
        return 0;
    }
    if(size>1)
    {
        int i=arr[start]; //low
        int j=arr[end]; //high
        int pivot_index;
        int c=1;
        int long pivot;
        if (c==1)
        {
            //first
            pivot_index=start;
            pivot=i;
        }
        else if(c==2)
        {
            //median
            pivot_index=pivot_median(arr, size);
            pivot=arr[pivot_index];
        }
        else if (c==3)
        {
            pivot_index=end;
            //last
            pivot=j;
        }
        //cout<<"Pivot: "<<pivot<<endl;
       // swap pivot with last element in list
        long int x=arr[pivot_index];
        arr[pivot_index]=j;
        arr[end]=x;
        int y=start-1;
        for (int l=start; l<end; l++)
        {
            if (arr[l]<=pivot)
            {
                y++;
                x=arr[y];
                arr[y]=arr[l];
                arr[l]=x;
            }
        }
        //pivot position wapis
        x=arr[y+1];
        arr[y+1]=arr[end];
        arr[end]=x;
        //two arrays should be made at this point
        // for (int u =0; u<size; u++)
        // {
        //     cout<<arr[u]<<" ";
        // }
        // cout<<endl;
        // //long int* fin= new long int[end+1]; 1,2 piv=y+1     y
        // cout<<"left:" <<endl;
        //         //two arrays should be made at this point
        // for (int u =start; u<y+1; u++)
        // {
        //     cout<<arr[u]<<" ";
        // }
        // cout<<endl;

        // cout<<"right:"<<endl;
        //         //two arrays should be made at this point
        // for (int u =y+2; u<size; u++)
        // {
        //     cout<<arr[u]<<" ";
        // }
        // cout<<endl;
        // cout<<"left recur"<<endl;
        QSA(arr,start, y);
        //cout<<"right recur"<<endl;
        QSA(arr, y+2,end); /////edge casesfkancnasln
        return arr;
    }
    else
    {
        // cout<<"size: "<<size<<endl;
        // cout<<"base case "<<endl;
        return arr;
    }
}
//=====================================================================================
vector<long> QuickSortArray(vector<long> nums)
{
       // cout<<"ssss"<<std::flush<<endl;
        //long int* arr= new long int[nums.size()];
        // for (int x=0; x<nums.size(); x++)
        // {
        //     arr[x]=nums.at(x);
        // }
        //long int* arr2= new long int[nums.size()];
        QSA(nums.data(), 0, nums.size()-1);
        // cout<<"final: "<<std::flush<<endl;
        // for (int x=0; x<nums.size(); x++)
        // {
        //     cout<<nums.data()[x]<<" ";
        // }
        // cout<<endl;
        // for (int x=0; x<nums.size(); x++)
        // {
        //     nums.at(x)=arr[x];
        // }
        return nums;

}
void quicklist(List <long int >* list, ListItem<long int >* h, ListItem<long int >* t)
{

    //taking random node as pivot
    if (h!=NULL && t!=h)
    {
        // cout<<"head   "<<h->value<<endl;
        // cout<<"tail   "<<t->value<<endl;
        ListItem<long int> *temp;
        int len=1;
        temp = h;
        while (temp != t)
        {
                temp = temp->next;
                len++;
        }
        // cout<<"length of LL: "<<len<<endl;
        // int pivot_node=rand()%len;
        ListItem<long int>* traverse=t;//---tail as pivot for optimized performancw
        // for (int i=0; i<pivot_node-1; i++)
        // {
        //     traverse=traverse->next;
        // }
        long int pivot=traverse->value;
        // cout<<"pivot node: "<<pivot_node<<endl;
        // cout<<"value at pivot: "<<pivot<<endl;
        // ListItem<long int>* last=t;//list.getTail();
        
        //swap:
        long int p=traverse->value; 
        // traverse->value=t->value;
        // t->value=p;

        // cout<<"After swap: "<<endl;
        // ListItem<long int> *temp2;
        // temp2 = h;
        // while (temp2 != t)
        // {
        //     cout<< temp2->value <<" ";
        //     temp2 = temp2->next;
        // }
        // cout<<temp2->value<<" ";
        // cout<<endl;
        ListItem<long int>* i=h;//list.getHead();
        ListItem<long int>* j=h;//list.getHead();
        // cout<<"J vale "<<j->value<<"    i val "<<i->value<<endl;
        for (int l=0; l<len-1; l++)
        {
            if (j->value<=pivot)
            {
                if(j->value!=i->value)
                {
                    p=j->value;
                    j->value=i->value;
                    i->value=p;
                }
                i=i->next;
            }
            j=j->next;
        // cout<<"J vale "<<j->value<<"    i val "<<i->value<<endl;

        }


        //pivot position wapis
        traverse=t;//list.getTail();
        p=traverse->value;
        traverse->value=i->value;
        i->value=p;
        // cout<<"Displaying list after partition: "<<endl;
        // temp2 = h;
        // while (temp2 != t)
        // {
        //     cout<< temp2->value <<" ";
        //     temp2 = temp2->next;
        // }
        // cout<< temp2->value <<" ";

        // cout<<endl;
        
        // cout<<"head2   "<<h->value<<endl;
        // cout<<"tail2  "<<t->value<<endl;
        // //recursion karni 
        // if(i->prev)
        //     cout<<"Value before pivot: "<<i->prev->value<<endl;
        // else
        //     cout<<"no value before pivot"<<endl;
        // if(i->next)
        //     cout<<"Value after pivot: "<<i->next->value<<endl;
        // else
        //     cout<<"no value after pivot"<<endl;
        // cout<<"left: "<<endl;
        if(i!=h)
            quicklist(list,h, i->prev);
        // cout<<"right: "<<endl;
        if(i!=t)
            quicklist(list, i->next ,t);
    }
    // else
    // {
    //     cout<<"base case"<<endl;
    // }
}
//=====================================================================================
vector<long> QuickSortList(vector<long> nums)
{
    //cout<<"QuickSort"<<endl;
//use two queues as halves then merge
    List<long int>* list=new List<long int>; 
    //ismai daalo sab

    for (int o=nums.size()-1; o>-1; o--)
    {
        list->insertAtHead(nums.at(o));
    }
    // cout<<"Displating initial list: "<<endl;
    // list.display_list();
    //split into two

    quicklist(list, list->getHead(), list->getTail());

    // cout<<"Final list: "<<endl;
    // list->display_list();
    ListItem <long int>*o=list->getHead();
    int x=list->length();
    for (int i=0; i< x; i++)
    {
        nums.at(i)=o->value;
        o=o->next;
        //////////list->deleteHead();
    }
    // cout<<"Final vector: "<<endl;
    // for (int i=0; i< x; i++)
    // {
    //     cout<<nums.at(i)<<" ";
    // }
    // cout<<endl;
    return nums;

}

//=====================================================================================
vector<long> HeapSort(vector<long> nums)
{

    MinHeap *heap=new MinHeap(nums.size());
    for (int i=0; i< nums.size(); i++)
    {
        heap->insertKey(nums.at(i));
    }
    for (int x=0; x< nums.size(); x++)
    {
        nums.at(x)=heap->extractMin();
    }
    return nums;


}

//=====================================================================================
/*The class mate's claims are incorrect because his algorithm does not deal with negative entries
 and the time complexity goes up by O(n) times each time he copies the array into a new one, time complexity
 will be O(n^2). To optimize performance, I used a method that did not require resizing but starts with an array 
 (or arrays if we have negative entries) with the size same as the initial unsorted list. Instead of adding values to the
 indices of thoses values, I've made buckets that can hold equal number of entries based on calculating the maximum and minimum values
 in the input list and dividing the max possible ranges on either side of 0 by the size of resulting lists. Duplicates are dealt with using
 the concept of chaining. Instead of using a linked list as we did in hash tables, I used a vector for chaining as it was easier to 
 sort using insertion sort then. By using two separate arrays for positive and negative values, it was easier to sort and later concatenate the chains
 into one sorted final array.*/
vector<long> QueenOfAllSorts(vector<long> nums)
{
    //max value in array for positive
    long int max=nums.data()[0];
    for (int i=0; i< nums.size(); i++)
    {
        if(nums.data()[i]>max)
        {
            max=nums.data()[i];
        }
    }
    //min value for neg
    long int min=nums.data()[0];//std::min(nums.data());
    for (int i=0; i< nums.size(); i++)
    {
        if(nums.data()[i]<min)
        {
            min=nums.data()[i];
        }
    }

    //cout<<"Min value: "<<min<<"   Max value: "<<max<<endl;
    //make bucket ranges---
    long int pos_range=ceil((double(max+1))/double(nums.size()));
    //cout<<"Values in each positive bucket: "<<pos_range<<endl;
    long int neg_range=ceil((double(abs(min)+1))/double(nums.size()));
    //cout<<"Values in each negative bucket: "<<neg_range<<endl;
    //array of vectors----if optimise karna hua tu try with LL and merge sort/quicksort
    //try using quicksort vector par array wala
    vector <long int>* arr1= new vector<long int>[nums.size()]; //iss array ko ulta chalana
    vector <long int>* arr2= new vector<long int>[nums.size()]; //isko seedha
    //vector <long int>* arr3= new vector<long int>[nums.size()];



    //fill--three arrays, aik negative, aik bigger than n values aur aik 0-size wali vals
    for(int i=0; i<nums.size(); i++)
    {
        if(nums.data()[i]<0)//neg nos
        {
            long int x= double(abs(nums.data()[i]))/double(neg_range); //floor khud hi?
  //          cout<<"For value "<<nums.data()[i]<<" index jo nikla of arr1: "<<x<<endl;
            arr1[x].push_back(nums.data()[i]);

        }
        else //positive
        {
            long int x= double(nums.data()[i])/double(pos_range); //floor khud hi?
//            cout<<"For value "<<nums.data()[i]<<" index jo nikla of arr2: "<<x<<endl;
            arr2[x].push_back(nums.data()[i]);
        }
    }

    //before sorting check:
    // cout<<"neg unsorted list: "<<endl;
    // for (int i=0; i<nums.size(); i++ )
    // {
    //     for (int j=0; j<arr1[i].size(); j++)
    //     {
    //         cout<<arr1[i].at(j)<<"  "<<endl;
    //     }
    // }
    // cout<<"pos unsorted list: "<<endl;
    // for (int i=0; i<nums.size(); i++ )
    // {
    //     for (int j=0; j<arr2[i].size(); j++)
    //     {
    //         cout<<arr2[i].at(j)<<"  "<<endl;
    //     }
    // }
    //sort buckets
    for (int i=0; i<nums.size();i++)
    {
        arr1[i]=InsertionSort(arr1[i]);
        arr2[i]=InsertionSort(arr2[i]);
    }


    // cout<<"neg sorted list: "<<endl;
    // for (int i=0; i<nums.size(); i++ )
    // {
    //     for (int j=0; j<arr1[i].size(); j++)
    //     {
    //         cout<<arr1[i].at(j)<<"  "<<endl;
    //     }
    // }
    // cout<<"pos sorted list: "<<endl;
    // for (int i=0; i<nums.size(); i++ )
    // {
    //     for (int j=0; j<arr2[i].size(); j++)
    //     {
    //         cout<<arr2[i].at(j)<<"  "<<endl;
    //     }
    // }

    // cout<<"nums pehle: "<<endl;
    // for (int i=0; i<nums.size(); i++ )
    // {
    //     cout<<nums.at(i)<<"  ";
        
    // }
    // cout<<endl;

    //concatenate---neg list ulta + pos list seedhi and put back in nums
    int y=0;
    for (int i=nums.size()-1; i>-1; i-- )
    {
        for (int j=arr1[i].size()-1; j>-1; j--)
        {
            nums.at(y)=arr1[i].at(j);
            y++;
        }
    }   
    for (int i=0; i<nums.size(); i++ )
    {
        for (int j=0; j<arr2[i].size(); j++)
        {
            nums.at(y)=arr2[i].at(j);
            y++;
        }
    } 

    //check nums:
    //cout<<"Final list: "<<endl;
    // for (int i=0; i<nums.size(); i++ )
    // {
    //     cout<<nums.at(i)<<"  ";
        
    // }
    // cout<<endl;
    return nums; //migght need to change
}
#endif

// int main()
// {
//     vector <long int> array(11);

//     array.at(0)=20;
//     array.at(1)=10;
//     array.at(2)=24;
//     array.at(3)=6;
//     array.at(4)=0;
//     array.at(5)=-1;
//     array.at(6)=-3;
//     array.at(7)=4;
//     array.at(8)=3;
//     array.at(9)=4;
//     array.at(10)=40;
//     cout<<"Initial vector: "<<endl;
//     for (int i =0; i<array.size(); i++)
//     {
//         cout<<array.at(i)<<" ";
//     }
//     cout<<endl;
//     array=MergeSort(array);
//     cout<<"Final vector: "<<endl;
//     for (int i =0; i<array.size(); i++)
//     {
//         cout<<array.at(i)<<" ";
//     }
//     cout<<endl;

//     return 0;
// }