#include <bits/stdc++.h>
#include "node.hpp"

using namespace std;

class tree
{

    node *root;
    int size;

    void rotateleft(node *&Node)
    {
        node *child = Node->right;
        Node->right = child->left;
        if (Node->right != nullptr)
            Node->right->parent = Node;
        child->parent = Node->parent;
        if (Node->parent == nullptr)
            root = child;
        else if (Node == Node->parent->left)
            Node->parent->left = child;
        else
            Node->parent->right = child;
        child->left = Node;
        Node->parent = child;
    }

    void rotateright(node *Node)
    {
        node *child = Node->left;
        Node->left = child->right;
        if (Node->left != nullptr)
            Node->left->parent = Node;
        child->parent = Node->parent;
        if (Node->parent == nullptr)
            root = child;
        else if (Node == Node->parent->left)
            Node->parent->left = child;
        else
            Node->parent->right = child;
        child->right = Node;
        Node->parent = child;
    }

    void insertHelper(node *Node)
    {
        node *parent = nullptr;
        node *grandparent = nullptr;
        while (Node != root && Node->color == RED && Node->parent->color == RED)
        {
            parent = Node->parent;
            grandparent = parent->parent;
            if (parent == grandparent->left)
            {
                node *uncle = grandparent->right;
                if (uncle != nullptr && uncle->color == RED)
                {
                    grandparent->color = RED;
                    parent->color = BLACK;
                    uncle->color = BLACK;
                    Node = grandparent;
                }
                else
                {
                    if (Node == parent->right)
                    {
                        rotateleft(parent);
                        Node = parent;
                        parent = Node->parent;
                    }
                    rotateright(grandparent);
                    swap(parent->color, grandparent->color);
                    Node = parent;
                }
            }
            else
            {
                node *uncle = grandparent->left;
                if (uncle != nullptr && uncle->color == RED)
                {
                    grandparent->color = RED;
                    parent->color = BLACK;
                    uncle->color = BLACK;
                    Node = grandparent;
                }
                else
                {
                    if (Node == parent->left)
                    {
                        rotateright(parent);
                        Node = parent;
                        parent = Node->parent;
                    }
                    rotateleft(grandparent);
                    swap(parent->color, grandparent->color);
                    Node = parent;
                }
            }
        }
        root->color = BLACK;
    }

    void deleteHelper(node *&Node)
    {
        if (Node == nullptr)
            return;
        while (Node != root && (Node == nullptr || Node->color == BLACK))
        {
            if (Node == Node->parent->left)
            {
                node *sibling = Node->parent->right;

                if (sibling != nullptr && sibling->color == RED)
                {
                    sibling->color = BLACK;
                    Node->parent->color = RED;
                    rotateleft(Node->parent);
                    sibling = Node->parent->right;
                }

                if (sibling != nullptr &&
                    ((sibling->left == nullptr || sibling->left->color == BLACK) &&
                     (sibling->right == nullptr || sibling->right->color == BLACK)))
                {
                    sibling->color = RED;
                    Node = Node->parent;
                }
                else
                {
                    if (sibling != nullptr && (sibling->right == nullptr || sibling->right->color == BLACK))
                    {
                        if (sibling->left != nullptr)
                            sibling->left->color = BLACK;
                        if (sibling != nullptr)
                            sibling->color = RED;
                        rotateright(sibling);
                        sibling = Node->parent->right;
                    }

                    if (sibling != nullptr)
                    {
                        sibling->color = Node->parent->color;
                        Node->parent->color = BLACK;
                        if (sibling->right != nullptr)
                            sibling->right->color = BLACK;
                        rotateleft(Node->parent);
                    }
                    Node = root;
                }
            }
            else
            {
                node *sibling = Node->parent->left;

                if (sibling != nullptr && sibling->color == RED)
                {
                    sibling->color = BLACK;
                    Node->parent->color = RED;
                    rotateright(Node->parent);
                    sibling = Node->parent->left;
                }

                if (sibling != nullptr &&
                    ((sibling->left == nullptr || sibling->left->color == BLACK) &&
                     (sibling->right == nullptr || sibling->right->color == BLACK)))
                {
                    sibling->color = RED;
                    Node = Node->parent;
                }
                else
                {
                    if (sibling != nullptr && (sibling->left == nullptr || sibling->left->color == BLACK))
                    {
                        if (sibling->right != nullptr)
                            sibling->right->color = BLACK;
                        sibling->color = RED;
                        rotateleft(sibling);
                        sibling = Node->parent->left;
                    }

                    if (sibling != nullptr)
                    {
                        sibling->color = Node->parent->color;
                        Node->parent->color = BLACK;
                        if (sibling->left != nullptr)
                            sibling->left->color = BLACK;
                        rotateright(Node->parent);
                    }
                    Node = root;
                }
            }
        }

        if (Node != nullptr)
            Node->color = BLACK;
    }

