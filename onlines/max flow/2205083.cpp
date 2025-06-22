#include<bits/stdc++.h>


using namespace std;

const int INF = 1e9;

int n;
vector<vector<int>> capacity;
vector<vector<int>> adj;


double dist (int x1, int y1, int x2, int y2)
{
    return (double)sqrt((double)((x1-x2)*(x1-x2))+(double)((y1-y2)*(y1-y2)));
}

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
        vector<int>path;
        int cur = t;
        while (cur != s) {
            int prev = parent[cur];
            capacity[prev][cur] -= new_flow;
            capacity[cur][prev] += new_flow;
            cur = prev;
            path.push_back(cur);
        }
        int size = path.size();
              
        flow++;

    }

    return flow;
}




int main()
{   int T;
    cin>>T;
    for (int t=1; t<=T; t++)
    {
        int m,h;
        double r;
        cin>>m>>h>>r;
        vector<vector<int>>mouse(m);
        vector<vector<int>>hole(h);
        for (int i=0; i<m; i++)
        {
            int a,b;
            cin>>a>>b;
            mouse[i].push_back(a);
            mouse[i].push_back(b);
        }
        for (int i=0; i<h; i++)
        {
            int a,b,c;
            cin>>a>>b>>c;
            hole[i].push_back(a);
            hole[i].push_back(b);
            hole[i].push_back(c);
        }
        n = m+h+2;
         capacity = vector<vector<int>>(n,vector<int>(n,0));
         adj = vector<vector<int>>(n);
        for (int i=0; i<m; i++)
        {
            adj[m+h].push_back(i);
            adj[i].push_back(m+h);
            capacity[m+h][i]=1;
        }
        int x=0;
        for (int j=m; j<m+h; j++)
        {
            adj[m+h+1].push_back(j);
            adj[j].push_back(m+h+1);
            capacity[j][m+h+1]=hole[x][2];
            x++;
        }
        for (int mouse_no=0; mouse_no<m; mouse_no++)
        {
            for (int hole_no=0; hole_no<h; hole_no++)
            {
                 if (dist(hole[hole_no][0], hole[hole_no][1],mouse[mouse_no][0], mouse[mouse_no][1])<(double)r)
                 {
                    adj[mouse_no].push_back(m+hole_no);
                    adj[m+hole_no].push_back(mouse_no);
                    capacity[mouse_no][m+hole_no]=1;
                 }
            }
        }
        cout<<"Case "<<t<<": "<<maxflow(m+h,m+h+1)<<endl;
        

    }
    

    return 0;

}