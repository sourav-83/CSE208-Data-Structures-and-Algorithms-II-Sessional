#include <bits/stdc++.h>
#include <fstream>
#include <sstream>



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
    
    
    void print(string s)
    {
        cout << s << endl;
        file << s << endl;
    }
};
