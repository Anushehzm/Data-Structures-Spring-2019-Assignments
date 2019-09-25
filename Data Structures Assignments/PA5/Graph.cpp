#ifndef GRAPH__CPP
#define GRAPH__CPP
#include "Graph.h"
#include "iostream"
#include "string"
#include <queue>
#include "fstream"
#include "stack"
using namespace std;


Graph::Graph(char* file, bool isUnitLength=false)
{
    bool people=true;
    string line;
    ifstream f;
    f.open(file);
    int count=0;
    string src="";
    string dest="";
    int weight=1;
    while (!f.eof())
    {
        f>>line;
        if (line=="CONNECTIONS")
        {
            people=false;
        }
        if (people && line!="PEOPLE"){
            node *p=new node(line);
            vertices.push_back(p); 
        }
        if (!people && line!="CONNECTIONS")
        {
            if (count==0)
            {
                src=line; 
            }
            else if (count==1)
            {
                dest=line;
            }
            else if (count==2 && !isUnitLength) //2
            {
                weight=stoi(line);
            }
            // cout<<"stored "<<line<<endl;
            count++;

            if (count==3)
            {
                // cout<<"source: "<<src<<"     dest: "<<dest<<"    weight: "<<weight<<endl;
                count=0;
                node *first;//=vertices.at(i);
                node *second;

                for (int i=0; i<vertices.size(); i++)
                {

                    if (vertices.at(i)->name==src)
                    {
                        first=vertices.at(i);
                    }
                    if (vertices.at(i)->name==dest)
                    {

                        second=vertices.at(i);
                    }
                }

                edge e= edge(first, second, weight); //check if dynamic hona chahiye ya nahi
                first->edges.push_back(e);
                second->edges.push_back(e);
                arcs.push_back(e);
            }

        }
    }
    
    // cout<<"Checking vertices vector and it's edges: "<<endl;
    // for (int i=0; i<vertices.size(); i++)
    // {
    //     cout<<"Name: "<<vertices.at(i)->name<<endl;
    //     cout<<"Edges: "<<endl;
    //     for (int j=0; j<vertices.at(i)->edges.size(); j++)
    //     {
    //         cout<<"Source: "<<vertices.at(i)->edges.at(j).Origin->name<<"    Dest: "<<vertices.at(i)->edges.at(j).Dest->name<<"   Weight: "<<vertices.at(i)->edges.at(j).weight<<endl;
    //     }
    //     cout<<endl;

    // }


    // cout<<"Checking arcs vector: "<<endl;
    // for (int i=0; i<arcs.size(); i++)
    // {
    //     cout<<"Source of edge: "<<arcs.at(i).Origin->name<<endl;
    //     cout<<"Dest of edge: "<<arcs.at(i).Dest->name<<endl;
    //     cout<<"Weight of edge: "<<arcs.at(i).weight<<endl;
    // }
    // cout<<vertices[0]->name<<endl;
    // cout<<"Displaying"<<endl;
    // display(vertices[0]);
}

void Graph::display(node* temp)
{
	if(temp->visit)
		return;
	
	cout << "Person: " << temp->name;
	temp->visit = 1;
	for(int i=0; i< temp->edges.size(); i++)
	{
		if(!temp->edges[i].Origin->visit || !temp->edges[i].Dest->visit)
		cout << "->" << temp->edges[i].weight << endl;
		display(temp->edges[i].Origin);
		display(temp->edges[i].Dest);
	}
}

