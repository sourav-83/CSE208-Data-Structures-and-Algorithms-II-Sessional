#include<bits/stdc++.h>
using namespace std;
class Solution {
    public:
        int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        vector<int>distance(n,INT_MAX);
        distance[k-1] = 0;
        for (int i=0; i<n-1; i++)
        {
            for(auto v: times)
            {
                if(distance[v[0]-1]!=INT_MAX && distance[v[1]-1]>distance[v[0]-1]+v[2]) distance[v[1]-1] = distance[v[0]-1]+v[2]; 
            }
        }
        int ans = INT_MIN;
        for(auto d: distance) 
        {
            if(d==INT_MAX) return -1;
            ans = max(ans,d);
        }
        return ans;    
        }
    };