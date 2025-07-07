#include <bits/stdc++.h>
#include "HashNode.hpp"
#include "tree.hpp"

using namespace std;

bool isPrime(int n)
{
    if (n <= 1)
        return false;
    for (int i = 2; i * i <= n; i++)
    {
        if (n % i == 0)
            return false;
    }
    return true;
}

int nearestPrime(int n)
{
    if (n <= 1)
        return 2;
    while (!isPrime(n))
    {
        n++;
    }
    return n;
}

class HashTable
{
private:
    int tableSize;
    int stepSize;
    int currentValue;
    int collisionCount;
    int probeCount;
    vector<tree *> chainTable;
    vector<HashNode> openTable;

public:
    HashTable(int size)
    {
        tableSize = nearestPrime(size);
        stepSize = 5;
        currentValue = 1;
        collisionCount = 0;
        probeCount = 0;
        chainTable.resize(tableSize);
        for (int i = 0; i < tableSize; i++)
        {
            chainTable[i] = new tree();
        }
        openTable.resize(tableSize);
    }

    ~HashTable()
    {
        for (int i = 0; i < tableSize; i++)
        {
            delete chainTable[i];
        }
    };

    int hash1(string &key)
    {
        unsigned long hashvalue = 0;
        const int base = 31;
        for (char c : key)
        {
            hashvalue = hashvalue * base + c;
        }
        return hashvalue % tableSize;
    }

    int hash2(string &key)
    {
        unsigned long hash = 2166136261u; // FNV offset basis
        for (char c : key)
        {
            hash ^= c;
            hash *= 16777619u; // FNV prime
        }
        return hash % tableSize;
    }

    int getTableSize()
    {
        return tableSize;
    }

    pair<bool, int> insertChaining(string key, int hash)
    {
        int hashValue;

        if (hash == 1)
            hashValue = hash1(key);
        else if (hash == 2)
            hashValue = hash2(key);
        else
            return {false, -1};

        if (chainTable[hashValue]->search(key))
        {
            return {false, -1};
        }

        if (chainTable[hashValue]->getSize() != 0)
        {
            collisionCount++;
        }

        chainTable[hashValue]->insert(key, currentValue);
        return {true, currentValue++};
    }

    bool searchChaining(string key, int hash)
    {
        int hashValue;
        if (hash == 1)
        {
            hashValue = hash1(key);
        }
        else if (hash == 2)
        {
            hashValue = hash2(key);
        }
        else
        {
            return false;
        }

        return chainTable[hashValue]->search(key);
    }

    bool deleteChaining(string key, int hash)
    {
        int hashValue;
        if (hash == 1)
        {
            hashValue = hash1(key);
        }
        else if (hash == 2)
        {
            hashValue = hash2(key);
        }
        else
        {
            return false;
        }
        return chainTable[hashValue]->deleteNode(key);
    }

    pair<bool, int> insertLinearProbing(string key, int hash)
    {
        int hashValue;
        if (hash == 1)
            hashValue = hash1(key);
        else if (hash == 2)
            hashValue = hash2(key);
        else
            return {false, -1};

        int probes = 0;

        while (probes < tableSize)
        {
            int index = (hashValue + probes * stepSize) % tableSize;

            if (openTable[index].key == "" || openTable[index].deleted)
            {
                collisionCount += probes;
                openTable[index] = HashNode(key, currentValue);
                return {true, currentValue++};
            }

            if (openTable[index].key == key && !openTable[index].deleted)
            {
                collisionCount += probes;
                return {false, -1}; 
            }
            probes++;
        }

        collisionCount += probes;
        return {false, -1}; 
    }

