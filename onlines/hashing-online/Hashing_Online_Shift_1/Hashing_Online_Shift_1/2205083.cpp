#include<bits/stdc++.h>
#include "HashTable.cpp"

using namespace std;

int main()
{   
    
    int N,P_Max, Q;
    cin>>N>>P_Max>>Q;
    HashTable ht(N,P_Max);
    for (int i=0; i<Q; i++)
    {
        string s;
        int n;
        cin>>s>>n;
        if(s=="ALLOCATE")
        {
            ht.allocate(n);
        }
        else if(s=="FREE")
        {
            ht.free(n);
        }
    }
}