    node *minValue(node *&Node)
    {
        node *current = Node;
        while (current->left != nullptr)
            current = current->left;
        return current;
    }

    void transplant(node *&root, node *&u, node *&v)
    {
        if (u->parent == nullptr)
            root = v;
        else if (u == u->parent->left)
            u->parent->left = v;
        else
            u->parent->right = v;

        if (v != nullptr)
            v->parent = u->parent;
    }

    bool remove(node *&z)
    {
        size--;

        node *x = nullptr;
        node *y = z;
        Color yOriginalColor = y->color;

        if (z->left == nullptr)
        {
            x = z->right;
            transplant(root, z, z->right);
        }
        else if (z->right == nullptr)
        {
            x = z->left;
            transplant(root, z, z->left);
        }
        else
        {
            y = minValue(z->right);
            yOriginalColor = y->color;
            x = y->right;

            if (y->parent == z)
            {
                if (x != nullptr)
                    x->parent = y;
            }
            else
            {
                transplant(root, y, y->right);
                y->right = z->right;
                if (y->right != nullptr)
                    y->right->parent = y;
            }

            transplant(root, z, y);
            y->left = z->left;
            if (y->left != nullptr)
                y->left->parent = y;
            y->color = z->color;
        }

        delete z;
        z = nullptr;

        if (yOriginalColor == BLACK)
        {
            deleteHelper(x);
        }
        return true;
    }

public:
    tree()
    {
        root = nullptr;
        size = 0;
    }
    ~tree()
    {
        deleteTree(root);
    }
    void insert(string name1, int id1)
    {
        node *Node = root;
        node *z = nullptr;
        while (Node != nullptr)
        {
            if (Node->name == name1)
            {
                z = Node;
                break;
            }
            else if (Node->name > name1)
                Node = Node->left;
            else
                Node = Node->right;
        }

        if (z != nullptr)
        {
            z->id = id1;
            return;
        }

        size++;
        Node = new node(name1, id1);
        node *parent = nullptr;
        node *current = root;

        while (current != nullptr)
        {
            parent = current;
            if (Node->name < current->name)
                current = current->left;
            else
                current = current->right;
        }

        Node->parent = parent;

        if (parent == nullptr)
            root = Node;
        else if (Node->name < parent->name)
            parent->left = Node;
        else
            parent->right = Node;

        insertHelper(Node);
    }

    bool deleteNode(string name)
    {
        node *Node = root;
        node *z = nullptr;
        while (Node != nullptr)
        {
            if (Node->name == name)
            {
                z = Node;
                break;
            }
            else if (Node->name > name)
                Node = Node->left;
            else
                Node = Node->right;
        }

        if (z == nullptr)
            return false;

        return remove(z);
    }

    bool search(string name)
    {
        node *Node = root;
        while (Node != nullptr)
        {
            if (Node->name == name)
                return true;
            else if (Node->name > name)
                Node = Node->left;
            else
                Node = Node->right;
        }
        return false;
    }

    node *getRoot()
    {
        return root;
    }
    void deleteTree(node *Node)
    {
        if (Node != nullptr)
        {
            deleteTree(Node->left);
            deleteTree(Node->right);
            delete Node;
            size--;
        }
    }
    int getSize()
    {
        return size;
    }
};