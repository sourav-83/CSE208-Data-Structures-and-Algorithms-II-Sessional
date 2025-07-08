#include <iostream>
#include <bits/stdc++.h>

using namespace std;

struct HashNode {
    int key;
    
    int status;

    HashNode (int k)
    {
        key = k;
        
        status = 1; // filled
    }
    HashNode ()
    {
        key = -1;
        
        status = 0; // empty
    }

};