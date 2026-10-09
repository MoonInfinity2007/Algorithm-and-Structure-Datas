#include <iostream>
#include <cstdint>
#include <vector>
#include <map>
#include <string>

int64_t count;

struct Node {
    std::map<char, Node> next;
    int64_t is_terminal = -1;
} root;

void insert(const std::string& s) {
    Node* v = &root;
    for (const char c : s) v = &v->next[c];
    v->is_terminal = count;
    ++count;
}

// std::string find(const std::string& s) {
//     Node* v = &root;
//     std::string pref;
//     for (const char c : s) {
//         if (!v->next.num(c)) return 0;
//         v = &v->next[c];
//         pref.push_back(c);
//         if (v->num == 1) return pref;
//     }
//     return "-";
// }

void build() {}

int main() {
    std::string text;
    std::cin >> text;
    int64_t n = 0;
    std::cin >> n;
    for (int64_t i = 0; i < n; ++i) {
        std::string word;
        std::cin >> word;
        insert(word);
    }
    build();
    //auto res = find(text);
    std::vector<int64_t> mask(n);
    for (int64_t i = 0; i < text.size(); ++i) {
        Node* v = &root;
        for (int64_t j = i; j < text.size(); ++j) {
            char c = text[j];
            if (!v->next.count(c)) break;
            v = &v->next[c];
            if (v->is_terminal != -1) mask[v->is_terminal] = 1;
        }
    }
    for (const int64_t i : mask) {
        std::cout << (i ? "Yes" : "No") << "\n";
    }
}