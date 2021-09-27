#include <memory>
#include <vector>
#include <iostream>

using namespace std;

class Trie {
private:
    struct Node {
        vector<shared_ptr<Node>> childs;
        char c;
        bool is_end;
    };
    shared_ptr<Node> tree;
public:
    Trie() {
        tree = make_shared<Node>();
    }
    
    void insert(string word) {
        auto p = tree;
        for(int i=0;i<word.size();i++) {
            shared_ptr<Node> match = nullptr;
            for(auto& ch : p->childs) {
                if(ch->c == word[i]) {
                    match = ch;
                    break;
                }
            }
            if(match == nullptr) {
                match = make_shared<Node>();
                match->c = word[i];
                p->childs.push_back(match);
            }
            p = match;
        }
        p->is_end = true;
    }
    
    bool search(string word) {
        auto p = tree;
        for(int i=0;i<word.size();i++) {
            shared_ptr<Node> match = nullptr;
            for(auto& ch : p->childs) {
                if(ch->c == word[i]) {
                    match = ch;
                    break;
                }
            }
            if(match == nullptr) return false;
            p = match;
        }
        if(p->is_end) return true;
        return false;
    }
    
    bool startsWith(string prefix) {
        auto p = tree;
        for(int i=0;i<prefix.size();i++) {
            shared_ptr<Node> match = nullptr;
            for(auto& ch : p->childs) {
                if(ch->c == prefix[i]) {
                    match = ch;
                    break;
                }
            }
            if(match == nullptr) return false;
            p = match;
        }
        return true;
    }
};


int main() {
    Trie trie;
    trie.insert("apple");
    cout<<trie.search("apple")<<endl;   // True
    cout<<trie.search("app")<<endl;     // False
    cout<<trie.startsWith("app")<<endl; // True
    trie.insert("app");
    cout<<trie.search("app")<<endl;     // True
}
