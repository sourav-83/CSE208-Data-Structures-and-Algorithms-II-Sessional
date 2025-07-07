#include <bits/stdc++.h>
#include "HashTable.hpp"
#include "WordGenerator.hpp"

using namespace std;

class PerformanceTester {
private:
    HashTable* hashTable;
    WordGenerator wordGen;

public:
    PerformanceTester(HashTable* ht) : hashTable(ht) {}

    struct TestResult {
        int collisions;
        double avgSearchTimeBefore;
        double avgProbesBefore;
        double avgSearchTimeAfter;
        double avgProbesAfter;
    };

    void runTests(int tableSize) {
       
        displayHashUniqueness(tableSize);

        for (double loadFactor = 0.4; loadFactor <= 0.9; loadFactor += 0.1) {
            cout << "\nFor Load Factor: " << fixed << setprecision(1) << loadFactor << "\n";

            map<string, map<int, TestResult>> results;
            testLoadFactor(loadFactor, results);
            displayResults(loadFactor, results);
        }
    }

private:
    void displayHashUniqueness(int tableSize) {
        vector<string> testWords = wordGen.generateWords(tableSize);
        set<int> uniqueHash1, uniqueHash2;

        for (string& word : testWords) {
            uniqueHash1.insert(hashTable->hash1(word));
            uniqueHash2.insert(hashTable->hash2(word));
        }

        double percentUniqueH1 = 100.0 * uniqueHash1.size() / testWords.size();
        double percentUniqueH2 = 100.0 * uniqueHash2.size() / testWords.size();

        cout << fixed << setprecision(2);
        cout << "\nHash Uniqueness Check (out of " << testWords.size() << " generated words):\n";
        cout << "- Hash1 Unique Hashes: " << uniqueHash1.size() << " (" << percentUniqueH1 << "%)\n";
        cout << "- Hash2 Unique Hashes: " << uniqueHash2.size() << " (" << percentUniqueH2 << "%)\n";
    }

    void testLoadFactor(double loadFactor, map<string, map<int, TestResult>>& results) {
        int numElements = (int)(loadFactor * hashTable->getTableSize());

        vector<string> words = wordGen.generateWords(numElements * 2);
        vector<string> methods = {"Separate Chaining", "Linear Probing", "Double Hashing"};

        for (const string& method : methods) {
            testMethod(method, words, numElements, results);
        }
    }

    void testMethod(const string& methodName, const vector<string>& words,
                    int numElements, map<string, map<int, TestResult>>& results) {
        for (int hashFunc = 1; hashFunc <= 2; hashFunc++) {
            hashTable->clearTable();
            hashTable->resetCollisionCount();
            hashTable->resetProbeCount();

            vector<string> insertedWords;

            for (int i = 0; i < (int)words.size() && (int)insertedWords.size() < numElements; ++i) {
                bool inserted = false;
                if (methodName == "Separate Chaining") {
                    auto result = hashTable->insertChaining(words[i], hashFunc);
                    inserted = result.first;
                } else if (methodName == "Linear Probing") {
                    auto result = hashTable->insertLinearProbing(words[i], hashFunc);
                    inserted = result.first;
                } else if (methodName == "Double Hashing") {
                    auto result = hashTable->insertDoubleHashing(words[i]);
                    inserted = result.first;
                }
                if (inserted) insertedWords.push_back(words[i]);
            }

            int collisions = hashTable->getCollisionCount();

            hashTable->resetProbeCount();
            vector<string> searchSetBefore = getRandomSample(insertedWords, 0.1);
            double searchTimeBefore = performSearchTest(methodName, searchSetBefore, hashFunc);
            double probesBefore = (methodName == "Separate Chaining") ? 0.0 : 
                                hashTable->getProbeCount() / (double)max(1, (int)searchSetBefore.size());

            vector<string> deletedWords = getRandomSample(insertedWords, 0.1);
            for (const string& word : deletedWords) {
                if (methodName == "Separate Chaining") {
                    hashTable->deleteChaining(word, hashFunc);
                } else if (methodName == "Linear Probing") {
                    hashTable->deleteLinearProbing(word, hashFunc);
                } else if (methodName == "Double Hashing") {
                    hashTable->deleteDoubleHashing(word);
                }
            }

            vector<string> searchSetAfter = createMixedSearchSet(insertedWords, deletedWords, searchSetBefore.size());

            hashTable->resetProbeCount();
            double searchTimeAfter = performSearchTest(methodName, searchSetAfter, hashFunc);
            double probesAfter = (methodName == "Separate Chaining") ? 0.0 : 
                               hashTable->getProbeCount() / (double)max(1, (int)searchSetAfter.size());

            results[methodName][hashFunc] = {
                collisions, searchTimeBefore, probesBefore, searchTimeAfter, probesAfter
            };
        }
    }

