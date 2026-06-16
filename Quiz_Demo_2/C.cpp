#include <iostream>
#include <cstdint>
#include <map>
#include <string>

class Trie {
    struct Node {
        int64_t count = 0;
        std::map<char, Node> next;
        bool is_terminal = true;
    } root;
public:
    void insert(const std::string& s) {
        Node* v = &root;
        ++v->count;
        for (char ch : s) {
            v = &v->next[ch];
            ++v->count;
        }
        v->is_terminal = true;
    }
    int64_t find(const std::string& s) {
        Node* v = &root;
        for (char ch : s) {
            if (v->next.count(ch) == 0) return 0;
            v = &v->next[ch];
        }
        return v->count;
    }
};

int main() {
    Trie trie;
    int64_t n;
    std::string s;
    std::cin >> n;
    for (int64_t i = 0; i < n; ++i) {
        std::cin >> s;
        trie.insert(s);
    }
    int64_t q;
    std::cin >> q;
    for (int64_t i = 0; i < q; ++i) {
        std::cin >> s;
        std::cout << trie.find(s) << "\n";
    }
}