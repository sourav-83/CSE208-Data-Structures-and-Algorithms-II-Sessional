#include <bits/stdc++.h>

using namespace std;

char reverse(char c)
{
    if (c=='A') return 'T';
    else if (c=='T') return 'A';
    else if (c=='G') return 'C';
    else return 'G';
}

int main()
{

    int n,l;
    cin>>n>>l;
    unordered_map<string,int>m;
    for (int i=0; i<n; i++)
    {
        string present, complement;
        for (int j=0; j<l; j++)
        {
            char c;
            cin>>c;
            char c_bar = reverse(c);
            present += c;
            complement += c_bar;

        }
        reverse(complement.begin(), complement.end());
        if (m.count(complement)) cout<<present<<" "<<complement<<endl;
        m[present] = 1;

    }

}


