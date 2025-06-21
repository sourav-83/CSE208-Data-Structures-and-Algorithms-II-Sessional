#include<bits/stdc++.h>

using namespace std;


// eloge

int find(int x, vector<int>& link) {

    if (x != link[x]) link[x] = find(link[x], link);  

    return link[x];
}


void unite (int a, int b, vector<int>& link, vector<int>& size)
{
    a = find(a,link);
    b = find(b,link);
    if (size[a]<size[b]) swap(a,b);
    size[a] += size[b];
    link[b] = a;

}

int main ()
{
    int n,m;
    cin>>n>>m;
    vector<pair<int,pair<int,int>>>edges;
    for (int i=0; i<m; i++)
    {
        int w,a,b;
        cin>>w>>a>>b;
        edges.push_back({w,{a,b}});
    }
    sort(edges.begin(),edges.end());
    vector<int>link(n+1);
    vector<int>size(n+1,1);
    for (int i=1; i<=n; i++) link[i]=i;
    int mst = 0;
    for (auto e: edges)
    {   
        int a = e.second.first;
        int b = e.second.second;
        if (find(a,link) != find(b,link))
        {
            unite(a,b,link,size);
            mst += e.first;
            
        }
    }
    cout<<mst<<endl;

    return 0;

}