/*I'm using BFS to check reachability eventhough the worst case for DFS and BFS are the same so either could be used
but BFS gives a more optimal solution as it gives us an answer faster, with least possible depth compared to DFS which is more
space efficient than BFS but since our graph isn't very extensive so BFS seemed like a better choice.*/
bool Graph::Reachable(string start, string dest)
{

    node *src=NULL;
    node *dst=NULL;
    for (int i=0; i< vertices.size(); i++)
    {
        vertices.at(i)->visit=0;
        if (vertices.at(i)->name==start)
        {
            src=vertices.at(i);
        }
        if (vertices.at(i)->name==dest)
        {
            dst=vertices.at(i);
        }
    }

    if (src && dst)
    {
        // cout<<"Source node: "<<src->name<<"    Dest node: "<<dst->name<<endl;
        if (src->name==dst->name)
        {
            return true;
        }
        else
        {
            queue <node*> Queue;
            src->visit=1;
            // cout<<"Enqueing "<<src->name<<endl;
            Queue.push(src);
            while (!Queue.empty())
            {
                node *front=Queue.front();
                Queue.pop();
                // cout<<"Dequeing "<<front->name<<endl;
                // cout<<"size: "<<front->edges.size()<<endl;
                for (int i=0; i<front->edges.size(); i++)
                {
                    if (front->edges.at(i).Origin->name!=front->name) //other wala node is src in the edge
                    {
                        if (front->edges.at(i).Origin->visit==0) //unvisited
                        {
                            // cout<<"Enqueing "<<front->edges.at(i).Origin->name<<endl;
                            front->edges.at(i).Origin->visit=1;
                            if (front->edges.at(i).Origin->name==dst->name)
                            {
                                return true;
                            }
                            Queue.push(front->edges.at(i).Origin);
                        }
                    }
                    else //other wala node is dest in the edge
                    {
                        if (front->edges.at(i).Dest->visit==0) //unvisited
                        {
                            // cout<<"Enqueing "<<front->edges.at(i).Dest->name<<endl;
                            front->edges.at(i).Dest->visit=1;
                            if (front->edges.at(i).Dest->name==dst->name)
                            {
                                return true;
                            }
                            Queue.push(front->edges.at(i).Dest);
                        }
                    }
                }
            }
            return false;
        }

    }
    else
    {
        // cout<<"Your start or end node is not part of the graph."<<endl;
        return false;
    }
}

