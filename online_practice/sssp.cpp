#include<iostream>
#include<vector>
#include<queue>
#include <utility>

using namespace std;

int main ()
{
    int n,m;
    cin>>n>>m;
    vector<int>tax(n);
    for (int i=0; i<n; i++) 
    {
        int w;
        cin>>w;
        tax[i]=w;
    }
    vector<vector<pair<int,int>>>adj(n);
    for (int i=0; i<m; i++)
    {
        int a,b;
        cin>>a>>b;
        adj[a-1].push_back({b-1,tax[b-1]});
    }
    vector<int>distance(n,INT32_MAX);
    
    vector<int>processed(n,0);
    distance[0]=0;
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> q;
    q.push({0,0});
    while(!q.empty())
    {
        auto x = q.top();
        q.pop();
        if(processed[x.second]) continue;
        processed[x.second] = 1;
        for(auto y: adj[x.second])
        {
            if(distance[x.second]!= INT32_MAX && distance[y.first]>y.second+distance[x.second])
            {
                distance[y.first] = y.second+distance[x.second];
                q.push({distance[y.first],y.first});
            }
        }
    }
    cout<<distance[n-1]<<endl;
}
