#include<iostream>
#include<list>
#include<queue>
#include<vector>
//#include<climits>
#include<set>

using namespace std;

class Graph{
    int V;
    list<pair<int, int>> *adj;

    public:
    Graph(int size)
    {
        V = size;
        adj = new list<pair<int, int>>[V];
    }

    void addEdge(int a, int b, int wt, bool undir=true)
    {
        adj[a].push_back({wt, b});
        if(undir)
            adj[b].push_back({wt, a});
    }

    int dijkstra(int src, int dest)
    {
        vector<int> dist(V, __INT_MAX__);
        dist[src] = 0;
        set<pair<int, int>> s;
        s.insert({0, src});

        while(!s.empty())
        {
            auto it = s.begin();
            int node = it->second;
            int distTillNow = it->first;
            s.erase(it);
            for(auto nbrs : adj[node])
            {
                int nbr = nbrs.second;
                int edgeLen = nbrs.first;
                if(distTillNow + edgeLen < dist[nbr])
                {
                    auto f = s.find({dist[nbr], nbr});
                    if(f != s.end())
                        s.erase(f);
                    dist[nbr] = distTillNow + edgeLen;
                    s.insert({dist[nbr], nbr});
                }
            }
        }

        for(int i=0; i<V; i++)
            cout<<i<<" is at a distance of "<<dist[i]<<endl;

        return dist[dest];
    }
};

int main()
{
    Graph g(5); // 5 vertices numbered from 0 to 4
    g.addEdge(0, 1, 1);
    g.addEdge(1, 2, 1);
    g.addEdge(0, 2, 4);
    g.addEdge(0, 3, 7);
    g.addEdge(3, 2, 2);
    g.addEdge(3, 4, 3);
    cout<<endl<<g.dijkstra(0, 4)<<endl;
    return 0;
}