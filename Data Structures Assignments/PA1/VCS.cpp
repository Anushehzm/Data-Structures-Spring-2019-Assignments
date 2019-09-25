#ifndef VCS_CPP
#define VCS_CPP
#include "fstream"
#include "iostream"
#include "LinkedList.cpp"
#include "LinkedList.h"
#include "VCS.h"
#include <string>
using namespace std;

/*Making use of two stacks for vcs as the FILO implementation facilitates the undo and redo functions such that the order of 
the original stack is maintained despite these operations. Had we used two queues instead, the order would have been messed up.*/
VCS::VCS(string fname)
{
	curr_size=0;
	filename=fname;
}

//destructor
VCS::~VCS()
{
}


//time to commit
void VCS::commit(string msg)
{
	string l;
	ifstream f (filename+".txt");
	ofstream n (filename+(to_string(curr_size)+".txt"));
	while (getline(f,l))
	{
		n<<l;
	}
	VCS_node a(msg, curr_size);
	container1.push(a);
	curr_size++;
	
}
//Prints the information (Associated message and version number) about all nodes
//on the VCS. For checking purposes, you may print information of last 5 commits
//only.
//print status of every version
void VCS::status()
{
	Stack<VCS_node> temp;
	cout<<"Status:"<<endl;
	int y=container1.length();
	for (int i=0; i<y; i++)
	{
	string m=(container1.top()).message;
	int t=(container1.top()).time_stamp;
	cout<<"Message: "<<m<<endl<<"Time: "<<t<<endl;
	temp.push(container1.pop());
	}
	for (int u=0; u<y;u++)
	{
		container1.push(temp.pop());
	}
}

// Undo method takes user to one version back without losing information of the
// current version. For example, if you had 3 versions v1, v2 and v3 in order and you
// were on v3 currently, the undo method will return you to v2 but it will not lose v3.
// Retrieve the version number from node, read the file content associated to that
// version number, write them to original file and return contents of that file in a
// string.

//goes one step back
string VCS::undo()
{
	if (!container1.isEmpty())
	{
	container2.push(container1.pop());
	int y=container1.top().time_stamp;
	//cout<<"NO: "<<y<<endl;
	ifstream x (filename+(to_string(y))+".txt");
	string l;
	ofstream f (filename+".txt");
	while (getline(x,l))
	{
	//	cout<<"LLLL: "<<l<<endl;
		f<<l;
	}
	f.close();
	ifstream o (filename+".txt");
	string d="";
	string h;
	while (getline(o,h))
	{
		//cout<<"DDD-------------------------:"<<d<<endl;
		d=d+h;
	}
	//cout<<"string: "<<d<<endl;
	return d;
	}

}

// Redo method takes user one step forward. Building on the example from
// previous paragraph, if you were on v2, calling redo will return v3 back without
// losing information of v2. Rest of the implementation will be like undo method.

//one step ahead
string VCS::redo()
{
	if (!container2.isEmpty())
	{
	container1.push(container2.pop());
	int y=container1.top().time_stamp;
	ifstream x (filename+(to_string(y))+".txt");
	string l;
	ofstream f (filename+".txt");
	while (getline(x,l))
	{
		f<<l;
	}
	f.close();
	ifstream o (filename+".txt");
	string d = "";
	while (getline(o,l))
	{
		d=d+l;
	}
	return d;
	}
}

// Revert method finds the version with time_stamp having value t_stamp and
// returns data stored in that version to user. While doing so it does not alter order in
// which nodes were already placed in VCS. For Example: if you had 5 versions v0, v1,
// v2, v3 and v4 and you were currently on v4, calling revert(2) will return you content
// of v2 and if you call undo from here you will be returned contents of v1. Similar to
// undo and redo, you will have to update original file according to version number as
// well.


//goes t_stamp step back or ahead
string VCS::revert(int t_stamp)
{
	if (t_stamp>-1 && t_stamp<(container1.length()+container2.length()))
	{
		int p=container1.top().time_stamp;
		if (t_stamp<=p)
		{
			while(t_stamp!=container1.top().time_stamp)
			{
				undo();
			}
		}
		else
		{
			while(t_stamp!=container1.top().time_stamp)
			{
				redo();
			}
		}
	
	ifstream x (filename+(to_string(t_stamp))+".txt");
	string l;
	ofstream f (filename+".txt");
	while (getline(x,l))
	{
		//cout<<l<<endl;
		f<<l;

	}
	f.close();
	ifstream o (filename+".txt");
	string d = "";
	string h;
	//cout<<"Check"<<endl;
	while (getline(o,h))
	{
		d=d+h;
	}
	//cout<<d<<endl;
	return d;
	}

}

#endif