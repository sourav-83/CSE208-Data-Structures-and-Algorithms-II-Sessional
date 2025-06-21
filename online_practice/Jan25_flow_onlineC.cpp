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

int maxflow(int s, int t) {
    int flow = 0;
    vector<int> parent(n);
    int new_flow;

    while (new_flow = bfs(s, t, parent)) {
        flow += new_flow;
        int cur = t;
        while (cur != s) {
            int prev = parent[cur];
            capacity[prev][cur] -= new_flow;
            capacity[cur][prev] += new_flow;
            cur = prev;
        }
    }

    return flow;
}


int main()
{
    int T;
    cin>>T;
    for (int t=1; t<=T; t++)
    {
        int M,N;
        cin>>M>>N;
        vector<vector<int>>gang_members(M,vector<int>(7,0));
        for (int i=0; i<M; i++)
        {
            for (int j=0; j<7; j++)
            {
                int x;
                cin>>x;
                gang_members[i][j]=x;
            }
        }
        vector<vector<int>>partners(N,vector<int>(7,0));
        for (int i=0; i<N; i++)
        {
            for (int j=0; j<7; j++)
            {
                int x;
                cin>>x;
                partners[i][j]=x;
            }
        }
        n = M+N+2;
        capacity = vector<vector<int>>(n,vector<int>(n,0));
        adj = vector<vector<int>>(n);
        for (int i=0; i<M; i++)
        {
            for (int j=0; j<N; j++)
            {
                int check = 0;
                if(abs(gang_members[i][0]-partners[j][0]) > 12 || abs(gang_members[i][1]-partners[j][1]) > 5 || gang_members[i][2] != partners[j][2] || gang_members[i][3] != partners[j][3] || gang_members[i][5]+partners[j][5] < 10 || (!gang_members[i][4] && !partners[j][4]) || (gang_members[i][6] & partners[j][6] == 0)) check = 1;
                if (check == 0)
                {
                    adj[i].push_back(M+j);
                    adj[M+j].push_back(i);
                    capacity[i][M+j] = 1;
                }

            }
            adj[i].push_back(N+M);
            adj[N+M].push_back(i);
            capacity[N+M][i]=1;
        }
        for (int j=0; j<N; j++)
        {
            adj[N+j].push_back(N+M+1);
            adj[N+M+1].push_back(N+j);
            capacity[N+j][N+M+1]=1;
        }
        

        cout<<"case "<<t<<": "<<maxflow(N+M,N+M+1);


    }
    
    
    
    
    
    

    return 0;

}