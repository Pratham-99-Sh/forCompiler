#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include<fstream>
using namespace std;

// Mapper function
vector<pair<string, int>> map(const string& line) {
    vector<pair<string, int>> words;
    istringstream iss(line);
    string word;
    while (iss >> word) {

        // remove punctuation
        char ch = word[word.size()-1];
        if(ch == '.' || ch == ',' || ch == '!' || ch == '?')
        {
            word = word.substr(0, word.size()-1);
        }
        transform(word.begin(), word.end(), word.begin(), ::tolower);
        
        words.push_back({word, 1});  
    }
    return words;
}

// Reducer function
unordered_map<string, int> reduce(const vector<pair<string, int>>& wordCounts) {
    unordered_map<string, int> counts;
    for (const auto& wordCount : wordCounts) {
        counts[wordCount.first] += wordCount.second;  
    }
    return counts;
}


int main() {
    string input = "";
    
    ifstream in("file.txt");
    while(!in.eof()) 
    {
        string text; 
        getline(in, text);
        input += text + " ";
    }

    
    vector<pair<string, int>> mappedWords = map(input);
    
    unordered_map<string, int> wordCounts = reduce(mappedWords);

    // Print word counts
    for (const auto& wordCount : wordCounts) {
        cout << wordCount.first << " : " << wordCount.second << endl;
    }

    return 0;
}