vector<node*> Graph::Prims()
{
    vector <node*> MST;
    Graph g=Graph((char*)"friends.txt", 0); //weighted
    g.arcs.clear(); //cleared all edges

    for (int i =0; i<g.vertices.size(); i++)
    {
        g.vertices.at(i)->visit=0;
        g.vertices.at(i)->edges.clear();
    }
    node* temp=g.vertices[0];

    for (int i =0; i<g.vertices.size(); i++) //make all unvisited
    {
        g.vertices.at(i)->visit=0;
        vertices.at(i)->prev=NULL;
        if (g.vertices.at(i)->name==temp->name)
        {
            g.vertices.at(i)->distance=0;
            // cout<<"Name: "<<vertices.at(i)->name<<"   Dist: "<<vertices.at(i)->distance<<endl;
            
        }
        else
        {
            g.vertices.at(i)->distance=10000000;
            // cout<<"Name: "<<vertices.at(i)->name<<"   Dist: "<<vertices.at(i)->distance<<endl;
        }
    }
    priority_queue<node*, vector<node*>, compare >Queue;
    Queue.push(temp);
        // src->visit=1;
    // bool run=true;
    while (MST.size()!=vertices.size())// && run)
    {
        node *front=Queue.top();
        front->visit=1;
        Queue.pop();
        MST.push_back(front);
        // if (front->name==dst->name)
        // {
        //     run=false;
        //     path.push_back(front->name);
        //     break;
        // }
        // path.push_back(front->name+"->");
        // cout<<"Dequeing "<<front->name<<endl;
        // cout<<"size: "<<front->edges.size()<<endl;
        for (int i=0; i<front->edges.size(); i++)
        {
            if (front->edges.at(i).Origin->name!=front->name) //other wala node is src in the edge
            {
                if (front->edges.at(i).Origin->visit==0) //unvisited
                {
                    // front->edges.at(i).Origin->visit=1;
                    // if (front->edges.at(i).Origin->name==dst->name)
                    // {
                    //     run=false;
                    //     path.push_back(front->edges.at(i).Origin->name);
                    //     break;
                    // }
                    int tent_dis=front->edges.at(i).weight; //parent ka distance pkus edge weight
                    // cout<<"Pehle distance: "<<front->edges.at(i).Origin->distance<<endl;

                    if (tent_dis < front->edges.at(i).Origin->distance)
                    {
                        front->edges.at(i).Origin->distance=tent_dis;
                        front->edges.at(i).Origin->prev=front;
                        // edges.at(i).Origin->distance
                    }
                    // cout<<"Ab distance: "<<front->edges.at(i).Origin->distance<<endl;

                    // cout<<"name: "<<front->edges.at(i).Origin->name<<"   dist: "<<front->edges.at(i).Origin->distance<<endl;
                    // cout<<"Enqueing "<<front->edges.at(i).Origin->name<<endl;
                    Queue.push(front->edges.at(i).Origin);
                }
            }
            else //other wala node is dest in the edge
            {
                if (front->edges.at(i).Dest->visit==0) //unvisited
                {
                    // cout<<"Enqueing "<<front->edges.at(i).Dest->name<<endl;
                    // front->edges.at(i).Dest->visit=1;
                    // if (front->edges.at(i).Dest->name==dst->name)
                    // {
                    //     run=false;
                    //     path.push_back(front->edges.at(i).Dest->name);
                    //     break;
                    // }
                    int tent_dis=front->edges.at(i).weight; //parent ka distance pkus edge weight
                    // cout<<"Pehle distance: "<<front->edges.at(i).Dest->distance<<endl;
                    
                    if (tent_dis< front->edges.at(i).Dest->distance)
                    {
                        front->edges.at(i).Dest->distance=tent_dis;
                        front->edges.at(i).Dest->prev=front;

                    }
                    // cout<<"Ab distance: "<<front->edges.at(i).Dest->distance<<endl;
                
                    // cout<<"name: "<<front->edges.at(i).Dest->name<<"   dist: "<<front->edges.at(i).Dest->distance<<endl;

                    Queue.push(front->edges.at(i).Dest);
                }
            }
        }
    }

    
    // checking sab kay final distances:
    // for (int i=0; i< vertices.size(); i++)
    // {
    //     cout<<"Name: "<<vertices.at(i)->name<<"    Distance from "<<start<<"  "<<vertices.at(i)->distance<<"         "; 
    //     if (vertices.at(i)->prev)
    //         cout<<"Prev's name: "<<  vertices.at(i)->prev->name;//<<endl; 
    //     cout<<endl;     
    // }
    // d=dst->distance;
    // cout<<dest<<" is "<<d<<" units away from "<<start<<endl;


    //use stack for path
    // stack <node*>p;
    // node* temp=dst;
    // while (temp!=NULL)
    // {
    //     p.push(temp);
    //     temp=temp->prev;
    // }

    // while (!p.empty())
    // {
    //     path.push_back(p.top()->name);
    //     p.pop();
    // }
    cout<<"MST from Prims"<<endl;
    for (int i=0; i< MST.size(); i++)
    {
        cout<<MST.at(i)->name<<"    ";
    }
    cout<<endl;
    return MST;
}

void display_pq(priority_queue<edge, vector<edge>, greater<edge> >pq)
{
    // cout<<"y"<<endl;
    priority_queue<edge, vector<edge>, greater<edge> >p=pq;
    while (!p.empty())
    {
        cout<<p.top().weight<<"   ";
        p.pop();
    }
    cout<<endl;
}

