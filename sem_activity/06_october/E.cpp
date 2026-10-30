#include <cctype>
#include <iostream>
#include <map>
#include <string>

struct Node {
    std::map<char, Node> next;
    int sub = 0;
    bool terminal = false;
};

Node root;

bool exists(const std::string& s) {
    Node* v = &root;
    for (char c : s) {
        auto it = v->next.find(c);
        if (it == v->next.end()) {
            return false;
        }
        v = &it->second;
    }
    return v->terminal;
}

void insert(const std::string& s) {
    if (exists(s)) {
        return;
    }

    Node* v = &root;
    for (char c : s) {
        v = &v->next[c];
        ++v->sub;
    }
    v->terminal = true;
}

std::string kth(int k) {
    Node* v = &root;
    std::string res;

    while (true) {
        if (v->terminal) {
            if (k == 1) return res;
            --k;
        }
        bool found = false;
        for (auto& [c, to] : v->next) {
            if (k <= to.sub) {
                res.push_back(c);
                v = &to;
                found = true;
                break;
            }
            k -= to.sub;
        }
        if (!found) return "";
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n = 0;
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        std::string cmd;
        std::cin >> cmd;
        bool is_query = true;
        for (char c : cmd) {
            if (!std::isdigit(static_cast<unsigned char>(c))) {
                is_query = false;
                break;
            }
        }
        if (is_query) {
            int k = std::stoi(cmd);
            std::cout << kth(k) << '\n';
        } else insert(cmd);
    }

    return 0;
}