    pair<bool, int> searchLinearProbing(string key, int hash)
    {
        int hashValue;
        if (hash == 1)
            hashValue = hash1(key);
        else if (hash == 2)
            hashValue = hash2(key);
        else
            return {false, -1};

        int probes = 0;

        while (probes < tableSize)
        {
            int index = (hashValue + probes * stepSize) % tableSize;

            if (openTable[index].key == "")
            {
                probeCount += probes + 1;
                return {false, probes + 1};
            }

            if (openTable[index].key == key && !openTable[index].deleted)
            {
                probeCount += probes + 1;
                return {true, probes + 1};
            }

            probes++;
        }

        probeCount += probes;
        return {false, probes};
    }

    pair<bool, int> deleteLinearProbing(string key, int hash)
    {
        int hashValue;
        if (hash == 1)
            hashValue = hash1(key);
        else if (hash == 2)
            hashValue = hash2(key);
        else
            return {false, -1};
        int probes = 0;

        while (probes < tableSize)
        {
            int index = (hashValue + probes * stepSize) % tableSize;

            if (openTable[index].key == "")
            {
                return {false, probes + 1};
            }

            if (openTable[index].key == key && !openTable[index].deleted)
            {
                openTable[index].deleted = true;
                return {true, probes + 1};
            }

            probes++;
        }

        return {false, probes};
    }

    pair<bool, int> insertDoubleHashing(string key)
    {
        int hash1Value = hash1(key);
        int hash2Value = hash2(key);
        
        
        if (hash2Value == 0)
            hash2Value = 1;
        
        if (hash2Value % 2 == 0)
            hash2Value += 1;

        int probes = 0;

        while (probes < tableSize)
        {
            int index = (hash1Value + probes * hash2Value) % tableSize;

            if (openTable[index].key == "" || openTable[index].deleted)
            {
                collisionCount += probes;
                openTable[index] = HashNode(key, currentValue);
                return {true, currentValue++};
            }

            if (openTable[index].key == key && !openTable[index].deleted)
            {   
                collisionCount += probes;
                return {false, -1}; 
            }

            probes++;
        }
        
        collisionCount += probes;
        return {false, -1}; 
    }

    pair<bool, int> searchDoubleHashing(string key)
    {
        int hash1Value = hash1(key);
        int hash2Value = hash2(key);
        
        if (hash2Value == 0)
            hash2Value = 1;
        if (hash2Value % 2 == 0)
            hash2Value += 1;

        int probes = 0;

        while (probes < tableSize)
        {
            int index = (hash1Value + probes * hash2Value) % tableSize;

            if (openTable[index].key == "")
            {
                probeCount += probes + 1;
                return {false, probes + 1};
            }

            if (openTable[index].key == key && !openTable[index].deleted)
            {
                probeCount += probes + 1;
                return {true, probes + 1};
            }

            probes++;
        }

        probeCount += probes;
        return {false, probes};
    }

    pair<bool, int> deleteDoubleHashing(string key)
    {
        int hash1Value = hash1(key);
        int hash2Value = hash2(key);
        
        if (hash2Value == 0)
            hash2Value = 1;
        if (hash2Value % 2 == 0)
            hash2Value += 1;

        int probes = 0;

        while (probes < tableSize)
        {
            int index = (hash1Value + probes * hash2Value) % tableSize;

            if (openTable[index].key == "")
            {
                return {false, probes + 1};
            }

            if (openTable[index].key == key && !openTable[index].deleted)
            {
                openTable[index].deleted = true;
                return {true, probes + 1};
            }

            probes++;
        }

        return {false, probes};
    }

    void resetCollisionCount()
    {
        collisionCount = 0;
    }

    void resetProbeCount()
    {
        probeCount = 0;
    }

    int getCollisionCount()
    {
        return collisionCount;
    }

    int getProbeCount() const
    {
        return probeCount;
    }

    void clearTable()
    {
        for (int i = 0; i < tableSize; i++)
        {
            delete chainTable[i];
            chainTable[i] = new tree();
        }

        for (int i = 0; i < tableSize; i++)
        {
            openTable[i] = HashNode();
        }

        currentValue = 1;
        collisionCount = 0;
        probeCount = 0;
    }
};