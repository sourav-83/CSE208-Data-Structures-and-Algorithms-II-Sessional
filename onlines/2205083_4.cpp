#include <bits/stdc++.h>

using namespace std;

// runtime-complexity : O((V + E) * log V)
// space-complexity : O(v^2)

double dist (int x1, int x2, int y1, int y2)
{
    return sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
}


int main() {
    int n, r;
    cin >> n >> r;
    vector<pair<int,int>>coord(n+1);
    for (int i=1; i<=n; i++)
    {
        int a,b;
        cin>>a>>b;
        coord[i] = {a,b};
    }
    int states = 1;
    double road_length = 0;
    double rail_length = 0;
    

    vector<bool> visited(n + 1, false);
    priority_queue<pair<double, int>, vector<pair<double, int>>, greater<>> pq;

    
    pq.push({0.0, 1}); 

    while (!pq.empty()) {
        auto x = pq.top();
        double w = x.first;
        int u = x.second;
        pq.pop();

        if (visited[u]) continue;
        visited[u] = true;
        
        if (w>r) {
            rail_length += w;
            states++;
        }
        else road_length += w;

        
        for (int i=1; i<=n; i++) {
            if (i == u) continue;
            double weight = dist(coord[i].first,coord[u].first,coord[i].second,coord[u].second);
            int v = i;

            if (!visited[v]) {
                pq.push({weight, v});
            }
        }
    }

    cout <<states <<" "<<round(road_length)<<" "<<round(rail_length)<< endl;

    return 0;
}