vector<node*> Graph::Kruskal()
{
    //pehle saare nodes unconnected. Put arcs in priority queue based on edge weights. Pop from queue only if it
    //doesnt result in a cycle (reachability true before adding it tu dont add warna add)
    // vector<node*> ver=vertices;
    //name same, edges empty and unvisited. Baaki fields dont matter here
    // for (int i =0; i<vertices.size(); i++)
    // {
    //     ver.at(i)->visit=0;
    //     ver.at(i)->edges.clear();
    // }


    //make new graph not vertices
    Graph g=Graph((char*)"friends.txt", 0); //weighted
    g.arcs.clear(); //cleared all edges

    for (int i =0; i<g.vertices.size(); i++)
    {
        g.vertices.at(i)->visit=0;
        g.vertices.at(i)->edges.clear();
    }

    // cout<<ver.at(3)->edges.empty()<<endl;
    priority_queue<edge, vector<edge>, greater<edge> >Queue;
    for (int i=0; i< arcs.size(); i++)
    {
        Queue.push(arcs.at(i));   
    }
    //     for (int i =0; i<vertices.size(); i++)
    // {
    //     ver.at(i)->visit=0;
    //     ver.at(i)->edges.clear();
    // }    for (int i =0; i<vertices.size(); i++)
    // {
    //     ver.at(i)->visit=0;
    //     ver.at(i)->edges.clear();
    // }
    // Queue.push(edge{NULL, NULL, 232});
    // Queue.push(edge{NULL, NULL, 9});
    // Queue.push(edge{NULL, NULL, 22});
    // Queue.push(edge{NULL, NULL, -232});
    // display_pq(Queue);
    bool check=true;
    while (!Queue.empty() && check)
    {
        edge temp=Queue.top();
        Queue.pop();
        node* src=temp.Origin;
        node* dst=temp.Dest;
        for (int i=0; i<g.vertices.size(); i++)
        {
            if (src->name==g.vertices.at(i)->name)
            {
                src=g.vertices.at(i);
            }
            if (dst->name==g.vertices.at(i)->name)
            {
                dst=g.vertices.at(i);
            }
        }
        if (!g.Reachable(src->name, dst->name)) //yeh reachable tu apne graph kay mutabik check kare ga...
        {
            //join
            //edge x=edge(src,dst,1)
            src->edges.push_back(edge(src,dst,temp.weight));
            dst->edges.push_back(edge(src,dst,temp.weight));
            g.arcs.push_back(edge(src,dst,temp.weight));
        }
        check=false;
        for (int i=0; i<g.vertices.size(); i++) //if broken link found, check true again so loop again. If none found, leave loop 
        {
            for (int j=0; j<g.vertices.size(); j++)
            {
                if(!g.Reachable(g.vertices.at(i)->name, g.vertices.at(j)->name))
                {
                    check=true;
                    break;
                }
            }
            if(check==true)
            {
                break;
            }
        }
        //change check if all are connected now

    }

    //check final graph:
    cout<<"Checking vertices vector and it's edges on MST: "<<endl;
    for (int i=0; i<g.vertices.size(); i++)
    {
        cout<<"Name: "<<g.vertices.at(i)->name<<endl;
        cout<<"Edges: "<<endl;
        for (int j=0; j<g.vertices.at(i)->edges.size(); j++)
        {
            cout<<"Source: "<<g.vertices.at(i)->edges.at(j).Origin->name<<"    Dest: "<<g.vertices.at(i)->edges.at(j).Dest->name<<"   Weight: "<<g.vertices.at(i)->edges.at(j).weight<<endl;
        }
        cout<<endl;

    }

    return g.vertices; //change later

}


void display_pq(priority_queue<node*, vector<node*>, compare >pq)
{
    // cout<<"y"<<endl;
    priority_queue<node*, vector<node*>, compare >p=pq;
    while (!p.empty())
    {
        cout<<p.top()->name<<"   ";
        p.pop();
    }
}

