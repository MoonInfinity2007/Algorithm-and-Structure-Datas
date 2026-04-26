#include <iostream>
#include <string>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::string s;
    int v[1000000];
    int l = 0;
    while (std::cin >> s && s != "exit") {
        if (s == "push") {
            int x;
            std::cin >> x;
            ++l;
            v[l - 1] = x;
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
        } else if (s == "size") std::cout << l << "\n";
        else if (s == "clear") {
            l = 0;
            std::cout << "ok\n";
        }
    }
    std::cout << "bye";
}