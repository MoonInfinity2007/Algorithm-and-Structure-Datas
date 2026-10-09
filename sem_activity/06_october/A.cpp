#include <iostream>
#include <cstdint>
#include <vector>
#include <map>
#include <string>

struct Node {
    std::map<char, Node> next;
    int64_t count = 0;
} root;

void insert(const std::string& s) {
    Node* v = &root;
    ++v->count;
    for (const char c : s) {
        v = &v->next[c];
        ++v->count;
    }
}

int64_t find(const std::string& s) {
    Node* v = &root;
    for (const char c : s) {
        if (!v->next.count(c)) return 0;
        v = &v->next[c];
    }
    return v->count;
}

int main() {
    int64_t n = 0, m = 0; 
    std::cin >> n;
    std::string word;
    for (int64_t i = 0; i < n; ++i) {
        std::cin >> word;
        insert(word);
    }
    std::cin >> m;
    while (m--) {
        std::cin >> word;
        std::cout << find(word) << "\n";
    }
}