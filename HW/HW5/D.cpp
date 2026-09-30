#include <iostream>
#include <string>
#include <unordered_set>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::unordered_set<std::string> table;
    char command;
    while (std::cin >> command && command != '#') {
        std::string s;
        std::cin >> s;
        if (command == '+') table.insert(s);
        else if (command == '-') table.erase(s);
        else if (command == '?') {
            if (table.find(s) != table.end()) std::cout << "YES\n";
            else std::cout << "NO\n";
        }
    }
}
