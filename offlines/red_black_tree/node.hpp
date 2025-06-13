#include <bits/stdc++.h>

using namespace std;

enum Color
{
    RED,
    BLACK
};

struct node
{
    int id;
    string name;
    int count;
    node *parent;
    node *left;
    node *right;
    Color color;

    node(int id1, string name1, int count1)
    {
        id = id1;
        name = name1;
        count = count1;
        parent = nullptr;
        left = nullptr;
        right = nullptr;
        color = RED;
    }
};