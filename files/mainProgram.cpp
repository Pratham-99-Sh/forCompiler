#include<iostream>
#include<list>

using namespace std;

class Graph{
    int V;
    list<int> *adj;

    public:
    Graph(int size)
    {
        V = size;
        adj = new list<int>[V];
    }

    void addEdge(int a, int b, bool undir=true)
    {
        adj[a].push_back(b);
        if(undir)
            adj[b].push_back(a);
    }

    void printAdj()
    {
        for(int i=0; i<V; i++)
        {
            cout<<i<<" --> ";
            for(int elem : adj[i])
                cout<<elem<<", ";
            cout<<endl;
        }
    }
};

int main()
{
    Graph g(6); // means my edges can be pair from 0,1,2,3,4,5 only
    g.addEdge(0,1);
    g.addEdge(0,4);
    g.addEdge(2,1);
    g.addEdge(3,4);
    g.addEdge(4,5);
    g.addEdge(2,3);
    g.addEdge(3,5);

    g.printAdj();
    return 0;
}