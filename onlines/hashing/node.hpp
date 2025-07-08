#include <bits/stdc++.h>

using namespace std;

enum Color
{
    RED,
    BLACK
};

struct node
{
    string name;   
    int id;        
    node *parent;
    node *left;
    node *right;
    Color color;

    node(string name1, int id1)
    {
        name = name1;
        id = id1;
        parent = nullptr;
        left = nullptr;
        right = nullptr;
        color = RED;
    }
};
