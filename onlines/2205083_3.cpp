#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;


int main() {
    int n, m ,k;
    cin>>n>>m>>k;
    vector<int>from(n+1);
    vector<int>to(n+1);
    for (int i=1; i<=n; i++) cin>>from[i];
    for (int i=1; i<=n; i++) cin>>to[i];

    

    vector<vector<int>> matrix(n + 1, vector<int>(n + 1, INF));
    

    for (int i = 1; i <= n; i++) {
        matrix[i][i] = 0;
        
    }

    for (int i = 0; i < m; i++) {
        int a, b, w;
        cin >> a >> b >> w;
        matrix[a][b] = w;
        
    }

    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (matrix[i][k] + matrix[k][j] < matrix[i][j]) {
                    matrix[i][j] = matrix[i][k] + matrix[k][j];
                    
                }
            }
        }
    
    }
    priority_queue<int>q;
    for (int i=1; i<=n; i++) q.push(matrix[from[i]][to[i]]);
    int multiplier = 1;
    int current = 0;
    int ans = 0;
    while (!q.empty())
    {
       int x = q.top();
       q.pop();
       if (x==INF) continue;
       ans += x*multiplier;
       current++;
       if (current==k) {
        current = 0;
        multiplier *= 2;
       }
    }
    cout<<ans<<endl;

    

    return 0;
}
