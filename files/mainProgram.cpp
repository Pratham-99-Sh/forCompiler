#include<iostream>
#include<list>
#include<queue>

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

    void bfs(int source)
    {
        queue<int> q;
        bool *visited = new bool[V]{0};

        q.push(source);
        visited[source] = true;

        while(!q.empty())
        {
            int node = q.front();
            q.pop();
            cout<<node<<" ";

            for(int neighbour : adj[node])
                if(!visited[neighbour])
                {
                    q.push(neighbour);
                    visited[neighbour] = true;
                }
        }
    }
};

int main()
{
    Graph g(7); // 7 vertices numbered from 0 to 6
    g.addEdge(0,1);
    g.addEdge(1,2);
    g.addEdge(2,3);
    g.addEdge(3,5);
    g.addEdge(5,6);
    g.addEdge(4,5);
    g.addEdge(0,4);
    g.addEdge(3,4);

    g.bfs(1);
    return 0;
}