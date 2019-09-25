#ifndef __TREE_CPP
#define __TREE_CPP
#include "tree.h"
#include "string"
#include "iostream"
#include "queue.h"
#include "cmath"
using namespace std;

Tree::Tree(string data)
{
	TreeItem* new_node= new TreeItem();
	new_node->id = 1;
	new_node->latest_data=data;
	//cout<<"SIZE:"<<new_node->child.size()<<endl;
	//new_node->child.push_back(NULL); //this line might be unneeded
	//cout<<"SIZE:"<<new_node->child.size()<<endl;
	new_node->container.push_back(VCS_node(data,0));
	root=new_node;
}

Tree::~Tree()
{
	Queue<TreeItem*> b; 
	TreeItem* traverse= root;
	while (traverse!=NULL)
	{
		
		for (int i=0; i< traverse->child.size(); i++)
		{
			b.enqueue(traverse->child[i]);
		}
		//cout<<"deleting::: ID: "<<traverse->id<<"     latest data: "<<traverse->latest_data<<endl;

		if (b.isEmpty())
			return;
		delete traverse;
		traverse=b.dequeue();
	}	
}
/*void branch (int id):
○ This function is the core of this VCS implementation. When a branch is
called on a given node, you need to create a child node with an
appropriate ID. The child branch will have the same data as the latest
version of the parent node.*/
void Tree::branch(int id)
{	
	TreeItem* new_node= new TreeItem();
	TreeItem* nod=get_node(id); //found node jis par branch karna
	if(nod!=NULL)
	{
		if (id==12)
		{
			// cout<<"12 wala masla.....nod kay child ka size: "<<nod->child.size()<<endl;
		}
		int new_id=id*10 + nod->child.size()+1; //parent node kay id mai aik digit add kiya
		
		new_node->id=new_id;
		new_node->latest_data=nod->latest_data;
		new_node->container.push_back(VCS_node(new_node->latest_data,0));
		nod->child.push_back(new_node); //child pointer mai new node daal diya
	}
}
/*When a merge is called from a source node to a destination node, all the
data from the latest version of source node is appended back to data of
the latest version destination node. Don’t add any spaces between the
two strings while concatenation. Use the following convention for
appending data:
○ dst_data = dst_data + src_data*/
// struct merge_state{
// 	int src_id;
// 	int dst_id;
// };
void Tree::merge(int src_id,int dst_id)
{
	TreeItem* src=get_node(src_id);
	TreeItem* dst=get_node(dst_id);
	if (src && dst){
		dst->latest_data=(dst->latest_data)+(src->latest_data);
		VCS_node b(dst->latest_data, (dst->container.size()-1));
		dst->container.at((dst->container.size()-1))=b;
		merge_state a;
		a.src_id=src_id;
		a.dst_id=dst_id;
		history.push_back(a);
	}
}
/*void commit (int id, string new data):
○ As implemented in PA-1 as well, when a commit is called on a given id,
you have to store a new version of the file with the addition of the
new_data that comes with the commit in the container along with its
corresponding time_stamp and update the latest_data item in Tree node*/
void Tree::commit(int src_id,string new_data)
{
	//timestamp index hai tu last element will be size-1 of container
	TreeItem* src=get_node(src_id);
	if (src){
		int time_stamp=(src->container.size());//latest timestamp
		src->latest_data=src->latest_data+new_data;
		src->container.push_back(VCS_node(src->latest_data,time_stamp));
	}
}

string Tree::get_file(int id, int t_stamp)
{
	
	if (get_node(id)==NULL)
	{
		return "";
	}
	TreeItem* a=get_node(id);
	//time stamp is index
	if (a){
		for (int i=0; i<a->container.size(); i++)
		{
			if(a->container.at(i).time_stamp==t_stamp)
			{
				return a->container.at(i).data;
			}
		}
	}
	return "";
} 

int relevantBits(int id, int size) {
	int power = to_string(id).length() - size;
	if (power <= 0) return id;
	return id/int (pow(10,power));
}

TreeItem* Tree::get_node(int id)
{
	//cout << ".";
	TreeItem* traverse = root;
	//traverse tree and get node
	//cout<<3<<endl;
	string ID= to_string(id);
	int lengthofID = ID.length();
	for(int i=1; i<lengthofID+1; i++)
	{
		if (traverse==NULL)
		{
			return NULL;
		}
		if (traverse->id == id)
		{
			if (id==12)
			{
				// cout<<"12 in get_node issue:::: traverse kay bachoun ka size "<<traverse->child.size()<<endl;
			}
			return traverse;
		}

		int relevant_bits = relevantBits(id, i+1);
		vector <TreeItem*> child = traverse->child;
		bool a=false;
		for(int o=0; o<child.size(); o++)//idhar masle----id 111 mai
		{
			//cout<<traverse->id<<endl;
			int ID2 = relevantBits(child[o]->id, i+1);

			//cout<<"ID: "<<id2<<endl;
			//cout<<str<<endl;
			if (relevant_bits==ID2)
			{
				a = true;
//				cout<<"second if "<<endl;
				traverse=child[o];
				break;
			}
		}
		if (a==false)
		{
			return NULL;
		}
	}
	//cout<<"Returning value other than root"<<endl;
	return traverse;
} 

vector<merge_state> Tree::merge_history()
{
	return history;
}
/*Performs and displays the level order traversal of the tree. Prints out the
(id, latest_data) pair of each node.*/
//template <class T>
void Tree::level_traversal() 
{
	Queue<TreeItem*> b; 
	TreeItem* traverse= root;
	while (traverse!=NULL)
	{
		cout<<"ID: "<<traverse->id<<"     latest data: "<<traverse->latest_data<<endl;
		for (int i=0; i< traverse->child.size(); i++)
		{
			b.enqueue(traverse->child[i]);
		}
		if (b.isEmpty())
			return;
		
		traverse=b.dequeue();
	}
}

#endif