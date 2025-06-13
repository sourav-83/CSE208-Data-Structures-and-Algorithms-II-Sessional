#include <bits/stdc++.h>
#include "tree.hpp"
#include <fstream>
#include <sstream>
#include "color.hpp"


using namespace std;


class output
{
    ofstream file;

public:
    output(const string &filename)
    {
        file.open(filename);
        if (!file.is_open())
        {
            cerr << "Error in opening output file" << endl;
            exit(-1);
        }
    }
    ~output()
    {
        file.close();
    }
    void print(node *&root)
    {
        if (root)
        {
            if (root->color == RED)
            {

                cout << dye::red(root->id) << dye::red("_") << dye::red(root->name);
            }
            else
                cout << dye::black(root->id) << dye::black("_") << dye::black(root->name);

            file << root->id << "_" << root->name;
        }
        else
            return;
        if (!root->left && !root->right)
            return;
        cout << "(";
        file << "(";
        print(root->left);
        cout << ",";
        file << ",";
        print(root->right);
        cout << ")";
        file << ")";
    }
    void inOrderPrint(node *&root)
    {
        if (root == nullptr)
            return;

        inOrderPrint(root->left);

        if (root->color == RED)
            cout << dye::red(root->id) << " => " << dye::red(root->name) << " (" << root->count << ")\n";
        else
            cout << root->id << " => " << root->name << " (" << root->count << ")\n";

        file << root->id << " => " << root->name << " (" << root->count << ")\n";

        inOrderPrint(root->right);
    }

    void print(string s)
    {
        cout << s << endl;
        file << s << endl;
    }
};
