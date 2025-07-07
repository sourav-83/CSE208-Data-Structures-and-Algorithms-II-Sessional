#include <iostream>
#include <bits/stdc++.h>

using namespace std;

struct HashNode {
    string key;
    int value;
    bool deleted;

    HashNode (string k, int v)
    {
        key = k;
        value = v;
        deleted = false;
    }
    HashNode ()
    {
        key = "";
        value = -1;
        deleted = false;
    }

};