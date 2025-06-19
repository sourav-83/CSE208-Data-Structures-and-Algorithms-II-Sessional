#include <bits/stdc++.h>
#include "Node.hpp"
#include "outputStream.hpp"

using namespace std;

class BinomialHeap {

    private:

    Node* head;

    Node* mergeTrees(Node* node1, Node* node2)
    {
        if(node1->key > node2->key) swap(node1, node2);
        node2->parent = node1;
        node2->sibling = node1->child;
        node1->child = node2;
        node1->degree++;
        
        return node1;
    }
    void restructure()
    {
        vector<Node*> trees(64, nullptr);
        Node* current = head;
        head = nullptr;
        while (current != nullptr)
        {
            Node* next = current->sibling;
            current->sibling = nullptr;
            int degree = current->degree;
            while (trees[degree] != nullptr)
            {
                current = mergeTrees(trees[degree], current);
                trees[degree] = nullptr;
                degree++;
            }
            trees[degree] = current;
            current = next;
        }

    Node* prev = nullptr;
    Node* newHead = nullptr;

    for (int i = 0; i < (int)trees.size(); i++) {
        if (trees[i] != nullptr) {
            if (newHead == nullptr) {
                newHead = trees[i];
                prev = trees[i];
            } else {
                prev->sibling = trees[i];
                prev = trees[i];
            }
        }
    }
    if (prev != nullptr) prev->sibling = nullptr;
    head = newHead;

    }
    Node* findNode(Node* root, int key)
    {
        if (root == nullptr) return nullptr;

        if (root->key == key) return root;

        Node* found = findNode(root->child, key);
        if (found != nullptr) return found;

        return findNode(root->sibling, key);
    }

    public:

    BinomialHeap()
    {
        head = nullptr;
    }
    void insert(int x)
    {
        BinomialHeap bh;
        bh.head = new Node(x);
        merge(bh);
    }
    void merge(BinomialHeap& bh)
    {
        Node* newHead = nullptr;
        Node* tail = nullptr;

        Node* head1 = head;
        Node* head2 = bh.head;

        while (head1 != nullptr && head2 != nullptr)
        {
            Node* toBeAdded;
            if (head1->degree <= head2->degree)
            {
                toBeAdded = head1;
                head1 = head1->sibling;   
            }
            else 
            {
                toBeAdded = head2;
                head2 = head2->sibling;

            }
            if (newHead == nullptr)
            { 
                newHead = toBeAdded;
                tail = toBeAdded;
            }
            else 
            {
                tail->sibling = toBeAdded;
                tail = toBeAdded;
            }
        }

        Node* remaining;
        if (head1 != nullptr) remaining = head1;
        else remaining = head2;

        if (tail == nullptr) newHead = remaining;
        else tail->sibling = remaining;

        head = newHead;

        restructure();

        bh.head = nullptr;
    }

    int findMin ()
    {   
        if (head == nullptr) throw runtime_error("Binomial Heap is empty.");

        Node* minNode = head;
        Node* current = head->sibling;

        while (current != nullptr)
        {
            if (current->key < minNode->key)
            {
                minNode = current;
                
            }

            current = current->sibling;
        }

        return minNode->key;

    }

    int extractMin()
    {
        if (head == nullptr) throw runtime_error("Can't perform extract operation.Binomial Heap is empty.");

        Node* minNode = head;
        Node* prevMin = nullptr;
        Node* current = head->sibling;
        Node* prev = head;

        while (current != nullptr)
        {
            if (current->key < minNode->key)
            {
                minNode = current;
                prevMin = prev;
            }
            prev = current;
            current = current->sibling;
        }

        if (prevMin == nullptr) head = head->sibling;
        else prevMin->sibling = minNode->sibling;

        BinomialHeap newHeap;
        Node* child = minNode->child;
        while (child != nullptr)
        {
            Node* next = child->sibling;
            child->parent = nullptr;
            child->sibling = newHeap.head;
            newHeap.head = child;
            child = next;
        }

        int minKey = minNode->key;
        delete minNode;
        merge(newHeap);
        return minKey;

    }

    void updateKey (int prevKey, int newKey)
    {
        if (newKey > prevKey) throw runtime_error("New key can't be greater than existing Key.");

        Node* node = findNode(head, prevKey);

        if (node == nullptr) throw runtime_error("Node does not exist.");
        node->key = newKey;
        Node* current = node;
        Node* parent = current->parent;

        while (parent != nullptr && current->key < parent->key)
        {
            swap(parent->key, current->key);
            current = parent;
            parent = parent->parent;
        }

    }

    void deleteKey (int key)
    {
        updateKey(key, INT32_MIN);
        extractMin();
        
    }

    void print(output& out)
    {
        out.print("Printing Binomial Heap...");
        if (head == nullptr) return;

        Node* currentTree = head;

        while (currentTree != nullptr)
        {
            out.print("Binomial Tree, B" + to_string(currentTree->degree));

            queue<pair<Node*, int>>q;
            map<int, vector<int>> levels;

            q.push({currentTree, 0});

            while (!q.empty())
            {
               pair<Node*, int> p = q.front();
               q.pop();
               levels[p.second].push_back(p.first->key); 
               
               Node* child = p.first->child;

               while (child != nullptr)
               {
                q.push({child,p.second+1});
                child = child->sibling;
               }
            }

            for (auto l: levels)
            {
                string line = "Level " + to_string(l.first) + ":";
                for (int key: l.second)
                {
                    line += " " + to_string(key);
                }
                out.print(line);
            }

            currentTree = currentTree->sibling;
        }
    }





};