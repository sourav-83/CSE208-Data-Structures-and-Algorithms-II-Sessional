#include<bits/stdc++.h>

using namespace std;

const int INF = 1e9;

int n;
vector<vector<int>> capacity;
vector<vector<int>> adj;


int bfs(int s, int t, vector<int>& parent) {
    fill(parent.begin(), parent.end(), -1);
    parent[s] = -2;
    queue<pair<int, int>> q;
    q.push({s, INF});

    while (!q.empty()) {
        int cur = q.front().first;
        int flow = q.front().second;
        q.pop();

        for (int next : adj[cur]) {
            if (parent[next] == -1 && capacity[cur][next]) {
                parent[next] = cur;
                int new_flow = min(flow, capacity[cur][next]);
                
                if (next == t)
                    return new_flow;
                q.push({next, new_flow});
            }
        }
    }

    return 0;
}



void maxflow(int s, int t) {
    
    int flow = 0;
    vector<int> parent(n);
    int new_flow;
    vector<stack<int>>routes;

    while (new_flow = bfs(s, t, parent)) {
        flow ++;
        int cur = t;
        stack<int> temp;
        temp.push(cur+1);
        while (cur != s) {
            int prev = parent[cur];
            capacity[prev][cur] -= new_flow;
            capacity[cur][prev] += new_flow;
            cur = prev;
            temp.push(cur+1);
        }
        routes.push_back(temp);
    }
    cout<<flow<<endl;
    if (flow == 0) cout<<"No escape route possible! The Professor needs a new plan."<<endl;
    for (int i=0; i<flow; i++)
    {
        while(!routes[i].empty())
        {
            cout<<routes[i].top();
            routes[i].pop();
            if (routes[i].empty()) break;
            cout<<" -> ";
        }
        cout<<endl;
    }

    
}


int main()
{   
    int T;
    cin>>T;
    for (int t=0; t<T; t++)
    { 
    cin>>n;
    capacity = vector<vector<int>>(n,vector<int>(n,0));
    adj = vector<vector<int>>(n);
    int edges;
    cin>>edges;
    for (int i=0; i<edges; i++)
    {
        int a,b;
        cin>>a>>b;
        a--;
        b--;
        adj[a].push_back(b);
        capacity[a][b]=1;
    }
    
    cout<<"case "<<t+1<<": ";
    maxflow(0,n-1);

    }
    

    return 0;

}


