// C++ program to find Minimum Spanning Tree
// of a graph using Reverse Delete Algorithm
#include<bits/stdc++.h>
#include<fstream>
using namespace std;

typedef  pair<int, int> iPair;

class Graph
{
    int V;  
    list<int> *adj;
    vector< pair<int, iPair> > edges;
    void DFS(int v, bool visited[]);
  
public:
    Graph(int V);  
  
    void addEdge(int u, int v, int w);

    bool isConnected();
  
    void reverseDeleteMST();
};
  
Graph::Graph(int V)
{
    this->V = V;
    adj = new list<int>[V];
}
  
void Graph::addEdge(int u, int v, int w)
{
    adj[u].push_back(v); 
    adj[v].push_back(u); 
    edges.push_back({w, {u, v}});
}
  
void Graph::DFS(int v, bool visited[])
{
    visited[v] = true;
  
    for (auto i = adj[v].begin(); i != adj[v].end(); ++i)
        if (!visited[*i])
            DFS(*i, visited);
}
  
bool Graph::isConnected()
{
    bool visited[V];
    memset(visited, false, sizeof(visited));

    DFS(0, visited);
  
    for (int i=1; i<V; i++)
        if (visited[i] == false)
            return false;
  
    return true;
}

void Graph::reverseDeleteMST()
{
    sort(edges.begin(), edges.end());
  
    int mst_wt = 0; 
  
    cout << "Edges in Minimum Spanning Tree\n";
 
    for (int i=edges.size()-1; i>=0; i--)
    {
        int u = edges[i].second.first;
        int v = edges[i].second.second;
  
        adj[u].remove(v);
        adj[v].remove(u);
  
        if (isConnected() == false)
        {
            adj[u].push_back(v);
            adj[v].push_back(u);
  
            cout << " ( "<< u << " - " << v <<" ), weight = "<<edges[i].first<<"\n";
            mst_wt += edges[i].first;
        }
    }
  
    cout << "Weight of Minimum Spanning Tree is " << mst_wt;
}
  
int main()
{
    ifstream infile("reverse_delete_input.txt");
    int n;
    infile>>n;
    Graph G1(n);

    int a, b, c;
    while (infile >> a >> b >> c)
    {
        G1.addEdge(a, b, c);
    }

    G1.reverseDeleteMST();

    return 0;
}