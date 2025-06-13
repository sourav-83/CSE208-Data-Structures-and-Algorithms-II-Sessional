#include <bits/stdc++.h>
#include "outputStream.hpp"


using namespace std;


int main()
{
    ifstream input("input.txt");
    if (!input.is_open())
    {
        cerr << "Error in opening input file" << endl;
        exit(-1);
    }

    output out("output.txt");
    string s;
    tree t;
    while (getline(input, s))
    {
        if (s.empty())
            continue;

        istringstream iss(s);
        string command;
        iss >> command;

        if (command == "AI")
        {
            int id, count;
            string nameQuoted;
            iss >> id >> ws;
            getline(iss, nameQuoted, '"');
            getline(iss, nameQuoted, '"');
            iss >> count;
            t.insert(id, nameQuoted, count);
            node *root = t.getRoot();
            out.print(root);
            out.print("");
        }
        else if (command == "BI")
        {
            int id, quantity;
            iss >> id >> quantity;
            t.buyItem(id, quantity);
            node *root = t.getRoot();
            out.print(root);
            out.print("");
        }
        else if (command == "CI")
        {
            int id;
            iss >> id;
            int quantity = t.checkItem(id);
            if (quantity == 0)
            {
                out.print("Not available");
            }
            else
            {
                out.print("Stock left: " + to_string(quantity));
            }
        }
        else if (command == "Clr")
        {
            node *root = t.getRoot();
            if (root == nullptr)
            {
                out.print("unsuccessful");
            }
            else
            {
                t.deleteTree(root);
                t = tree();
                out.print("successful");
            }
        }
        else if (command == "Em")
        {
            if (t.getRoot() == nullptr || t.getSize() == 0)
                out.print("yes");
            else
                out.print("no");
        }
        else if (command == "S")
        {
            out.print(to_string(t.getSize()));
        }
        else if (command == "Itr")
        {
            node *root = t.getRoot();
            out.inOrderPrint(root);
            
        }
        else
        {
            out.print("[Unknown Command]");
        }
    }

    input.close();
    return 0;
}
