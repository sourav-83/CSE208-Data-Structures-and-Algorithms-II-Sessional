#include <bits/stdc++.h>

using namespace std;

// O((V + E) * log V)


int main() {
    int n;
    cin >> n;
    vector<pair<int,int>>coord(n+1);
    for (int i=1; i<=n; i++)
    {
        int x,y;
        cin>>x>>y;
        coord[i]={x,y};
    }

    // vector<vector<pair<int, int>>> adj(n + 1);
    // for (int i = 0; i < m; i++) {
    //     int w, a, b;
    //     cin >> w >> a >> b;
    //     adj[a].push_back({w, b});
    //     adj[b].push_back({w, a});
    // }

    vector<bool> visited(n + 1, false);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;

    int mst = 0;
    pq.push({0, 1}); 

    while (!pq.empty()) {
        auto x = pq.top();
        int w = x.first;
        int u = x.second;
        pq.pop();

        if (visited[u]) continue;
        visited[u] = true;
        mst += w;

        // for (auto e: adj[u]) {
        //     int weight = e.first;
        //     int v = e.second;

        //     if (!visited[v]) {
        //         pq.push({weight, v});
        //     }
        // }
        for (int i=1; i<=n; i++)
        {
            if (i==u) continue;
            int weight = abs(coord[u].first-coord[i].first) + abs(coord[u].second-coord[i].second);
            if (!visited[i]) pq.push({weight,i});
        }
    }

    cout << mst << endl;

    return 0;
}
