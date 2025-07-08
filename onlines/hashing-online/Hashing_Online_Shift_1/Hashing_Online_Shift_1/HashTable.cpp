#include <bits/stdc++.h>
#include "HashNode.cpp"

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
    int size;
    int current_delete;
    // vector<tree *> chainTable;
    vector<HashNode> openTable;
    int pmax;

public:
    HashTable(int size, int p)
    {
        tableSize = nearestPrime(size);
        stepSize = 1;
        currentValue = 1;
        collisionCount = 0;
        probeCount = 0;
        size = 0;
        current_delete = 0;
        // chainTable.resize(tableSize);
        pmax = p;
        // for (int i = 0; i < tableSize; i++)
        // {
        //     chainTable[i] = new tree();
        // }
        openTable.resize(tableSize);
    }

    ~HashTable() {
        // for (int i = 0; i < tableSize; i++)
        // {
        //     delete chainTable[i];
        // }
    };

    int hash1(int key)
    {

        return key;
    }

    int getTableSize()
    {
        return tableSize;
    }
    void scaleUp()
    {
        vector<HashNode> newtable;
        int nextprime;
        for (int i = tableSize * 2;; i++)
        {
            if (isPrime(i))
            {
                nextprime = i;
                break;
            }
        }
        newtable.resize(nextprime);
        for (auto a : openTable)
        {
            if (a.status == 1)
            {

                int hashValue = hash1(a.key);

                int probes = 0;
                int done = 0;

                while (probes < nextprime)
                {
                    int index = (hashValue + probes * probes) % nextprime;

                    if (newtable[index].status == 2 || newtable[index].status == 0)
                    {
                        newtable[index].status == 1;

                        newtable[index] = HashNode(a.key);

                        done = 1;

                        // cout<<"ALLOCATE "<<key<<" :Inserted at index "<<index<<" (probes: "<<probes<< " )"<<endl;
                        // if(probes>pmax) scaleUp();
                        // return ;
                    }

                    if (openTable[index].key == a.key && openTable[index].status == 1)
                    {
                        done = 1;
                        // return;
                    }
                    if (done == 1)
                        break;
                }
            }
            openTable = newtable;
            tableSize = nextprime;
            current_delete = 0;
        }
    }
    void scaleDown()
    {
        vector<HashNode> newtable;
        int nextprime;
        for (int i = tableSize / 2;; i--)
        {
            if (isPrime(i))
            {
                nextprime = i;
                break;
            }
        }
        newtable.resize(nextprime);
        for (auto a : openTable)
        {
            if (a.status == 1)
            {

                int hashValue = hash1(a.key);

                int probes = 0;
                int done = 0;

                while (probes < nextprime)
                {
                    int index = (hashValue + probes * probes) % nextprime;

                    if (newtable[index].status == 2 || newtable[index].status == 0)
                    {
                        newtable[index].status == 1;

                        newtable[index] = HashNode(a.key);

                        done = 1;

                        // cout<<"ALLOCATE "<<key<<" :Inserted at index "<<index<<" (probes: "<<probes<< " )"<<endl;
                        // if(probes>pmax) scaleUp();
                        // return ;
                    }

                    if (openTable[index].key == a.key && openTable[index].status == 1)
                    {
                        done = 1;
                        // return;
                    }
                    if (done == 1)
                        break;
                }
            }
            openTable = newtable;
            tableSize = nextprime;
            current_delete = 0;
        }
    }

    void allocate(int key)
    {
        int hashValue = hash1(key);

        int probes = 0;

        while (probes < tableSize)
        {
            int index = (hashValue + probes * probes) % tableSize;

            if (openTable[index].status == 2 || openTable[index].status == 0)
            {
                openTable[index].status == 1;
                size++;
                openTable[index] = HashNode(key);

                probes++;

                cout << "ALLOCATE " << key << " :Inserted at index " << index << " (probes: " << probes << " )" << endl;
                if (probes > pmax)
                    scaleUp();
                return;
            }

            if (openTable[index].key == key && openTable[index].status == 1)
            {

                return;
            }
            probes++;
        }

        return;
    }

    // pair<bool, int> searchLinearProbing(string key, int hash)
    // {
    //     int hashValue;
    //     if (hash == 1)
    //         hashValue = hash1(key);
    //     else if (hash == 2)
    //         hashValue = hash2(key);
    //     else
    //         return {false, -1};

    //     int probes = 0;

    //     while (probes < tableSize)
    //     {
    //         int index = (hashValue + probes * stepSize) % tableSize;

    //         if (openTable[index].key == "")
    //         {
    //             probeCount += probes + 1;
    //             return {false, probes + 1};
    //         }

    //         if (openTable[index].key == key && !openTable[index].deleted)
    //         {
    //             probeCount += probes + 1;
    //             return {true, probes + 1};
    //         }

    //         probes++;
    //     }

    //     probeCount += probes;
    //     return {false, probes};
    // }

    void free(int key)
    {
        int hashValue = hash1(key);

        int probes = 0;

        while (probes < tableSize)
        {
            int index = (hashValue + probes * probes) % tableSize;

            if (openTable[index].status == 2 || openTable[index].status == 0)
            {
                cout << "FREE " << key << " : key not found" << endl;
                return;
            }

            if (openTable[index].key == key && openTable[index].status == 1)
            {
                openTable[index].key = -1;
                openTable[index].status = 2;
                cout << "FREE " << key << " : deleted from index: " << index << endl;
                size--;
                current_delete++;
                if (current_delete == 5)
                {
                    current_delete = 0;
                    if (size / tableSize < .2)
                        scaleDown();
                }
                return;
            }

            probes++;
        }

        return;
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
};