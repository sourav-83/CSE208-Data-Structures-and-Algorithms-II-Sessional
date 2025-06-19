#include <bits/stdc++.h>
#include "BinomialHeap.hpp"


using namespace std;

int main()
{
    ifstream input("input.txt");
    if (!input.is_open())
    {
        cerr << "Error in opening input file" << endl;
        return -1;
    }

    output out("output.txt");
    string s;

    BinomialHeap heap; 

    while (getline(input, s))
    {
        if (s.empty()) continue;

        istringstream iss(s);
        string command;
        iss >> command;

        if (command == "I")
        {
            int key;
            iss >> key;
            heap.insert(key);
        }
        else if (command == "F")
        {
            int ans = heap.findMin();
            out.print("Find Min returned: " + to_string(ans));
            
        }
        else if (command == "E")
        {
            int ans = heap.extractMin();
            out.print("Find Min returned: " + to_string(ans));
        }
        else if (command == "D")
        {
            int oldKey, newKey;
            iss >> oldKey >> newKey;
            heap.updateKey(oldKey, newKey);
            
        }
        else if (command == "R")
        {
            int key;
            iss >> key;
            heap.deleteKey(key);
            
        }
        else if (command == "P")
        {
            heap.print(out); 
        }
        else
        {
            out.print("[Unknown Command]");
        }
    }

    input.close();
    return 0;
}
