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

std::string find(const std::string& s) {
    Node* v = &root;
    std::string pref;
    for (const char c : s) {
        if (!v->next.count(c)) return 0;
        v = &v->next[c];
        pref.push_back(c);
        if (v->count == 1) return pref;
    }
    return "-";
}

int main() {
    int64_t n = 0, m = 0; 
    std::cin >> n;
    std::vector<std::string> word(n);
    for (int64_t i = 0; i < n; ++i) {
        std::cin >> word[i];
        insert(word[i]);
    }
    for (int64_t i = 0; i < n; ++i) {
        std::cout << find(word[i]) << '\n';
    }

}