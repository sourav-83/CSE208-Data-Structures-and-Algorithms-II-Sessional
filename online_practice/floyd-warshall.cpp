#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

void printPath(int src, int dest, vector<vector<int>>& parent) {
    if (parent[src][dest] == -1) {
        cout << "No path exists\n";
        return;
    }
    vector<int> path;
    int current = dest;
    while (current != src) {
        path.push_back(current);
        current = parent[src][current];
    }
    path.push_back(src);
    reverse(path.begin(), path.end());
    for (int node : path) cout << node << " ";
    cout << "\n";
}

int main() {
    int n, e;
    cin >> n >> e;

    vector<vector<int>> matrix(n + 1, vector<int>(n + 1, INF));
    vector<vector<int>> parent(n + 1, vector<int>(n + 1, -1));

    for (int i = 1; i <= n; i++) {
        matrix[i][i] = 0;
        parent[i][i] = i;
    }

    for (int i = 0; i < e; i++) {
        int a, b, w;
        cin >> a >> b >> w;
        matrix[a][b] = w;
        matrix[b][a] = w;
        parent[a][b] = a;
        parent[b][a] = b;
    }

    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (matrix[i][k] + matrix[k][j] < matrix[i][j]) {
                    matrix[i][j] = matrix[i][k] + matrix[k][j];
                    parent[i][j] = parent[k][j];
                }
            }
        }
    }

    int src, dest;
    cin >> src >> dest;

    if (matrix[src][dest] == INF)
        cout << "not reachable -.-\n";
    else {
        cout << "Shortest distance: " << matrix[src][dest] << "\n";
        cout << "Path: ";
        printPath(src, dest, parent);
    }

    return 0;
}
