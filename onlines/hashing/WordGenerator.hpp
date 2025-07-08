#include <bits/stdc++.h>
#include <random>
#include <chrono>
#include <iomanip>
#include <cmath>
#include <algorithm>


using namespace std;


class WordGenerator {
private:
    mt19937 rng;
    uniform_int_distribution<int> lengthDist;
    uniform_int_distribution<int> charDist;
    
public:
    WordGenerator() : rng(chrono::steady_clock::now().time_since_epoch().count()),
                      lengthDist(5, 10), charDist(0, 25) {}
    
    string generateWord() {
        int length = lengthDist(rng);
        string word;
        for (int i = 0; i < length; i++) {
            word += char('a' + charDist(rng));
        }
        return word;
    }
    
    vector<string> generateWords(int count) {
        vector<string> words;
        for (int i = 0; i < count; i++) {
            words.push_back(generateWord());
        }
        return words;
    }
};