vector<string> Graph::Dijkstra(string start, string dest, float &d)
{
    //d bhi badalna
    if (Reachable(start, dest))
    {
        vector<string> path;
        node *src=NULL;
        node *dst=NULL;
        for (int i =0; i<vertices.size(); i++) //make all unvisited
        {
            vertices.at(i)->visit=0;
            vertices.at(i)->prev=NULL;
            if (vertices.at(i)->name==start)
            {
                vertices.at(i)->distance=0;
                // cout<<"Name: "<<vertices.at(i)->name<<"   Dist: "<<vertices.at(i)->distance<<endl;
                
            }
            else
            {
                vertices.at(i)->distance=10000000;
                // cout<<"Name: "<<vertices.at(i)->name<<"   Dist: "<<vertices.at(i)->distance<<endl;
            }
            if (vertices.at(i)->name==start)
            {
                src=vertices.at(i);
            }
            if (vertices.at(i)->name==dest)
            {
                dst=vertices.at(i);
            }
        }
        priority_queue<node*, vector<node*>, compare >Queue;
        // cout<<"Enqueing "<<src->name<<endl;

        Queue.push(src);
        // src->visit=1;
        bool run=true;
        while (!Queue.empty() && run)
        {
            node *front=Queue.top();
            front->visit=1;
            Queue.pop();
            // if (front->name==dst->name)
            // {
            //     run=false;
            //     path.push_back(front->name);
            //     break;
            // }
            // path.push_back(front->name+"->");
            // cout<<"Dequeing "<<front->name<<endl;
            // cout<<"size: "<<front->edges.size()<<endl;
            for (int i=0; i<front->edges.size(); i++)
            {
                if (front->edges.at(i).Origin->name!=front->name) //other wala node is src in the edge
                {
                    if (front->edges.at(i).Origin->visit==0) //unvisited
                    {
                        // front->edges.at(i).Origin->visit=1;
                        // if (front->edges.at(i).Origin->name==dst->name)
                        // {
                        //     run=false;
                        //     path.push_back(front->edges.at(i).Origin->name);
                        //     break;
                        // }
                        int tent_dis=front->distance + front->edges.at(i).weight; //parent ka distance pkus edge weight
                        // cout<<"Pehle distance: "<<front->edges.at(i).Origin->distance<<endl;

                        if (tent_dis < front->edges.at(i).Origin->distance)
                        {
                            front->edges.at(i).Origin->distance=tent_dis;
                            front->edges.at(i).Origin->prev=front;
                            // edges.at(i).Origin->distance
                        }
                        // cout<<"Ab distance: "<<front->edges.at(i).Origin->distance<<endl;

                        // cout<<"name: "<<front->edges.at(i).Origin->name<<"   dist: "<<front->edges.at(i).Origin->distance<<endl;
                        // cout<<"Enqueing "<<front->edges.at(i).Origin->name<<endl;
                        Queue.push(front->edges.at(i).Origin);
                    }
                }
                else //other wala node is dest in the edge
                {
                    if (front->edges.at(i).Dest->visit==0) //unvisited
                    {
                        // cout<<"Enqueing "<<front->edges.at(i).Dest->name<<endl;
                        // front->edges.at(i).Dest->visit=1;
                        // if (front->edges.at(i).Dest->name==dst->name)
                        // {
                        //     run=false;
                        //     path.push_back(front->edges.at(i).Dest->name);
                        //     break;
                        // }
                        int tent_dis=front->distance + front->edges.at(i).weight; //parent ka distance pkus edge weight
                        // cout<<"Pehle distance: "<<front->edges.at(i).Dest->distance<<endl;
                        
                        if (tent_dis< front->edges.at(i).Dest->distance)
                        {
                            front->edges.at(i).Dest->distance=tent_dis;
                            front->edges.at(i).Dest->prev=front;

                        }
                        // cout<<"Ab distance: "<<front->edges.at(i).Dest->distance<<endl;
                    
                        // cout<<"name: "<<front->edges.at(i).Dest->name<<"   dist: "<<front->edges.at(i).Dest->distance<<endl;

                        Queue.push(front->edges.at(i).Dest);
                    }
                }
            }
        }

        
        // checking sab kay final distances:
        // for (int i=0; i< vertices.size(); i++)
        // {
        //     cout<<"Name: "<<vertices.at(i)->name<<"    Distance from "<<start<<"  "<<vertices.at(i)->distance<<"         "; 
        //     if (vertices.at(i)->prev)
        //         cout<<"Prev's name: "<<  vertices.at(i)->prev->name;//<<endl; 
        //     cout<<endl;     
        // }
        d=dst->distance;
        // cout<<dest<<" is "<<d<<" units away from "<<start<<endl;


        //use stack for path
        stack <node*>p;
        node* temp=dst;
        while (temp!=NULL)
        {
            p.push(temp);
            temp=temp->prev;
        }

        while (!p.empty())
        {
            path.push_back(p.top()->name);
            p.pop();
        }
        return path;


    }
    else
    {
        cout<<"No path"<<endl;
        vector<string> empty;
        return empty;
    }
}



