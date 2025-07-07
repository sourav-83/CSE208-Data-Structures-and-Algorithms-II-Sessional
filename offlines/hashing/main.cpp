#include <bits/stdc++.h>
#include "PerformanceTester.hpp"

using namespace std;

int main ()
{
    cout << "VaultX HashTable Performance Testing" << endl;
    
    
    int initialSize = 10000;
    
    
    
    HashTable hashTable(initialSize);
    PerformanceTester tester(&hashTable);
    
    
    
    
    tester.runTests(hashTable.getTableSize());
    
    return 0;

}

