#include <cstdint>
#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <vector>

int count = 0;
std::vector<int> res;

struct Node {
    std::map<char, Node> next;
    int is_terminal = -1;
    Node *term_link = nullptr;
    Node *suff_link = nullptr;
} root;

void insert(const std::string &s) {
    Node *v = &root;
    for (auto c : s) {
        v = &v->next[c];
    }
    v->is_terminal = count;
    ++count;
}

void build() {
    std::queue<Node *> q;
    root.suff_link = &root;
    for (auto &[c, to] : root.next) {
        to.suff_link = &root;
        q.push(&to);
    }
    while (!q.empty()) {
        Node *v = q.front();
        q.pop();
        for (auto &[c, to] : v->next) {
            Node *jumper = v->suff_link;
            while (!jumper->next.contains(c) && jumper != &root) {
                jumper = jumper->suff_link;
            }
            if (jumper->next.contains(c)) {
                to.suff_link = &jumper->next[c];
            } else {
                to.suff_link = &root;
            }
            if (to.suff_link->is_terminal != -1) {
                to.term_link = to.suff_link;
            } else {
                to.term_link = to.suff_link->term_link;
            }
            q.push(&to);
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string text;
    std::cin >> text;

    int n = 0;
    std::cin >> n;
    res.assign(n, 0);

    std::vector<std::string> words(n);
    for (auto &w : words) {
        std::cin >> w;
        insert(w);
    }

    build();

    Node *v = &root;
    for (char c : text) {
        while (v != &root && v->next.count(c) == 0) {
            v = v->suff_link;
        }
        if (v->next.contains(c)) {
            v = &v->next[c];
        } else {
            v = &root;
        }
        if (v->is_terminal != -1) {
            res[v->is_terminal] = 1;
        }
        for (Node *t = v->term_link; t != nullptr; t = t->term_link) {
            res[t->is_terminal] = 1;
        }
    }

    for (auto i : res) {
        std::cout << (i ? "Yes" : "No") << '\n';
    }

    return 0;
}
