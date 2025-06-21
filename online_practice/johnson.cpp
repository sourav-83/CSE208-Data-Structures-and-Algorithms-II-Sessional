#include <bits/stdc++.h>

using namespace std;

struct Edge {
    int u, v, weight;
};

const int INF = INT_MAX;

void bellmanFord(int V, int src, vector<Edge> &edges, vector<int> &h) {
    h.assign(V, INF);
    h[src] = 0;

    for (int i = 0; i < V - 1; ++i) {
        for (const auto &e : edges) {
            if (h[e.u] != INF && h[e.u] + e.weight < h[e.v]) {
                h[e.v] = h[e.u] + e.weight;
            }
        }
    }

    for (const auto &e : edges) {
        if (h[e.u] != INF && h[e.u] + e.weight < h[e.v]) {
            throw runtime_error("Graph contains a negative-weight cycle");
        }
    }
}

void dijkstra(int src, int V, const vector<vector<pair<int, int>>> &adj,
              vector<int> &dist, vector<int> &parent) {
    dist.assign(V, INF);
    parent.assign(V, -1);
    dist[src] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.emplace(0, src);

    while (!pq.empty()) {
        pair<int, int> top = pq.top(); pq.pop();
        int d = top.first, u = top.second;
        if (d > dist[u]) continue;

        for (const auto &edge : adj[u]) {
            int v = edge.first;
            int w = edge.second;
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                parent[v] = u;
                pq.emplace(dist[v], v);
            }
        }
    }
}

// Johnson's Algorithm
pair<vector<vector<int>>, vector<vector<int>>>
johnsonsAlgorithm(int V, vector<Edge> &edges) {
    vector<Edge> extendedEdges = edges;
    for (int i = 0; i < V; ++i) {
        extendedEdges.push_back({V, i, 0}); // connect dummy node V
    }

    vector<int> h;
    bellmanFord(V + 1, V, extendedEdges, h);

    // Reweight edges using h[]
    vector<vector<pair<int, int>>> adj(V);
    for (const auto &e : edges) {
        int newWeight = e.weight + h[e.u] - h[e.v];
        adj[e.u].emplace_back(e.v, newWeight);
    }

    vector<vector<int>> allPairsDist(V, vector<int>(V, INF));
    vector<vector<int>> parents(V, vector<int>(V, -1));

    for (int u = 0; u < V; ++u) {
        vector<int> dist, parent;
        dijkstra(u, V, adj, dist, parent);

        for (int v = 0; v < V; ++v) {
            if (dist[v] < INF) {
                allPairsDist[u][v] = dist[v] - h[u] + h[v];
                parents[u][v] = parent[v];
            }
        }
    }

    return make_pair(allPairsDist, parents);
}

// Reconstruct shortest path from u to v
vector<int> reconstructPath(int u, int v, const vector<vector<int>> &parents) {
    vector<int> path;
    while (v != -1) {
        path.push_back(v);
        v = parents[u][v];
    }
    reverse(path.begin(), path.end());
    return path;
}

// Demonstration
int main() {
    int V = 5;
    vector<Edge> edges = {
        {0, 1, 3},
        {0, 2, 8},
        {0, 4, -4},
        {1, 3, 1},
        {1, 4, 7},
        {2, 1, 4},
        {3, 2, -5},
        {4, 3, 6}
    };

    try {
        pair<vector<vector<int>>, vector<vector<int>>> result = johnsonsAlgorithm(V, edges);
        vector<vector<int>> distances = result.first;
        vector<vector<int>> parents = result.second;

        cout << "All-Pairs Shortest Distances:\n";
        for (int u = 0; u < V; ++u) {
            for (int v = 0; v < V; ++v) {
                if (distances[u][v] == INF)
                    cout << "INF ";
                else
                    cout << distances[u][v] << " ";
            }
            cout << "\n";
        }

        cout << "\nExample Path from 0 to 3:\n";
        vector<int> path = reconstructPath(0, 3, parents);
        for (int node : path) cout << node << " ";
        cout << "\n";

    } catch (const exception &e) {
        cout << "Error: " << e.what() << "\n";
    }

    return 0;
}