    vector<string> getRandomSample(const vector<string>& source, double ratio) {
        int sampleSize = max(1, (int)(source.size() * ratio));
        vector<string> sample;

        vector<int> indices(source.size());
        iota(indices.begin(), indices.end(), 0);
        random_shuffle(indices.begin(), indices.end());

        for (int i = 0; i < sampleSize && i < (int)indices.size(); ++i) {
            sample.push_back(source[indices[i]]);
        }

        return sample;
    }

    vector<string> createMixedSearchSet(const vector<string>& allWords, 
                                       const vector<string>& deletedWords, 
                                       int targetSize) {
        vector<string> mixedSet;

        int halfSize = targetSize / 2;
        for (int i = 0; i < halfSize && i < (int)deletedWords.size(); ++i) {
            mixedSet.push_back(deletedWords[i]);
        }

        set<string> deletedSet(deletedWords.begin(), deletedWords.end());
        int added = 0;
        for (const string& word : allWords) {
            if (deletedSet.find(word) == deletedSet.end() && added < halfSize) {
                mixedSet.push_back(word);
                added++;
            }
        }

        return mixedSet;
    }

    double performSearchTest(const string& methodName, const vector<string>& searchWords,
                             int hashFunc) {
        if (searchWords.empty()) return 0.0;

        auto start = chrono::high_resolution_clock::now();

        for (const string& searchKey : searchWords) {
            if (methodName == "Separate Chaining") {
                hashTable->searchChaining(searchKey, hashFunc);
            } else if (methodName == "Linear Probing") {
                hashTable->searchLinearProbing(searchKey, hashFunc);
            } else if (methodName == "Double Hashing") {
                hashTable->searchDoubleHashing(searchKey);
            }
        }

        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start);
        double avgTimeNano = duration.count() / (double)searchWords.size();

        return avgTimeNano;
    }

    void displayResults(double loadFactor, const map<string, map<int, TestResult>>& results) {
        cout << "\n" << string(140, '=') << "\n";
        cout << left
             << setw(25) << "Method"
             << setw(18) << "Hash1 Function"
             << setw(25) << ""
             << setw(18) << "Hash2 Function"
             << setw(25) << ""
             << "\n";

        cout << left
             << setw(25) << ""
             << setw(8) << "Coll"
             << setw(12) << "Before Del"
             << setw(12) << "After Del"
             << setw(8) << "Coll"
             << setw(12) << "Before Del"
             << setw(12) << "After Del"
             << "\n";

        cout << left
             << setw(25) << ""
             << setw(8) << ""
             << setw(6) << "Time"
             << setw(6) << "Probe"
             << setw(6) << "Time"
             << setw(6) << "Probe"
             << setw(8) << ""
             << setw(6) << "Time"
             << setw(6) << "Probe"
             << setw(6) << "Time"
             << setw(6) << "Probe"
             << "\n";

        cout << string(140, '-') << "\n";

        for (const auto& method : results) {
            cout << left << setw(25) << method.first;

            for (int hashFunc = 1; hashFunc <= 2; ++hashFunc) {
                if (method.second.find(hashFunc) != method.second.end()) {
                    const auto& result = method.second.at(hashFunc);
                    cout << setw(8) << result.collisions;

                    if (method.first == "Separate Chaining") {
                        cout << setw(6) << fixed << setprecision(1) << result.avgSearchTimeBefore
                             << setw(6) << "N/A"
                             << setw(6) << fixed << setprecision(1) << result.avgSearchTimeAfter
                             << setw(6) << "N/A";
                    } else {
                        cout << setw(6) << fixed << setprecision(1) << result.avgSearchTimeBefore
                             << setw(6) << fixed << setprecision(1) << result.avgProbesBefore
                             << setw(6) << fixed << setprecision(1) << result.avgSearchTimeAfter
                             << setw(6) << fixed << setprecision(1) << result.avgProbesAfter;
                    }
                } else {
                    cout << setw(8) << "N/A" << setw(6) << "N/A" << setw(6) << "N/A"
                         << setw(6) << "N/A" << setw(6) << "N/A";
                }
            }
            cout << "\n";
        }
        cout << string(140, '=') << "\n";
    }
};
