#include <bits/stdc++.h>

using namespace std;

// O((V + E) * log V)


int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<pair<int, int>>> adj(n + 1);
    for (int i = 0; i < m; i++) {
        int w, a, b;
        cin >> w >> a >> b;
        adj[a].push_back({w, b});
        adj[b].push_back({w, a});
    }

    vector<bool> processed(n + 1, false);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;

    int mst = 0;
    pq.push({0, 1}); 

    while (!pq.empty()) {
        auto x = pq.top();
        int w = x.first;
        int u = x.second;
        pq.pop();

        if (processed[u]) continue;
        processed[u] = true;
        mst += w;

        for (auto e: adj[u]) {
            int weight = e.first;
            int v = e.second;

            if (!processed[v]) {
                pq.push({weight, v});
            }
        }
    }

    cout << mst << endl;

    return 0;
}
