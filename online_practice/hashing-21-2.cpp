#include <bits/stdc++.h>

using namespace std;


int main()
{

    int l,k;
    cin>>l>>k;

    map<string,int>m;
    string present;

    for (int i=0; i<l; i++)
    {
            
        
            char c;
            cin>>c;
            present += c;
            int size = present.size();
            if (i==k-1)
            {
               m[present]++;
            }
            else if (i>k-1)
            {
               present = present.substr(1,k);
               m[present]++;
            }
            

        
    

    }
    for (auto a: m)
    {
        cout<<a.first<< " "<<a.second<<endl;;
    }
    return 0;

}