int main()
{
    // string choice;
	// cout<<"Initialize your graph in main!"<<endl;
    // cout<<"If you want your graph to be weighted, press 0. If not, press 1"<<endl;
    // cin>>choice;
    // while (choice!="0" && choice!="1")
    // {
    //     cout<<"Incorrect entry. Press either 0 or 1."<<endl;
    //     cin>>choice;
    // }
    Graph graph= Graph((char*)"friends.txt", 1);//stoi(choice));
    Graph w_graph= Graph((char*)"friends.txt", 0);//stoi(choice));
    // Graph agraph= Graph((char*)"test.txt", 1);//stoi(choice));
    // Graph aw_graph= Graph((char*)"test.txt", 0);//stoi(choice));

    // cout<<"Unweighted Prims: "<<endl;
    // agraph.Prims();
    // cout<<"Weighted Prims: "<<endl;
    // aw_graph.Prims();

//    Graph w_graph=

    // Graph graph2=Graph((char*)"test.txt", 1);




    cout<<"Part 6 Results:"<<endl;
    cout<<"Part 1:"<<endl;
    cout<<"Mannan and Ali Reachability: (1 for yes, 0 for no): "<<graph.Reachable("Mannan", "Ali")<<endl;
    cout<<"Mannan and Trump Reachability: (1 for yes, 0 for no): "<<graph.Reachable("Mannan", "Trump")<<endl;
    cout<<"Trump and Ali Reachability: (1 for yes, 0 for no): "<<graph.Reachable("Trump", "Ali")<<endl;
    
    cout<<"Part 2:"<<endl;
    cout<<"For unweighted:"<<endl;
    float p=0;
    float &d=p;
    vector <string> path=graph.Dijkstra("Ali", "Trump", d);
    cout<<"Ali is "<<d<<" hops away from Trump"<<endl;
    cout<<"Path: "<<endl;
    for (int i=0; i<path.size(); i++)
    {
        cout<<"  "<<path.at(i);
        if (i<path.size()-1)
            cout<<"  ->";
    }
    cout<<endl;
    float m=0;
    float &q=m;
    vector <string> pat=graph.Dijkstra("Mannan", "Trump", q);
    cout<<"Mannan is "<<q<<" hops away from Trump"<<endl;
    cout<<"Path: "<<endl;
    for (int i=0; i<pat.size(); i++)
    {
        cout<<"  "<<pat.at(i);
        if (i<pat.size()-1)
            cout<<"  ->";
    }
    cout<<endl;

    cout<<"For weighted:"<<endl;
    float x=0;
    float &y=x;
    vector <string> pa=w_graph.Dijkstra("Ali", "Trump", y);
    cout<<"Ali is "<<y<<" hops away from Trump"<<endl;
    cout<<"Path: "<<endl;
    for (int i=0; i<pa.size(); i++)
    {
        cout<<"  "<<pa.at(i);
        if (i<pa.size()-1)
            cout<<"  ->";
    }
    cout<<endl;
    float a=0;
    float &z=a;
    vector <string> patz=w_graph.Dijkstra("Mannan", "Trump", z);
    cout<<"Mannan is "<<z<<" hops away from Trump"<<endl;
    cout<<"Path: "<<endl;
    for (int i=0; i<patz.size(); i++)
    {
        cout<<"  "<<patz.at(i);
        if (i<patz.size()-1)
            cout<<"  ->";
    }
    cout<<endl;

    cout<<"So Mannan and Trump have a shorter path in terms of index of frienship."<<endl;

    cout<<"unweighted MST:"<<endl;
    graph.Kruskal();

    cout<<"Weighted MST:"<<endl;
    w_graph.Kruskal();

    cout<<"Yes, there can exist more than one MST of a given graph if the sum of minimum weights to connect all the vertices can be achieved with different paths. My results imply that there will be probably be more MSTs for an unweighted graph than a weighted one because getting the same weight sum from multiple paths is more likely. The MSTs produced can help social media companies infer how to connect to everyone on their system via other users with the minimum possible paths needed. MSTs also have applications in cable and telephone network designs as well as network protocols."<<endl;
    return 0; 
}

#endif
