#include <iostream>
#include <cstdint>
#include <vector>
#include <map>
#include <string>

struct Node {
    std::map<char, Node> next;
    int64_t count = 0;
    int64_t size = 0;
} root;

void insert(const std::string& s) {
    Node* v = &root;
    ++v->count;
    for (const char c : s) {
        if (!v->next.count(c)) {
            v->next[c] = Node{};
            ++root.size;
        };
        v = &v->next[c];
        ++v->count;
    }
}

int64_t coun() {
    Node* v = &root;
    return v->size + 1;
}

int main() {
    int64_t n = 0, m = 0; 
    std::cin >> n;
    std::vector<std::string> word(n);
    for (int64_t i = 0; i < n; ++i) {
        std::cin >> word[i];
        insert(word[i]);
    }
    std::cout << coun() << '\n';

}