#include <bits/stdc++.h>
#include <climits>
using namespace std;
struct Edge {
    int src, dest, weight;
};
unordered_map<int,int>blocked;
int temp = 0;
vector<int> bellmanFord(vector<Edge>& edges, int numVertices, int source) {
    vector<int> dist(numVertices, INT_MAX);
    dist[source] = 0;

    for (int i = 1; i <= numVertices - 1; ++i) {
        for (const Edge& edge : edges) {
            if (blocked[edge.src]==1 || blocked[edge.dest]==1) continue;
            if (dist[edge.src] != INT_MAX && dist[edge.src] + edge.weight < dist[edge.dest]) {
                dist[edge.dest] = dist[edge.src] + edge.weight;
            }
        }
    }

    for (const Edge& edge : edges) {
        if ((blocked[edge.src]!=1 && blocked[edge.dest]!=1) && dist[edge.src] != INT_MAX && dist[edge.src] + edge.weight < dist[edge.dest]) {
            // cout << "Graph contains negative weight cycle" << endl;
            temp = 1;
            return {};
        }
    }
    // cout << "Vertex\tDistance from Source" << endl;
    // for (int i = 0; i < numVertices; ++i) {
    //     cout << i << "\t" << dist[i] << endl;
    // }
    return dist;
}

int main ()
{
    int n,m,k,b,e;
    cin>>n>>m>>k>>b>>e;
    vector<int>capitals(k);
    for (int i=0; i<k; i++) {int a; cin>>a; capitals[i]=a-1;}
   
    for (int i=0; i<b; i++) {int a; cin>>a; blocked[a-1]=1;}
    vector<int>emergency(e);
    for (int i=0; i<e; i++) {int a; cin>>a; emergency[i]=a-1;}
    
    vector<Edge> edges(m);
    for (int i = 0; i < m; ++i) {
        int source, destination, weight;
        cin>>source>>destination>>weight;
        edges.push_back({source-1,destination-1,weight});
        
    }
    vector<int>ans(e,INT_MAX);
    for (auto capital: capitals)
    {
        vector<int>got = bellmanFord(edges, n, capital);
        if (temp == 1) {
            cout<<"Abyss Detected"<<endl;
            return 0;
        }
        for (int i=0; i<e; i++)
        {
            ans[i] = min(ans[i],got[emergency[i]]);
        }

    }
    for (int i=0; i<e; i++)
        {
            if (ans[i]==INT_MAX) cout<<"INF"<<endl;
            else cout<<ans[i]<<endl;
        }
        return 0;


}