#include <windows.h>

#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

#include "cfloat"
using namespace std;

class AntonyDictionary {
   private:
    string words[50];
    string antonyms[50];

   public:
    AntonyDictionary();
    int LoadWords(string);
    int SearchForWord(string);
    string GetAntonym(string);
};

AntonyDictionary::AntonyDictionary() {
    for (int i = 0; i < 50; i++) {
        words[i] = "";
        antonyms[i] = "";
    }
}

int AntonyDictionary::LoadWords(string filename) {
    ifstream infile(filename);
    if (infile.is_open()) {
        string line;
        int index = 0;
        while (getline(infile, line) || index == 49) {
            stringstream ss(line);
            string word;
            string ana;
            getline(ss, word, ',');
            words[index] = word;
            getline(ss, ana);
            antonyms[index] = ana;
            index++;
        }
        return 0;
    } else {
        return -1;
        
    }
}

int AntonyDictionary::SearchForWord(string word) {
    int index = -1;
    for (int i = 0; i < 50; i++) {
        if (words[i] == word) {
            index = i;
        }
    }
    return index;
}

string AntonyDictionary::GetAntonym(string word) {
    int index = -1;
    for (int i = 0; i < 50; i++) {
        if (words[i] == word) {
            index = i;
        }
    }
    if (index == -1) {
        return "";
    } else {
        return antonyms[index];
    }
}