#include <iostream>
#include <cstdint>
#include <string>
#include <vector>
#include <list>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int64_t base = 263;
    int64_t mod = 1e9 + 7;
    uint64_t m, n;
    std::cin >> m >> n;
    std::vector<std::list<std::string>> table(m);
    auto get_hash = [&](const std::string& s) -> uint64_t {
        int64_t res = 0;
        for (uint64_t i = s.size(); i > 0; --i) res = (res * base + s[i - 1]) % mod;
        return res % m;
    };
    while (n--) {
        std::string command;
        std::cin >> command;
        if (command == "check") {
            uint64_t i;
            std::cin >> i;
            for (auto it = table[i].begin(); it != table[i].end(); ++it) {
                if (it != table[i].begin()) std::cout << ' ';
                std::cout << *it;
            }
            std::cout << '\n';
            continue;
        }
        std::string s;
        std::cin >> s;
        uint64_t index = get_hash(s);
        auto it = table[index].begin();
        while (it != table[index].end() && *it != s) ++it;
        if (command == "add") {
            if (it == table[index].end()) table[index].push_front(s);
        }
        else if (command == "del") {
            if (it != table[index].end()) table[index].erase(it);
        }
        else if (command == "find") {
            if (it != table[index].end()) std::cout << "yes\n";
            else std::cout << "no\n";
        }
    }
}
