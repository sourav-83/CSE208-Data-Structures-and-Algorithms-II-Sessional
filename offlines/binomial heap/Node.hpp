#include<bits/stdc++.h>

using namespace std;

class Node {
    public: 
    int key;
    int degree;
    Node* parent;
    Node* child;
    Node* sibling;
    Node(int x)
    {
        key = x;
        degree = 0;
        parent = nullptr;
        child = nullptr;
        sibling = nullptr;
    }
};