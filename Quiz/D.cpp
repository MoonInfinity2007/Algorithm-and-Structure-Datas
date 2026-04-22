#include <iostream>
#include <vector>
#include <string>

int main() {
    std::string s;
    std::vector<int> v = {};
    int l = 0, r = 0;
    while (s != "exit") {
        if (s == "push") {
            int x;
            std::cin >> x;
            ++l;
            if (l > v.size()) v.push_back(x);
            else v[l - 1] = x;
            std::cout << "ok\n";
        } else if (s == "pop") {
            if (l == 0) std::cout << "error\n";
            else {
                std::cout << v[l - 1] << "\n";
                --l;
            }
        } else if (s == "back") {
            if (l == 0) std::cout << "error\n";
            else std::cout << v[l - 1] << "\n";
        } else if (s == "size") std::cout << l - r << "\n";
        else if (s == "clear") {
            v.clear();
            l = 0;
            std::cout << "ok\n";
        }
        std::cin >> s;
    }
    std::cout << "bye";
}