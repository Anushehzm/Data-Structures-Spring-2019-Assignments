#ifndef GRAPH__H
#define GRAPH__H
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <string>
#include <vector>
#include <fstream>
#include <limits>
#include <set>
#include <algorithm>
#include <queue>
// You may include more libraries.

using namespace std;
class node;

class edge
{
	// You may add more variables and functions in this class
	public:
		node* Origin;
		node* Dest;
		float weight;	
        edge(node* Origin, node* Dest ,float weight=1) //constructor
        {
            this->Origin=Origin;
            this->Dest=Dest;
            this->weight=weight;
        }
        bool operator > (const edge& other)const
        {
            return weight > other.weight;
        }
};



class node
{
	// You may add more variables and functions in this class
	public:
        node* prev;
        int distance;
		int visit; // flag to check if the node has been already visited
		string name;
		vector<edge> edges; // edges connected to node
        node(string name, int visit=0) //constructor
        {
            this->name=name;
            this->visit=visit;
            this->prev=NULL;
        }
        // bool operator > (const node*& other)
        // {
        //     return this->distance > other->distance;
        // }
        // bool operator < (const node*& other)
        // {
        //     return this->distance < other->distance;
        // }
};

// class compare_E{ //for priority queue comparison
//     public:
//         bool operator()(const edge first, const edge second)
//         {
//             return (first->distance > second->distance);
//         }
// };


class compare{ //for priority queue comparison
    public:
        bool operator()(const node* first, const node* second)
        {
            return (first->distance > second->distance);
        }
};


class Graph
{
	public:
		vector<node*> Mst; // minimum spanning tree
		vector<node*> vertices;
		vector<edge> arcs;
		Graph(char* filename, bool isUnitLength);
		void display(node* temp);// displays the graph

		bool Reachable(string start, string dest);
		vector<node*> Prims();
		vector<node*> Kruskal(); //runs kruskal algorithm and returns the Minimum spanning tree
		vector<string> Dijkstra(string start, string dest, float &d);
};

#endif