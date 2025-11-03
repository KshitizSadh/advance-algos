#include <iostream>
#include <string>
#include <map>
using namespace std;

class TrieNode {
public:
    map<char, TrieNode*> children;
    bool isEndOfSuffix;
    int suffixIndex;
    
    TrieNode() {
        isEndOfSuffix = false;
        suffixIndex = -1;
    }
};

class SuffixTrie {
    TrieNode* root;
    string text;
    
public:
    SuffixTrie(string s) {
        text = s + "$";
        root = new TrieNode();
        buildBruteForceSuffixTrie();
    }
    
    void buildBruteForceSuffixTrie() {
        int n = text.length();
        
        for (int i = 0; i < n; i++) {
            TrieNode* current = root;
            
            for (int j = i; j < n; j++) {
                char ch = text[j];
                
                if (current->children.find(ch) == current->children.end()) {
                    current->children[ch] = new TrieNode();
                }
                
                current = current->children[ch];
            }
            
            current->isEndOfSuffix = true;
            current->suffixIndex = i;
        }
    }
    
    bool search(string pattern) {
        TrieNode* current = root;
        
        for (char ch : pattern) {
            if (current->children.find(ch) == current->children.end())
                return false;
            current = current->children[ch];
        }
        
        return true;
    }
    
    void printSuffixes(TrieNode* node, string prefix) {
        if (node->isEndOfSuffix) {
            cout << "Suffix starting at index " << node->suffixIndex 
                 << ": " << prefix << endl;
        }
        
        for (auto& pair : node->children) {
            printSuffixes(pair.second, prefix + pair.first);
        }
    }
    
    void displayAllSuffixes() {
        cout << "All suffixes in trie:\n";
        printSuffixes(root, "");
    }
};

int main() {
    string text;
    cout << "Enter text: ";
    getline(cin, text);
    
    SuffixTrie trie(text);
    
    cout << "\nBuilding suffix trie...\n";
    trie.displayAllSuffixes();
    
    string pattern;
    cout << "\nEnter pattern to search: ";
    getline(cin, pattern);
    
    if (trie.search(pattern))
        cout << "Pattern '" << pattern << "' found in text" << endl;
    else
        cout << "Pattern '" << pattern << "' not found in text" << endl;
    
    return 0;
}
